# Simulador de Sistema Operativo Simple

Este proyecto implementa un simulador sencillo de **planificación de CPU** y gestión de procesos, con fines educativos.  
Permite analizar el comportamiento de distintos algoritmos y calcular métricas de desempeño de los procesos.  

---

## Requisitos

- **C++11 o superior**  
- Compilador como `g++` o el entorno de tu preferencia (Dev-C++, Code::Blocks, Visual Studio, etc.)  

---

## Compilación y ejecución

Compilar el simulador:  

```bash
g++ simulador.cpp -o simulador
```

Ejecutar el programa:  

```bash
./simulador
```

El programa pedirá:  
1. Número de procesos.  
2. Para cada proceso: `PID`, `Tiempo de llegada`, `Tiempo de servicio`.  
3. Algoritmo de planificación (`FCFS`, `SPN` o `RR`).  
4. Si se elige `RR`, se pedirá además el **quantum**.  

La salida será una tabla con las siguientes columnas:  

```
PID | Llegada | Servicio | Inicio | Fin | Respuesta | Espera | Retorno
```

---

## Ejemplo de uso

Entrada (modo interactivo):  
```
Cuantos procesos deseas ingresar: 3

PID: 1
Tiempo de llegada: 0
Tiempo de servicio: 12

PID: 2
Tiempo de llegada: 1
Tiempo de servicio: 5

PID: 3
Tiempo de llegada: 2
Tiempo de servicio: 8

Algoritmo (FCFS / SPN / RR): RR
Quantum: 4
```

Salida en tabla:  

```
PID | Llegada | Servicio | Inicio | Fin | Respuesta | Espera | Retorno
--- | ------- | -------- | ------ | --- | --------- | ------ | -------
1   | 0       | 12       | 0      | 22  | 0         | 10     | 22
2   | 1       | 5        | 2      | 9   | 1         | 3      | 8
3   | 2       | 8        | 9      | 21  | 7         | 11     | 19
```
