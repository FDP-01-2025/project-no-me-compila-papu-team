# Compilación del Proyecto Super Trivia Game

## Opciones de Compilación

### Opción 1: Compilación Simple (Recomendada)
```bash
cd src
g++ main.cpp -o test
```

### Opción 2: Usando el Script
```bash
./compile_simple.sh
```

### Opción 3: Usando Makefile
```bash
make
```

## Ejecutar el Programa
```bash
./src/test
```

## Estructura del Proyecto

El proyecto está organizado de la siguiente manera:
- `src/main.cpp` - Punto de entrada principal
- `src/all_implementations.cpp` - Archivo que incluye todas las implementaciones
- `src/*.h` - Archivos de cabecera
- `src/*.cpp` - Archivos de implementación

## Notas Importantes

- El proyecto usa C++11
- Hay algunas advertencias sobre `random_shuffle` deprecado, pero no afectan la funcionalidad
- Todos los archivos de datos (trivia_data.txt, words.txt) deben estar en el directorio raíz

## Solución de Problemas

Si encuentras errores de compilación:
1. Asegúrate de estar en el directorio correcto
2. Verifica que todos los archivos `.h` y `.cpp` estén presentes
3. Usa `make clean` para limpiar archivos compilados anteriormente 