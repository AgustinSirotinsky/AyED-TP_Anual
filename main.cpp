#include <iostream>
#include <cstring>

using namespace std;

/*

void push(nodo *&pila, alumno al);
alumno pop(nodo *&pila);

*/

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

// vector max 20
struct especialidad{
	int id;
	char descripcion [50+1];
};

// structs info
struct paciente {
	int id; //secuencia
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
	int diasAtencion; // Dias como secuencia numerica donde 1 es domingo
	int rangoHorario; // De 00 a 24
	int tiempoConsulta; // En minutos
};

struct turno { // Charlar si conviene dejarlo como struct o integrarlo a struct medico
	int id; //idmedico
	nodo_turnoPaciente *listaTurnoPaciente;//sublista con datos del turno + idpaciente
};

struct infoTurnoPaciente{
	int id; // Unico, secuencia
	int hora; 
	int diaSem; // Dias como secuencia numerica donde 1 es domingo
	int mes;
	char status; // (P:pendiente - A:atendido - C:cancelado - X:no atendido sin cancelar)
	int idPaciente;	
};

/*
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

// variables globales
nodo_paciente *listaPacientes = NULL;
nodo_medico *listaMedicos = NULL;
nodo_turno *listaTurnos = NULL;
especialidad vecEspecialidad[20];

// prototipos
void volcarArchivosaListas(); // Separar por cada tipo de lista o hacer template
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

*/

int imprimirMenu(){
	
	cout<<endl;
	cout<<" ** MENU **"<<endl;
	cout<<endl;
	cout<<"  ALTA"<<endl;
	cout<<"    1- NUEVO PACIENTE"<<endl; //Cargar en el archivo
	cout<<"    2- NUEVO TURNO"<<endl; //Carcar sublista de turnos
	cout<<"    3- NUEVO MEDICO"<<endl; //Cargar un medico
	cout<<endl;
	cout<<"  ACTUALIZACIONES"<<endl;
	cout<<"    4- ACTUALIZAR STATUS"<<endl;	
	cout<<endl;
	cout<<"  LISTADO"<<endl;
	cout<<"    5- TURNOS PENDIENTES"<<endl; // Ingresar mes e idmedico y muestra por pantalla la lista
	cout<<"    6- CANTIDAD ATENCIONES EFECTIVAS"<<endl; // Contador de todos los turnos atendidos
	cout<<"    7- CANCELACIONES"<<endl; // Ingresar nombre del paciente, medico, especialidad y dia y mostar por pantalla la lista
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

/* Cargar archivo o lista?
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
*/
