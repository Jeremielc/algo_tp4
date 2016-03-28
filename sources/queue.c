//file.c
/* Christine PORQUET */
#include "headers/header.h"

QUEUE newEmptyQueue(void) {
    QUEUE queue = {NULL, NULL};
    return queue;
}

int isEmpty(QUEUE queue) {
    return !queue.head;
}

ELEMENT getHead(QUEUE queue)
/* ATTENTION: consulter la tête d'une File vide n'a pas de sens */ {
    if (isEmpty(queue)) {
        printf("Error - The queue is empty\n");
        exit(-1);
    }
    
    return queue.head->value; /* la File n'est pas modifiée */
}

QUEUE add(ELEMENT element, QUEUE queue) {
    CELL *cell = (CELL*) malloc(sizeof (CELL));
    cell->value = element;
    cell->next = NULL;

    if (isEmpty(queue)) {
        queue.head = queue.tail = cell; /* la cellule créée est à la fois tête et queue */
    } else {
        queue.tail = queue.tail->next = cell; /* la cellule créée est la nouvelle queue	*/
    }
    
    return queue;
}

QUEUE get(QUEUE f)
/* ATTENTION: supprimer la tête d'une File vide n'a pas de sens */ {
    CELL *cell = f.head;
    
    if (isEmpty(f)) {
        printf("Error - The queue is empty\n");
        exit(-1);
    }

    if (f.head == f.tail) {
        f = newEmptyQueue(); /* la File n'avait plus qu'une seule cellule */
    } else {
        f.head = f.head->next; /* la queue ne change pas */
    }

    free(cell);

    return f;
}

ELEMENT add_2(QUEUE *queue) /* ATTENTION: la File est modifiée */
/* ATTENTION: supprimer la tête d'une File vide n'a pas de sens */ {
    ELEMENT element;
    CELL *cell = queue->head;

    if (isEmpty(*queue)) {
        printf("Error - The queue is empty\n");
        exit(-1);
    }

    element = queue->head->value;
    if (queue->head == queue->tail) {
        *queue = newEmptyQueue(); /* la File n'avait plus qu'une seule cellule */
    } else {
        queue->head = queue->head->next; /* la queue ne change pas */
    }

    free(cell);

    return element;
}

void concat(QUEUE *firstQueue, QUEUE *secondQueue) {
    if (firstQueue->head == NULL) {
        *firstQueue = *secondQueue;
    } else if (secondQueue->head != NULL) {
        firstQueue->tail->next = secondQueue->head;
        firstQueue->tail = secondQueue->tail;
    }

    *secondQueue = newEmptyQueue();
}

void displayQueue(char* msg, QUEUE queue) {
    CELL *cell = queue.head;
    int count = 0;

    printf("%s\n", msg);

    while (cell != NULL) {
        printf("%6d", cell->value);
        count++;

        if ((count % 10) == 0) {
            printf("\n");
        }

        cell = cell->next;
    }

    printf("\n");
}

