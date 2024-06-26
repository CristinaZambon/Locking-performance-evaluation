//
// Created by Cristina Zambon on 04/12/21.
//
#include "lib.h"
#include <stdio.h>
#include <sys/time.h>
#define MILION 1000000
#include <stdlib.h>

typedef struct node
{   int val;
    struct node *next;
} node;

typedef struct list
{ node *head;
    pthread_mutex_t mutex;
} linked_list;

static void initialize_list (linked_list * list)
{   list->head = NULL;
    Pthread_mutex_init (&list->mutex, NULL);
}
static void insert_node(linked_list * list, int val)
{ node *new_node = (node *) malloc (sizeof (node));
    if (new_node == NULL)
    {   fprintf(stderr,"malloc");
    }
    new_node->val = val;
    Pthread_mutex_lock(&list->mutex);
    new_node->next = list->head;
    list->head = new_node;
    Pthread_mutex_unlock(&list->mutex);
}


static void freeingList (linked_list * linkedList)
{
    Pthread_mutex_lock (&linkedList->mutex);
    node *n = linkedList->head;
    while (n)
    {
        node *temp = n;
        n = n->next;
        free (temp);
    }
    Pthread_mutex_unlock (&linkedList->mutex);
    free (linkedList);
}

static int List_Lookup(linked_list *L, int key) {
    int rv = -1;
    Pthread_mutex_lock(&L->mutex);
    node *curr = L->head;
    while (curr) {
        if (curr->val == key) {
            rv = 0;
            break;
        }
        curr = curr->next;
    }
    Pthread_mutex_unlock(&L->mutex);
    return rv; // now both success and failure
}

static void *thread_function_lookUp(void *args) {
    linked_list *l = (linked_list *)args;
    for(int i=0; i<10000;i++){
        List_Lookup(l, rand());}
    pthread_exit(EXIT_SUCCESS);
}

int main (int argc, char *argv[])
{   int num_thread = 2;
    linked_list *list = malloc (sizeof (linked_list));
    if (list == NULL)
    {fprintf (stderr, "error");
        exit (EXIT_FAILURE);
    }
    initialize_list (list);
    pthread_t *pts = malloc ((size_t) num_thread * sizeof (pthread_t));
    if (pts == NULL)
    { fprintf (stderr, "error");
        exit (EXIT_FAILURE);}

//here its different
    for (int y = 0; y < 100000; y++)
    {   
        node *newNode = malloc(sizeof(struct node));
        newNode->val = rand();
        newNode->next = list->head;
        list->head = newNode;

    }
   

    struct timeval start, end;
    if (gettimeofday (&start, NULL) != 0)
    { fprintf (stderr, "error");
        exit (EXIT_FAILURE);}
    pthread_create (&pts[0], NULL, &thread_function_lookUp, list);
    pthread_create (&pts[1], NULL, &thread_function_lookUp, list);

    for (int k = 0; k < num_thread; k++)
    {  Pthread_join (pts[k], NULL);
    }

    if (gettimeofday (&end, NULL) != 0)
    {
        fprintf (stderr, "error");
        exit (EXIT_FAILURE);
    }
    long long start_microSec, end_microsec;
    start_microSec = start.tv_sec * MILION + start.tv_usec;
    end_microsec = end.tv_sec * MILION + end.tv_usec;
    printf("\nEvaluating the simple lock with the 3rd workload: the threads terminate after %f (seconds)\n\n",
           ((double) (end_microsec - start_microSec) / MILION));
    free (pts);
    freeingList (list);
    return 0;
}
