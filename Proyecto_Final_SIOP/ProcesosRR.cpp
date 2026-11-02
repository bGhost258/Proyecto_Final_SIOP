#include <iostream>
#include "ProcesoRR.h"
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Estructura del PCB
struct PCB {
    int pid;
    string estado;
    int tamMemoria;
    int rafagaTotal;
    int rafagaRestante;
    int completionTime;
};

void menuProcesos() {
    vector<PCB> listaProcesos;
    vector<int> historialGantt;
    int opcionSub;
    const int QUANTUM = 3; // Quantum fijo q = 3

    do {
        system("cls");
        cout << "========================================================================" << endl;
        cout << "   MODULO: GESTION Y PLANIFICACION (RR)" << endl;
        cout << "========================================================================" << endl;
        cout << "1. Crear procesos y guardarlos" << endl;
        cout << "2. Mostrar tabla de estados y ejecutar Round Robin (q=3)" << endl;
        cout << "3. Ver Diagrama de Gantt (Historial de Ejecucion)" << endl;
        cout << "4. Regresar al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcionSub;

        if (opcionSub == 1) {
            system("cls");
            int n;
            cout << "Cuantos procesos desea crear?: ";
            cin >> n;

            listaProcesos.clear();
            historialGantt.clear();

            for (int i = 0; i < n; i++) {
                PCB p;
                p.pid = i + 1;
                p.estado = "Waiting";
                cout << "\n--- Configurando Proceso PID [" << p.pid << "] ---\n";
                cout << "Ingrese tamano en memoria (MB): ";
                cin >> p.tamMemoria;
                cout << "Ingrese tiempo requerido de procesador: ";
                cin >> p.rafagaTotal;
                p.rafagaRestante = p.rafagaTotal;
                p.completionTime = 0;

                listaProcesos.push_back(p);
            }
            cout << "\nProcesos creados y guardados exitosamente!" << endl;
            cout << "\nPresione ENTER para continuar...";
            cin.ignore();
            cin.get();

        }
        else if (opcionSub == 2) {
            if (listaProcesos.empty()) {
                cout << "[Advertencia] No hay procesos creados aun. Cree procesos primero (Opcion 1)." << endl;
                cout << "\nPresione ENTER para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            // Reiniciar rafagas y estados si ya se habian ejecutado antes
            for (size_t i = 0; i < listaProcesos.size(); i++) {
                listaProcesos[i].rafagaRestante = listaProcesos[i].rafagaTotal;
                listaProcesos[i].estado = "Waiting";
                listaProcesos[i].completionTime = 0;
            }
            historialGantt.clear();

            int tiempoActual = 0;
            bool simulando = true;

            cin.ignore(); // Limpiar buffer de entrada

            while (simulando) {
                system("cls");

                // Verificar si todos terminaron
                bool todosTerminados = true;
                for (size_t i = 0; i < listaProcesos.size(); i++) {
                    if (listaProcesos[i].rafagaRestante > 0) {
                        todosTerminados = false;
                        break;
                    }
                }

                if (todosTerminados) {
                    // Mostrar tabla final con todos en Terminated
                    for (size_t i = 0; i < listaProcesos.size(); i++) {
                        listaProcesos[i].estado = "Terminated";
                    }

                    cout << "\n==========================================================================================" << endl;
                    cout << "                     ESTADO ACTUAL DEL PLANIFICADOR                                       " << endl;
                    cout << "==========================================================================================" << endl;
                    cout << "PID \t Estado \t Memoria(MB) \t Tiempo requerido \t Raf.Rest. \t CT \t" << endl;
                    cout << "------------------------------------------------------------------------------------------" << endl;
                    for (size_t i = 0; i < listaProcesos.size(); i++) {
                        cout << listaProcesos[i].pid << "\t "
                            << listaProcesos[i].estado << "\t\t "
                            << listaProcesos[i].tamMemoria << "\t\t "
                            << listaProcesos[i].rafagaTotal << "\t\t "
                            << listaProcesos[i].rafagaRestante << "\t\t "
                            << listaProcesos[i].completionTime << endl;
                    }
                    cout << "==========================================================================================" << endl;
                    cout << "\nTodos los procesos han finalizado su ejecucion! Ya puede ver el Diagrama de Gantt." << endl;
                    cout << "\nPresione ENTER para regresar...";
                    cin.get();
                    simulando = false;
                    break;
                }

                // Identificar el proceso que va a correr
                int idxCorriendo = -1;
                int idxSiguiente = -1;

                for (size_t i = 0; i < listaProcesos.size(); i++) {
                    if (listaProcesos[i].rafagaRestante > 0) {
                        if (idxCorriendo == -1) {
                            idxCorriendo = i;
                        }
                        else if (idxSiguiente == -1) {
                            idxSiguiente = i;
                            break;
                        }
                    }
                }

                // Asignar estados visuales en la tabla actual
                for (size_t i = 0; i < listaProcesos.size(); i++) {
                    if (listaProcesos[i].rafagaRestante > 0) {
                        if ((int)i == idxCorriendo) {
                            listaProcesos[i].estado = "Running";
                        }
                        else {
                            listaProcesos[i].estado = "Waiting";
                        }
                    }
                    else {
                        listaProcesos[i].estado = "Terminated";
                    }
                }

                // Mostrar la tabla con el estado actualizado
                cout << "\n==========================================================================================" << endl;
                cout << "                     ESTADO ACTUAL DEL PLANIFICADOR                                       " << endl;
                cout << "==========================================================================================" << endl;
                cout << "PID \t Estado \t Memoria(MB) \t Tiempo requerido \t Raf.Rest. \t CT" << endl;
                cout << "------------------------------------------------------------------------------------------" << endl;
                for (size_t i = 0; i < listaProcesos.size(); i++) {
                    cout << listaProcesos[i].pid << "\t "
                        << listaProcesos[i].estado << "\t\t "
                        << listaProcesos[i].tamMemoria << "\t\t "
                        << listaProcesos[i].rafagaTotal << "\t\t\t "
                        << listaProcesos[i].rafagaRestante << "\t\t ";

                    if (listaProcesos[i].completionTime > 0)
                        cout << listaProcesos[i].completionTime << endl;
                    else
                        cout << "-" << endl;
                }
                cout << "==========================================================================================" << endl;
                cout << "[Quantum Asignado por turno: q = " << QUANTUM << "] | [Tiempo Global: " << tiempoActual << "]" << endl;

                // Anotacion inferior indicando quien corre y quien sigue
                cout << "------------------------------------------------------------------------------------------" << endl;
                if (idxCorriendo != -1) {
                    cout << ">>> ANOTACION: Proceso " << listaProcesos[idxCorriendo].pid << " RUNNING";
                    if (idxSiguiente != -1) {
                        cout << ", next proceso " << listaProcesos[idxSiguiente].pid;
                    }
                    else {
                        cout << ", (Ultimo proceso en ejecucion)";
                    }
                    cout << endl;
                }
                cout << "------------------------------------------------------------------------------------------" << endl;
                cout << "Presione [ENTER] para avanzar el ciclo (o digite 0 + ENTER para salir)...";

                string entrada;
                getline(cin, entrada);
                if (entrada == "0") {
                    simulando = false;
                    break;
                }

                // Procesar la ejecucion del turno actual
                if (idxCorriendo != -1) {
                    int tiempoEjecucion = (listaProcesos[idxCorriendo].rafagaRestante > QUANTUM) ? QUANTUM : listaProcesos[idxCorriendo].rafagaRestante;

                    for (int t = 0; t < tiempoEjecucion; t++) {
                        historialGantt.push_back(listaProcesos[idxCorriendo].pid);
                    }

                    tiempoActual += tiempoEjecucion;

                    if (listaProcesos[idxCorriendo].rafagaRestante > QUANTUM) {
                        listaProcesos[idxCorriendo].rafagaRestante -= QUANTUM;
                    }
                    else {
                        listaProcesos[idxCorriendo].rafagaRestante = 0;
                        listaProcesos[idxCorriendo].completionTime = tiempoActual;
                    }

                    // Rotacion de cola (Round Robin)
                    PCB temp = listaProcesos[idxCorriendo];
                    listaProcesos.erase(listaProcesos.begin() + idxCorriendo);
                    listaProcesos.push_back(temp);
                }
            }
        }
        else if (opcionSub == 3) {
            system("cls");
            if (historialGantt.empty()) {
                cout << "\n[Advertencia] Debe ejecutar la simulacion Round Robin (Opcion 2) primero para generar el Gantt.\n";
            }
            else {
                cout << "\n==========================================================================================" << endl;
                cout << "                     DIAGRAMA DE GANTT                                    " << endl;
                cout << "==========================================================================================" << endl;

                cout << "Tiempo: |";
                for (size_t t = 0; t < historialGantt.size(); t++) {
                    cout << " T" << t + 1 << " |";
                }
                cout << "\n--------+";
                for (size_t t = 0; t < historialGantt.size(); t++) {
                    cout << "----+";
                }
                cout << "\nProceso:|";

                for (size_t t = 0; t < historialGantt.size(); t++) {
                    cout << " P" << historialGantt[t] << " |";
                }
                cout << "\n==========================================================================================" << endl;
            }
            cout << "\nPresione ENTER para regresar...";
            cin.ignore();
            cin.get();

        }
        else if (opcionSub == 4) {
            cout << "\nRegresando al menu principal..." << endl;
        }
        else {
            cout << "\nOpcion invalida. Presione ENTER para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcionSub != 4);
}