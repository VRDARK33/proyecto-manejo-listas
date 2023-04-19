#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <iterator>
#include <sstream>
using namespace std;



/*
Objetivo: Crear una estructura llamada Pasajeros
Parametros:
    NroDeVuelo: Numero de vuelo
    Cedula: Cedula del pasajero
    NombrePersona: Nombre del pasajero
    Telefono: Telefono del pasajero
    estado: Estado del pasajero

*/

struct Pasajeros{
    string NroDeVuelo;
    string Cedula;
    string NombrePersona;
    string Telefono;
    int estado;

};typedef struct Pasajeros *ptrPasajero;

/*
Objetivo: Crear una estructura llamada Vuelos
Parametros:
    Nro_de_vuelo: Numero de vuelo
    Origen: Origen del vuelo
    Destino: Destino del vuelo
    Matricula_avion: Matricula del avion
    Nombre_piloto: Nombre del piloto
    Hora_vuelo: Hora del vuelo
    Fecha_vuelo: Fecha del vuelo
    Estado: Estado del vuelo
    Lista_pasajeros: Lista de pasajeros del vuelo
*/

struct Vuelos{
    string NroDeVuelo;
    string Origen;
    string Destino;
    string MatriculaAvion;
    string NombrePiloto;
    string HoraVuelo;
    string FechaVuelo;
    int Estado;
    list<void*> ListaPasajeros;

};typedef struct Vuelos *ptrVuelo;

/*
Objetivo: Crear una estructura llamada Aerolinea
Parametros:
    ListaVuelos: Lista de vuelos de la aerolinea
    ListaPasajeros: Lista de pasajeros de la aerolinea
*/

struct Aerolinea{
    list<void*> ListaVuelos;
    list<void*> ListaPasajeros;

};typedef struct Aerolinea *ptrAerolinea;

void ActualizarInformacion(ptrAerolinea aerolinea)
{
	ofstream archivo, archivo1;
	archivo.open("vuelos.txt", fstream::out);
	archivo1.open("pasajeros.txt", fstream::out);


    for(auto it = aerolinea->ListaVuelos.begin(); it != aerolinea->ListaVuelos.end(); ++it){
        ptrVuelo vuelo = reinterpret_cast<ptrVuelo>(*it);
        archivo << vuelo->NroDeVuelo << "," << vuelo->Estado << "," << vuelo->Origen << "," << vuelo->Destino << "," << vuelo->MatriculaAvion << "," << vuelo->NombrePiloto << "," << vuelo->HoraVuelo << "," << vuelo->FechaVuelo << "\n";    
    }

    for(auto it = aerolinea->ListaPasajeros.begin(); it != aerolinea->ListaPasajeros.end(); ++it) {
        ptrPasajero pasajero = reinterpret_cast<ptrPasajero>(*it);
        archivo1 << pasajero->NroDeVuelo << "," << pasajero->estado << "," << pasajero->Cedula << "," << pasajero->NombrePersona << "," << pasajero->Telefono << "\n";
    }

	archivo.close();
    archivo1.close();
}

