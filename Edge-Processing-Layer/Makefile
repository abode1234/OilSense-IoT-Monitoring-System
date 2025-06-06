Compiler = g++
CXXFLAGS = -std=c++17 -I./include -I/usr/local/include
LD_FLAGS = -lpaho-mqttpp3 -lpaho-mqtt3as -pthread -L/usr/local/lib

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = edge-processing-layer

all: $(TARGET)

$(TARGET): $(OBJ)
	$(Compiler) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LD_FLAGS)

%.o: %.cpp
	$(Compiler) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

