# Makefile
CXX = g++
CXXFLAGS = -I./include

SRC = src/main.cpp src/funcoesDeOrdenacao.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = build/estruturaDeDados

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p build
	$(CXX) $(OBJ) -o $(TARGET)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