void LeerInformacion(ptrAerolinea aerolinea,string NombreArchivo, string NombreArchivo1)
{
	ifstream archivo(NombreArchivo.c_str());
	ifstream archivo1(NombreArchivo1.c_str());
	string linea;

    if (archivo.is_open() && archivo1.is_open()){
        string NroDeVuelo, Origen, Destino, MatriculaAvion, NombrePiloto, HoraVuelo, FechaVuelo, Estado, NroDeVueloPasajero, Cedula, NombrePersona, Telefono, EstadoPasajero;

        while(getline(archivo, linea)){
            stringstream input_stringstream(linea);
            getline(input_stringstream, NroDeVuelo, ',');
            getline(input_stringstream, Estado, ',');
            getline(input_stringstream, Origen, ',');
            getline(input_stringstream, Destino, ',');
            getline(input_stringstream, MatriculaAvion, ',');
            getline(input_stringstream, NombrePiloto, ',');
            getline(input_stringstream, HoraVuelo, ',');
            getline(input_stringstream, FechaVuelo, ',');
            
            ptrVuelo vuelo = new Vuelos;
            vuelo->NroDeVuelo = NroDeVuelo;
            vuelo->Origen = Origen;
            vuelo->Destino = Destino;
            vuelo->MatriculaAvion = MatriculaAvion;
            vuelo->NombrePiloto = NombrePiloto;
            vuelo->HoraVuelo = HoraVuelo;
            vuelo->FechaVuelo = FechaVuelo;
            vuelo->Estado = stoi(Estado);
            vuelo->ListaPasajeros = list<void*>();

            aerolinea->ListaVuelos.push_back(vuelo);
      
        }

        while(getline(archivo1, linea)){
            stringstream input_stringstream(linea);
            getline(input_stringstream, NroDeVueloPasajero, ',');
            getline(input_stringstream, EstadoPasajero, ',');
            getline(input_stringstream, Cedula, ',');
            getline(input_stringstream, NombrePersona, ',');
            getline(input_stringstream, Telefono, ',');
                
            ptrPasajero pasajero = new Pasajeros;
            pasajero->NroDeVuelo = NroDeVueloPasajero;
            pasajero->Cedula = Cedula;
            pasajero->NombrePersona = NombrePersona;
            pasajero->Telefono = Telefono;
            pasajero->estado = stoi(EstadoPasajero);

            aerolinea->ListaPasajeros.push_back(pasajero);
        }
    }

    for(auto it = aerolinea->ListaVuelos.begin(); it != aerolinea->ListaVuelos.end(); ++it){
        ptrVuelo vuelo = reinterpret_cast<ptrVuelo>(*it);
        for(auto it = aerolinea->ListaPasajeros.begin(); it != aerolinea->ListaPasajeros.end(); ++it) {
            ptrPasajero pasajero = reinterpret_cast<ptrPasajero>(*it);
            if(vuelo->NroDeVuelo == pasajero->NroDeVuelo){
                vuelo->ListaPasajeros.push_back(pasajero);
            }
        }
    }

    archivo.close();
    archivo1.close(); 
}

/*
Objetivo: Funcion que permita crear un dato de tipo Vuelo y
llenar todos los campos a excepción de la lista de pasajeros. 
Este vuelo se almacena en la lista de vuelos (ListaVuelos) de la
estructura Aerolinea utilizando la libreria estandar de c++ (list)
Parametros:
    ptrVuelo vuelo;
Nombre función: void AdicionarVuelos
*/

// A function to add flights to a airline
// @param aerolinea The airline where the flights will be added
void AdicionarVuelos(ptrAerolinea aerolinea) {
    // Allocate memory for a new flight
    ptrVuelo vuelo = new Vuelos;

    // Get the flight number
    cout << "\n\t\t Ingrese el numero de vuelo: ";
    cin >> vuelo->NroDeVuelo;
    cin.ignore();

    // Get the origin
    cout << "\t\t Ingrese el origen del vuelo: ";
    cin >> vuelo->Origen;
    cin.ignore();

    // Get the destination
    cout << "\t\t Ingrese el destino del vuelo: ";
    cin >> vuelo->Destino;
    cin.ignore();

    // Get the plane's registration number
    cout << "\t\t Ingrese la matricula del avion: ";
    cin >> vuelo->MatriculaAvion;
    cin.ignore();

    // Get the pilot's name
    cout << "\t\t Ingrese el nombre del piloto: ";
    cin >> vuelo->NombrePiloto;
    cin.ignore();

    // Get the flight time
    cout << "\t\t Ingrese la hora del vuelo: ";
    cin >> vuelo->HoraVuelo;
    cin.ignore();

    // Get the flight date
    cout << "\t\t Ingrese la fecha del vuelo: ";
    cin >> vuelo->FechaVuelo;
    cin.ignore();

    // Set the flight status to 0 (available)
    vuelo->Estado = 0;

    // Add the flight to the airline
    aerolinea->ListaVuelos.push_back(vuelo);
}


/*
Objetivo: Funcion que permita buscar en una lista un vuelo con la libreria list, dicho pasajero será
filtrado por su posicion en la lista y será retornado
Parametros:
    list<void*> lista;
    int PosicionVuelo;
Nombre función: ptrVuelo search_flight()    
*/

ptrVuelo search_flight(list<void*> lista, int PosicionVuelo){
    list<void*>::iterator it = lista.begin();
    advance(it, PosicionVuelo);
    ptrVuelo ptr = reinterpret_cast<ptrVuelo>(*it);

    if(ptr->Estado == 1)
        return search_flight(lista, PosicionVuelo+1);
    else{
        return ptr;
    }
}

