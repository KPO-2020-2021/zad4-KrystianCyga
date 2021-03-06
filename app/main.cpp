#include <iostream>
#include <iomanip>
#include <fstream>
#include "vector.hh"
#include "matrix.hh"
#include "Prostopadloscian.hh"
#include "lacze_do_gnuplota.hh"
#include <string>
#include <unistd.h>
#include <stdlib.h>


Vector<double, 3> VecPrzesu;
Matrix<3> MROT;
Prostopadloscian<double> cuboid;
PzG::LaczeDoGNUPlota Lacze;

void menu();

int main()
{
       if (!cuboid.wczytaj("../datasets/orginalny.dat"))
       {
              std::cerr << "Nie udalo sie wczytac prostopadloscianu!!!\n";
       }

       cuboid.boki();
       cuboid.zapis("../datasets/anim.dat");

       Lacze.DodajNazwePliku("../datasets/anim.dat", PzG::RR_Ciagly, 2);
       Lacze.ZmienTrybRys(PzG::TR_3D);

       Lacze.UstawZakresY(-155, 155);
       Lacze.UstawZakresX(-155, 155);
       Lacze.UstawZakresZ(-155, 155);

       Lacze.Rysuj();

       std::cout << "Naciśnij ENTER, aby kontynuowac" << std::endl;
       std::cin.ignore(10000, '\n');

       menu();
}

void menu()
{
       char wyb;
       std::cout << "\n"
                 << "************************MENU************************\n";
       std::cout << "  o-obrot bryly o zadany kat wzgledem danej osi\n";
       std::cout << "  p-przesuniecie o dany wektor\n";
       std::cout << "  w-wyswietlenie wspolrzednych wierzcholkow\n";
       std::cout << "  m-powrot do menu\n";
       std::cout << "  k-koniec dzialania programu\n";
       std::cout << "  r-Rysuj prostokat w Gnuplocie\n";
       std::cout << "  t-wyswietlenie macierzy rotacji\n";
       std::cout << "  Twoj wybor -> :";
       std::cin >> wyb;
       std::cout << "\n";

       switch (wyb)
       {

       case 'o':
              char os;
              double kat, ilosc;
              std::cout << "Podaj kat obrotu: ";
              std::cin >> kat;
              std::cout << "Podaj ilosc operacji: ";
              std::cin >> ilosc;
              std::cout << "Podaj os operacji: ";
              std::cin >> os;
              MROT.Mobrot3D_tworzenie(kat, os);
              

              if (ilosc > 1 && ilosc <= 720)
              {      
                     Lacze.Rysuj();
                     usleep(2000000);
                     for (int i = 0; i < ilosc; i++)
                     {
                            cuboid.obrot(kat, 1, os);
                            cuboid.zapis("../datasets/anim.dat");
                            Lacze.Rysuj();
                            int czas = 10000000 / ilosc;
                            usleep(czas);
                     }
              }
              else
              {
                     cuboid.obrot(kat, ilosc, os);
                     cuboid.zapis("../datasets/anim.dat");
                     Lacze.Rysuj();
              }

              break;

       case 'p':

              std::cout << "Podaj wektor przesuniecia (x) (y) (z): ";
              std::cin >> VecPrzesu;
              cuboid.owektor(VecPrzesu);
              std::cout << cuboid;
              break;

       case 'w':
              std::cout << cuboid;
              break;

       case 'r':
              cuboid.boki();
              cuboid.zapis("../datasets/anim.dat");
              Lacze.Rysuj();
              break;

       case 't':

              std::cout << MROT;

              break;

       case 'm':

              return menu();

              break;

       case 'k':
              std::cout << "Koniec dzialania programu.\n ";
              return;

              break;

       default:
              std::cout << "Zly wybor !!! \n";
              std::cout << "Mozliwe to o,r,p,w,m,k,t\n";
              break;
       }
       return menu();
}
