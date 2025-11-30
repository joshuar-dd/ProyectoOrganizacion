#include <iostream>
#include <string>
using namespace std;

struct Contacto {
    string nombre;
    string telefono;
    string email;
    Contacto* siguiente;
};

struct NodoArbol {
    Contacto* contacto;
    NodoArbol* izquierdo;
    NodoArbol* derecho;
};

struct Operacion {
    string tipo;
    string contacto;
    Operacion* siguiente;
};

const int MAX_CONTACTOS = 100;
Contacto* contactos[MAX_CONTACTOS];
int totalContactos = 0;

Contacto* listaEliminados = NULL;
Operacion* pilaHistorial = NULL;
Contacto* frenteCola = NULL;
Contacto* finalCola = NULL;
NodoArbol* arbolContactos = NULL;

void limpiarPantalla() {
    system("cls");
}

void pausar() {
    cout << "\nPresione enter para continuar";
    cin.ignore();
    cin.get();
}
