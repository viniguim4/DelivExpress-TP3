CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror 

SRCS = main.cpp delivexpress.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = tp3

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
