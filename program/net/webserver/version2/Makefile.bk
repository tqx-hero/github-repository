SRC_DIRS := . /home/tqx/net/wrapper ./function/src
SRC_DIRS_THREAD := /home/tqx/net/thread-pool
SRC_NORMAL := $(shell find $(SRC_DIRS) -name "*.c")
SRC_THREAD := $(foreach dir,$(SRC_DIRS_THREAD),$(wildcard $(dir)/*.c))

OBJ_NORMAL := $(patsubst %.c,%.o,$(SRC_NORMAL))
OBJ_THREAD := $(SRC_THREAD:.c=.o)

OBJ := $(OBJ_NORMAL) $(OBJ_THREAD)

CFLAGE_THREAD := -pthread

TARGET := webserver
CC := gcc

BACKUP_DIR := ./backup

$(TARGET) : $(OBJ)
	$(CC) $^ -o $@ $(CFLAGE_THREAD)

$(OBJ_NORMAL) : %.o : %.c
	$(CC) -c $< -o $@

$(OBJ_THREAD) : %.o : %.c
	$(CC) -c $< -o $@ $(CFLAGE_THREAD)

print:
	@echo "src normal = $(SRC_NORMAL)"	
	@echo "src thread = $(SRC_THREAD)"	
	@echo "obj normal = $(OBJ_NORMAL)"	
	@echo "obj thread = $(OBJ_THREAD)"	
	@echo "obj = $(OBJ)"	

.PHONY: clean

clean :
	# [ ! -d "$(BACKUP_DIR)" ] && mkdir -p "$(BACKUP_DIR)" || true
	mkdir -p "$(BACKUP_DIR)"
	tar -zcvf $(BACKUP_DIR)/webserver-backup.tar.gz \
	$(HOME)/net/webserver/* \
	$(HOME)/net/wrapper/* \
	$(HOME)/net/thread-pool/* 
	rm -rf $(TARGET) $(OBJ)
