SRC_DIRS := . /home/tqx/net/wrapper 
SRC_DIRS_THREAD := /home/tqx/net/thread-pool
SRC_NORMAL := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
SRC_WITH_THREAD := $(foreach dir,$(SRC_DIRS_THREAD),$(wildcard $(dir)/*.c))
OBJ_NORMAL := $(SRC_NORMAL:.c=.o)
OBJ_THREAD := $(SRC_WITH_THREAD:.c=.o)
OBJ := $(OBJ_NORMAL) $(OBJ_THREAD)
CFLAGS_THREAD := -pthread
TARGET := server
CC := gcc

$(TARGET) : $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS_THREAD)

#使用分组编译，线程相关的需要添加第三方库
$(OBJ_THREAD): %.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS_THREAD)

#普通编译
$(OBJ_NORMAL): %.o : %.c
	$(CC) -c $< -o $@ 

.PHONY:clean 

clean:
	rm -rf $(OBJ) $(TARGET)	

print:
	@echo "SRC = $(SRC_NORMAL)"
	@echo "SRC THREAD = $(SRC_WITH_THREAD)"
	@echo "OBJ NOR= $(OBJ_NORMAL)"
	@echo "OBJ TH= $(OBJ_THREAD)"
	@echo "OBJ ALL= $(OBJ)"

