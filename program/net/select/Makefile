SRC_DIRS := .
SRC_DIRS_THREAD := /home/tqx/net/wrapper 
SRC_NORMAL := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
SRC_THREAD := $(shell find $(SRC_DIRS_THREAD) -name "*.c")

OBJ_NORMAL := $(SRC_NORMAL:.c=.o)
OBJ_THREAD := $(SRC_THREAD:.c=.o)

OBJ := $(OBJ_NORMAL) $(OBJ_THREAD)
CFLAG_THREAD := -pthread
CC := gcc
TARGET := server

$(TARGET) : $(OBJ)
	$(CC) $^ -o $@ $(CFLAG_THREAD)

#分组编译普通源文件与第三方库的源文件

$(OBJ_NORMAL) : %.o : %.c
	$(CC) -c $< -o $@

$(OBJ_THREAD) : %.o : %.c
	$(CC) -c $< -o $@ $(CFLAG_THREAD)

print:
	@echo "SRC normal = $(SRC_NORMAL)"
	@echo "SRC thread = $(SRC_THREAD)"
	@echo "obj normal = $(OBJ_NORMAL)"
	@echo "obj thread = $(OBJ_THREAD)"
	@echo "OBJ = $(OBJ)"

.PHONY:clean 
#定义清理规则
clean: 
	rm -rf $(TARGET) $(OBJ)	
