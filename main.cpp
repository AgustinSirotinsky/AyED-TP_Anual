#include <iostream>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>

using namespace std;

struct Paciente
{
	int id_paciente;
	char nomb_P[15];
	char ape_P[15];
	int edad;
	int dni;
	int telefono;
};

struct Medicos
{
	int id_medico;
	char nomb_M[15];
	char ape_M[15];
	int matricula;
	int id_especialidad;
	int disponibilidad; // secuencia numerica 7 dias 1234567, 1 es domingo
	int rango;			// De 00 a 24
	int tiempo;
};

struct Especialidades
{
	int id_especialidades;
	char descrip[20];
};

struct info_turnos
{
	int id_turno;
	int h;
	int d;
	int m;
	char estatus;
	int id_psub;
	int f; // fecha
};

struct Turnos
{
	info_turnos info;
	Turnos *sgte = NULL;
};

struct Lista_M
{
	int id_listM;
	Turnos *x = NULL;
	Lista_M *sgte = NULL;
};

void carga(Paciente y, Medicos j, Especialidades v[], char ruta1[], char ruta2[], Lista_M *&lista);
Lista_M *Buscar_ID(Lista_M *lista, int i);
Turnos *buscarTURNf(Turnos *n, int i);
Turnos *buscarTURNID(Turnos *n, int i);
void InsertarOrdenado(Turnos *&n, info_turnos y);
void InsertarOrdenadoM(Lista_M *&lista, int i);
int InsertarSinRepetir(Turnos *&n, info_turnos &y);
int imprimirMenu();
void ejecutarOpcion(int opc, Lista_M *&lista);
void mostrarMenu(Lista_M *&lista, Especialidades vec[]);
void nuevoPaciente();
void nuevoTurno(Lista_M *&lista);
void nuevoMedico(Lista_M *&lista);
void actualizarStatus(Lista_M *&lista);
void buscarMES(Turnos *n, int i);
void listarTurnosPendientes(Lista_M *&lista);
void listarAtencionesEfectivas(Lista_M *&lista);
void listarCancelaciones(Lista_M *&lista, Especialidades vec[]);
//Paciente apareoP(char ruta1[], int id);
Paciente apareoP(FILE *a, int id);
//Medicos apareoM(char ruta2[], int id);
Medicos apareoM(FILE *b, int id);
int apareoE(int id, Especialidades vec[]);
int buscarMayor(Lista_M *&lista);
void carga_T(Lista_M *&lista, info_turnos m);

int main(int argc, char **argv)
{
	Paciente y;
	Medicos j;
	int z = -1;
	info_turnos m;
	Especialidades v[20];
	char ruta1[] = "PACIENTES.bin";
	char ruta2[] = "MEDICOS.bin";
	Lista_M *lista = NULL;
	InsertarOrdenadoM(lista, 1);
	InsertarOrdenadoM(lista, 2);
	InsertarOrdenadoM(lista, 3);

	carga(y, j, v, ruta1, ruta2, lista);
	carga_T(lista, m);
	mostrarMenu(lista, v);

	return 0;
}

