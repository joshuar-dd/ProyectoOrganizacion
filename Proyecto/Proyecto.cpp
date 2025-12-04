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

void agregarContacto() {
    if (totalContactos >= MAX_CONTACTOS) {
        cout << "No se pueden agregar mas contactos\n";
        return;
    }

    Contacto* nuevo = new Contacto;
    cout << "Nombre: ";
    cin.ignore();
    getline(cin, nuevo->nombre);
    cout << "Telefono: ";
    getline(cin, nuevo->telefono);
    cout << "Email: ";
    getline(cin, nuevo->email);
    nuevo->siguiente = NULL;

    contactos[totalContactos] = nuevo;
    totalContactos++;

    Operacion* nuevaOp = new Operacion;
    nuevaOp->tipo = "AGREGAR";
    nuevaOp->contacto = nuevo->nombre;
    nuevaOp->siguiente = pilaHistorial;
    pilaHistorial = nuevaOp;

    cout << "Contacto agregado exitosamente\n";
}

void ordenarContactos() {
    for (int i = 0; i < totalContactos - 1; i++) {
        for (int j = 0; j < totalContactos - i - 1; j++) {
            if (contactos[j]->nombre > contactos[j + 1]->nombre) {
                Contacto* temp = contactos[j];
                contactos[j] = contactos[j + 1];
                contactos[j + 1] = temp;
            }
        }
    }
}

void listaContactos() {
    if (totalContactos == 0) {
        cout << "No hay contactos registrados\n";
        return;
    }

    ordenarContactos();

    cout << "LISTA DE CONTACTOS  \n";
    for (int i = 0; i < totalContactos; i++) {
        cout << i + 1 << contactos[i]->nombre
            << " | " << contactos[i]->telefono
            << " | " << contactos[i]->email << endl;
    }
}
