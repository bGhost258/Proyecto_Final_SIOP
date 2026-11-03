#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>
#include "concurrencia.h"

using namespace std;

// Mutex simulando semaforo binario, esto con su funcion especifica
int recursoCompartido = 50;
int estadoSemaforo = 1;       // 1 = Libre, 0 = Ocupado
int procesosEnColaEspera = 0; // Control visual de la cola de espera

static void pausarConcurrencia() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "Presione ENTER para continuar...";
    cin.get();
}

void menuConcurrencia() {
    int opcionSub;

    // Este es el ciclo de toda la simulacion.

    do {
        system("cls");
        cout << "========================================================================" << endl;
        cout << "   MODULO: CONCURRENCIA Y SINCRONIZACION (SEMAFOROS)" << endl;
        cout << "========================================================================" << endl;
        cout << "1. Simulacion de Exclusion Mutua (Seccion Critica con Semaforo Binario)" << endl;
        cout << "2. Regresar al menu principal" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcionSub)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcionSub == 1) {
            system("cls");
            cout << "\n========================================================================" << endl;
            cout << "              SIMULACION DE EXCLUSION MUTUA (SEMAFOROS)                 " << endl;
            cout << "========================================================================" << endl;
            cout << "Lanzando procesos paso a paso hacia la seccion critica..." << endl;

            recursoCompartido = 50; // Valor inicial
            estadoSemaforo = 1;
            procesosEnColaEspera = 0;
            pausarConcurrencia();

            // --- Proceso 1 ---
            system("cls");
            //  Esta parte de aqui muestra el momento especifico  en que solicita entrar a la seccion critica
            cout << "\n[Proceso 1] -> Solicita entrar (Ejecutando operacion wait())..." << endl;

            // Incrementar la cola de espera si el mutex esta ocupado.
            {
                // Seccion para conteo de cola de espera
                procesosEnColaEspera++;
                cout << "   [Cola de espera] Procesos esperando en la cola: " << procesosEnColaEspera << endl;
            }

            //  Semaforo binario: wait()
            cout << endl << " [SEMAFORO BINARIO] wait() exitoso. Proceso 1 adquirio el recurso." << endl;
            estadoSemaforo = 0;
            procesosEnColaEspera--; // El proceso ya entro, sale de la cola
            pausarConcurrencia();

            // Seccion critica  BASTANTE IMPORTANTE
            system("cls");
            cout << "========================================================================" << endl;
            cout << " >>> [INICIO DE SECCION CRITICA] -- Proceso 1" << endl;
            cout << "     Valor actual del recurso compartido: " << recursoCompartido << endl;
            recursoCompartido += 15; // Modificacion segura del recurso
            cout << "     Nuevo valor modificado en seccion critica: " << recursoCompartido << endl;
            cout << " <<< [FIN DE SECCION CRITICA] ---- Proceso 1" << endl;
            cout << "========================================================================" << endl;
            pausarConcurrencia();

            // Semaforo binario: signal() (liberacion del recurso)
            cout << "\n------------------------------------------------------------------------" << endl;
            cout << " [SEMAFORO BINARIO] signal() ejecutado. Proceso 1 libera el recurso." << endl;
            cout << "------------------------------------------------------------------------" << endl;
            estadoSemaforo = 1;
            pausarConcurrencia();

            // --- Proceso 2 ---
            system("cls");
            //  Esta parte de aqui muestra el momento especifico  en que solicita entrar a la seccion critica
            cout << "\n[Proceso 2] -> Solicita entrar (Ejecutando operacion wait())..." << endl;
            cout << endl << " [SEMAFORO BINARIO] wait() exitoso. Proceso 2 adquirio el recurso." << endl;
            estadoSemaforo = 0;
            pausarConcurrencia();

            system("cls");
            // Seccion critica  BASTANTE IMPORTANTE
            cout << "========================================================================" << endl;
            cout << " >>> [INICIO DE SECCION CRITICA] -- Proceso 2" << endl;
            cout << "     Valor actual del recurso compartido: " << recursoCompartido << endl;
            recursoCompartido += 15; // Modificacion segura del recurso
            cout << "     Nuevo valor modificado en seccion critica: " << recursoCompartido << endl;
            cout << " <<< [FIN DE SECCION CRITICA] ---- Proceso 2" << endl;
            cout << "========================================================================" << endl;

            //  Esta parte de aqui muestra el momento especifico  en que solicita entrar a la seccion critica
            cout << "\n[Proceso 3] -> Solicita entrar (Ejecutando operacion wait())..." << endl;
            // Incrementar la cola de espera si el mutex esta ocupado.
            {
                // Seccion para conteo de cola de espera
                procesosEnColaEspera++;
                cout << "   [Cola de espera] Procesos esperando en la cola: " << procesosEnColaEspera << endl;
            }
            pausarConcurrencia();

            // Semaforo binario: signal() (liberacion del recurso)
            cout << "\n------------------------------------------------------------------------" << endl;
            cout << " [SEMAFORO BINARIO] signal() ejecutado. Proceso 2 libera el recurso." << endl;
            cout << "------------------------------------------------------------------------" << endl;
            estadoSemaforo = 1;
            pausarConcurrencia();

            // --- Proceso 3 desbloqueado ---
            system("cls");
            //  Semaforo binario: wait()
            cout << endl << " [SEMAFORO BINARIO] wait() exitoso. Proceso 3 adquirio el recurso." << endl;
            // El proceso ya entro, por lo tanto sale de la cola de espera
            {
                // Seccion para conteo de cola de espera
                procesosEnColaEspera--;
                cout << "   [Cola de espera] Un proceso salio de la cola. Restantes en espera: " << procesosEnColaEspera << endl;
            }
            estadoSemaforo = 0;
            pausarConcurrencia();

            // Seccion critica  BASTANTE IMPORTANTE
            system("cls");
            cout << "========================================================================" << endl;
            cout << " >>> [INICIO DE SECCION CRITICA] -- Proceso 3" << endl;
            cout << "     Valor actual del recurso compartido: " << recursoCompartido << endl;
            recursoCompartido += 15; // Modificacion segura del recurso
            cout << "     Nuevo valor modificado en seccion critica: " << recursoCompartido << endl;
            cout << " <<< [FIN DE SECCION CRITICA] ---- Proceso 3" << endl;
            cout << "========================================================================" << endl;
            pausarConcurrencia();

            // Semaforo binario: signal() (liberacion del recurso)
            cout << "\n------------------------------------------------------------------------" << endl;
            cout << " [SEMAFORO BINARIO] signal() ejecutado. Proceso 3 libera el recurso." << endl;
            cout << "------------------------------------------------------------------------" << endl;
            estadoSemaforo = 1;

            cout << "\nTodos los procesos ejecutaron su seccion critica de forma sincronizada." << endl;
            pausarConcurrencia();

        }
        else if (opcionSub == 2) {
            cout << "\nRegresando al menu principal..." << endl;
        }
        else {
            cout << "\nOpcion invalida." << endl;
            pausarConcurrencia();
        }

    } while (opcionSub != 2);
}