/*
Objetivo: Funcion que permita acceder a un vuelo especificado por el usuario, dicho parametro sera la posicion del vuelo en la lista.
Luego, se almacenara un dato de tipo Pasajeros en la lista de pasajeros de la estructura vuelos (ListaPasajeros).
Parametros:
    ptrAerolinea aerolinea;
    int PosicionVuelo;
Nombre función: void AdicionarPasajeros
*/

void AdicionarPasajeros(ptrAerolinea aerolinea, int PosicionVuelo){
    ptrPasajero pasajero = new Pasajeros;
    ptrVuelo vuelo = search_flight(aerolinea->ListaVuelos,PosicionVuelo);
    pasajero->NroDeVuelo.assign(vuelo->NroDeVuelo);
    cout << "\t\t Ingrese la cedula del pasajero: ";
    cin >> pasajero->Cedula;
    cin.ignore();
    cout << "\t\t Ingrese el nombre del pasajero: ";
    cin >> pasajero->NombrePersona;
    cin.ignore();
    cout << "\t\t Ingrese el telefono del pasajero: ";
    cin >> pasajero->Telefono;
    cin.ignore();
    pasajero->estado = 0;
   
    vuelo->ListaPasajeros.push_back(pasajero);
    aerolinea->ListaPasajeros.push_back(pasajero);
}

/*
Objetivo: Crear una función que me permita acceder a todos los vuelos dentro
de la lista de vuelos en la estructura Aerolinea (ListaVuelos) y me los muestre en el siguiente formato:

1.
Nro de vuelo: 123
Origen: Bogota
Destino: Medellin
Matricula: 123ABC
Piloto: Juan Perez
Hora de vuelo: 12:00
Fecha de vuelo: 12/12/2012
Estado: 0

Parametros:
    ptrAerolinea aerolinea;
Nombre función: void MostrarVuelos
*/

void MostrarVuelos(ptrAerolinea aerolinea){
    int i = 1;
    for(list<void*>::iterator it = aerolinea->ListaVuelos.begin(); it != aerolinea->ListaVuelos.end(); it++){
        ptrVuelo vuelo = reinterpret_cast<ptrVuelo>(*it);
        cout << i << ".\n";
        cout << "\t Nro de vuelo: " << vuelo->NroDeVuelo << endl;
        cout << "\t Origen: " << vuelo->Origen << endl;
        cout << "\t Destino: " << vuelo->Destino << endl;
        cout << "\t Matricula: " << vuelo->MatriculaAvion << endl;
        cout << "\t Piloto: " << vuelo->NombrePiloto << endl;
        cout << "\t Hora de vuelo: " << vuelo->HoraVuelo << endl;
        cout << "\t Fecha de vuelo: " << vuelo->FechaVuelo << endl;
        cout << "\t Estado: " << vuelo->Estado << endl;
        i++;
    }
}




/*
Objetivo: Crear una función que me permita acceder a todos los vuelos dentro
de la lista de vuelos en la estructura Aerolinea (ListaVuelos) y me muestre aquellos vuelos
en los que el estado es igual a 0. Mostrarlos en el siguiente formato:

1.
Nro de vuelo: 123
Origen: Bogota
Destino: Medellin
Matricula: 123ABC
Piloto: Juan Perez
Hora de vuelo: 12:00
Fecha de vuelo: 12/12/2012
Estado: 0

Parametros:
    ptrAerolinea aerolinea;
Nombre función: void VuelosProgramados
*/

void VuelosProgramados(ptrAerolinea aerolinea){
    int i = 1;
    for(list<void*>::iterator it = aerolinea->ListaVuelos.begin(); it != aerolinea->ListaVuelos.end(); it++){
        ptrVuelo vuelo = reinterpret_cast<ptrVuelo>(*it);
        if(vuelo->Estado == 0){
            cout << i << ".\n";
            cout << " Nro de vuelo: " << vuelo->NroDeVuelo << endl;
            cout << " Origen: " << vuelo->Origen << endl;
            cout << " Destino: " << vuelo->Destino << endl;
            cout << " Matricula: " << vuelo->MatriculaAvion << endl;
            cout << " Piloto: " << vuelo->NombrePiloto << endl;
            cout << " Hora de vuelo: " << vuelo->HoraVuelo << endl;
            cout << " Fecha de vuelo: " << vuelo->FechaVuelo << endl;
            cout << " Estado: " << vuelo->Estado << endl;
            cout << endl;
            i++;
        }
    }
}

