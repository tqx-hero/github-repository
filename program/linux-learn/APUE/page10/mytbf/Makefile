TARGET:=main
all: $(TARGET)

$(TARGET): main.o mytbf.o
	gcc $^ -o $@

clean: 
	rm -rf *.o $(TARGET)
