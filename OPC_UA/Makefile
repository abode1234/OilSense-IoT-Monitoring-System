CXX = g++
CXXFLAGS = -std=c++17 -I/usr/local/include -I./include
LDFLAGS = -L/usr/local/lib -lopen62541 -lpaho-mqttpp3 -lpaho-mqtt3as -lpthread

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