void carga(Paciente y, Medicos j, Especialidades v[], char ruta1[], char ruta2[], Lista_M *&lista)
{ // Cargar en la lista
	Lista_M *aux;
	aux = lista;
	FILE *a = fopen(ruta1, "rb+");
	FILE *b = fopen(ruta2, "rb+");
	y.id_paciente = 1;
	strcpy(y.nomb_P, "Julian");
	strcpy(y.ape_P, "Novoa");
	y.dni = 43182547;
	y.edad = 22;
	y.telefono = 42256758;
	fwrite(&y, sizeof(Paciente), 1, a);
	y.id_paciente = 2;
	strcpy(y.nomb_P, "Gabriel");
	strcpy(y.ape_P, "Roldan");
	y.dni = 43184587;
	y.edad = 42;
	y.telefono = 42867890;
	fwrite(&y, sizeof(Paciente), 1, a);
	y.id_paciente = 3;
	strcpy(y.nomb_P, "Tomas");
	strcpy(y.ape_P, "Rodriguez");
	y.dni = 45098765;
	y.edad = 30;
	y.telefono = 43567435;
	fwrite(&y, sizeof(Paciente), 1, a);
	strcpy(j.nomb_M, "Alejo");
	strcpy(j.ape_M, "Ortega");
	j.matricula = 347;
	j.id_medico = 1;
	j.id_especialidad = 3;
	j.disponibilidad = 2345;
	j.rango = 1020;
	j.tiempo = 45;
	fwrite(&j, sizeof(Medicos), 1, b);
	strcpy(j.nomb_M, "Franco");
	strcpy(j.ape_M, "Diaz");
	j.matricula = 496;
	j.id_medico = 2;
	j.id_especialidad = 7;
	j.disponibilidad = 34567;
	j.rango = 1019;
	j.tiempo = 30;
	fwrite(&j, sizeof(Medicos), 1, b);
	strcpy(j.nomb_M, "Matias");
	strcpy(j.ape_M, "Lopez");
	j.matricula = 987;
	j.id_medico = 3;
	j.id_especialidad = 16;
	j.disponibilidad = 12456;
	j.rango = 1119;
	j.tiempo = 60;
	fwrite(&j, sizeof(Medicos), 1, b);
	fclose(a);
	fclose(b);

	for (int i = 0; i < 20; i++)
	{
		v[i].id_especialidades = i + 1;
	}
	strcpy(v[0].descrip, "Odontologia");
	strcpy(v[1].descrip, "Pediatria");
	strcpy(v[2].descrip, "Kinesiologia");
	strcpy(v[3].descrip, "Dermatologia");
	strcpy(v[4].descrip, "Ginecologia");
	strcpy(v[5].descrip, "Cardiologia");
	strcpy(v[6].descrip, "Coloproctologia");
	strcpy(v[7].descrip, "Infectologia");
	strcpy(v[8].descrip, "Traumatologia");
	strcpy(v[9].descrip, "Neurologia");
	strcpy(v[10].descrip, "Hepatologia");
	strcpy(v[11].descrip, "Inmunologia");
	strcpy(v[12].descrip, "Gastroenterologia");
	strcpy(v[13].descrip, "Anestesiologia");
	strcpy(v[14].descrip, "Oncologia");
	strcpy(v[15].descrip, "Toxicologia");
	strcpy(v[16].descrip, "Urologia");
	strcpy(v[17].descrip, "Neumologia");
	strcpy(v[18].descrip, "Obstetricia");
	strcpy(v[19].descrip, "Endocrinologia");
	return;
}

Lista_M *Buscar_ID(Lista_M *lista, int i)
{
	Lista_M *q = lista;
	while (q != NULL && q->id_listM != i)
	{
		q = q->sgte;
	}
	return q;
}

Turnos *buscarTURNf(Turnos *n, int i)
{
	Turnos *q = n;
	while (q != NULL && q->info.f != i)
	{
		q = q->sgte;
	}
	return q;
}

Turnos *buscarTURNID(Turnos *n, int i)
{
	Turnos *q = n;
	while (q != NULL && q->info.id_psub != i)
	{
		q = q->sgte;
	}
	return q;
}

void buscarMES(Turnos *n, int i)
{
	Turnos *q = n;
	while (q != NULL && q->info.m != i)
	{
		q = q->sgte;
	}
	cout << "ID PACIENTE:		ID TURNO:		HORA:		DIA:		MES:		ESTADO:" << endl;
	while (q!=NULL && q->info.m == i)
	{
		if (q->info.estatus == 'P')
		{
			cout << q->info.id_psub << "		" << q->info.id_turno << "		" << q->info.h << "			" << q->info.d << "		" << q->info.m << "			" << q->info.estatus << endl;
		}

		q = q->sgte;
	}
	return;
}

void cantMES(Lista_M *lista, int mes)
{
	Lista_M *aux = lista;
	int c = 0;
	while (aux != NULL)
	{
		while (aux->x != NULL && aux->x->info.m != mes)
		{
			aux->x = aux->x->sgte;
		}
		while (aux->x != NULL && aux->x->info.m == mes)
		{
			if (aux->x->info.estatus == 'A')
			{
				c++;
			}

			aux->x = aux->x->sgte;
		}
		cout << "CANT DE TURNOS ATENDIDOS DE ID MEDICO " << aux->id_listM << ": " << c << endl;
		aux = aux->sgte;
	}
	return;
}

