CC=gcc
TARGET=ret

$(TARGET): a.o b.o c.o
	$(CC) a.o b.o c.o -o $(TARGET)
a.o: a.c a.h
	$(CC) -c a.c -o a.o
b.o: b.c b.h
	$(CC) -c b.c -o b.o
c.o: c.c c.h
	$(CC) -c c.c -o c.o

