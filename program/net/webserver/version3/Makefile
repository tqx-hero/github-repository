SRC_DIRS := . ./function
SRC_EVENT := $(shell find $(SRC_DIRS) -name "*.c")
TARGET := webserver
CC := gcc
OBJ := $(SRC_EVENT:.c=.o)
FLAG_EVENT := -levent
$(TARGET) : $(OBJ)
	$(CC) $^ -o $@ $(FLAG_EVENT)

%.o : %.c 
	$(CC) -c $< -o $@ $(FLAG_EVENT)

print:
	@echo "SRC EVENT = $(SRC_EVENT)"
	@echo "OBJ= $(OBJ)"
.PHONY:clean
clean:
	rm -rf $(TARGET) $(OBJ)
