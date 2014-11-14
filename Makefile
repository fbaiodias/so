all: escritor leitor escritor-helper leitor-pai leitor-threads-2 leitor-threads-3

escritor: escritor.c consts.h
	gcc -g -o escritor escritor.c

leitor: leitor.c consts.h
	gcc -g -o leitor leitor.c

escritor-helper: escritor-helper.c consts.h
	gcc -g -o escritor-helper escritor-helper.c

leitor-pai: leitor-pai.c consts.h
	gcc -g -o leitor-pai leitor-pai.c

leitor-threads-2: leitor-threads-2.c consts.h
	gcc -g -o leitor-threads-2 leitor-threads-2.c -lpthread

leitor-threads-3: leitor-threads-3.c consts.h
	gcc -Wall -g -o leitor-threads-3 leitor-threads-3.c -lpthread

clean:
	rm -f leitor escritor escritor-helper leitor-pai leitor-threads-2 leitor-threads-3 *.txt
