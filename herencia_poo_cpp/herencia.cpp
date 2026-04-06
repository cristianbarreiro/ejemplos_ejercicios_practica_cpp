// Herencia en POO

#include <iostream>
#include <stdlib.h>
#include <cstdio>

using namespace std;

class Persona
{
private:
    string nombre;
    int edad;

public:
    Persona(string, int);
    void mostrarPersona();
};

class Alumno : public Persona
{
private:
    string codAlumno;
    float notaFinal;

public:
    Alumno(string, int, string, float);
    void mostrarAlumno();
};

// Constructor de la clase Persona (Clase Padre)
Persona::Persona(string _nombre, int _edad)
{
    nombre = _nombre;
    edad = _edad;
}

//Constructor de la clase Alumno (Clase Hija)
Alumno::Alumno(string _nombre, int _edad, string _codAlumno, float _notaFinal) : Persona(_nombre, _edad)
{
    codAlumno = _codAlumno;
    notaFinal = _notaFinal;
}

void Persona::mostrarPersona()
{
    cout << "Nombre: " << nombre << endl;
    cout << "Edad: " << edad << endl;
}

void Alumno::mostrarAlumno()
{
    mostrarPersona(); // Llamamos a la función de la clase padre para mostrar el nombre y edad
    cout << "Codigo de Alumno: " << codAlumno << endl;
    cout << "Nota Final: " << notaFinal << endl;
}

int main()
{
    Alumno alumno1("Juan Perez", 20, "A12345", 8.5);
    alumno1.mostrarAlumno();

    cout << "Presiona una tecla para continuar..." << endl;
    getchar();
    return 0;
}