CXX := g++
CXX_FLAGS := -Wall -Wextra -std=c++11 -ggdb -O3

BIN		:= bin
SRC		:= src
SRC2	:= src/handlers
SRC3	:= src/engine
SRC4	:= src/graphics
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lGL -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
EXECUTABLE	:= main.out


all: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c* $(SRC2)/*.cpp $(SRC3)/*.cpp $(SRC4)/*.cpp
	-mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

run: all
	./$(BIN)/$(EXECUTABLE)
