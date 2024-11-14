#include <iostream>
#include <cstring>

using namespace std;

/*
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
*/

// vector
struct especialidad{
	int id;
	char descrpcion [50+1];
};


// structs info
struct paciente {
	int id;
	char nombre[50+1];
	char apellido[50+1];
	int edad;
	char dni [8+1];
	int telefono;
};
struct medico {
	int id;
	char nombre[50+1];
	char apellido[50+1];
	int matricula;
	int idEspecialidad;
	int diasAtencion;
	int rangoHorario;
	int tiempoConsulta;
};
struct turno {
	int id;
	nodo_turnoPaciente *listaTurnoPaciente;
};

struct infoTurnoPaciente{
	int id;
	int hora;
	int diaSem;
	int mes;
	char status;
	int idPaciente;	
};

// structs nodos
struct nodo_turnoPaciente{
	infoTurnoPaciente info;
	nodo_turnoPaciente *sgte;
};

struct nodo_paciente {
	paciente info;
	nodo_paciente *sgte;
};
struct nodo_medico {
	medico info;
	nodo_medico *sgte;
	
};
struct nodo_turno {
	turno info;
	nodo_turno *sgte;
	
};

// variables globales
nodo_paciente *listaPacientes = NULL;
nodo_medico *listaMedicos = NULL;
nodo_turno *listaTurnos = NULL;
especialidad vecEspecialidad[20];

// prototipos
void volcarArchivosaListas();
void mostrarMenu();

int main()
{
	volcarArchivosaListas();
	mostrarMenu();

    return 0;
}

/*
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

nodo *insertarsinRepetir(nodo *&lista, int sucursal)
{
    nodo *aux = buscar(lista, sucursal);
    if (aux == NULL)
    {
        aux = insertarOrdenado(lista, aux->info); // Posiblemente hay que corregir
    }
    return aux;
}
*/

int imprimirMenu(){
	
	cout<<endl;
	cout<<" ** MENU **"<<endl;
	cout<<endl;
	cout<<"  ALTA"<<endl;
	cout<<"    1- NUEVO PACIENTE"<<endl;
	cout<<"    2- NUEVO TURNO"<<endl;
	cout<<"    3- NUEVO MEDICO"<<endl;	
	cout<<endl;
	cout<<"  ACTUALIZACIONES"<<endl;
	cout<<"    4- ACTUALIZAR STATUS"<<endl;	
	cout<<endl;
	cout<<"  LISTADO"<<endl;
	cout<<"    5- TURNOS PENDIENTES"<<endl;
	cout<<"    6- CANTIDAD ATENCIONES EFECTIVAS"<<endl;
	cout<<"    7- CANCELACIONES"<<endl;
	cout<<endl;
	
	int opc = -1;
	cout<<"ingrese una opcion: ";
	cin>>opc;
	cout<<endl;
	
	return 0;
}

void ejecutarOpcion(int opc){
	switch(opc){
		case 1:
			nuevoPaciente();
			break;
		case 2:
			nuevoTurno();
			break;
		case 3:
			nuevoMedico();
			break;
		case 4:
			actualizarStatus();
			break;
		case 5:
			listarTurnosPendientes();
			break;
		case 6:
			listarAtencionesEfectivas();
			break;
		case 7:
			listarCancelaciones();
			break;
		default:
			break;
	}
}

void mostrarMenu(){
	int opcion = -1;
	while(opcion != 0){
		//mostrar menu y recibir opcion
		opcion = imprimirMenu();
		//ejecutar la opcion 
		ejecutarOpcion(opcion);
	}
}
void insertarPacienteOrd(nodo_paciente *nodo){
	if (listaPacientes == NULL ||
        nodo->info.id < listaPacientes->info.id) {
        nodo->sgte = listaPacientes;
        listaPacientes = nodo;
    } else {
        nodo_paciente *q = listaPacientes;
        while (q->sgte != NULL &&
               q->sgte->info.id < nodo->info.id) {
            q = q->sgte;
        }
        nodo->sgte = q->sgte;
        q->sgte = nodo;
    }
}

void volcarPacientesaLista(){
	FILE *f = fopen("PACIENTES","rb");
	paciente reg ;
	
	while(fread(&reg,sizeof(reg),1,f)){
		//creo un nodo
		nodo_paciente *nodo = new nodo_paciente();
		//cargo el nodo con registro
		nodo->info.id = reg.id;
		nodo->info.apellido = reg.apellido;
		nodo->info.dni = reg.dni;
		nodo->info.edad = reg.edad;
		nodo->info.nombre = reg.nombre;
		nodo->info.telefono = reg.telefono;
		nodo->sgte = NULL;
		//inserto nodo en la lista
		insertarPacienteOrd(nodo);
		}
	}
	
	fclose(f);
}
void volcarMedicosaLista(){
	cout<<"volcarMedicosaLista";
}
void volcarArchivosaListas(){
	volcarPacientesaLista();
	volcarMedicosaLista();
}