void VuelosRealizados(ptrAerolinea aerolinea){
    int i = 1;
    for(list<void*>::iterator it = aerolinea->ListaVuelos.begin(); it != aerolinea->ListaVuelos.end(); it++){
        ptrVuelo vuelo = reinterpret_cast<ptrVuelo>(*it);
        if(vuelo->Estado == 1){
            cout << i << ".\n";
            cout << " Nro de vuelo: " << vuelo->NroDeVuelo << endl;
            cout << " Origen: " << vuelo->Origen << endl;
            cout << " Destino: " << vuelo->Destino << endl;
            cout << " Matricula: " << vuelo->MatriculaAvion << endl;
            cout << " Piloto: " << vuelo->NombrePiloto << endl;
            cout << " Hora de vuelo: " << vuelo->HoraVuelo << endl;
            cout << " Fecha de vuelo: " << vuelo->FechaVuelo << endl;
            cout << " Estado: " << vuelo->Estado << endl;
            cout << endl;
            i++;
        }
    }
}





/*
Objetivo: Crear una función que me permita acceder a todos los pasajeros dentro de un vuelo
con el siguiente formato:

nro de vuelo: 123
Cedula: 123456789
Nombre: Juan Perez
Telefono: 123456789


Parametros:
    ptrAerolinea aerolinea;
    string NroDeVuelos;
Nombre función: void MostrarPasajeros
*/

void MostrarPasajeros(ptrAerolinea aerolinea, string NroDeVuelo){
    int i = 1;
    for(list<void*>::iterator it = aerolinea->ListaVuelos.begin(); it != aerolinea->ListaVuelos.end(); it++){
        ptrVuelo vuelo = reinterpret_cast<ptrVuelo>(*it);
        if((vuelo->NroDeVuelo.compare(NroDeVuelo))==0){
            for(list<void*>::iterator it2 = vuelo->ListaPasajeros.begin(); it2 != vuelo->ListaPasajeros.end(); it2++){
                ptrPasajero pasajero = reinterpret_cast<ptrPasajero>(*it2);
                cout << i << ".\n";
                cout << " Nro de vuelo: " << vuelo->NroDeVuelo << endl;
                cout << " Cedula: " << pasajero->Cedula << endl;
                cout << " Nombre: " << pasajero->NombrePersona << endl;
                cout << " Telefono: " << pasajero->Telefono << endl;
                cout << endl;
                i++;
            }
        }
    }
}

/*
Objetivo: Crear una que me permita buscar en una lista un pasajero, dicho pasajero será
filtrado por su número de cedulA y será retornado
Parametros:
    list<void*> lista;
    string cedula;
Nombre función: ptrPasajero search_passenger()
*/
ptrPasajero search_passenger(list<void*> lista, string cedula){
    for(auto it = lista.begin(); it != lista.end(); ++it) {
        ptrPasajero pasajero = reinterpret_cast<ptrPasajero>(*it);
        if((pasajero->Cedula.compare(cedula))==0){
            return pasajero;
        }
    }
    return NULL;
}


/*
Objetivo: crear una funcion que me permita acceder a todos los vuelos en los que un pasajero
se encuentra registrado, dicho pasajero será identificado por su número de cédula y se mostrará
en el siguiente formato:

nro de vuelo: 123
Origen: Guayaquil
Destino: Quito
Matricula: 123456
Piloto: Juan Perez
Hora de vuelo: 12:00
Fecha de vuelo: 12/12/2020
Estado: 0



Parametros:
    ptrAerolinea aerolinea;
    string cedula;
Nombre función: void VuelosPasajeros
*/

void VuelosPasajeros(ptrAerolinea aerolinea, string cedula){
    int i = 1;
    for(list<void*>::iterator it = aerolinea->ListaVuelos.begin(); it != aerolinea->ListaVuelos.end(); it++){
        ptrVuelo vuelo = reinterpret_cast<ptrVuelo>(*it);
        for(list<void*>::iterator it2 = vuelo->ListaPasajeros.begin(); it2 != vuelo->ListaPasajeros.end(); it2++){
            ptrPasajero pasajero = reinterpret_cast<ptrPasajero>(*it2);
            if((pasajero->Cedula.compare(cedula))==0){
                cout << i << ".\n";
                cout << " Nro de vuelo: " << vuelo->NroDeVuelo << endl;
                cout << " Origen: " << vuelo->Origen << endl;
                cout << " Destino: " << vuelo->Destino << endl;
                cout << " Matricula: " << vuelo->MatriculaAvion << endl;
                cout << " Piloto: " << vuelo->NombrePiloto << endl;
                cout << " Hora de vuelo: " << vuelo->HoraVuelo << endl;
                cout << " Fecha de vuelo: " << vuelo->FechaVuelo << endl;
                cout << " Estado: " << vuelo->Estado << endl;
                cout << endl;
                i++;
            }
        }
    }
}




