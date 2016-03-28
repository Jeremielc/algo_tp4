all : main queue genere_graph
	gcc genere_graphe_0.o main.o queue.o -std=c99 -Wall -o output
	rm -rf *.o
	./output > trace.txt
	nano trace.txt || vi trace.txt || vim trace.txt

genere_graph : sources/genere_graphe_0.c
	gcc -c sources/genere_graphe_0.c -std=c99 -Wall

main : sources/main.c
	gcc -c sources/main.c -std=c99 -Wall

queue : sources/queue.c
	gcc -c sources/queue.c -std=c99 -Wall

zip : 
	zip -r TP4_Jeremie_Leclerc_Pierrick_Hue.zip sources/ graphe_alea.txt Makefile output trace.txt
