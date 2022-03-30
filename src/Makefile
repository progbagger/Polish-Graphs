all: graph

graph: graph.c string_analysis.o cstack.o stack.o
	gcc -Wall -Werror -Wextra graph.c string_analysis.o cstack.o stack.o -o ../build/graph

stack.o: stack.c stack.h
	gcc -Wall -Werror -Wextra -c stack.c

string_analysis.o: string_analysis.c string_analysis.h
	gcc -Wall -Werror -Wextra -c string_analysis.c

cstack.o: cstack.c cstack.h
	gcc -Wall -Werror -Wextra -c cstack.c

clean:
	rm -rf *.o *.a *.out ../build/graph