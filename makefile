main: main.o A4Main.o A4.o A2.o A1.o
	gcc -Wall -Werror -o game main.o A4Main.o A4.o A2.o A1.o -lm

main.o: main.c A4Main.c A4.c
	gcc -Wall -Werror -std=c11 -c A4Main.c A4.c main.c -lm

A4Main.o: A4Main.c
	gcc -Wall -Werror -std=c11 -c A4Main.c A4.c -lm

A4.o: A4.c
	gcc -Wall -Werror -std=c11 -c A4.c -lm

A2.o: A2.c
	gcc -Wall -Werror -std=c11 -c A2.c -lm

A1.o: A1.c
	gcc -Wall -Werror -std=c11 -c A1.c -lm

clean:
	@rm -f $(PROGRAMS) *.o core
