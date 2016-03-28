//main.c
/* Jérémie Leclerc & Pierrick Hue */

#include "headers/header.h"

int main() {
    GRAPH graph;
    int i;

    loadGraph("./graphe_alea.txt", &graph);
    
    printf("%s\n", "################ Matrice d'adjacence ################");
    afficher_graph(&graph);

    printf("\n%s\n", "################ Parcours en profondeur ################");
    parcoursProfondeur(&graph);
    printf("Nombre de composants : %d\n", graph.con_info.nbComposantes);

    for (i = 0; i < graph.nbSummit; i++) {
        printf("%d | ", i);
    }

    printf("\n");

    for (i = 0; i < graph.nbSummit; i++) {
        printf("%d | ", graph.con_info.composantes_connexes[i]);
    }

    printf("\n");

    free(graph.con_info.composantes_connexes);

    printf("\n%s\n", "################ Parcours en largeur ################");
    ParcoursLargeur(&graph);
    printf("\nNombre de composants : %d\n", graph.con_info.nbComposantes);

    for (i = 0; i < graph.nbSummit; i++) {
        printf("%d | ", i);
    }

    printf("\n");

    for (i = 0; i < graph.nbSummit; i++) {
        printf("%d | ", graph.con_info.composantes_connexes[i]);
    }

    printf("\n");

    free(graph.con_info.composantes_connexes);

    return 0;
}

void loadGraph(char* filename, GRAPH* graph) {
    FILE* canal = NULL;
    int nbLine = 0, x, y;

    if (filename == NULL || graph == NULL) {
        printf("%s\n", "Error - NULL");
        return;
    }

    canal = fopen(filename, "rt");
    if (canal == NULL) {
        printf("%s\n", "Error - NULL");
        return;
    }

    fscanf(canal, "%d %d", &graph->nbSummit, &graph->nbArc);
    graph->matrix = (float**) calloc(graph->nbSummit, sizeof (float*));

    if (graph->matrix == NULL) {
        printf("%s\n", "Error - NULL");
        fclose(canal);
        return;
    }

    for (nbLine = 0; nbLine < graph->nbSummit; nbLine++) {
        graph->matrix[nbLine] = (float*) calloc(graph->nbSummit, sizeof (float));

        if (graph->matrix[nbLine] == NULL) {
            printf("%s\n", "Error - NULL");
            fclose(canal);
            return;
        }
    }

    for (nbLine = graph->nbArc; nbLine >= 0; nbLine--) {
        fscanf(canal, "%d %d", &x, &y);

        graph->matrix[x][y] = 1;
        graph->matrix[y][x] = 1;
    }

    fclose(canal);
}

int visiteProfondeur(GRAPH* graph, int nbSummit) {
    int y, nodeNumber = 0;

    if (nbSummit < 0) {
        return 0;
    }

    if (graph->nodeStatus == NULL) {
        return 0;
    }

    graph->nodeStatus[nbSummit] = GREY;
    printf("Noeud prefixe : %d\n", nbSummit);

    for (y = 0; y < graph->nbSummit; y++) {
        if (graph->matrix[nbSummit][y] == 0) {
            continue;
        }

        if (graph->nodeStatus[y] == WHITE) {
            nodeNumber += visiteProfondeur(graph, y);
        }
    }

    graph->nodeStatus[nbSummit] = BLACK;
    nodeNumber++;
    graph->con_info.composantes_connexes[nbSummit] = graph->con_info.nbComposantes;
    printf("Noeud suffixe : %d\n", nbSummit);

    return nodeNumber;
}

bool parcoursProfondeur(GRAPH* graph) {
    int x = 0, nodeNumber = 0;

    if (graph == NULL) {
        return false;
    }

    graph->con_info.nbComposantes = 0;
    graph->con_info.composantes_connexes = (int*) calloc(graph->nbSummit, sizeof (int));
    graph->nodeStatus = (char*) calloc(graph->nbSummit, sizeof (char));

    if (graph->nodeStatus == NULL) {
        return false;
    }

    for (x = 0; x < graph->nbSummit; x++) {
        if (graph->nodeStatus[x] == WHITE) {
            graph->con_info.nbComposantes++;
            nodeNumber += visiteProfondeur(graph, x);
        }
    }

    printf("Nombre de noeuds visites : %d\n", nodeNumber);
    free(graph->nodeStatus);
    graph->nodeStatus = NULL;

    return graph->con_info.nbComposantes == 1;
}

int visiteLargeur(GRAPH* graph, int nbSummit) {
    int y, nodeNumber = 0;
    QUEUE queue;

    if (nbSummit < 0) {
        return 0;
    }

    if (graph->nodeStatus == NULL) {
        return 0;
    }

    graph->nodeStatus[nbSummit] = GREY;
    queue = newEmptyQueue();
    queue = add(nbSummit, queue);

    while (!isEmpty(queue)) {
        int nbSommet = getHead(queue);

        for (y = 0; y < graph->nbSummit; y++) {
            if (graph->matrix[nbSommet][y] == 0) {
                continue;
            }

            if (graph->nodeStatus[y] != WHITE) {
                continue;
            }

            graph->nodeStatus[y] = GREY;
            queue = add(y, queue);
        }

        queue = get(queue);
        graph->nodeStatus[nbSommet] = BLACK;
        printf("Noeud visité : %d\n", nbSommet);
        graph->con_info.composantes_connexes[nbSommet] = graph->con_info.nbComposantes;
        nodeNumber++;
    }

    return nodeNumber;
}

bool ParcoursLargeur(GRAPH* graph) {
    int nodeNumber = 0, x = 0;

    if (graph == NULL) {
        return false;
    }

    graph->con_info.nbComposantes = 0;
    graph->con_info.composantes_connexes = (int*) calloc(graph->nbSummit, sizeof (int));
    graph->nodeStatus = (char*) calloc(graph->nbSummit, sizeof (char));

    if (graph->nodeStatus == NULL) {
        return false;
    }

    for (x = 0; x < graph->nbSummit; x++) {
        if (graph->nodeStatus[x] == WHITE) {
            graph->con_info.nbComposantes++;
            nodeNumber += visiteLargeur(graph, x);
        }
    }

    printf("Nombre de noeuds visites : %d\n", nodeNumber);
    free(graph->nodeStatus);
    graph->nodeStatus = NULL;

    return graph->con_info.nbComposantes == 1;
}