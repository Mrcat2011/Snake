CXX = g++
CXXFLAGS = -Iinc -std=c++17 -g
LDFLAGS = -lraylib -lm -ldl -lpthread
SOURCES = src/main.cpp src/Food.cpp src/Cube.cpp src/Snake.cpp src/Button.cpp
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
EXECUTABLE = game

all: $(EXECUTABLE)

build/%.o: src/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -rf build $(EXECUTABLE)

run:
	@$(MAKE) && ./$(EXECUTABLE) $(ARGS)
