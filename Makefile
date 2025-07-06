# Makefile for Super Trivia Game Project
# Author: No me compila papu team 
# Language: C++

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall
SOURCES = src/main.cpp src/SuperTriviaGame.cpp src/jugador.cpp src/preguntas.cpp src/potenciadores.cpp src/sprite.cpp src/trivia.cpp src/Crossword.cpp src/Hangman.cpp src/RPSGame.cpp src/TicTacToe.cpp src/MiniGameHandler.cpp
TARGET = test

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)
	@echo "Build complete! Run with: ./$(TARGET)"

# Clean build files
clean:
	rm -f $(TARGET)
	@echo "Clean complete!"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build files"
	@echo "  run     - Build and run the program"
	@echo "  debug   - Build with debug symbols"
	@echo "  help    - Show this help message"

.PHONY: all clean run debug help 