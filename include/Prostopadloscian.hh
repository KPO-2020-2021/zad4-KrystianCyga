#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include "vector.hh"
#include <iostream>
#include <cstdlib>
#include "matrix.hh"
#include <stdexcept>
#include <string>
#include <fstream>
#include <iomanip>

/*!
 * \file
 * \brief Definicja Szablonu Prostopadloscianu.
 *  Jest on postaci 8 wektorow.
 */
template <typename T>
class Prostopadloscian
{

  Vector<T, 3> wektor[8];

public:
  Prostopadloscian();
  void boki();
  Prostopadloscian obrot(const double kat, const int ilosc, const int os);
  Vector<double, 3> operator[](const int punkt);
  bool zapis(const std::string &nazwa) const;
  bool owektor(Vector<double, 3> &wek);
  bool wczytaj(const std::string &nazwa);

  friend std::ostream &operator<<(std::ostream &out, Prostopadloscian<double> const &prost);
  friend std::ofstream &operator<<(std::ofstream &of, Prostopadloscian<double> const &prost);
};

/*!
 * \brief Przeciazenie operatora <<
 *                                                                  
 *     \param[in] out strumien wyjsciowy                                                              
 *     \param[in] prost prostopadloscian                                                               
 *     \return strumien  wyjsciowy                                                               
 */
std::ostream &operator<<(std::ostream &out, Prostopadloscian<double> const &prost)
{
    for (int i = 0; i < 8; i++)
    {
        out << prost.wektor[i] << std::endl;
    }
    out << prost.wektor[0];
    
    return out;
}

/*!
 * \brief Przeciazenie operatora << do zapisu do pliku
 *                                                                  
 *     \param[in] out strumien plikowy                                                              
 *     \param[in] prost prostopadloscian                                                               
 *     \return strumien  plikowy                                                              
 */
std::ofstream &operator<<(std::ofstream &of, Prostopadloscian<double> const &prost)
{
    of << std::setprecision(10) << std::fixed;
    for (int i = 0; i < 8; i++)
    {
        of << prost.wektor[i] << std::endl;
    }
    return of;
}

/*!
 * \brief Konstruktor klasy Prostopadloscian
 */
template <>
Prostopadloscian<double>::Prostopadloscian()
{
  int m = 0;
  for (double i = 0; i < 4; ++i)
  {
    for (double j = 0; j < 4; ++j)
    {
      for (double k = 0; k < 4; ++k)
      {
        double tab[3] = {i, j,k};
        this->wektor[m].zapeln(tab);
        m++;
      }
    }
  }
}

/*!
 * \brief Metoda obrotu prostopadloscianu
 *                                                                  
 *     \param[in] kat kat obrotu                                                              
 *     \param[in] ilosc ilosc operacji
 *     \param[in] os os obrotu                                                         
 *     \return Obrocony prostopadloscian                                                              
 */
template <>
Prostopadloscian<double> Prostopadloscian<double>::obrot(const double kat, const int ilosc, const int os)
{
  Matrix<3> Mrotacji;

  Mrotacji.Mobrot3D_tworzenie(kat, os);

  for (int j = 0; j < ilosc; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      this->wektor[i] = Mrotacji * this->wektor[i];
    }
  }

  return *this;
}
/*!
 * \brief Metoda obrotu prostopadloscianu
 *                                                                  
 *     \param[in] punkt numer punktu                                                                                                                  
 *     \return Dany punkt prostopadloscianu                                                              
 */
template <>
Vector<double, 3> Prostopadloscian<double>::operator[](const int punkt)
{
  return wektor[punkt];
}
/*!
 * \brief Metoda obliczajaca i porownujaca boki prostopadloscianu.
 * Wyswietla ona te dlugosci i okresla czy sa rowne.
 *      \param[in] this Prostopadloscian 
 */
