TARGET:= main
all: $(TARGET)

$(TARGET): main.o anytimer.o
	gcc $^ -o $@ -g

main.o: main.c
	gcc -c $^ -o $@ -g
anytimer.o: anytimer.c
	gcc -c $^ -o $@ -g
clean:
	rm -rf *.o $(TARGET)
