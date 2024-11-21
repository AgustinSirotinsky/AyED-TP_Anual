#include <iostream>
#include <string.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

struct Paciente {
	int id_paciente;
	char nomb_P[15];
	char ape_P[15];
	int edad;
	int dni;
	int telefono;
};

struct Medicos {
int id_medico;
char nomb_M[15];
char ape_M[15];
int matricula;
int id_especialidad;
int disponibilidad;  //secuencia numerica 7 dias 1234567, 1 es domingo
char rango[10]; // De 00 a 24
int tiempo;
};

struct Especialidades {
int id_especialidades;
char descrip[20];
};

struct info_turnos {
int id_turno; 
int h;
int d;
int m;
char estatus;
int id_psub;
int f; //fecha
};

struct Turnos{
info_turnos info;
Turnos *sgte=NULL;
};

struct Lista_M{
	int id_listM;
	Turnos *x=NULL;
	Lista_M *sgte=NULL;
	};

Lista_M *Buscar_ID(Lista_M *lista,int i);
Turnos *buscarTURNf(Turnos *n,int i);
Turnos *buscarTURNID(Turnos *n,int i);
void InsertarOrdenado(Turnos *&n,info_turnos y);
void InsertarOrdenadoM(Lista_M *&lista,int i);
int InsertarSinRepetir(Turnos *&n,info_turnos &y);	
int imprimirMenu();
void ejecutarOpcion(int opc,Lista_M *&lista);
void mostrarMenu(Lista_M *&lista);
void nuevoPaciente();
void nuevoTurno(Lista_M *&lista);
void nuevoMedico(Lista_M *&lista);

int main(int argc, char** argv) {
	Especialidades v[20];
	Lista_M *lista=NULL;
	mostrarMenu(lista);
	
	return 0;
}

Lista_M *Buscar_ID(Lista_M *lista,int i){
	Lista_M *q=lista;
	while(q!=NULL&&q->id_listM!=i){
	q=q->sgte;
}
return q;
}

Turnos *buscarTURNf(Turnos *n,int i){
	Turnos *q=n;
	while(q!=NULL&&q->info.f!=i){
	q=q->sgte;
}
return q;
}

Turnos *buscarTURNID(Turnos *n,int i){
	Turnos *q=n;
	while(q!=NULL&&q->info.id_psub!=i){
	q=q->sgte;
}
return q;
}

void InsertarOrdenado(Turnos *&n,info_turnos y){
	
	Turnos *p=new Turnos();
	p->info=y;
	p->sgte=NULL;
	if(n==NULL||y.f<n->info.f){
		p->sgte=n;
		n=p;
}
else{
	Turnos *q=n;
	while(q->sgte!=NULL&&q->sgte->info.f<y.f){
		q=q->sgte;
}
p->sgte=q->sgte;
q->sgte=p;
}
return;
}

void InsertarOrdenadoM(Lista_M *&lista,int i){
	Lista_M *p=new Lista_M();
	p->id_listM=i;
	p->sgte=NULL;
		if(lista==NULL||i<lista->id_listM){
		p->sgte==lista;
		lista==p;
}
else{
	Lista_M *q=lista;
	while(q->sgte!=NULL&&q->sgte->id_listM<i){
		q=q->sgte;
}
p->sgte=q->sgte;
q->sgte=p;
}
return;
}

int InsertarSinRepetir(Turnos *&n,info_turnos &y){
    int f,s=0;
	f=y.h*1000+y.d*100+y.m; //fecha
	y.f=f;
	Turnos *aux1=buscarTURNf(n,y.f);
	Turnos *aux2=buscarTURNID(n,y.id_psub);
	if(aux1==NULL&&aux2==NULL){
	InsertarOrdenado(n,y);
	s=1;
}
if(aux2!=NULL){
	s=2;
	}
if(aux1!=NULL&&aux2==NULL){
	s=0;
	}
return s;
}

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
	
	return opc;
}

void nuevoPaciente(){
	Paciente x;
	FILE *a=fopen("PACIENTES.bin","rb+");
	cout << "Ingrese id del paciente" << endl;
	cin >> x.id_paciente;
	cout << "Ingrese nombre del paciente" << endl;
	cin >> x.nomb_P;
	cout << "Ingrese apellido del paciente" << endl;
	cin >> x.ape_P;
	cout << "Ingrese edad del paciente" << endl;
	cin >> x.edad;
	cout << "Ingrese dni del paciente" << endl;
	cin >> x.dni;
	cout << "Ingrese telefono del paciente" << endl;
	cin >> x.telefono;
	fwrite(&x,sizeof(Paciente),1,a);
	fclose(a);
return;	
}

void nuevoTurno(Lista_M *&lista){
Lista_M *aux;
info_turnos m;
int i=0, j=0, b=0;
cout << "Ingrese id del medico a atenderse" << endl;
cin >> i;
aux=Buscar_ID(lista,i);
if(aux!=NULL){ // m no tiene nada asignado entonces sería 1 aunque el valor mas bajo de la lista sea por ej 2. Declarar m.
	m.id_turno++;
	}
do{
	
cout << " ingrese hora del turno" << endl;
cin >> m.h;
cout << " ingrese dia del turno" << endl;
cin >> m.d;
cout << " ingrese mes del turno" << endl;
cin >> m.m;
m.estatus='P';
cout << " ingrese id del paciente" << endl;
cin >> m.id_psub;
b=InsertarSinRepetir(aux->x,m);
if(b==2){
cout << "El paciente ya tiene turno con el medico" << endl;
}
if(b==0){
	cout << "Turno ya ocupado, vuelva a ingresar en otro horario/dia/mes" << endl;
}
}while(b==0);
return;
}

void nuevoMedico(Lista_M *&lista){
Medicos h;
FILE *b=fopen("MEDICOS.bin","rb+");
	cout << "Ingrese id del medico" << endl;
	cin >> h.id_medico;
	cout << "Ingrese nombre del medico" << endl;
	cin >> h.nomb_M;
	cout << "Ingrese apellido del medico" << endl;
	cin >> h.ape_M;
	cout << "Ingrese matricula del medico" << endl;
	cin >> h.matricula;
	cout << "Ingrese id de la especdialidad del medico" << endl;
	cin >> h.id_especialidad;
	cout << "Ingrese disponibilidad diaria del medico" << endl;
	cin >> h.disponibilidad;
	cout << "Ingrese rango horaria del medico" << endl;
	cin >> h.rango;
	cout << "Ingrese tiempo de consulta en minutos" << endl;
	cin >> h.tiempo;
	fwrite(&h,sizeof(Medicos),1,b);
	fclose(b);
	InsertarOrdenadoM(lista,h.id_medico);
return;	
	
}

void ejecutarOpcion(int opc, Lista_M *&lista){
	switch(opc){
		case 1:
			nuevoPaciente();
			break;
		case 2:
			nuevoTurno(lista);
			break;
		case 3:
			nuevoMedico(lista);
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

void mostrarMenu(Lista_M *&lista){
	int opcion = -1;
	while(opcion != 0){
		//mostrar menu y recibir opcion
		opcion = imprimirMenu();
		//ejecutar la opcion 
		ejecutarOpcion(opcion, lista);
	}
}
