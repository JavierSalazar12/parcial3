#include <iostream>

using namespace std;

struct nodo{
    int valor;
    nodo *izq;
    nodo *der;
    int altura;
    };

struct nodo *raiz, *aux, *aux2;

// Función para calcular la altura de un nodo
int calcularAltura(nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    } else {
        return nodo->altura;
    }
}

// Función para verificar factor de equilibrio
int equilibrio(nodo *a) {
    if (a == NULL) {
        return 0;
    } else {
        return calcularAltura(a->izq) - calcularAltura(a->der);
    }
}

// Funciones de rotación
nodo *rotacionDerecha(nodo *y) {
    nodo *x = y->izq;
    nodo *T = x->der;
        x->der = y;
        y->izq = T;
    y->altura = max(calcularAltura(y->izq), calcularAltura(y->der)) + 1;
    x->altura = max(calcularAltura(x->izq), calcularAltura(x->der)) + 1;

    return x;
}
nodo *rotacionIzquierda(nodo *x) {
    nodo *y = x->der;
    nodo *T = y->izq;
        y->izq = x;
        x->der = T;
    x->altura = max(calcularAltura(x->izq), calcularAltura(x->der)) + 1;
    y->altura = max(calcularAltura(y->izq), calcularAltura(y->der)) + 1;

    return y;
}

//Función de balanceo
nodo *balancearNodo(nodo *n) {
    int eq = equilibrio(n);

    // Rotación derecha
    if (eq > 1 && equilibrio(n->izq) >= 0) {
        return rotacionDerecha(n);
            }
    // Rotación izquierda
    if (eq < -1 && equilibrio(n->der) <= 0) {
        return rotacionIzquierda(n);
            }
    // Rotación izquierda-derecha
    if (eq > 1 && equilibrio(n->izq) < 0) {
        n->izq = rotacionIzquierda(n->izq);
        return rotacionDerecha(n);
            }
    // Rotación derecha-izquierda
    if (eq < -1 && equilibrio(n->der) > 0) {
        n->der = rotacionDerecha(n->der);
        return rotacionIzquierda(n);
            }
    return n;
}

//recorrer arbol en orden
void recorrer(nodo* a) {
    if (a != nullptr) {
        recorrer(a->izq);
        cout << "Valor: " << a->valor << " con altura: " << a->altura << endl;
        recorrer(a->der);
    }
}

//Ubicar un nodo correctamente en el arbol
nodo* posicionar(nodo* raiz, nodo* nuevo) {
    if (raiz == NULL)
        return nuevo;

    if (nuevo->valor < raiz->valor)
        raiz->izq = posicionar(raiz->izq, nuevo);
    else if (nuevo->valor > raiz->valor)
        raiz->der = posicionar(raiz->der, nuevo);

    raiz->altura = max(calcularAltura(raiz->izq), calcularAltura(raiz->der)) + 1;

    return balancearNodo(raiz);
}

//Insercion
int insertar(){
    aux = (struct nodo*) malloc(sizeof(struct nodo));
    cout<<"Digite el valor del nodo: ";
    cin>>aux->valor;
    aux->izq = aux->der = NULL;
    aux->altura = 0;

        if(!raiz){
            raiz = aux;
            aux = NULL;
            free (aux);
        }
        else{
            aux2 = raiz;
            aux->altura=1;
            posicionar(raiz, aux);
            aux = NULL;
            free (aux);
        }
    raiz = balancearNodo(raiz);
}

//Imprimir arbol
int mostrar(){
    if(raiz){
        recorrer(raiz);
    }
}

// Función para encontrar el nodo con el valor mínimo en un subárbol
nodo* nodoMinimo(nodo* nodo) {
    while (nodo->izq != NULL) {
        nodo = nodo->izq;
    }
    return nodo;
}

// Función para eliminar un nodo del árbol AVL
nodo* eliminarNodo(nodo* raiz, int valor) {
    // Caso base: árbol vacío
    if (raiz == NULL) {
        return raiz;
    }

    // Buscar el nodo a eliminar
    if (valor < raiz->valor) {
        // El valor está en el subárbol izquierdo
        raiz->izq = eliminarNodo(raiz->izq, valor);
    } else if (valor > raiz->valor) {
        // El valor está en el subárbol derecho
        raiz->der = eliminarNodo(raiz->der, valor);
    } else {
        // Nodo encontrado
        if (raiz->izq == NULL && raiz->der == NULL) {
            // Caso 1: Nodo sin hijos
            free(raiz);
            return NULL;
        } else if (raiz->izq == NULL || raiz->der == NULL) {
            // Caso 2: Nodo con un solo hijo
            nodo* temp = (raiz->izq != NULL) ? raiz->izq : raiz->der;
            free(raiz);
            return temp;
        } else {
            // Caso 3: Nodo con dos hijos
            // Encontrar el nodo con el valor mínimo en el subárbol derecho
            nodo* temp = nodoMinimo(raiz->der);
            raiz->valor = temp->valor; // Copiar el valor del sucesor
            // Eliminar el sucesor
            raiz->der = eliminarNodo(raiz->der, temp->valor);
        }
    }

    // Actualizar la altura del nodo actual
    raiz->altura = max(calcularAltura(raiz->izq), calcularAltura(raiz->der)) + 1;

    // Balancear el árbol
    return balancearNodo(raiz);
}

// Función para iniciar la eliminación desde la raíz
void eliminar() {
    int valor;
    cout << "Digite el valor del nodo a eliminar: ";
    cin >> valor;
    raiz = eliminarNodo(raiz, valor);
    cout << "Nodo eliminado con éxito." << endl;
}

int main() {
    int opcion;
    do {
        cout << "\n*** Menu ***" << endl;
        cout << "1. Insertar un nodo" << endl;
        cout << "2. Mostrar el arbol" << endl;
        cout << "3. Eliminar un nodo" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                insertar();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                eliminar();
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }
    } while (opcion != 4);

    return 0;
}