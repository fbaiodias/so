all: escritor leitor escritor-helper leitor-pai

escritor: escritor.c consts.h
	gcc -g -o escritor escritor.c

leitor: leitor.c consts.h
	gcc -g -o leitor leitor.c

escritor-helper: escritor-helper.c consts.h
	gcc -g -o escritor-helper escritor-helper.c

leitor-pai: leitor-pai.c consts.h
	gcc -g -o leitor-pai leitor-pai.c

clean:
	rm -f leitor escritor escritor-helper leitor-pai *.txt