Paciente apareoP(FILE *a, int id) //char ruta1[]
{
	Paciente y;
	//FILE *a = fopen(ruta1, "rb");
	//fread(&y, sizeof(Paciente), 1, a);
	while (fread(&y, sizeof(Paciente), 1, a))
	{
		fread(&y, sizeof(Paciente), 1, a);
		if (y.id_paciente != id)
		{
			fread(&y, sizeof(Paciente), 1, a);
		}
		else
		{
			fseek(a, sizeof(Paciente), SEEK_END);
		}
	}
	//fclose(a);
	return y;
}

Medicos apareoM(FILE *b, int id)
{
	Medicos y;
	//FILE *a = fopen(ruta2, "rb");
	while (fread(&y, sizeof(Medicos), 1, b))
	{
		if (y.id_medico != id)
		{
			fread(&y, sizeof(Medicos), 1, b);
		}
		else
		{
			fseek(b, sizeof(Medicos), SEEK_END);
		}
	}
	//fclose(a);
	return y;
}

int apareoE(int id, Especialidades vec[])
{
	int i = 0;
	while (vec[i].id_especialidades != id)
	{
		i++;
	}
	return i;
}

void InsertarOrdenado(Turnos *&n, info_turnos y)
{

	Turnos *p = new Turnos();
	p->info = y;
	p->sgte = NULL;
	if (n == NULL || y.f < n->info.f)
	{
		p->sgte = n;
		n = p;
	}
	else
	{
		Turnos *q = n;
		while (q->sgte != NULL && q->sgte->info.f < y.f)
		{
			q = q->sgte;
		}
		p->sgte = q->sgte;
		q->sgte = p;
	}
	return;
}

void InsertarOrdenadoM(Lista_M *&lista, int i)
{
	Lista_M *p = new Lista_M();
	p->id_listM = i;
	p->sgte = NULL;
	if (lista == NULL || i < lista->id_listM)
	{
		p->sgte = lista;
		lista = p;
	}
	else
	{
		Lista_M *q = lista;
		while (q->sgte != NULL && q->sgte->id_listM < i)
		{
			q = q->sgte;
		}
		p->sgte = q->sgte;
		q->sgte = p;
	}
	return;
}

int InsertarSinRepetir(Turnos *&n, info_turnos &y)
{
	int f, s = 0;
	f = y.h * 1000 + y.d * 100 + y.m; // fecha
	y.f = f;
	Turnos *aux1 = buscarTURNf(n, y.f);
	Turnos *aux2 = buscarTURNID(n, y.id_psub);

	if (aux1 == NULL && aux2 == NULL)
	{

		InsertarOrdenado(n, y);
		s = 1;
	}
	if (aux2 != NULL)
	{
		s = 2;
	}
	if (aux1 != NULL && aux2 == NULL)
	{
		s = 0;
	}
	return s;
}

void carga_T(Lista_M *&lista, info_turnos m)
{
	Turnos *aux = NULL;
	int z = -1;
	aux = lista->x;
	m.h = 20;
	m.d = 24;
	m.m = 10;
	m.estatus = 'P';
	m.id_psub = 2;
	z = InsertarSinRepetir(aux, m);
	if (z == 1)
	{
		cout << "carga de turno correcta" << endl;
	}
	aux = lista->sgte->x;
	m.h = 13;
	m.d = 17;
	m.m = 11;
	m.estatus = 'P';
	m.id_psub = 3;
	z = InsertarSinRepetir(aux, m);
	if (z == 1)
	{
		cout << "carga de turno correcta" << endl;
	}
	aux = lista->sgte->x;
	m.h = 11;
	m.d = 29;
	m.m = 10;
	m.estatus = 'P';
	m.id_psub = 1;
	z = InsertarSinRepetir(aux, m);
	if (z == 1)
	{
		cout << "carga de turno correcta" << endl;
	}
	return;
}

int imprimirMenu()
{

	cout << endl;
	cout << " ** MENU **" << endl;
	cout << endl;
	cout << "  ALTA" << endl;
	cout << "    1- NUEVO PACIENTE" << endl; // Cargar en el archivo
	cout << "    2- NUEVO TURNO" << endl;	 // Carcar sublista de turnos
	cout << "    3- NUEVO MEDICO" << endl;	 // Cargar un medico
	cout << endl;
	cout << "  ACTUALIZACIONES" << endl;
	cout << "    4- ACTUALIZAR STATUS" << endl;
	cout << endl;
	cout << "  LISTADO" << endl;
	cout << "    5- TURNOS PENDIENTES" << endl;				// Ingresar mes e idmedico y muestra por pantalla la lista
	cout << "    6- CANTIDAD ATENCIONES EFECTIVAS" << endl; // Contador de todos los turnos atendidos
	cout << "    7- CANCELACIONES" << endl;					// Ingresar nombre del paciente, medico, especialidad y dia y mostar por pantalla la lista
	cout << endl;

	int opc = -1;
	cout << "Ingrese una opcion: ";
	cin >> opc;
	cout << endl;

	return opc;
}

