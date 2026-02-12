CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = sgr

SRCS = main.cpp \
       domain/Despesa.cpp \
       domain/Usuario.cpp \
       domain/Rateio.cpp \
       services/ServicoDespesas.cpp \
       services/ServicoRateio.cpp

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
