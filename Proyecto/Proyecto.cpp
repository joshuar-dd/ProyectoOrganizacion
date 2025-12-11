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
void busquedaSecuencial() {
    string nombreBuscado;
    cout << "Nombre a buscar: ";
    cin.ignore();
    getline(cin, nombreBuscado);

    bool encontrado = false;
    for (int i = 0; i < totalContactos; i++) {
        if (contactos[i]->nombre.find(nombreBuscado) != string::npos) {
            cout << "Encontrado: " << contactos[i]->nombre
                << " | " << contactos[i]->telefono
                << " | " << contactos[i]->email << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "Contacto no encontrado\n";
    }
}

void busquedaBinaria() {
    if (totalContactos == 0) {
        cout << "No hay contactos para buscar\n";
        return;
    }

    string telefonoBuscado;
    cout << "Telefono a buscar: ";
    cin.ignore();
    getline(cin, telefonoBuscado);

    ordenarContactos();

    int inicio = 0;
    int fin = totalContactos - 1;
    bool encontrado = false;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        if (contactos[medio]->telefono == telefonoBuscado) {
            cout << "Encontrado: " << contactos[medio]->nombre
                << " | " << contactos[medio]->telefono
                << " | " << contactos[medio]->email << endl;
            encontrado = true;
            break;
        }
        else if (contactos[medio]->telefono < telefonoBuscado) {
            inicio = medio + 1;
        }
        else {
            fin = medio - 1;
        }
    }

    if (!encontrado) {
        cout << "Contacto no encontrado\n";
    }
}
void eliminarContacto() {
    if (totalContactos == 0) {
        cout << "No hay contactos para eliminar\n";
        return;
    }

    listaContactos();
    int posicion;
    cout << "Seleccione el numero del contacto a eliminar ";
    cin >> posicion;

    if (posicion < 1 || posicion > totalContactos) {
        cout << "Posicion invalida\n";
        return;
    }

    posicion--;

    contactos[posicion]->siguiente = listaEliminados;
    listaEliminados = contactos[posicion];

    Operacion* nuevaOp = new Operacion;
    nuevaOp->tipo = "ELIMINAR";
    nuevaOp->contacto = contactos[posicion]->nombre;
    nuevaOp->siguiente = pilaHistorial;
    pilaHistorial = nuevaOp;
    for (int i = posicion; i < totalContactos - 1; i++) {
        contactos[i] = contactos[i + 1];
    }
    totalContactos--;

    cout << "Contacto eliminado exitosamente\n";
}
void mostrarHistorial() {
    if (pilaHistorial == NULL) {
        cout << "No hay operaciones en el historial\n";
        return;
    }

    cout << "HISTORIAL DE OPERACIONES\n";
    Operacion* actual = pilaHistorial;
    int contador = 1;

    while (actual != NULL) {
        cout << contador << actual->tipo << " - " << actual->contacto << endl;
        actual = actual->siguiente;
        contador++;
    }
}

void encolarContacto() {
    Contacto* nuevo = new Contacto;
    cout << "Nombre del contacto pendiente: ";
    cin.ignore();
    getline(cin, nuevo->nombre);
    cout << "Telefono: ";
    getline(cin, nuevo->telefono);
    cout << "Email: ";
    getline(cin, nuevo->email);
    nuevo->siguiente = NULL;
    if (frenteCola == NULL) {
        frenteCola = nuevo;
        finalCola = nuevo;
    }
    else {
        finalCola->siguiente = nuevo;
        finalCola = nuevo;
    }

    cout << "Contacto encolado exitosamente\n";
}
void procesarCola() {
    if (frenteCola == NULL) {
        cout << "No hay contactos pendientes en la cola\n";
        return;
    }

    int procesados = 0;
    while (frenteCola != NULL && totalContactos < MAX_CONTACTOS) {
        contactos[totalContactos] = frenteCola;
        totalContactos++;

        Operacion* nuevaOp = new Operacion;
        nuevaOp->tipo = "AGREGAR";
        nuevaOp->contacto = frenteCola->nombre;
        nuevaOp->siguiente = pilaHistorial;
        pilaHistorial = nuevaOp;

        Contacto* temp = frenteCola;
        frenteCola = frenteCola->siguiente;
        temp->siguiente = NULL;

        procesados++;
    }

    if (frenteCola == NULL) {
        finalCola = NULL;
    }

    cout << "Se procesaron " << procesados << " contactos de la cola\n";
}

NodoArbol* insertarArbol(NodoArbol* nodo, Contacto* contacto) {
    if (nodo == NULL) {
        NodoArbol* nuevo = new NodoArbol;
        nuevo->contacto = contacto;
        nuevo->izquierdo = NULL;
        nuevo->derecho = NULL;
        return nuevo;
    }

    if (contacto->nombre < nodo->contacto->nombre) {
        nodo->izquierdo = insertarArbol(nodo->izquierdo, contacto);
    }
    else {
        nodo->derecho = insertarArbol(nodo->derecho, contacto);
    }

    return nodo;
}

void recorridoInorden(NodoArbol* nodo) {
    if (nodo != NULL) {
        recorridoInorden(nodo->izquierdo);
        cout << "- " << nodo->contacto->nombre << " | "
            << nodo->contacto->telefono << " | "
            << nodo->contacto->email << endl;
        recorridoInorden(nodo->derecho);
    }
}

void construirArbol() {
    arbolContactos = NULL;

    for (int i = 0; i < totalContactos; i++) {
        arbolContactos = insertarArbol(arbolContactos, contactos[i]);
    }

    cout << "Arbol construido exitosamente\n";
}

void mostrarArbol() {
    if (arbolContactos == NULL) {
        cout << "El arbol esta vacio debe construir el arbol primero\n";
        return;
    }

    cout << "CONTACTOS EN ARBOL (inorden)\n";
    recorridoInorden(arbolContactos);
}

void mostrarMenu() {
    limpiarPantalla();
    cout << "SISTEMA DE GESTION DE CONTACTOS \n";
    cout << "1. Agregar contacto\n";
    cout << "2. Listar contactos\n";
    cout << "3. Buscar contacto (nombre)\n";
    cout << "4. Buscar contacto (Telefono)\n";
    cout << "5. Eliminar contacto\n";
    cout << "6. Mostrar historial de operaciones\n";
    cout << "7. Encolar contacto pendiente\n";
    cout << "8. Procesar cola de contactos pendientes\n";
    cout << "9. Construir arbol de contactos\n";
    cout << "10. Mostrar arbol de contactos\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}


