/*Punteros- Declaración de Punteros

&n = La direccion de n
*n = la variable cuya dirección está almacenada en n


g++ pointers.cpp -o pointers -lncurses

*/

#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int num, *dir_num;
    num = 20;
    dir_num = &num;

    cout << "Numero: " << num << endl;
    cout << "Direccion de memoria: " << dir_num << endl;
    cout << "Presiona una tecla..." << endl;
    
    getchar();
    return 0;
}