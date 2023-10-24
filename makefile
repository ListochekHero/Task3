CC=gcc 
CFLAGS=-I.
LIBS=-lcjson
DEPS = main_s.h fs_operations.h mtools.h mtools_commands.h
OBJ = main.o
SOBJ = main_s.o fs_operations.o mtools.o mtools_commands.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

s: $(SOBJ)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm *.o main s