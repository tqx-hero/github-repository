SRC_DIRS := . 
SRC := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJ := $(SRC:.c=.o)
TARGET := thread-pool

print:
	@echo "SRC = $(SRC)"
	@echo "OBJ = $(OBJ)"


