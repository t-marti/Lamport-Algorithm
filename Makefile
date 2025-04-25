# Nome do executável 
TARGET = lamport

CXX = g++
CXXFLAGS = -Wall -std=c++17

# Arquivos-fonte
SRC = lamport_algorithm.cpp lamport_mutex.cpp

# Cabeçalhos 
HEADERS = lamport_mutex.h

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
