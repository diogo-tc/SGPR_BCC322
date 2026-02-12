CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = sgr

SRCS = main.cpp \
       domain/Despesa.cpp \
       services/ServicoDespesas.cpp

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
