CC := gcc
DIR := appendix
SRC := src
TARGET := $(DIR)/program

CFLAGS := -Iincludes
include .make/lint.mk

SRCS := $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(DIR)/%.o, $(SRCS)) $(DIR)/main.o

.PHONY: all clean run debug

all: $(DIR) $(TARGET)

debug: CFLAGS += -g -O0
debug: all

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(DIR)/main.o: main.c | $(DIR)
	$(CC) $(CFLAGS) -c main.c -o $(DIR)/main.o

$(DIR)/%.o: $(SRC)/%.c | $(DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR):
	mkdir -p $(DIR)

clean:
	sudo rm -rf $(DIR)

run: $(TARGET)
	sudo ./$(TARGET)