all: clean escritor leitor escritor-helper

escritor: escritor.c
	gcc -g -o escritor escritor.c

leitor: leitor.c
	gcc -g -o leitor leitor.c

escritor-helper: escritor-helper.c
	gcc -g -o escritor-helper escritor-helper.c

clean: 
	rm -f leitor escritor escritor-helper *.txt
