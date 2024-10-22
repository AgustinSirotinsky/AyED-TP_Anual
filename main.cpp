#include <iostream>
#include <cstring>

using namespace std;

struct alumno
{
    int legajo;
    char nombre[20];
};

struct nodo
{
    alumno info;
    nodo *sgte;
};

void push(nodo *&pila, alumno al);
alumno pop(nodo *&pila);
void encolar(nodo *fte, nodo *fin, alumno al);
alumno desencolar(nodo *&fte, nodo *&fin);
nodo *insertarOrdenado(nodo *&lista, alumno info);
nodo *buscar(nodo *lista, int legajo);
nodo *insertarsinRepetir(nodo *&lista, int sucursal);

int main()
{

    return 0;
}

alumno pop(nodo *&pila)
{
    alumno aux;        // aux para guardar la info
    nodo *p = pila;    // preservo la direccion del nodo
    aux = p->info;     // le doy la info al aux
    pila = pila->sgte; // pila apunta al anterior
    delete p;          // libero la memoria
    return aux;        // retorna el dato
}

void push(nodo *&pila, alumno al)
{
    nodo *p = new nodo();
    p->info = al;
    p->sgte = pila;

    pila = p;
}

void encolar(nodo *fte, nodo *fin, alumno al)
{
    nodo *p = new nodo(); // reservo espacio en memoria
    p->info = al;         // guardo la info
    p->sgte = NULL;       // inicializo el puntero

    if (fte == NULL)
    {            // si es la primera vez
        fte = p; // enlazo al frente
    }
    else
    {
        fin->sgte = p;
        // cuando hay datos actualizo el
        // puntero del que va a dejar ser ultimo.
    }
    fin = p; // apunto fin al nodo nuevo
}

alumno desencolar(nodo *&fte, nodo *&fin)
{
    alumno aux;    // AUX para devolver el dato
    nodo *p = fte; // aux para el nodo que se borra
    aux = p->info; // recupero la info
    fte = p->sgte; // avanzo el ptro a fte
    if (fte == NULL)
    {               // si no hay mas nodos
        fin = NULL; // fin apunta a null
    }
    delete p;   // libero el nodo
    return aux; // retorno el contenido de info
}

nodo *insertarOrdenado(nodo *&lista, alumno info)
{
    // 1) armar el nodo
    nodo *p = new nodo();
    p->info = info;
    p->sgte = NULL;

    // lista vacia o menor al primero
    if (lista == NULL ||
        info.legajo < lista->info.legajo)
    {
        p->sgte = lista;
        lista = p;
    }
    else // entre dos o ultimo
    {
        nodo *q = lista;
        while (q->sgte != NULL &&
               q->sgte->info.legajo < info.legajo)
        {
            q = q->sgte;
        }
        p->sgte = q->sgte;
        q->sgte = p;
    }

    return p;
}

nodo *buscar(nodo *lista, int legajo)
{
    nodo *q = lista;
    while (q != NULL && q->info.legajo != legajo)
    {
        q = q->sgte;
    }
    return q;
}

nodo *insertarsinRepetir(nodo *&lista, int sucursal)\
{
    nodo *aux = buscar(lista, sucursal);
    if (aux == NULL)
    {
        aux = insertarOrdenado(lista, aux->info); // Posiblemente hay que corregir
    }
    return aux;
}