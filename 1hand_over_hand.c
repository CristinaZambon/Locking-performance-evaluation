//
// Created by Cristina Zambon on 04/12/21.
//
#include "lib.h"
#include <stdio.h>
#include <sys/time.h>
#define MILION 1000000
#include <stdlib.h>

typedef struct node
{int val;
    struct node *next;
    struct node *prev;
    pthread_mutex_t mutex;
} node;

typedef struct list
{ node *head;
    pthread_mutex_t mutex;
} linked_list;

static node * create_node (int val)
{node *new_node = (node *) malloc (sizeof (node));
    if (new_node == NULL)
    {   fprintf(stderr,"malloc");
        return NULL;
    }
    new_node->val = val;
    new_node->next = NULL;
    new_node->prev = NULL;
    Pthread_mutex_init (&new_node->mutex, NULL);
    return new_node;
}

static void initialize_list (linked_list * list)
{   list->head = NULL;
    Pthread_mutex_init (&list->mutex, NULL);
}

static void insert_value (linked_list * L, int val)
{
    if (!L) //list doesn't exist
    {  fprintf (stderr, "initialisation error");
        return;
    }
    pthread_mutex_lock (&(L->mutex)); //lock the mutex of the list
    if (!(L->head)) //list is empty
    { L->head = create_node (val);
        Pthread_mutex_unlock (&(L->mutex));
    }
    else //list is not empty
    { node *h_pointer = L->head;
        Pthread_mutex_unlock (&(L->mutex)); //unlock list mutex
        pthread_mutex_lock (&(h_pointer->mutex)); //lock head mutex
      
        node *new_node = create_node (val);
       
       //add node to starting of the list
            h_pointer->prev = new_node;
            new_node->next = h_pointer;
            Pthread_mutex_unlock (&(h_pointer->mutex));
        
        pthread_mutex_lock (&(L->mutex));
        L->head = new_node;
        Pthread_mutex_unlock (&(L->mutex));
        
       
       
    }
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

static void * thread_function (void *args)
{
    linked_list *l = (linked_list *) args;
    int max = 1000000;
    for (int y = 0; y < max; y++)
    {
        insert_value (l, rand ());
    }
    pthread_exit (EXIT_SUCCESS);
}

int main (int argc, char *argv[])
{   int num_thread = 2;
    linked_list *list = malloc (sizeof (linked_list));
    if (list == NULL)
     {fprintf (stderr, "error");
        exit (EXIT_FAILURE);
    }
    initialize_list (list);

    struct timeval start, end;
    if (gettimeofday (&start, NULL) != 0)
    { fprintf (stderr, "error");
        exit (EXIT_FAILURE);}

    pthread_t *pts = malloc ((size_t) num_thread * sizeof (pthread_t));
    if (pts == NULL)
    { fprintf (stderr, "error");
        exit (EXIT_FAILURE);}

    for (int j = 0; j < num_thread; j++)
    { Pthread_create (&pts[j], NULL, &thread_function, list);
    }
    for (int k = 0; k < num_thread; k++)
    {  Pthread_join (pts[k], NULL);
    }
    
    node *curr = list->head;
    while (curr) {
        printf("%d\n", curr->val);
        curr = curr->next;
    }

    if (gettimeofday (&end, NULL) != 0)
    {
        fprintf (stderr, "error");
        exit (EXIT_FAILURE);
    }
    long long start_microSec, end_microsec;
    start_microSec = start.tv_sec * MILION + start.tv_usec;
    end_microsec = end.tv_sec * MILION + end.tv_usec;
    printf("Evaluating the hand-over-hand locking with the 3rd workload: the threads terminate after: %f (seconds)\n\n",
           ((double) (end_microsec - start_microSec) / MILION));
    free (pts);
    freeingList (list);
    return 0;
}
