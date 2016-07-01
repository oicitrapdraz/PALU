palu: palu.o matrix.o matrix.h
	gcc palu.o matrix.o -o palu

palu.o: palu.c matrix.h
	gcc -c palu.c

matrix.o: matrix.c matrix.h
	gcc -c matrix.c

clean:
	rm -rf *~
	rm -rf *.o
