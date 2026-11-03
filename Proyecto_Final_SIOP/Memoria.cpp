#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <limits>
#include "memoria.h"

using namespace std;

void menuMemoria() {
    int opcionSub;
    int tipoAlgoritmo = 1; // 1. Continua estatica, 2. Continua dinamica, 3. Paginacion simple

    // Matriz 10x10 para representar los 100 MB

    vector<vector<int>> matrizMemoria(10, vector<int>(10, 0));
    vector<pair<int, int>> procesosMemoria; // Guarda {pid, tamano en mb}

    do {
        system("cls");
        cout << "========================================================================" << endl;
        cout << "   MODULO: GESTION DE MEMORIA (RAM 100 MB)" << endl;
        cout << "========================================================================" << endl;
        cout << "1. Ver estado actual de la memoria (Matriz 10x10)" << endl;
        cout << "2. Seleccionar algoritmo y gestionar procesos (Validacion RAM)" << endl;
        cout << "3. Liberar memoria de un proceso" << endl;
        cout << "4. Regresar al menu principal" << endl;
        cout << "Seleccione una opcion: ";

        // Validación de opción de menú principal
        if (!(cin >> opcionSub)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcionSub == 1) {
            system("cls");
            cout << endl << "========================================================================" << endl;
            cout << "                 MAPA FISICO DE LA MEMORIA RAM (100 MB)                 " << endl;
            cout << "========================================================================" << endl;
            cout << "Leyenda: [ 0 ] = Libre  |  [ Px ] = Ocupado por Proceso x" << endl;
            cout << "------------------------------------------------------------------------" << endl;

            if (tipoAlgoritmo == 1) cout << "Vista estatica: cada fila es una particion fija de 10 MB." << endl;
            else if (tipoAlgoritmo == 2) cout << "Vista dinamica: solo se ocupan los MB necesarios de forma consecutiva." << endl;
            else if (tipoAlgoritmo == 3) cout << "Vista paginacion: cada celda es un marco de 1 MB; pueden estar dispersos." << endl;

            for (int r = 0; r < 10; r++) {
                cout << "Bloques " << (r * 10 + 1) << "-" << ((r + 1) * 10) << ": |";
                for (int c = 0; c < 10; c++) {
                    if (matrizMemoria[r][c] == 0) {
                        cout << "  0  |";
                    }
                    else {
                        cout << " P" << matrizMemoria[r][c] << "  |";
                    }
                }
                cout << endl;
            }
            cout << "========================================================================" << endl;
            cout << endl << "Presione ENTER para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

        }
        else if (opcionSub == 2) {
            system("cls");
            cout << "Seleccione el tipo de estrategia de asignacion:" << endl;
            cout << "1. Asignacion Continua Estatica" << endl;
            cout << "2. Asignacion Continua Dinamica" << endl;
            cout << "3. Paginacion Simple" << endl;

            // Validación estricta para seleccionar algoritmo (solo 1, 2 o 3 positivos)
            do {
                cout << "Opcion: ";
                if (!(cin >> tipoAlgoritmo)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[Error] Entrada invalida. Ingrese un numero entre 1 y 3.\n";
                }
                else if (tipoAlgoritmo < 1 || tipoAlgoritmo > 3) {
                    cout << "[Error] Opcion fuera de rango. Seleccione 1, 2 o 3.\n";
                }
            } while (tipoAlgoritmo < 1 || tipoAlgoritmo > 3);

            char continuar = 's';
            while (continuar == 's' || continuar == 'S') {
                int pid = procesosMemoria.empty() ? 1 : procesosMemoria.back().first + 1;
                int tam = 0;
                cout << endl << "--- Configurando Proceso PID [" << pid << "] ---" << endl;

                // Validación estricta para el tamaño en MB (solo números positivos mayores a 0)
                do {
                    cout << "Ingrese tamano en MB: ";
                    if (!(cin >> tam)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "[Error] Entrada invalida. Ingrese un numero entero positivo.\n";
                    }
                    else if (tam <= 0) {
                        cout << "[Error] El tamano debe ser un valor positivo mayor a 0.\n";
                    }
                } while (tam <= 0);

                // Calcular bloques ocupados totales en la matriz
                int bloquesOcupadosTotales = 0;
                for (int r = 0; r < 10; r++) {
                    for (int c = 0; c < 10; c++) {
                        if (matrizMemoria[r][c] != 0) {
                            bloquesOcupadosTotales++;
                        }
                    }
                }

                // Validacion de desbordamiento (Out of Memory) general
                if ((bloquesOcupadosTotales + tam) > 100) {
                    system("cls");
                    cout << endl << "========================================================================" << endl;
                    cout << "                      ERROR: OUT OF MEMORY                              " << endl;
                    cout << "========================================================================" << endl;
                    cout << "La suma total de memoria excede el limite de la RAM (100 MB)." << endl;
                    cout << "========================================================================" << endl;
                    cout << endl << "Desea visualizar el estado actual de la memoria? (S/N): ";
                    char respuesta;
                    cin >> respuesta;

                    if (respuesta == 's' || respuesta == 'S') {
                        system("cls");
                        cout << endl << "========================================================================" << endl;
                        cout << "             MAPA DE MEMORIA ACTUAL (ESTADO ANTERIOR)                   " << endl;
                        cout << "========================================================================" << endl;
                        if (tipoAlgoritmo == 1) cout << "Vista estatica: cada fila es una particion fija de 10 MB." << endl;
                        else if (tipoAlgoritmo == 2) cout << "Vista dinamica: solo se ocupan los MB necesarios de forma consecutiva." << endl;
                        else if (tipoAlgoritmo == 3) cout << "Vista paginacion: cada celda es un marco de 1 MB; pueden estar dispersos." << endl;
                        for (int r = 0; r < 10; r++) {
                            cout << "Bloques " << (r * 10 + 1) << "-" << ((r + 1) * 10) << ": |";
                            for (int c = 0; c < 10; c++) {
                                if (matrizMemoria[r][c] == 0) cout << "  0  |";
                                else cout << " P" << matrizMemoria[r][c] << "  |";
                            }
                            cout << endl;
                        }
                        cout << "========================================================================" << endl;
                    }
                    cout << endl << "Presione ENTER para regresar...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    break;
                }

                // Asignar dependiendo de la opcion seleccionada
                bool asignadoConExito = false;

                switch (tipoAlgoritmo) {
                case 1: // Asignacion Continua Estatica, osea que cada fila de la matriz representa una particion fija de 10 MB
                {

                    if (tam <= 0 || tam > 10) {
                        cout << endl << "[Aviso] En asignacion estatica, el proceso debe medir entre 1 y 10 MB." << endl;
                        break;
                    }

                    for (int r = 0; r < 10; r++) {
                        bool particionLibre = true;
                        for (int c = 0; c < 10; c++) {
                            if (matrizMemoria[r][c] != 0) particionLibre = false;
                        }

                        if (particionLibre) {
                            for (int c = 0; c < 10; c++) matrizMemoria[r][c] = pid;
                            asignadoConExito = true;
                            break;
                        }
                    }

                    if (!asignadoConExito) {
                        cout << endl << "[Aviso] No hay particiones fijas libres de 10 MB." << endl;
                    }
                    break;
                }
                case 2: { // Asignacion Continua Dinamica
                    if (tam <= 0) {
                        cout << endl << "[Aviso] El tamano debe ser mayor que 0 MB." << endl;
                        break;
                    }
                    int inicioSecuencia = -1;
                    int contadorConsecutivo = 0;

                    for (int i = 0; i < 100; i++) {
                        int r = i / 10;
                        int c = i % 10;
                        if (matrizMemoria[r][c] == 0) {
                            if (inicioSecuencia == -1) inicioSecuencia = i;
                            contadorConsecutivo++;
                            if (contadorConsecutivo == tam) break;
                        }
                        else {
                            inicioSecuencia = -1;
                            contadorConsecutivo = 0;
                        }
                    }

                    if (contadorConsecutivo == tam) {
                        for (int i = 0; i < tam; i++) {
                            int idx = inicioSecuencia + i;
                            int r = idx / 10;
                            int c = idx % 10;
                            matrizMemoria[r][c] = pid;
                        }
                        asignadoConExito = true;
                    }
                    else {
                        cout << endl << "[Aviso] No hay bloques contiguos suficientes para este proceso." << endl;
                    }
                    break;
                }
                case 3: { // Paginacion Simple (bloques no contiguos)
                    if (tam <= 0) {
                        cout << endl << "[Aviso] El tamano debe ser mayor que 0 MB." << endl;
                        break;
                    }
                    int bloquesAsignados = 0;
                    // Se buscan marcos libres en orden no consecutivo para mostrar la paginacion.
                    for (int i = 0; i < 100 && bloquesAsignados < tam; i++) {
                        int posicion = (i * 37) % 100;
                        int r = posicion / 10;
                        int c = posicion % 10;
                        if (matrizMemoria[r][c] == 0) {
                            matrizMemoria[r][c] = pid;
                            bloquesAsignados++;
                        }
                    }
                    if (bloquesAsignados == tam) {
                        asignadoConExito = true;
                    }
                    break;
                }
                default:
                    cout << endl << "Opcion de algoritmo invalida." << endl;
                    break;
                }

                if (!asignadoConExito) {
                    cout << endl << "No se pudo asignar memoria debido a restricciones del algoritmo." << endl;
                    cout << endl << "Presione ENTER para continuar...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    break;
                }

                procesosMemoria.push_back({ pid, tam });

                // Mostrar estado actual de la memoria despues de agregar el proceso
                system("cls");
                cout << endl << "========================================================================" << endl;
                cout << "             ESTADO ACTUAL DE LA MEMORIA (RAM 100 MB)                   " << endl;
                cout << "========================================================================" << endl;
                cout << "Leyenda: [ 0 ] = Libre  |  [ Px ] = Ocupado por Proceso x" << endl;
                cout << "------------------------------------------------------------------------" << endl;

                if (tipoAlgoritmo == 1) cout << "Vista estatica: cada fila es una particion fija de 10 MB." << endl;
                else if (tipoAlgoritmo == 2) cout << "Vista dinamica: solo se ocupan los MB necesarios de forma consecutiva." << endl;
                else if (tipoAlgoritmo == 3) cout << "Vista paginacion: cada celda es un marco de 1 MB; pueden estar dispersos." << endl;

                for (int r = 0; r < 10; r++) {
                    cout << "Bloques " << (r * 10 + 1) << "-" << ((r + 1) * 10) << ": |";
                    for (int c = 0; c < 10; c++) {
                        if (matrizMemoria[r][c] == 0) {
                            cout << "  0  |";
                        }
                        else {
                            cout << " P" << matrizMemoria[r][c] << "  |";
                        }
                    }
                    cout << endl;
                }
                cout << "========================================================================" << endl;
                cout << endl << "Desea ingresar otro proceso? (S/N): ";
                cin >> continuar;
            }

        }
        else if (opcionSub == 3) {
            system("cls");
            cout << endl << "========================================================================" << endl;
            cout << "                    LIBERAR MEMORIA DE UN PROCESO                       " << endl;
            cout << "========================================================================" << endl;
            if (procesosMemoria.empty()) {
                cout << "No hay procesos activos en memoria actualmente." << endl;
            }
            else {
                cout << "Procesos activos en memoria:" << endl;
                for (size_t i = 0; i < procesosMemoria.size(); i++) {
                    cout << " - PID [" << procesosMemoria[i].first << "] (" << procesosMemoria[i].second << " MB)" << endl;
                }
                cout << endl << "0. Liberar todos los procesos y reiniciar memoria" << endl;
                int pidLiberar = -1;

                // Validación para asegurar que el PID ingresado sea un número entero positivo/cero válido
                do {
                    cout << endl << "Ingrese el PID del proceso que desea liberar: ";
                    if (!(cin >> pidLiberar)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "[Error] Entrada invalida. Ingrese un numero de la lista.\n";
                    }
                    else if (pidLiberar < 0) {
                        cout << "[Error] El PID no puede ser un numero negativo.\n";
                    }
                } while (pidLiberar < 0);

                if (pidLiberar == 0) {
                    char confirmar;
                    cout << endl << "Esta seguro de liberar toda la memoria? (S/N): ";
                    cin >> confirmar;
                    if (confirmar == 's' || confirmar == 'S') {
                        for (int r = 0; r < 10; r++) {
                            for (int c = 0; c < 10; c++) {
                                matrizMemoria[r][c] = 0;
                            }
                        }
                        procesosMemoria.clear();
                        cout << endl << "Todos los procesos fueron eliminados exitosamente!" << endl;
                        cout << "La memoria RAM ha sido reiniciada (100 MB libres)." << endl;
                    }
                    else {
                        cout << endl << "Operacion cancelada." << endl;
                    }
                }
                else {
                    bool encontrado = false;
                    for (int r = 0; r < 10; r++) {
                        for (int c = 0; c < 10; c++) {
                            if (matrizMemoria[r][c] == pidLiberar) {
                                matrizMemoria[r][c] = 0; // Liberar bloque
                                encontrado = true;
                            }
                        }
                    }

                    if (encontrado) {
                        // Remover de la lista de procesos
                        for (auto it = procesosMemoria.begin(); it != procesosMemoria.end(); ++it) {
                            if (it->first == pidLiberar) {
                                procesosMemoria.erase(it);
                                break;
                            }
                        }
                        cout << endl << "¡Memoria del Proceso PID [" << pidLiberar << "] liberada exitosamente!" << endl;
                    }
                    else {
                        cout << endl << "[Error] No se encontro ningun proceso con ese PID en la memoria." << endl;
                    }
                }
            }
            cout << endl << "Presione ENTER para continuar...";
            cin.ignore();
            cin.get();

        }
        else if (opcionSub == 4) {
            cout << endl << "Regresando al menu principal..." << endl;
        }
        else {
            cout << endl << "Opcion invalida." << endl;
        }

    } while (opcionSub != 4);
}