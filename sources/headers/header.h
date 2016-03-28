#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define WHITE           0
#define GREY            1
#define BLACK           2

#define MAXSOMMET       250
#define MAXVALUATION    20.0
#define MAXSUCC         10

typedef int ELEMENT;

typedef struct CELL {
    ELEMENT value;
    struct CELL* next;
} CELL;

typedef struct QUEUE {
    CELL* head;
    CELL* tail;
} QUEUE;

typedef struct COMPO_CONNEXES_STR_T {
    int* composantes_connexes;
    int nbComposantes;
} COMPO_CONNEXES_STR_T;

typedef struct GRAPH {
    int nbSummit;
    int nbArc;
    float** matrix; /* matrice d'adjacence */
    char* nodeStatus;
    COMPO_CONNEXES_STR_T con_info;
} GRAPH;

typedef struct {
    int* parent;
    int nbElem;
    int nbClass;
} t_ens;

//queue.c
QUEUE newEmptyQueue(void);
int isEmpty(QUEUE f);
ELEMENT getHead(QUEUE f);
QUEUE add(ELEMENT e, QUEUE f);
QUEUE get(QUEUE f);
ELEMENT add_2(QUEUE* f);
void concat(QUEUE* f1, QUEUE* f2);
void displayQueue(char* msg, QUEUE f);

//genere_graph_0.c
void afficher_graph(const GRAPH*);
void init_ens(int, t_ens*);
void init_graphe(int, int, GRAPH*);
void cree_graphe_connexe_non_value(char*, int, int);
void cree_graphe_connexe_value(char*, int, int);
void cree_graphe_non_oriente_value(char*, int, int);
void cree_graphe_non_oriente_non_value(char*, int, int);
void cree_graphe_oriente_value(char*, int, int);
void cree_graphe_oriente_non_value(char*, int, int);
void cree_graphe_topo_value(char*, int, int);
void cree_graphe_topo_non_value(char*, int, int);
void reunir(int, int, t_ens*);
int trouver(int, t_ens*);

//main.c
void loadGraph(char*, GRAPH*);
int visiteProfondeur(GRAPH*, int);
bool parcoursProfondeur(GRAPH*);
int visiteLargeur(GRAPH*, int);
bool ParcoursLargeur(GRAPH*);

#endif
