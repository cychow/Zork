# define g++
CC = g++

#compiler flags:
# -g
# -Wall
CFLAGS = -g -Wall

TARGET = zork

all: $(TARGET)

$(TARGET): $(TARGET).cpp
   $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
   
clean:
   $(RM) $(TARGET)