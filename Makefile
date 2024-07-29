CC=gcc
CFLAGS= -g
DEPS=city.h neighbor.h source.h vector.h 
OBJ=main.o city.o neighbor.o source.o vector.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

principal: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	echo "Compilado!"

clear:
	rm -rf *.o principal

run:
	./principal