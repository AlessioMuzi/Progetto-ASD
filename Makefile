# Compilazione programma originale
albero_binario_di_ricerca: albero_binario_di_ricerca.c Makefile
	gcc -ansi -Wall -O albero_binario_di_ricerca.c -o albero_binario_di_ricerca
pulisci:
	rm -f albero_binario_di_ricerca.o
pulisci_tutto:
	rm -f albero_binario_di_ricerca albero_binario_di_ricerca.o
#
# Compilazione programma con contatori
#
albero_binario_di_ricerca_count: albero_binario_di_ricerca_count.c Makefile
	gcc -ansi -Wall -O albero_binario_di_ricerca_count.c -o albero_binario_di_ricerca_count
pulisci:
	rm -f albero_binario_di_ricerca_count.o
pulisci_tutto:
	rm -f albero_binario_di_ricerca_count albero_binario_di_ricerca_count.o