/*
Objetivo: Crear una función que me permita acceder al estado de un vuelo en especifico, dicho vuelo
será identificado por su numero de vuelo y el estado será modificado a 1
Parametros:
    ptrAerolinea aerolinea;
    string NroDeVuelo;
Nombre función: void EstadoVuelo
*/

void EstadoVuelo(ptrAerolinea aerolinea, string NroDeVuelo){
    for(auto it = aerolinea->ListaVuelos.begin(); it != aerolinea->ListaVuelos.end(); ++it) {
        ptrVuelo vuelo = reinterpret_cast<ptrVuelo>(*it);
        if((vuelo->NroDeVuelo.compare(NroDeVuelo))==0){
            vuelo->Estado=1;
        }
    }
}

/*
Objetivo: Crear una función que me permita acceder al estado de un pasajero dentro de un vuelo en especifico, dicho vuelo
será identificado por su numero de vuelo, el pasajero será identificado por su cedula y el estado del pasajero será modificado a 1.
El vuelo será agregado a la lista de vuelos realizados del pasajero en concreto
Parametros:
    ptrAerolinea aerolinea;
    string NroDeVuelo;
    string cedula;
Nombre función: void EstadoPasajero
*/

void EstadoPasajero(ptrAerolinea aerolinea, string NroDeVuelo, string cedula){
    ptrPasajero pasajero = NULL;
    for(auto it = aerolinea->ListaVuelos.begin(); it != aerolinea->ListaVuelos.end(); ++it) {
        ptrVuelo vuelo = reinterpret_cast<ptrVuelo>(*it);
        if((vuelo->NroDeVuelo.compare(NroDeVuelo))==0){
            pasajero = search_passenger(aerolinea->ListaPasajeros, cedula);
            pasajero->estado = 1;
        }
    }                
}

/*crear una funcion llamada menu que tenga la siguiente lista de tesxtos por pantalla:
 1.crear archivo
 2.guardar archivo
 3.eliminar archivo
 4.Se debe poder adicionar vuelos.
 5.Adicionar pasajeros
 6.obtener listado
 7.info de pasajero
 8.estado del vuelo
 9.pasajeros abordo
 15.mostrar archivo
 11.salir
 */

void menu(){
    cout << "\n\t\t |-----------| Aerolinea |-----------|"<< endl;
    cout << "\n\t\t 1. Adicionar vuelos" << endl;
    cout << "\t\t 2. Lista de vuelos programados" << endl;
    cout << "\t\t 3. Lista de vuelos realizados" << endl;
    cout << "\t\t 4. Lista de vuelos." << endl;
    cout << "\t\t 5. Adicionar pasajeros" << endl;
    cout << "\t\t 6. Pasajeros de un vuelo" << endl;
    cout << "\t\t 7. Informacion vuelos de pasajero" << endl;
    cout << "\t\t 8. Estado del vuelo" << endl;
    cout << "\t\t 9. Estado del pasajero" << endl;
    cout << "\t\t 10. Salir" << endl;
}

