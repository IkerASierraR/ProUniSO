# Simulador de Sistema Operativo Simple

Este proyecto implementa un simulador sencillo de planificación de CPU y gestión de procesos, con fines educativos.  
Permite analizar el comportamiento de distintos algoritmos y calcular métricas de desempeño de los procesos.


## Requisitos

- Python **3.8 o superior**  
- No requiere librerías externas, funciona solo con la librería estándar de Python.  

---

## Ejecución

Ejecutar el simulador en modo interactivo:  

```bash
python3 src/simulador_simple.py
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
¿Cuántos procesos desea ingresar? 3

Proceso #1:
  PID: 1
  Llegada: 0
  Servicio: 12

Proceso #2:
  PID: 2
  Llegada: 1
  Servicio: 5

Proceso #3:
  PID: 3
  Llegada: 2
  Servicio: 8

Algoritmo: RR
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

---
