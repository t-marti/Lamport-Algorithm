# Nome do executável 
TARGET = lamport_algorithm

CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

# Arquivos-fonte
SRC = lamport_algorithm.cpp libmutex.cpp

# Cabeçalhos 
HEADERS = libmutex.h

# Objeto compilado
OBJ = $(SRC:.cpp=.o)

# Regra padrão
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET)
