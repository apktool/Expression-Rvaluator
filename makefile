CFLAGS=-Wall -std=c++11
CC=g++
BIN=a.out
OBJS=main.o Node.o Scanner.o Parser.o SymbolTable.o Storage.o Calc.o FunctionTable.o Exception.o

$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) 

%.o:%.c
	$(CC) %< -o $@ $(CFLAGS) -c

.PHONY:clean
clean:
	@echo delete object file and a.out 
	@-rm -f *.o $(BIN) 
