# Compiler and flags
CXX = g++
CXXFLAGS = -Iinc -std=c++17 -g

# Platform-specific linker flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    LDFLAGS = -lraylib -lm -ldl -lpthread
else ifeq ($(UNAME_S), Windows_NT)
    CXX = x86_64-w64-mingw32-g++
    LDFLAGS = -Lwin-lib -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -luser32
endif

# Directories and files
SOURCES = src/main.cpp src/Food.cpp src/Cube.cpp src/Snake.cpp src/Button.cpp
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
EXECUTABLE = game

# Default target
all: $(EXECUTABLE)

# Rule to compile source files into object files
build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link object files into the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Clean target
clean:
	rm -rf build $(EXECUTABLE)

# Run target
run:
	@$(MAKE) && ./$(EXECUTABLE) $(ARGS)

