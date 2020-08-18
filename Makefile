all: programa

programa: sllist.o thash.o glist.o conjunto.o
	gcc -Wall -Wextra -Werror -g -std=c99 -o interprete interprete.c sllist.o thash.o glist.o conjunto.o -lm

sllist.o: ./SLList/sllist.c
	gcc -Wall -Wextra -Werror -g -std=c99 -c ./SLList/sllist.c

thash.o: ./THash/thash.c
	gcc -Wall -Wextra -Werror -g -std=c99 -c ./THash/thash.c

glist.o: ./GList/glist.c
	gcc -Wall -Wextra -Werror -g -std=c99 -c ./GList/glist.c

conjunto.o: ./Conjunto/conjunto.c
	gcc -Wall -Wextra -Werror -g -std=c99 -c ./Conjunto/conjunto.c

clean:
	rm -f programa *.o
