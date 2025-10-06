CC = gcc
CXX = g++
CFLAGS = -Iinclude `pkg-config --cflags gtk+-3.0` -Wall -g
CXXFLAGS = $(CFLAGS)
LDFLAGS = `pkg-config --libs gtk+-3.0`


SRC_CPP = gui.cpp source/header.cpp source/program.cpp source/utils.cpp source/section.cpp source/library.cpp source/strings.cpp

OBJ_C = $(SRC_C:.c=.o)
OBJ_CPP = $(SRC_CPP:.cpp=.o)

OBJS = $(OBJ_C) $(OBJ_CPP)

TARGET = melf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

# compile C sources
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# compile C++ sources
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

