#ifndef VECTOR_HH
#define VECTOR_HH

#include <iostream>
#include <iostream>
#include <stdexcept>
#include <math.h>
#define epsilon 0.000001

/*!
 * \file
 * \brief Ten plik powinien zawierać definicję szablonu Wektor<>
 *
 * Ten plik powinien zawierać definicję szablonu Wektor<>.
 * W tym celu należy przerobić definicję klasy Wektor2D.
 */
template <typename T,unsigned int ROZMIAR>
class Vector
{

    T wspolrzedne[ROZMIAR]; //Tablica wektora

public:
    Vector();

    Vector(T[ROZMIAR]);

    T dlugosc(const Vector &drugi);

    Vector operator+(const Vector &v);

    Vector operator-(const Vector &v);

    Vector operator*(const T &tmp);

    Vector operator/(const T &tmp);

    const T &operator[](int index) const;

    T &operator[](int index);

    bool operator==(const Vector &drugi) const;

    void zapeln(T argu[ROZMIAR]);

    T modul();
};

/*!
 * \brief Przeciazenie operatora >>
 *                                                  
 *  Argumenty:                                                                
 *      in - strumien wyjsciowy,                                              
 *      tmp - wektor.  
 */
template <typename T,unsigned int ROZMIAR>
inline std::istream &operator>>(std::istream &in, Vector<T,ROZMIAR> &tmp)
{
    for (int i = 0; i < ROZMIAR; ++i)
    {
        in >> tmp[i];
    }
    std::cout << std::endl;
    return in;
}

/*!
 * \brief Przeciazenie operatora <<                                                  
 *  Argumenty:                                                                
 *      out - strumien wejsciowy,                                             
 *      tmp - wektor
 */
template <typename T,unsigned int ROZMIAR>
inline std::ostream &operator<<(std::ostream &out, const Vector<T,ROZMIAR> &tmp)
{
    for (int i = 0; i < ROZMIAR; ++i)
    {
        out << tmp[i] << " ";
    }
    return out;
}

/*!
 * \brief Konstruktor klasy Vector
 *
 *  Argumenty:                                                                
 *      Brak argumentow.                                                      
 *  Zwraca:                                                                   
 *      Tablice wypelniona wartoscia 0. 
 */
template <typename T,unsigned int ROZMIAR>
Vector<T,ROZMIAR>::Vector()
{
    {
        for (T &wsp1 : wspolrzedne)
        {
            wsp1 = 0;
        }
    }
}

/*!
 * \brief Konstruktor parametryczny klasy Vector
 *
 *  Argumenty:                                                                
 *      Tablica typu t.                                                       
 *  Zwraca:                                                                   
 *      Tablice wypelniona wartoscia tablicy. 
 */
template <typename T,unsigned int ROZMIAR>
Vector<T,ROZMIAR>::Vector(T tmp[ROZMIAR])
{
    for (int i = 0; i < ROZMIAR; ++i)
    {
        wspolrzedne[i] = tmp[i];
    }
}

/*!
 * \brief Metoda zwracająca dlugosc wektora
 *
 *  Argumenty:                                                                
 *      Wektor                                                                
 *  Zwraca:                                                                   
 *      Dlugosc wektora 
 */
template <typename T,unsigned int ROZMIAR>
T Vector<T,ROZMIAR>::dlugosc(const Vector<T,ROZMIAR> &drugi)
{
    T tmp;
    for (int i = 0; i < ROZMIAR; i++)
    {
        tmp += pow(drugi.wspolrzedne[i] - this->wspolrzedne[i], 2);
    }
    return sqrt(tmp);
}

/*!
 * \brief Metoda zwracająca wspolrzedna wektora
 *
 *  Argumenty:                                                                
 *      Wektor                                                                
 *  Zwraca:                                                                   
 *      Wspolrzedna 
 */
template <typename T,unsigned int ROZMIAR>
const T &Vector<T,ROZMIAR>::operator[](int index) const
{
    if (index < 0 ** index >= ROZMIAR)
    {
        std::out_of_range("Error: Vektor jest poza zasiegiem");
    }
    return wspolrzedne[index];
}
/*!
 * \brief Operator porownania
 *  Argumenty:                                                                
 *      Wektory                                                               
 *  Zwraca:                                                                   
 *      bool 
 */
template <typename T,unsigned int ROZMIAR>
bool Vector<T,ROZMIAR>::operator==(const Vector<T,ROZMIAR> &drugi) const
{
    int tmp = 0;
    for (int i = 0; i < ROZMIAR; ++i)
    {
        tmp += (int)(abs(wspolrzedne[i] - drugi.wspolrzedne[i]) <= epsilon);
    }
    if (tmp == ROZMIAR)
    {
        return true;
    }
    else
        return false;
}

/*!
 * \brief Operator porownania
 *  Argumenty:                                                                
 *      Wektory                                                               
 *  Zwraca:                                                                   
 *      bool                                                                  
 */
template <typename T,unsigned int ROZMIAR>
void Vector<T,ROZMIAR>::zapeln(T argu[ROZMIAR])
{
    for (int i = 0; i < ROZMIAR; i++)
    {
       wspolrzedne[i]=argu[i]; 
    }
}
/*!
 * \brief Oblicza modul
 *  Argumenty:                                                                
 *      Wektor                                                               
 *  Zwraca:                                                                   
 *      modul                                                                  
 */
template <typename T,unsigned int ROZMIAR>
T Vector<T,ROZMIAR>::modul()
{   
    T tmp;
    for(int i=0;i<ROZMIAR;i++)
    {
        tmp+=(wspolrzedne[i] * wspolrzedne[i]);
    }
    return sqrt(tmp);
}

#endif
