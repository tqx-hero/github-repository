SRC_DIRS := . ../function 
SRC := $(shell find $(SRC_DIRS) -name "*.c")
TARGET := webserver
CC := gcc
OBJ := $(SRC:.c=.o)

$(TARGET) : $(OBJ)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) -c $< -o $@

print:
	@echo "SRC = $(SRC)"
	@echo "OBJ = $(OBJ)"
.PHONY:clean
clean:
	rm -rf $(TARGET) $(OBJ)
