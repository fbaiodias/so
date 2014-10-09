all: escritor leitor

escritor: escritor.c
	gcc -g -o escritor escritor.c

leitor: leitor.c
	gcc -g -o leitor leitor.c

clean: 
	rm -f leitor escritor *.txt
