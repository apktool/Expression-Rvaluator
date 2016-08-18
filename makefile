CFLAGS=-Wall -std=c++11
CC=g++
BIN=a.out
OBJS=main.o Node.o Scanner.o Parser.o

$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) 

%.o:%.c
	$(CC) %< -o $@ $(CFLAGS) -c

.PHONY:clean
clean:
	@echo delete object file and a.out 
	@-rm -f *.o $(BIN) 
