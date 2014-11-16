CC = gcc
BCSRC = better-console
SRC = src
OUT = bin
OBJECTS = main.o betterconsole.o

consoletris: $(OBJECTS)
	mkdir $(OUT)
	$(CC) -o $(OUT)/consoletris $(OBJECTS)

main.o:
	$(CC) -c $(SRC)/main.c -I./$(BCSRC)

betterconsole.o:
	$(CC) -c $(BCSRC)/betterconsole.c

clean:
	rm -rf $(OUT)
	rm -rf $(OBJECTS)

