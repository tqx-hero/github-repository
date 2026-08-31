# Makefile

1. wildcard函数：

   ```makefile
   #扫描指定包下面的指定文件。如果有多个可以使用空格隔开
   SRC := $(wildcard ./*.c ../file/*.c)
   #也可以使用+=拼接
   SRC += $(wildcard /home/*.c)
   #或者使用linux的find指令,注意使用''或者""把条件看作一个整体
   SRC := $(shell find ./ -name '*.c')
   #也可以使用foreach，迭代获取一个目录集合下面的所有制定文件
   SRC_DIRS := . src dev	#定义目录集合，后续可直接从这里添加目录
   SRC := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
   ```

   

2. patsubst:

   ```makefile
   #GNU make内置函数，将待处理的字符串，通过模式匹配，替换成替换文本
   #语法：$(patsubst 模式,替换文本,待处理字符串)
   # %是通配符，匹配任意长度的字符
   #将SRC的所有.c后缀的字符串全部替换成.o字符串,立即赋值给OBJ变量
   OBJ := $(patsubst %.c,%.o,$(SRC))
   #可以使用语法糖写法，更简洁：
   OBJ := $(SRC:.c=.o)
   ```

   

3. demo:

   ```makefile
     1 #使用2个函数，分别用来获取指定目录下的文件、根据指定要求对文件进行替换
     2 #$(wildcard [路径])用来获得指定路径下的文件,多个路径可用空格隔开
     3 #可使用如下方法，调用foreach函数迭代获取所有SRC_DIRS目录下的.c文件
     4 SRC_DIRS := .
     5 SRC := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
     6 #可以通过+=拼接
     7 SRC += $(wildcard file/*.c)
     8 #OBJ = test.o add.o sub.o mul.o div.o
     9 #使用patsubst函数可以将制定文件按需求进行替换
    10 #下面使用的是将$(SRC)下的所有.c文件全部替换为.o文件
    11 #OBJ := $(patsubst %.c,%.o,$(SRC))
    12 OBJ := $(SRC:.c=.o)		#注意这里语法糖中的:.c=.o之间不能用空格隔开,否则会把OBJ识别为.c文件
    13 TARGET = test
    14 GCC = gcc
    15 $(TARGET) : $(OBJ)
    16         $(GCC) $^ -o $@
    17
    18 %.o : %.c
    19         $(GCC) -c $< -o $@
    20
    21 print:
    22         @echo "SRC = $(SRC)"
    23         @echo "OBJ = $(OBJ)"
    24
    25 clean :
    26         rm -rf $(OBJ) $(TARGET)
   ```

   

4. 需要分组编译：

   ```makefile
   CC := gcc
   CFLAGS := -Wall -g
   # 第三方库额外编译链接参数，例如 libcurl
   THIRD_CFLAGS := -DUSE_THIRD
   THIRD_LDFLAGS := -lcurl
   
   # 普通c文件，不需要第三方库
   SRCS_NORMAL := main.c util.c
   # 需要第三方库的c文件
   SRCS_THIRDPARTY := http_client.c net_api.c
   
   OBJS_NORMAL := $(SRCS_NORMAL:.c=.o)
   OBJS_THIRDPARTY := $(SRCS_THIRDPARTY:.c=.o)
   OBJS := $(OBJS_NORMAL) $(OBJS_THIRDPARTY)
   
   TARGET := app
   
   all: $(TARGET)
   
   # 链接阶段，整体链接第三方库
   $(TARGET): $(OBJS)
   	$(CC) $^ -o $@ $(THIRD_LDFLAGS)
   
   # ========== 重点：分组编译 ==========
   # 普通.o：使用默认CFLAGS
   $(OBJS_NORMAL): %.o: %.c
   	$(CC) $(CFLAGS) -c $< -o $@
   
   # 第三方源码对应的.o：追加额外编译标志
   $(OBJS_THIRDPARTY): %.o: %.c
   	$(CC) $(CFLAGS) $(THIRD_CFLAGS) -c $< -o $@
   #添加.PHONY声明clean为目标,当Makefile所在文件夹出现clean文件时，避免出现歧义
   .PHONY:clean
   clean:
   	rm -f $(OBJS) $(TARGET)
   
   ```

   

5. 