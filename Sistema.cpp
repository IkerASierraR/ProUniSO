#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Proceso {
    int pid;
    int llegada;
    int servicio;
    int inicio;
    int fin;
};

// ---------------- FCFS ----------------
vector<Proceso> fcfs(vector<Proceso> procesos) {
    int tiempo = 0;
    vector<Proceso> resultado;

    for (int i = 0; i < procesos.size(); i++) {
        if (tiempo < procesos[i].llegada) {
            tiempo = procesos[i].llegada;
        }
        procesos[i].inicio = tiempo;
        procesos[i].fin = tiempo + procesos[i].servicio;
        tiempo = procesos[i].fin;

        resultado.push_back(procesos[i]);
    }
    return resultado;
}

// ---------------- SPN ----------------
vector<Proceso> spn(vector<Proceso> procesos) {
    int tiempo = 0, completados = 0;
    int n = procesos.size();
    vector<bool> hecho(n, false);
    vector<Proceso> resultado;

    while (completados < n) {
        int idx = -1;
        int menor = 999999;

        // Buscar proceso más corto disponible
        for (int i = 0; i < n; i++) {
            if (!hecho[i] && procesos[i].llegada <= tiempo) {
                if (procesos[i].servicio < menor) {
                    menor = procesos[i].servicio;
                    idx = i;
                }
            }
        }

        // Si no hay proceso disponible, avanzar el tiempo
        if (idx == -1) {
            tiempo++;
            continue;
        }

        procesos[idx].inicio = tiempo;
        procesos[idx].fin = tiempo + procesos[idx].servicio;
        tiempo = procesos[idx].fin;
        hecho[idx] = true;
        completados++;

        resultado.push_back(procesos[idx]);
    }
    return resultado;
}

// ---------------- Round Robin ----------------
vector<Proceso> round_robin(vector<Proceso> procesos, int quantum) {
    int n = procesos.size();
    vector<int> restante(n);
    vector<int> inicio(n, -1);
    vector<int> fin(n);
    queue<int> cola;
    int tiempo = 0, completados = 0;

    for (int i = 0; i < n; i++) {
        restante[i] = procesos[i].servicio;
    }

    // empezar con el primero que llega
    cola.push(0);

    while (completados < n) {
        if (cola.empty()) {
            tiempo++;
            for (int i = 0; i < n; i++) {
                if (restante[i] > 0 && procesos[i].llegada <= tiempo) {
                    cola.push(i);
                }
            }
            continue;
        }

        int idx = cola.front();
        cola.pop();

        if (inicio[idx] == -1) inicio[idx] = tiempo;

        int ejecutar = (restante[idx] < quantum) ? restante[idx] : quantum;
        restante[idx] -= ejecutar;
        tiempo += ejecutar;

        // agregar procesos que llegan mientras tanto
        for (int i = 0; i < n; i++) {
            if (restante[i] > 0 && procesos[i].llegada <= tiempo) {
                bool ya_esta = false;
                queue<int> temp = cola;
                while (!temp.empty()) {
                    if (temp.front() == i) ya_esta = true;
                    temp.pop();
                }
                if (!ya_esta && i != idx) cola.push(i);
            }
        }

        if (restante[idx] > 0) {
            cola.push(idx);
        } else {
            fin[idx] = tiempo;
            completados++;
        }
    }

    vector<Proceso> resultado;
    for (int i = 0; i < n; i++) {
        Proceso p = procesos[i];
        p.inicio = inicio[i];
        p.fin = fin[i];
        resultado.push_back(p);
    }
    return resultado;
}

// ---------------- Tabla de resultados ----------------
void imprimir_resultados(vector<Proceso> procesos) {
    cout << "\nPID | Llegada | Servicio | Inicio | Fin | Respuesta | Espera | Retorno\n";
    cout << "---------------------------------------------------------------------\n";

    for (int i = 0; i < procesos.size(); i++) {
        int respuesta = procesos[i].inicio - procesos[i].llegada;
        int retorno = procesos[i].fin - procesos[i].llegada;
        int espera = retorno - procesos[i].servicio;

        cout << procesos[i].pid << "   | "
             << procesos[i].llegada << "       | "
             << procesos[i].servicio << "        | "
             << procesos[i].inicio << "      | "
             << procesos[i].fin << "   | "
             << respuesta << "         | "
             << espera << "      | "
             << retorno << "\n";
    }
}

// ---------------- MAIN ----------------
int main() {
    int n;
    cout << "Cuantos procesos deseas ingresar: ";
    cin >> n;

    vector<Proceso> procesos(n);
    for (int i = 0; i < n; i++) {
        cout << "PID: ";
        cin >> procesos[i].pid;
        cout << "Tiempo de llegada: ";
        cin >> procesos[i].llegada;
        cout << "Tiempo de servicio: ";
        cin >> procesos[i].servicio;
    }

    string alg;
    cout << "Algoritmo (FCFS / SPN / RR): ";
    cin >> alg;

    vector<Proceso> resultado;

    if (alg == "FCFS") {
        resultado = fcfs(procesos);
    } else if (alg == "SPN") {
        resultado = spn(procesos);
    } else if (alg == "RR") {
        int q;
        cout << "Quantum: ";
        cin >> q;
        resultado = round_robin(procesos, q);
    } else {
        cout << "Algoritmo no valido.\n";
        return 0;
    }

    imprimir_resultados(resultado);

    return 0;
}
