#ifndef MATRIX_HH
#define MATRIX_HH

#include "vector.hh"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

#define epsilon 0.000001



/*!
 * \file
 * \brief Definicja Szablonu macierz
 *  
 *  Jest ona postaci tablicy dwuwymiarowej
 *  
 */
template <int WYMIAR>
class Matrix{

  double value[WYMIAR][WYMIAR];

  public:
    Matrix(double[WYMIAR][WYMIAR]); // Konstruktor klasy

    Matrix(); // Konstruktor klasy

    Vector<double,WYMIAR> operator*(Vector<double,WYMIAR> tmp); // Operator mnożenia przez wektor

    Matrix operator+(Matrix tmp);

    double &operator()(unsigned int row, unsigned int column);

    const double &operator()(unsigned int row, unsigned int column) const;

    Matrix Mobrot2D_tworzenie(int kat);

    Matrix Mobrot3D_tworzenie(int kat,char os);

    bool operator==(const Matrix &tmp) const;
    
    double gauss();    
};




/*!*****************************************************************************
 |  \brief Konstruktor klasy Matrix.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Macierz wypelnione wartoscia 0.                                       |
 */
template <int WYMIAR>
Matrix<WYMIAR>::Matrix()
{
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            value[i][j] = 0;
        }
    }
}

/*!*****************************************************************************
 | \brief Konstruktor parametryczny klasy Matrix.                                   |
 |  Argumenty:                                                                |
 |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
 |  Zwraca:                                                                   |
 |      Macierz wypelniona wartosciami podanymi w argumencie.                 |
 */
template <int WYMIAR>
Matrix<WYMIAR>::Matrix(double tmp[WYMIAR][WYMIAR])
{
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            value[i][j] = tmp[i][j];
        }
    }
}

/*!*****************************************************************************
 |  \brief Realizuje mnozenie macierzy przez wektor.                                 |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik mnozenia,                     |
 |      v - wektor, czyli drugi skladnik mnozenia.                            |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wektor.                    |
 */
template <int WYMIAR>
Vector<double,WYMIAR> Matrix<WYMIAR>::operator*(Vector<double,WYMIAR> tmp)
{
    Vector<double,WYMIAR> result;
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}

/*!*****************************************************************************
 |  \brief Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy.                             |
 */
