#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <limits>
#include "deadlock.h"

using namespace std;

static void pausarDeadlock() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "Presione ENTER para continuar...";
    cin.get();
}

void menuDeadlock() {
    int opcionSub;

    // Estructuras de datos para la simulacion de Deadlock Y asignacion por defecto de recursos
    string recurso1 = "Recurso 1";
    string recurso2 = "Recurso 2";
    string procesoA = "Proceso A";
    string procesoB = "Proceso B";

    string asignadoA = "Recurso 1";
    string solicitandoA = "Recurso 2";

    string asignadoB = "Recurso 2";
    string solicitandoB = "Recurso 1";

    bool deadlockActivo = true;


    // inicio del menu del la opcion
    do {
        system("cls");
        cout << "========================================================================" << endl;
        cout << "   MODULO: INTERBLOQUEO (DEADLOCK)" << endl;
        cout << "========================================================================" << endl;
        cout << "1. Visualizar recursos disponibles y configurar asignacion/solicitudes" << endl;
        cout << "2. Iniciar simulacion paso a paso de Bloqueo Mutuo y resolucion" << endl;
        cout << "3. Regresar al menu principal" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcionSub)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcionSub == 1) {
            system("cls");
            cout << "\n========================================================================" << endl;
            cout << "            CONFIGURACION Y RECURSOS DISPONIBLES                        " << endl;
            cout << "========================================================================" << endl;
            cout << " Recursos exclusivos del sistema: [ " << recurso1 << " ] | [ " << recurso2 << " ]" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << " Se estan configurando para los procesos:" << endl;
            cout << "  - " << procesoA << " -> Tiene asignado: [" << asignadoA << "] | Solicita: [" << solicitandoA << "]" << endl;
            cout << "  - " << procesoB << " -> Tiene asignado: [" << asignadoB << "] | Solicita: [" << solicitandoB << "]" << endl;
            cout << "========================================================================" << endl;
            cout << "\n[Aviso] Datos de configuracion cargados correctamente para la simulacion." << endl;
            pausarDeadlock();

        }
        else if (opcionSub == 2) {
            system("cls");
            cout << "\n========================================================================" << endl;
            cout << "         SIMULACION PASO A PASO: BLOQUEO MUTUO (DEADLOCK)               " << endl;
            cout << "========================================================================" << endl;
            cout << "Iniciando asignacion inicial de recursos exclusivos..." << endl;
            pausarDeadlock();

            // Aqui esta la signacion inicial
            system("cls");
            cout << "------------------------------------------------------------------------" << endl;
            cout << "[1 FASE... running] Asignacion de Recursos Exclusivos:" << endl;
            cout << "  -> " << procesoA << " adquiere y retiene el [" << asignadoA << "]." << endl;
            cout << "  -> " << procesoB << " adquiere y retiene el [" << asignadoB << "]." << endl;
            cout << "------------------------------------------------------------------------" << endl;
            pausarDeadlock();

            // Solicitudes que generan conflicto
            system("cls");
            cout << "------------------------------------------------------------------------" << endl;
            cout << "[2 FASE... running] Solicitudes concurrentes:" << endl;
            cout << "  -> " << procesoA << " solicita el [" << solicitandoA << "]." << endl;
            cout << "     [Alerta] El [" << solicitandoA << "] ya esta ocupado por " << procesoB << "!" << endl;
            cout << "  -> " << procesoB << " solicita el [" << solicitandoB << "]." << endl;
            cout << "     [Alerta] El [" << solicitandoB << "] ya esta ocupado por " << procesoA << "!" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            pausarDeadlock();

            // Deteccion de interbloqueo
            system("cls");
            cout << "========================================================================" << endl;
            cout << "                  ## ALERTA CRITICA ## : DEADLOCK DETECTADO             " << endl;
            cout << "========================================================================" << endl;
            cout << " Se ha formado una condicion de espera circular (Bloqueo Mutuo):" << endl;
            cout << "  * " << procesoA << " espera el recurso retenido por " << procesoB << "." << endl;
            cout << "  * " << procesoB << " espera el recurso retenido por " << procesoA << "." << endl;
            cout << " Ningun proceso puede avanzar por si mismo." << endl;
            cout << "========================================================================" << endl;
            pausarDeadlock();

            // Resolucion abortando un proceso
            int opcionAbortar;   // nueva variable para elegir abortar un proceso En un ciclo por si ingresa numeros nada que ver
            do {
                system("cls");
                cout << "========================================================================" << endl;
                cout << "                     GESTION DE RECURSOS MANUAL                         " << endl;
                cout << "========================================================================" << endl;
                cout << "Seleccione el proceso que desea abortar forzosamente para romper el ciclo:" << endl;
                cout << "1. Abortar " << procesoA << " (Libera " << asignadoA << ")" << endl;
                cout << "2. Abortar " << procesoB << " (Libera " << asignadoB << ")" << endl;
                cout << "Opcion: ";
                cin >> opcionAbortar;

                if (opcionAbortar != 1 && opcionAbortar != 2) {
                    cout << endl << "[Error] Opcion invalida. Intente de nuevo.";
                    pausarDeadlock();
                }
            } while (opcionAbortar != 1 && opcionAbortar != 2);


            // Mostrar resultado de la resolucion (la simulacion sigue)

            system("cls");
            cout << "------------------------------------------------------------------------" << endl;
            if (opcionAbortar == 1) {
                cout << "[Recurso Liberado] Se aborto forzosamente al " << procesoA << "." << endl;
                cout << "El [" << asignadoA << "] ha quedado libre." << endl;
                cout << "El " << procesoB << " puede adquirirlo y finalizar su ejecucion exitosamente." << endl;
            }
            else {
                cout << "[Recurso Liberado] Se aborto forzosamente al " << procesoB << "." << endl;
                cout << "El [" << asignadoB << "] ha quedado libre." << endl;
                cout << "El " << procesoA << " puede adquirirlo y finalizar su ejecucion exitosamente." << endl;
            }
            cout << "------------------------------------------------------------------------" << endl;
            cout << "\n¡El ciclo de interbloqueo ha sido roto y la simulacion ha terminado con exito!" << endl;
            pausarDeadlock();

        }
        else if (opcionSub == 3) {
            cout << endl << "Regresando al menu principal..." << endl;
        }
        else {
            cout << endl << "Opcion invalida." << endl;
            pausarDeadlock();
        }

    } while (opcionSub != 3);
}