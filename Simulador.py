def fcfs(processes):
    procs = sorted(processes, key=lambda p: (p['llegada'], p['pid']))
    time = 0
    result = []
    for p in procs:
        if time < p['llegada']:
            time = p['llegada']
        inicio = time
        fin = inicio + p['servicio']
        time = fin
        result.append({'pid': p['pid'], 'llegada': p['llegada'], 'servicio': p['servicio'], 'inicio': inicio, 'fin': fin})
    return result

def spn(processes):
    procs = sorted(processes, key=lambda p: (p['llegada'], p['pid']))
    time = 0
    finished, ready = [], []
    i = 0
    while len(finished) < len(procs):
        while i < len(procs) and procs[i]['llegada'] <= time:
            ready.append(procs[i]); i += 1
        if not ready:
            time = procs[i]['llegada']; continue
        ready.sort(key=lambda p: (p['servicio'], p['llegada'], p['pid']))
        p = ready.pop(0)
        inicio, fin = time, time + p['servicio']
        time = fin
        finished.append({'pid': p['pid'], 'llegada': p['llegada'], 'servicio': p['servicio'], 'inicio': inicio, 'fin': fin})
    return finished

def round_robin(processes, quantum):
    from copy import deepcopy
    procs = deepcopy(sorted(processes, key=lambda p: (p['llegada'], p['pid'])))
    remaining = {p['pid']: p['servicio'] for p in procs}
    inicio, fin, time, i, ready = {}, {}, 0, 0, []
    while len(fin) < len(procs):
        while i < len(procs) and procs[i]['llegada'] <= time:
            ready.append(procs[i]); i += 1
        if not ready:
            time = procs[i]['llegada']; continue
        p = ready.pop(0)
        pid = p['pid']
        if pid not in inicio: inicio[pid] = time
        slice_time = min(quantum, remaining[pid])
        remaining[pid] -= slice_time
        time += slice_time
        while i < len(procs) and procs[i]['llegada'] <= time:
            ready.append(procs[i]); i += 1
        if remaining[pid] == 0:
            fin[pid] = time
        else:
            ready.append(p)
    return [{'pid': p['pid'], 'llegada': p['llegada'], 'servicio': p['servicio'], 'inicio': inicio[p['pid']], 'fin': fin[p['pid']]} for p in procs]

def calcular_metricas(tabla):
    filas = []
    for t in sorted(tabla, key=lambda x: x['pid']):
        resp = t['inicio'] - t['llegada']
        ret = t['fin'] - t['llegada']
        esp = ret - t['servicio']
        filas.append([t['pid'], t['llegada'], t['servicio'], t['inicio'], t['fin'], resp, esp, ret])
    return filas

def imprimir_tabla(filas):
    headers = ["PID","Llegada","Servicio","Inicio","Fin","Respuesta","Espera","Retorno"]
    print(" | ".join(headers))
    print("--- | " + " | ".join(["-"*len(h) for h in headers[1:]]))
    for f in filas:
        print(" | ".join(str(x) for x in f))

def main():
    n = int(input("¿Cuántos procesos deseas ingresar?: "))
    procesos = []
    for _ in range(n):
        pid = int(input("PID: "))
        llegada = int(input("Tiempo de llegada: "))
        servicio = int(input("Tiempo de servicio: "))
        procesos.append({'pid': pid, 'llegada': llegada, 'servicio': servicio})

    alg = input("Algoritmo (FCFS / SPN / RR): ").upper()
    if alg == "FCFS":
        tabla = fcfs(procesos)
    elif alg == "SPN":
        tabla = spn(procesos)
    elif alg == "RR":
        q = int(input("Quantum: "))
        tabla = round_robin(procesos, q)
    else:
        print("Algoritmo no válido."); return

    filas = calcular_metricas(tabla)
    print("\nResultado:\n")
    imprimir_tabla(filas)

if __name__ == "__main__":
    main()