template <>
void Prostopadloscian<double>::boki()
{
  double A0, A1, A2, A3, B0, B1, B2, B3, C0, C1, C2, C3;

  A0 = wektor[0].dlugosc(wektor[1]);
  A1 = wektor[2].dlugosc(wektor[3]);
  A2 = wektor[4].dlugosc(wektor[5]);
  A3 = wektor[6].dlugosc(wektor[7]);
  B0 = wektor[1].dlugosc(wektor[2]);
  B1 = wektor[0].dlugosc(wektor[3]);
  B2 = wektor[5].dlugosc(wektor[6]);
  B3 = wektor[4].dlugosc(wektor[7]);
  C0 = wektor[0].dlugosc(wektor[4]);
  C1 = wektor[1].dlugosc(wektor[5]);
  C2 = wektor[2].dlugosc(wektor[6]);
  C3 = wektor[3].dlugosc(wektor[7]);

  std::cout.precision(15);

  std::string dlugosc1, dlugosc2, dlugosc3;

  if (A0 > B0 && A0 > C0)
  {
    dlugosc1 = "Dluzsze";
    if (B0 > C0)
    {
      dlugosc2 = "Poprzeczne";
      dlugosc3 = "Krotsze";
    }
    else
    {
      dlugosc3 = "Poprzeczne";
      dlugosc2 = "Krotsze";
    }
  }
  if (B0 > A0 && B0 > C0)
  {
    dlugosc2 = "Dluzsze";
    if (A0 > C0)
    {
      dlugosc1 = "Poprzeczne";
      dlugosc3 = "Krotsze";
    }
    else
    {
      dlugosc3 = "Poprzeczne";
      dlugosc1 = "Krotsze";
    }
  }
  if (C0 > A0 && C0 > C0)
  {
    dlugosc3 = "Dluzsze";
    if (A0 > B0)
    {
      dlugosc1 = "Poprzeczne";
      dlugosc2 = "Krotsze";
    }
    else
    {
      dlugosc2 = "Poprzeczne";
      dlugosc1 = "Krotsze";
    }
  }
  if ((abs(A0 - A1) < epsilon) && (abs(A0 - A2) < epsilon) && (abs(A0 - A3) < epsilon))
  {
    std::cout << "  " << dlugosc1 << " boki sa sobie rowne.\n";
    std::cout << "   Dlugosc pierwszego boku: " << A0 << "\n";
    std::cout << "   Dlugosc drugiego boku: " << A1 << "\n";
    std::cout << "   Dlugosc trzeciego boku: " << A2 << "\n";
    std::cout << "   Dlugosc czwartego boku: " << A3 << "\n";
  }
  if ((abs(B0 - B1) < epsilon) && (abs(B0 - B2) < epsilon) && (abs(B0 - B3) < epsilon))
  {
    std::cout << "  " << dlugosc2 << " boki sB sobie rowne.\n";
    std::cout << "   Dlugosc pierwszego boku: " << B0 << "\n";
    std::cout << "   Dlugosc drugiego boku: " << B1 << "\n";
    std::cout << "   Dlugosc trzeciego boku: " << B2 << "\n";
    std::cout << "   Dlugosc czwartego boku: " << B3 << "\n";
  }
  if ((abs(C0 - C1) < epsilon) && (abs(C0 - C2) < epsilon) && (abs(C0 - C3) < epsilon))
  {
    std::cout << "  " << dlugosc3 << " boki sa sobie rowne.\n";
    std::cout << "   Dlugosc pierwszego boku: " << C0 << "\n";
    std::cout << "   Dlugosc drugiego boku: " << C1 << "\n";
    std::cout << "   Dlugosc trzeciego boku: " << C2 << "\n";
    std::cout << "   Dlugosc czwartego boku: " << C3 << "\n";
  }
}
/*!
 * \brief Metoda zapisu Prostopadlosscianu do pliku
 *                                                                  
 *     \param[in] nazwa nazwa/sciezka do pliku
*      \param[in] this Prostopadloscian                                                                                                                   
 *     \return poprawnosc operacji                                                              
 */
template<>
bool Prostopadloscian<double>::zapis(const std::string &nazwa) const
{
    std::ofstream plik;

    plik.open(nazwa, std::ofstream::out);
    if (plik.is_open() == false)
    {
        return false;
    }

    plik << *this;
    plik << this->wektor[0];
    if (plik.fail())
    {
        plik.close();
        return false;
    }
    plik.close();
    return true;
}
/*!
 * \brief Metoda wczytania Prostopadlosscianu z pliku
 *                                                                  
 *     \param[in] nazwa nazwa/sciezka do pliku   
 *     \param[in] this Prostopadloscian                                                                                                                
 *     \return poprawnosc operacji                                                              
 */
template<>
bool Prostopadloscian<double>::wczytaj(const std::string &nazwa)
{
    std::fstream plik;

    plik.open(nazwa);
    if (plik.is_open() == false)
    {
        return false;
    }

    for (int i = 0; i < 8; i++)
    {
        plik >> wektor[i];
        if (plik.fail())
        {
            plik.close();
            return false;
        }
    }
    plik.close();
    return true;
}

/*!
 * \brief Metoda przesuniecia Prostopadloscianu 
 *                                                                  
 *     \param[in] wek wektor przesuniecia 
 *     \param[in] this Prostopadloscian                                                                                                                 
 *     \return poprawnosc operacji                                                              
 */
template<>
bool Prostopadloscian<double>::owektor(Vector<double,3> &wek)
{
    if (wek.modul() == 0) return false;
    for (int i = 0; i < 8; i++)
    {
        wektor[i] = wektor[i] + wek;
    }
    return true;
}


#endif
