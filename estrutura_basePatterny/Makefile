CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = sgr

SRCS = main.cpp \
       domain/Despesa.cpp \
       domain/Usuario.cpp \
       domain/Rateio.cpp \
       domain/Extrato.cpp \
       domain/EqualRateio.cpp \
       services/ServicoDespesas.cpp \
       services/ServicoRateio.cpp \
       services/ServicoExtrato.cpp \
       infra/repository/InMemoryDespesaRepository.cpp \
       infra/factory/Factory.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
