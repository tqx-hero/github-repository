#使用2个函数，分别用来获取指定目录下的文件、根据指定要求对文件进行替换
#$(wildcard [路径])用来获得指定路径下的文件,多个路径可用空格隔开
#可使用如下方法，调用foreach函数迭代获取所有SRC_DIRS目录下的.c文件
SRC_DIRS := . 
SRC := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
#可以通过+=拼接
SRC += $(wildcard file/*.c)
#OBJ = test.o add.o sub.o mul.o div.o
#使用patsubst函数可以将制定文件按需求进行替换
#下面使用的是将$(SRC)下的所有.c文件全部替换为.o文件
#OBJ := $(patsubst %.c,%.o,$(SRC))
OBJ := $(SRC:.c=.o)
TARGET = test
CC = gcc
$(TARGET) : $(OBJ)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) -c $< -o $@

print:
	@echo "SRC = $(SRC)"
	@echo "OBJ = $(OBJ)"

clean : 
	rm -rf $(OBJ) $(TARGET)
