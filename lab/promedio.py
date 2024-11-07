from collections import defaultdict

def calcular_promedios_por_combinacion(archivo):
    # Diccionario para almacenar listas de números por combinación de hebra1 y hebra2
    numeros_por_combinacion = defaultdict(lambda: {
        "segundos_numeros": [], 
        "terceros_numeros": [], 
        "quintos_numeros": [], 
        "sextos_numeros": []
    })

    with open(archivo, 'r') as file:
        lineas = file.readlines()
        for i, linea in enumerate(lineas):
            if "hebras1" in linea:
                # Extraer hebra1 y hebra2
                partes = linea.strip().split(", ")
                hebras1 = partes[0].split(": ")[1]
                hebras2 = partes[1].split(": ")[1]
                combinacion = f"hebras1: {hebras1}, hebras2: {hebras2}"

                # Capturar el segundo, tercer, quinto y sexto número en las siguientes líneas
                try:
                    segundo = float(lineas[i + 2].strip())
                    tercero = float(lineas[i + 3].strip())
                    quinto = float(lineas[i + 5].strip())
                    sexto = float(lineas[i + 6].strip())
                    numeros_por_combinacion[combinacion]["segundos_numeros"].append(segundo)
                    numeros_por_combinacion[combinacion]["terceros_numeros"].append(tercero)
                    numeros_por_combinacion[combinacion]["quintos_numeros"].append(quinto)
                    numeros_por_combinacion[combinacion]["sextos_numeros"].append(sexto)
                except (IndexError, ValueError):
                    # Ignorar errores de índice o conversión
                    pass

    # Calcular promedios para cada combinación
    promedios = {}
    for combinacion, numeros in numeros_por_combinacion.items():
        promedio_segundo = sum(numeros["segundos_numeros"]) / len(numeros["segundos_numeros"]) if numeros["segundos_numeros"] else 0
        promedio_tercero = sum(numeros["terceros_numeros"]) / len(numeros["terceros_numeros"]) if numeros["terceros_numeros"] else 0
        promedio_quinto = sum(numeros["quintos_numeros"]) / len(numeros["quintos_numeros"]) if numeros["quintos_numeros"] else 0
        promedio_sexto = sum(numeros["sextos_numeros"]) / len(numeros["sextos_numeros"]) if numeros["sextos_numeros"] else 0
        promedios[combinacion] = (promedio_segundo, promedio_tercero, promedio_quinto, promedio_sexto)

    return promedios

# Usar la función y mostrar los resultados
archivo = 'ruta_al_archivo.txt'
promedios = calcular_promedios_por_combinacion("resultados_simple.txt")
for combinacion, (promedio_segundo, promedio_tercero, promedio_quinto, promedio_sexto) in promedios.items():
    print(f"{combinacion} -> Promedio del segundo número: {promedio_segundo:.5f}, "
          f"Promedio del tercer número: {promedio_tercero:.5f}, "
          f"Promedio del quinto número: {promedio_quinto:.5f}, "
          f"Promedio del sexto número: {promedio_sexto:.5f}")