void nuevoPaciente()
{
	Paciente x;
	FILE *a = fopen("PACIENTES.bin", "ab+");
	cout << "Ingrese id del paciente (numerico)" << endl;
	cin >> x.id_paciente;
	cout << "Ingrese nombre del paciente" << endl;
	cin >> x.nomb_P;
	cout << "Ingrese apellido del paciente" << endl;
	cin >> x.ape_P;
	cout << "Ingrese edad del paciente" << endl;
	cin >> x.edad;
	cout << "Ingrese dni del paciente (sin puntos)" << endl;
	cin >> x.dni;
	cout << "Ingrese telefono del paciente" << endl;
	cin >> x.telefono;
	fwrite(&x, sizeof(Paciente), 1, a);
	fclose(a);
	cout << "PACIENTE CARGADO CORRECTAMENTE" << endl;
	return;
}

int buscarMayor(Lista_M *&lista)
{
	Lista_M *aux = lista;
	int mayor = 0;
	while (aux != NULL)
	{
		while (aux->x != NULL)
		{
			if (aux->x->info.id_turno > mayor)
			{
				mayor = aux->x->info.id_turno;
			}

			aux->x = aux->x->sgte;
		}
		aux = aux->sgte;
	}

	return mayor;
}
void nuevoTurno(Lista_M *&lista)
{
	Lista_M *aux;
	info_turnos m;
	int i = 0, j = 0, b = -1, z = 0;
	do
	{

		cout << "Ingrese id del medico a atenderse (numerico)" << endl;
		cin >> i;
		aux = Buscar_ID(lista, i);
		if (aux == NULL)
		{
			cout << "Id de medico invalido, reintentar" << endl;
		}
	} while (aux == NULL);
	z = buscarMayor(lista);
	do
	{
		cout << "Ingrese hora del turno (HH)" << endl;
		cin >> m.h;
		cout << "Ingrese dia del turno (DD)" << endl;
		cin >> m.d;
		cout << "Ingrese mes del turno (MM)" << endl;
		cin >> m.m;
		m.estatus = 'P';
		cout << "Ingrese id del paciente (numerico)" << endl;
		cin >> m.id_psub;
		z++;
		m.id_turno = z;
		b = InsertarSinRepetir(aux->x, m);
		if (b == 2)
		{
			cout << "El paciente ya tiene turno con el medico" << endl;
		}
		if (b == 0)
		{
			cout << "Turno ya ocupado, vuelva a ingresar en otro horario/dia/mes" << endl;
		}
		if (b == 1)
		{
			cout << "TURNO CARGADO CORRECTAMENTE" << endl;
		}

	} while (b == 0);
	return;
}

void nuevoMedico(Lista_M *&lista) // Salta ingresos por la cant de caracteres ingresados
{
	Medicos h;
	FILE *b = fopen("MEDICOS.bin", "ab+");
	cout << "Ingrese id del medico" << endl;
	cin >> h.id_medico;
	cout << "Ingrese nombre del medico" << endl;
	cin >> h.nomb_M;
	cout << "Ingrese apellido del medico" << endl;
	cin >> h.ape_M;
	cout << "Ingrese matricula del medico" << endl;
	cin >> h.matricula;
	cout << "Ingrese id de la especialidad del medico" << endl;
	cin >> h.id_especialidad;
	cout << "Ingrese disponibilidad diaria del medico" << endl;
	cin >> h.disponibilidad;
	cout << "Ingrese rango horario del medico (iiff)" << endl;
	cin >> h.rango;
	cout << "Ingrese tiempo de consulta en minutos" << endl;
	cin >> h.tiempo;
	fwrite(&h, sizeof(Medicos), 1, b);
	fclose(b);
	InsertarOrdenadoM(lista, h.id_medico);
	cout << "MEDICO CARGADO CORRECTAMENTE" << endl;
	return;
}

