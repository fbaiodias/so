all: clean escritor leitor escritor-helper

escritor: escritor.c consts.h
	gcc -g -o escritor escritor.c

leitor: leitor.c consts.h
	gcc -g -o leitor leitor.c

escritor-helper: escritor-helper.c consts.h
	gcc -g -o escritor-helper escritor-helper.c

clean: 
	rm -f leitor escritor escritor-helper *.txt
