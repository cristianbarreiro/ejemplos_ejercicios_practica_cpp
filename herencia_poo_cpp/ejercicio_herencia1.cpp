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

class Empleado : public Persona
{
private:
    int sueldo;

public:
    Empleado(string, int, int);
    void mostrarEmpleado();
};

class Estudiante : public Persona
{
private:
    string codAlumno;
    float notaFinal;

public:
    Estudiante(string, int, string, float);
    void mostrarEstudiante();
};

class Universitario : public Estudiante
{
private:
    string carrera;

public:
    Universitario(string, int, string, float, string);
    void mostrarUniversitario();
};

Persona::Persona(string _nombre, int _edad)
{
    nombre = _nombre;
    edad = _edad;
}

Empleado::Empleado(string _nombre, int _edad, int _sueldo) : Persona(_nombre, _edad)
{
    sueldo = _sueldo;
}

Estudiante::Estudiante(string _nombre, int _edad, string _codAlumno, float _notaFinal) : Persona(_nombre, _edad)
{
    codAlumno = _codAlumno;
    notaFinal = _notaFinal;
}

Universitario::Universitario(string _nombre, int _edad, string _codAlumno, float _notaFinal, string _carrera) : Estudiante(_nombre, _edad, _codAlumno, _notaFinal)
{
    carrera = _carrera;
}

void Persona::mostrarPersona()
{
    cout << "Nombre: " << nombre << endl;
    cout << "Edad: " << edad << endl;
}

void Empleado::mostrarEmpleado()
{
    mostrarPersona(); // Llamamos a la función de la clase padre para mostrar el nombre y edad
    cout << "Sueldo: " << sueldo << endl;
}

void Estudiante::mostrarEstudiante()
{
    mostrarPersona(); // Llamamos a la función de la clase padre para mostrar el nombre y edad
    cout << "Codigo de Alumno: " << codAlumno << endl;
    cout << "Nota Final: " << notaFinal << endl;
}

void Universitario::mostrarUniversitario()
{
    mostrarEstudiante(); // Llamamos a la función de la clase padre para mostrar el nombre, edad, codigo de alumno y nota final
    cout << "Carrera: " << carrera << endl;
}

int main()
{
    Universitario uni1("Maria Lopez", 22, "U54321", 9.0, "Ingenieria Informatica");
    uni1.mostrarUniversitario();

    Estudiante est1("Carlos Gomez", 19, "E67890", 7.5);
    est1.mostrarEstudiante();

    Empleado emp1("Ana Martinez", 30, 3500);
    emp1.mostrarEmpleado();

    Persona per1("Luis Ramirez", 40);
    per1.mostrarPersona();


    cout << "Presiona una tecla para continuar..." << endl;
    getchar();
    return 0;
}