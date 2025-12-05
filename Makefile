CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = Lab_6_my
OBJS = main.o lib.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c lib.h
	$(CC) $(CFLAGS) -c main.c

lib.o: lib.c lib.h
	$(CC) $(CFLAGS) -c lib.c

clean:
	rm -f $(OBJS) $(TARGET)
