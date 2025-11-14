CXX = g++
CXXFLAGS = -std=c++17 -O2 -g -Iinclude -Iexternal/imgui
LDFLAGS = -lglfw -ldl -lGL -lassimp

SRC_DIR = src
EXTERNAL_DIR = external/imgui

SRC = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c) $(wildcard $(EXTERNAL_DIR)/*.cpp)

OBJ = $(SRC:.cpp=.o)

OUT = app

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT) $(OBJ)
