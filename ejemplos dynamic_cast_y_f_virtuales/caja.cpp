/*
*   Uso de funciones virtuales y polimorfismo en C++
*   Conversión de tipos en tiempo de ejecución utilizando dynamic_cast
*/

#include <iostream>
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846

class Figura
{
private:
    double perimetro, area;

public:
    Figura(double p, double a) : perimetro(p), area(a) {}

    double retPerimetro() const
    {
        return perimetro;
    }

    double retArea() const
    {
        return area;
    }

    void ingPerimetro(double p)
    {
        perimetro = p;
    }

    void ingArea(double a)
    {
        area = a;
    }

    virtual void ver() = 0;
};

class Cuadrado : public Figura
{
private:
    double lado;

public:
    Cuadrado(double l) : Figura(l * 4, l * l)
    {
        lado = l;
    }

    double retLado() const
    {
        return lado;
    }

    void ingLado(double l)
    {
        lado = l;
        ingArea(lado * lado);
        ingPerimetro(lado * 4);
    }

    //Implementamos la función virtual
    void ver()
    {
        std::cout << "Lado: " << lado << " Area:" << retArea() << " Perimetro: " << retPerimetro() << std::endl;
    }
};

class Circulo : public Figura
{
private:
    double radio;

public:
    Circulo(double r) : Figura(2 * M_PI * r, M_PI * std::pow(r, 2)), radio(r) {}

    void ingRadio(double r)
    {
        radio = r;
        ingArea(M_PI * std::pow(r, 2));
        ingPerimetro(2 * M_PI * radio);
    }

    double retRadio() const
    {
        return radio;
    }

    //Implementamos la función virtual
    void ver()
    {
        std::cout << "Radio: " << radio << " Area:" << retArea() << " Perimetro: " << retPerimetro() << std::endl;
    }
};

//CajaFigura guarda los tipos de datos creados, utilizando un vector de punteros a la clase base (Figura).
class CajaFigura
{
private:
    //Este vector contendrá todos los datos
    std::vector<Figura *> figuras;

public:
    CajaFigura() {}

    //Esta funcion recibe los distintos tipos de datos y los almacena en el vector de figuras, 
    //utilizando el polimorfismo para almacenar objetos de diferentes tipos en el mismo vector.
    template <typename T>
    void agregar(T *t)
    {
        if (!t)
        {a
            return;
        }
        figuras.push_back(dynamic_cast<Figura *> (t));
    }

    //Mostrar los tipos de datos
    void mostrar()
    {
        for (Figura *f : figuras)
        {
            f->ver();
        }
    }   
};

int main()
{
    //Estructura del programa
    CajaFigura caja;

    Cuadrado cuadrado(7);
    Circulo circulo(5);

    //La función recibe distintos tipos
    //pero estos datos son derivadas de la clase base (Figura), por lo que se pueden almacenar en el mismo vector.
    caja.agregar(&cuadrado);
    caja.agregar(&circulo);

    //Llamar a la función mostrar llamará a la función
    //virtual general de cada tipo de dato.
    caja.mostrar();
}