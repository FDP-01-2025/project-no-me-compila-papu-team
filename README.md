[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ - "¿Quién quiere dejar de ser pobre?"

## Descripción del Proyecto

Este proyecto consiste en una colección de minijuegos educativos desarrollados en C++ que implementan estructuras de control como `if`, `switch`, y bucles `while` y `for` para generar interacciones dinámicas. Los juegos incluyen:

- **Hangman (Ahorcado)**: Juego de adivinanza de palabras relacionadas con programación
- **Tic Tac Toe**: Juego de estrategia contra la computadora
- **RPG Fight**: Juego de batalla por turnos con diferentes niveles de dificultad
- **Rock Paper Scissors**: Clásico juego de piedra, papel o tijeras con gráficos ASCII

Cada juego implementa validación de entrada, manejo de errores, y utiliza estructuras de datos para mantener el estado del juego.

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

## Estructura del Proyecto

```
project-no-me-compila-papu-team/
├── src/                    # Código fuente principal
│   ├── main.cpp           # Punto de entrada del programa
│   ├── hangman.cpp/h      # Juego del ahorcado
│   ├── tictactoe.cpp/h    # Juego de tic tac toe
│   ├── rpgfight.cpp/h     # Juego de batalla RPG
│   ├── rock_paper_scissors.cpp/h  # Piedra, papel o tijeras
│   ├── ascii_art.cpp/h    # Utilidades de arte ASCII
│   ├── utils.cpp/h        # Funciones utilitarias
│   ├── crossword.cpp/h    # Juego de crucigrama
│   └── game_data/         # Datos del juego
│       ├── words.txt      # Palabras para el ahorcado
│       └── scores.txt     # Puntuaciones altas
├── old_files/             # Archivos antiguos preservados
├── obj/                   # Archivos objeto de compilación
├── Makefile              # Script de compilación
├── .gitignore            # Archivos ignorados por Git
└── README.md             # Este archivo
```

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
      - **Opción 1:** Hangman (Ahorcado) - Adivina palabras de programación
      - **Opción 2:** Tic Tac Toe - Juega contra la computadora
      - **Opción 3:** RPG Fight - Batalla épica con diferentes dificultades
      - **Opción 4:** Rock Paper Scissors - Duelo clásico con gráficos ASCII
      - **Opción 5:** Ver puntuaciones altas
      - **Opción 6:** Salir
   3. ¡Diviértete y gana puntos de conocimiento!

## Características de los Juegos

### 🎯 Hangman (Ahorcado)
- Palabras relacionadas con programación
- Interfaz visual del ahorcado
- Seguimiento de letras usadas
- Sistema de puntuación

### ⚔️ Tic Tac Toe
- Juego contra IA
- Validación de movimientos
- Interfaz gráfica ASCII
- Diferentes niveles de dificultad

### 🎮 RPG Fight
- Sistema de estadísticas del jugador
- Diferentes niveles de dificultad
- Gráficos ASCII del enemigo
- Sistema de batalla por turnos

### ✂️ Rock Paper Scissors
- Gráficos ASCII de las manos
- Sistema de puntuación
- Múltiples rondas
- Estadísticas del juego

## Tecnologías Utilizadas

- **Lenguaje:** C++11
- **Estructuras de Control:** if, switch, while, for
- **Estructuras de Datos:** Arrays, Strings, Structs
- **Entrada/Salida:** iostream, fstream
- **Utilidades:** cstdlib, ctime, limits
