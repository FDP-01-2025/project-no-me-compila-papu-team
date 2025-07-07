# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11

# Output executable
TARGET = ucaroulette

# Source files
SRCS = Uca_Roulette.cpp ascii_art_FIXED.cpp

# Build rule
all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule
clean:
	del $(TARGET).exe 2>nul || exit 0
