CXX = g++
CXXFLAGS = -g -O2 -Wall -std=c++17
TARGET = a

SRC = src
OBJ = obj
INC = include

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(SRCS:$(SRC)/%.cpp=$(OBJ)/%.o)

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -I $(INC) -c $< -o $@

clean:
	del /f obj\\*.o
	del /f a.exe