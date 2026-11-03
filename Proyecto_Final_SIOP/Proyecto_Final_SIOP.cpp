#include <iostream>
#include "ProcesoRR.h"
#include "Memoria.h"
#include "concurrencia.h"
#include "deadlock.h"


using namespace std;

//void menuProcesos(); // Este es el de ProcesosRR
//void menuMemoria();  // Este es el de Memoria
//void menuConcurrencia(); // Este esta en concurrencia.cpp
//void menuDeadlock(); // Este esta en deadlock.cpp

int main() {
    int opcion = 0;

    do {
		system("cls");
        // Inicio del ciclo y menu principal del simulador
        cout << "\n=========================================" << endl;
        cout << "   SIMULADOR DE KERNEL - SISTEMAS OPERATIVOS" << endl;
        cout << "=========================================" << endl;
        cout << "1. Gestion y Planificacion de Procesos (Round Robin)" << endl;
        cout << "2. Gestion de Memoria" << endl;
        cout << "3. Concurrencia y Sincronizacion" << endl;
        cout << "4. Interbloqueo (Deadlock)" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            system("cls");
            cout << "\n--- Modulo de Procesos ---" << endl;
            menuProcesos();
            break;
        case 2:

            system("cls");
            cout << "\n--- Modulo de Memoria ---" << endl;
            menuMemoria();
            break;
        case 3:

            system("cls");
            cout << "\n--- Modulo de Concurrencia ---" << endl;
            menuConcurrencia();
            break;
        case 4:
            system("cls");

            cout << "\n--- Modulo de Interbloqueo (Deadlock) ---" << endl;
            menuDeadlock();
            break;

        case 5:
            cout << "Saliendo del simulador..." << endl;
            break;

        default:

            cout << "Opcion invalida. Intente de nuevo." << endl;
        }

        cin.ignore();
    } while (opcion != 5);

    return 0;
}

// Antes aqui teniamos las funciones Dummy del proyecto, ahora ya estan en cada file respectivo.



