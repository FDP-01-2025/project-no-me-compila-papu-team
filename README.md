[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ - "¿Quién quiere dejar de ser pobre?"

## Descripción del Proyecto

Breve descripción del juego, su propósito, cómo se juega y cualquier otro detalle importante que describa la idea general del proyecto.

**Por ejemplo:**
Este proyecto consiste en un juego de aventuras donde el jugador debe explorar un mundo virtual, recoger objetos, resolver acertijos y enfrentar enemigos. El juego utiliza estructuras de control como `if`, `switch`, y bucles `while` y `for` para generar interacciones dinámicas.

## Equipo

- **Nombre del equipo:**  No me compila papu team 

### Integrantes del equipo

1. **Nombre completo:** Alejandra Paola Orellana Valladares  
   **Carnet:** 00108225

2. **Nombre completo:** Edgar Ari Peñate Rivera
   **Carnet:** 00021725

3. **Nombre completo:** [Nombre del estudiante 3]  
   **Carnet:** [Carnet del estudiante 3]

(Agregar más integrantes si es necesario)

## Instrucciones de Ejecución

   ### Prerrequisitos
   - Compilador de C++ (g++ recomendado)
   - Utilidad Make (opcional pero recomendado)

   ### Método 1: Usando Makefile (Recomendado)
   ```bash
   # 1. Clona este repositorio en tu máquina local:
   git clone https://github.com/FDP-01-2025/project-no-me-compila-papu-team.git
   cd project-no-me-compila-papu-team

   # 2. Compila el proyecto
   make

   # 3. Ejecuta el juego
   make run

   # O ejecuta directamente
   ./game_collection
   ```

   ### Método 2: Compilación Manual
   ```bash
   # Compila manualmente todos los archivos
   g++ -std=c++11 -Wall -Wextra -O2 src/*.cpp -o game_collection

   # Ejecuta el juego
   ./game_collection
   ```

   ### Otros Comandos Útiles
   ```bash
   make clean    # Elimina archivos de compilación
   make setup    # Crea directorios necesarios
   make debug    # Compila con símbolos de debug
   make help     # Muestra comandos disponibles
   ```

   ### Cómo Jugar
   1. Ejecuta el programa con `./game_collection`
   2. Selecciona tu juego favorito del menú:
      - **Opción 1:** Hangman (Ahorcado) - Adivina la palabra
      - **Opción 2:** Tic Tac Toe - Juega contra la computadora
      - **Opción 3:** Ver puntuaciones altas
      - **Opción 4:** Salir
   3. ¡Diviértete y gana puntos de conocimiento!
