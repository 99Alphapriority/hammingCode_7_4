#! /bin/bash

SRC = ../src
INC = ../include
BIN = ../bin
OBJ = ../obj
CC = gcc

OBJS = $(OBJ)/main.o $(OBJ)/hamming_calculations.o $(OBJ)/hamming_validation.o

$(BIN)/hamming_code: $(OBJS)
		CC -o $@ $(OBJS)

$(OBJS): $(OBJ)/%.o: $(SRC)/%.c
		mkdir -p $(OBJ) $(BIN)
		CC -c -w $< -o $@ -I $(INC)

clean:
		rm -rf $(BIN) $(OBJS) $(OBJ)