template <int WYMIAR>
double &Matrix<WYMIAR>::operator()(unsigned int row, unsigned int column)
{

    if (row >= WYMIAR)
    {
        std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    if (column >= WYMIAR)
    {
        std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    return value[row][column];
}

/*!*****************************************************************************
 |  \brief Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy jako stala.                  |
 */
template <int WYMIAR>
const double &Matrix<WYMIAR>::operator()(unsigned int row, unsigned int column) const
{

    if (row >= WYMIAR)
    {
        std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    if (column >= WYMIAR)
    {
        std::out_of_range("Error: Macierz jest poza zasiegiem");
    }

    return value[row][column];
}

/*! *****************************************************************************
 |  \brief Przeciążenie dodawania macierzy                                           |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik dodawania,                    |
 |      tmp - macierz czyli drugi skladnik dodawania.                           |
 |  Zwraca:                                                                   |
 |      Macierz - sume macierzy.                            |
 */
template <int WYMIAR>
Matrix<WYMIAR> Matrix<WYMIAR>::operator+(Matrix<WYMIAR> tmp)
{
    Matrix result;
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}

/*! *****************************************************************************
 |  \brief Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      mat - macierz.                                                        |
 */
template <int WYMIAR>
std::istream &operator>>(std::istream &in, Matrix<WYMIAR> &mat)
{
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            in >> mat(i, j);
        }
    }
    return in;
}

/*! *****************************************************************************
 |  \brief Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      mat - macierz.                                                        |
 */
template <int WYMIAR>
std::ostream &operator<<(std::ostream &out, const Matrix<WYMIAR> &mat)
{
    for (int i = 0; i < WYMIAR; ++i)
    {
        for (int j = 0; j < WYMIAR; ++j)
        {
            out << "| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        std::cout << std::endl;
    }
    return out;
}

/*! *****************************************************************************
 |  \brief Tworzy macierz obrotu  2D                                                 |
 |  Argumenty:                                                              |
 |      kat - kat obrotu,                                                   |
 |  Zwraca:                                                                 |
 |      Macierz obrotu                                                      |
 */
template <int WYMIAR>
Matrix<WYMIAR> Matrix<WYMIAR>::Mobrot2D_tworzenie(int kat)
{
    double rad = kat * M_PI / 180;
    value[0][0] = cos(rad);
    value[0][1] = -sin(rad);
    value[1][0] = sin(rad);
    value[1][1] = cos(rad);
    return *this;
}

/*! *****************************************************************************
 |  \brief Tworzy macierz obrotu  3D                                                 |
 |  Argumenty:                                                              |
 |      kat - kat obrotu,                                                   |
 *      os - os obrotu
 |  Zwraca:                                                                 |
 |      Macierz obrotu                                                      |
 */
template <int WYMIAR>
Matrix<WYMIAR> Matrix<WYMIAR>::Mobrot3D_tworzenie(int kat,char os)
{
    double rad = kat * M_PI / 180;
    do
    {
    switch (os)
    {
    case 'z':
    value[0][0] = cos(rad);
    value[0][1] = -sin(rad);
    value[1][0] = sin(rad);
    value[1][1] = cos(rad);
    value[2][0] = 0;
    value[2][1] = 0;
    value[2][2] = 1;
    value[0][2] = 0;
    value[1][2] = 0;
        break;
    
    
    case 'y':
    value[0][0] = cos(rad);
    value[0][2] = -sin(rad);
    value[2][0] = sin(rad);
    value[2][2] = cos(rad);
    value[1][0] = 0;
    value[2][1] = 0;
    value[1][1] = 1;
    value[0][1] = 0;
    value[1][2] = 0;
    break;
    case 'x':
    value[1][1] = cos(rad);
    value[1][2] = -sin(rad);
    value[2][1] = sin(rad);
    value[2][2] = cos(rad);
    value[2][0] = 0;
    value[0][1] = 0;
    value[0][0] = 1;
    value[0][2] = 0;
    value[1][0] = 0;
    break;

    default:
    std::cout<<"Blednie podana os! Mozliwe to x,y,z\nPodaj os: ";
    std::cin>>os;
    break;
    }
    }
    while (os!='z'&&os!='x'&&os!='y');

    return *this;
}
/*!
 * \brief Operator porownania
 *  Argumenty:                                                                
 *      Macierze                                                               
 *  Zwraca:                                                                   
 *      bool 
 */
template <int WYMIAR>
bool Matrix<WYMIAR>::operator==(const Matrix<WYMIAR> &tmp) const
{
    int prawdy = 0;
    for (int i = 0; i < WYMIAR; i++)
    {
        for (int j = 0; j < WYMIAR; j++)
        {
            prawdy += (int)(abs(this->value[i][j] - tmp.value[i][j]) <= epsilon);
        }
    }
    if (prawdy==WYMIAR*WYMIAR)
    {
        return true;
    }
    else
        return false;
}

/*!*****************************************************************************
 |  \brief Metoda liczenia wyznacznika Gaussem                                       |
 |  Argumenty:                                                                |
 |      Macierz                                                               |
 |  Zwraca:                                                                   |
 |      Wyznacznik typu double                                                |
 */
template <int WYMIAR>
double Matrix<WYMIAR>::gauss()
{
    int i, j, k;
    double temp, x[WYMIAR];
    for (j = 0; j < WYMIAR - 1; j++)
    {
        for (i = j + 1; i < WYMIAR; i++)
        {
            temp = value[i][j] / value[j][j];
            for (k = 0; k < WYMIAR; k++)
            {
                value[i][k] -= value[j][k] * temp;
            }
        }
    }
    for (int i = 0; i < WYMIAR; i++)
    {
        x[i] = value[i][i];
    }
    double wyznacznik = 1;
    for (i = 0; i < WYMIAR; i++)
    {
        wyznacznik *= x[i];
    }
    return wyznacznik;
}


#endif