void actualizarStatus(Lista_M *&lista)
{
	int em, ep;
	Lista_M *aux1;
	Turnos *aux2;
	char d;
	do
	{
		cout << "Ingrese id de medico a actualizar sus turnos" << endl;
		cin >> em;
		aux1 = Buscar_ID(lista, em);
		if (aux1 == NULL)
		{
			cout << "No se encontro el id del medico, reintentar" << endl;
		}
	} while (aux1 == NULL);

	cout << "Ingrese id de paciente a actualizar estado de su turno" << endl;
	cin >> ep;
	aux2 = buscarTURNID(aux1->x, ep);
	if (aux2 == NULL)
	{
		cout << "No se encontro el id del paciente, reintentar" << endl;
		return;
	}
	do
	{
		cout << "Ingrese el estado del turno actual (P-A-C-X)" << endl;
		cin >> d;
		if (d != 'P' && d != 'A' && d != 'C' && d != 'X')
		{
			cout << "Caracter invalido, reintentar" << endl;
		}
	} while (d != 'P' && d != 'A' && d != 'C' && d != 'X');
	aux1->x = aux2;
	aux1->x->info.estatus = d;
	cout << "Actualizado exitosamente" << endl;
	return;
}

void listarTurnosPendientes(Lista_M *&lista)
{
	int em, mes;
	Lista_M *aux1;
	char d;
	do
	{
		cout << "Ingrese id de medico para listar turnos pendientes" << endl;
		cin >> em;
		aux1 = Buscar_ID(lista, em);
		if (aux1 == NULL)
		{
			cout << "No se encontro el id del medico, reintentar" << endl;
		}
	} while (aux1 == NULL);
	cout << "Ingrese mes (numerico)" << endl;
	cin >> mes;
	buscarMES(aux1->x, mes);
	return;
}

void listarAtencionesEfectivas(Lista_M *&lista)
{
	Lista_M *aux;
	int mes;
	cout << "Ingrese mes (numerico)" << endl;
	cin >> mes;
	aux = lista;
	cantMES(aux, mes);
	return;
}

void listarCancelaciones(Lista_M *&lista, Especialidades vec[])
{
	Lista_M *aux = lista;
	FILE *a = fopen("PACIENTES.bin", "rb");
	FILE *b = fopen("MEDICOS.bin", "rb");
	Paciente auxp;
	Medicos auxm;
	char ruta1[] = "PACIENTES.bin";
	char ruta2[] = "MEDICOS.bin";
	int mes, i;
	cout << "Ingrese el mes a listar sus cancelaciones" << endl;
	cin >> mes;
	fread(&auxp, sizeof(Paciente), 1, a);
	fread(&auxm, sizeof(Medicos), 1, b);
	cout << "NOMBRE DEL PACIENTE:	NOMBRE DEL MEDICO:	ESPECIALIDAD:    DIA DE ATENCION:" << endl;
	while (aux != NULL)
	{
		while (aux->x != NULL && aux->x->info.m != mes)
		{
			aux->x = aux->x->sgte;
		}
		while (aux->x != NULL && aux->x->info.m == mes)
		{
			if (aux->x->info.estatus == 'C')
			{
				auxp = apareoP(a, aux->x->info.id_psub);
				auxm = apareoM(b, aux->id_listM);
				i = apareoE(auxm.id_especialidad, vec);
				cout << auxp.nomb_P << "		" << auxm.nomb_M << "		"<< vec[i].descrip << "		"<< auxm.disponibilidad<< endl;
			}

			aux->x = aux->x->sgte;
		}
		aux = aux->sgte;
	}
	fclose(a);
	fclose(b);
	return;
}

void ejecutarOpcion(int opc, Lista_M *&lista, Especialidades vec[])
{
	switch (opc)
	{
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
		actualizarStatus(lista);
		break;
	case 5:
		listarTurnosPendientes(lista);
		break;
	case 6:
		listarAtencionesEfectivas(lista);
		break;
	case 7:
		listarCancelaciones(lista, vec);
		break;
	default:
		break;
	}
}

void mostrarMenu(Lista_M *&lista, Especialidades vec[])
{
	int opcion = -1;
	while (opcion != 0)
	{
		// mostrar menu y recibir opcion
		opcion = imprimirMenu();
		// ejecutar la opcion
		ejecutarOpcion(opcion, lista, vec);
	}
}