int main(){
    int opcion;
    int eleccion, eleccion1;

    ptrAerolinea Aerolinea = new (struct Aerolinea);

    Aerolinea->ListaVuelos = list<void*>();
    Aerolinea->ListaPasajeros = list<void*>();
    
    LeerInformacion(Aerolinea, "vuelos.txt", "pasajeros.txt");

    do{
        menu();

        cout<<"\n\t\t Ingrese una opcion: ";
        cin>>opcion;

        cout<<endl;

        switch(opcion){
            case 1:
                cout<<"\n\n\t\t |-----------| ADICIONAR VUELOS |-----------| "<<endl;
                AdicionarVuelos(Aerolinea);
                break;

            case 2:
                cout<<"\n\n\t\t |-----------| LISTA DE VUELOS PROGRAMADOS |-----------| "<<endl;
                VuelosProgramados(Aerolinea);
                break;

            case 3:
                cout<<"\n\n\t\t |-----------| LISTA DE VUELOS REALIZADOS |-----------| "<<endl;
                VuelosRealizados(Aerolinea);
                break;

            case 4:
                if(Aerolinea->ListaVuelos.size() != 0){
                    cout<<"\n\n\t\t |-----------| LISTA DE VUELOS |-----------| "<<endl;
                    MostrarVuelos(Aerolinea);
                }
                else{
                    cout<<"\n\n\t\t |-----------| LISTA DE VUELOS |-----------| "<<endl;
                    cout<<"\n\n\t\t No hay vuelos programados, por favor adicione vuelos." << endl;
                }
                break;

            case 5:
                if(Aerolinea->ListaVuelos.size() != 0){
                    cout<<"\n\n\t\t |-----------| LISTA DE VUELOS |-----------| "<<endl;
                    VuelosProgramados(Aerolinea);
                    cout<<"\n\n\t\t |-----------| ADICIONAR PASAJEROS |-----------| "<<endl << endl;
                    cout<<"\n\n\t\t Seleccione un vuelo: ";
                    cin >> eleccion;
                    AdicionarPasajeros(Aerolinea, eleccion-1);
                }
                else{
                    cout<<"\n\n\t\t |-----------| ADICIONAR PASAJEROS |-----------| "<<endl << endl;
                    cout<<"\n\n\t\t No hay vuelos programados, por favor adicione vuelos." << endl;
                }
                break;

            case 6:
                if(Aerolinea->ListaVuelos.size() != 0){
                    cout<<"\n\n\t\t |-----------| LISTA DE VUELOS |-----------| "<<endl;
                    VuelosProgramados(Aerolinea);
                    cout<<"\n\n\t\t |-----------| PASAJEROS |-----------| "<<endl;
                    cout<< "\n\n\t\t Seleccione el numero de vuelo: ";
                    cin >> eleccion;
                    MostrarPasajeros(Aerolinea, to_string(eleccion));
                }
                else{
                    cout<<"\n\n\t\t |-----------| PASAJEROS |-----------| "<<endl;
                    cout<<"\n\n\t\t No hay vuelos programados, por favor adicione vuelos." << endl;
                }
                break;

            case 7:
                if(Aerolinea->ListaPasajeros.size() != 0){
                    cout<<"\n\n\t\t |-----------| BUSCAR PASAJERO |-----------| "<<endl;
                    cout<< "\n\n\t\t Escriba el numero de cedula del pasajero: ";
                    cin >> eleccion;
                    VuelosPasajeros(Aerolinea, to_string(eleccion));
                }
                else{
                    cout<<"\n\n\t\t |-----------| BUSCAR PASAJERO |-----------| "<<endl;
                    cout<<"\n\n\t\t No hay pasajeros registrados, por favor adicione pasajeros." << endl;
                }
                break;

            case 8:
                cout<<"\n\n\t\t |-----------| LISTA DE VUELOS |-----------| "<<endl;
                VuelosProgramados(Aerolinea);
                cout<<"\n\n\t\t |-----------| ESTADO DEL VUELO |-----------| "<<endl;
                cout<< "\n\n\t\t Seleccione el numero de vuelo: ";
                cin >> eleccion;
                EstadoVuelo(Aerolinea, to_string(eleccion));    
                break;

            case 9:
                cout<<"\n\n\t\t |-----------| LISTA DE VUELOS |-----------| "<<endl;
                VuelosProgramados(Aerolinea);
                cout<<"\n\n\t\t |-----------| ESTADO DE PASAJERO |-----------| "<<endl;
                cout<< "\n\n\t\t Seleccione el numero de vuelo: ";
                cin >> eleccion;
                cout<< "\n\n\t\t Escriba el numero de cedula del pasajero: ";
                cin >> eleccion1;
                EstadoPasajero(Aerolinea, to_string(eleccion), to_string(eleccion1));
                break;

            case 10:
                break;    

            default:
                cout<<"\n\n\t\t Opcion no valida"<<endl;
                break;
        }
        cout<<endl<<endl;
        system("pause | echo \t\tPresione cualquier tecla para continuar...");
        system("cls");
    }while(opcion!=10);

    ActualizarInformacion(Aerolinea);

    return 0;
}