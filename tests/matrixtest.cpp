#include "../tests/doctest/doctest.h"
#include "matrix.hh"
#include "vector.hh"

TEST_CASE("Operator porownania i konstruktor")
{
    double tab[2][2]={0,0,0,0};
    Matrix<2> a(tab),b;

  CHECK(a == b);
}

TEST_CASE("Operator mnozenia przez wektor")
{
    double tab[2][2]={2,2,1,1};
    double tab3[2]={2,2};
    double tab2[2]={8,4};
    

    Matrix<2> a(tab);
    Vector<double,2> wek(tab3),wek2(tab2);

  CHECK(a*wek==wek2);
}

TEST_CASE("Operator dodawania macierzy")
{
    double tab[2][2]={0,0,1,1};
    double tab2[2][2]={2,2,2,2};
    double tab3[2][2]={2,2,3,3};
    

    Matrix<2> a(tab),b(tab2),c(tab3);

  CHECK(a+b==c);
}

TEST_CASE("Wyłuskanie")
{
    double tab[2][2]={1,2,3,4};
    double d=4;
    Matrix<2> M(tab);


  CHECK(M(1,1)==d);
}

TEST_CASE("tworzenie macierzy obrotu")
{
    double tab2[2][2]={0,-1,1,0};
    Matrix<2> M,M2(tab2);
    double kat=90;

    M.Mobrot2D_tworzenie(kat);

  CHECK(M==M2);
}

TEST_CASE("tworzenie macierzy obrotu 2")
{
    double tab2[2][2]={0.866025,-0.5,0.5,0.866025};
    Matrix<2> M,M2(tab2);
    double kat=30;

    M.Mobrot2D_tworzenie(kat);

  CHECK(M==M2);
}

TEST_CASE("GAUSS")
{
    double tab2[2][2]={2,3,-1,7};
    Matrix<2> M(tab2);
    double wyznacznik,odp=17;

    wyznacznik=M.gauss();

  CHECK(odp==wyznacznik);
}