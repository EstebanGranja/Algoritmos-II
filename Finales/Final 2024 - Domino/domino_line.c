#include "domino_line.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "domino.h"

struct _s_line
{
     struct _line_node *first;
     unsigned int size;
};

struct _line_node
{
     domino tile;
     struct _line_node *next;
};

struct _line_node *create_node(domino t){
    line_iterator new_node = malloc(sizeof(struct _line_node));
    assert(new_node != NULL);
    new_node->tile = t;
    new_node->next = NULL;
    return new_node;
}

domino_line line_new(domino first)
{
    domino_line new_line = malloc(sizeof(struct _s_line));
    assert(new_line != NULL);
    new_line->first = create_node(first);
    new_line->size = 1;

    return new_line;
}

domino_line line_add(domino_line line, domino t)
{
    line_iterator aux = line->first;
    while(aux->next != NULL){
        aux = aux->next;
    }
    line_iterator new_node = create_node(t);
    aux->next = new_node;
    line->size++;
    return line;
}

unsigned int line_length(domino_line line)
{
    return (line->size);
}

bool line_n_correct(domino_line line, unsigned int n)
{
    assert(n < line->size);
    bool is_correct = true;
    line_iterator aux = line->first;
    line_iterator prev = aux;

    if(n == 0 && aux->next != NULL){
        is_correct = domino_matches(aux->tile, aux->next->tile);
    }

    if(n == (line->size-1)){
        while(aux->next != NULL){
            prev = aux;
            aux = aux->next;
        }
        is_correct = domino_matches(prev->tile, aux->tile);
    }

    else{
        unsigned int i = 0;
        while(i < n){
            prev = aux;
            aux = aux->next;
            i++;
        }
        is_correct = domino_matches(prev->tile, aux->tile) && 
                        domino_matches(aux->tile, aux->next->tile);
    }

    return is_correct;
}

int line_total_points(domino_line line)
{
    unsigned int sum = 0;
    line_iterator aux = line->first;
    while(aux!=NULL){
        sum = sum + (domino_up(aux->tile)) + domino_down(aux->tile);
        aux = aux->next;
    }

    return sum;
}

domino* line_to_array(domino_line line)
{
    domino *array = malloc(sizeof(domino) * line->size);
    unsigned int size = line->size;
    line_iterator aux = line->first;
    for (unsigned int i = 0; i < size; i++){
        array[i] = aux->tile;
        aux = aux->next;
    }
    return array;
}

void line_dump(domino_line line)
{
    domino* array = line_to_array(line);
    for (unsigned int i = 0u; i < line_length(line); i++)
    {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line)
{
    line_iterator aux = line->first;
    while(aux != NULL){
        line_iterator killme = aux;
        aux = aux->next;
        free(killme);
        killme = NULL;
    }
    free(line);
    line = NULL;
    return line;
}

line_iterator line_iterator_begin(domino_line line)
{
    line_iterator new = line->first;
    return new;
}

domino line_iterator_get(line_iterator lit)
{
    return (lit->tile);
}

line_iterator line_iterator_next(line_iterator lit)
{
    if(lit != NULL){
        lit = lit->next;
    }
    return lit;
}

bool line_iterator_end(line_iterator lit)
{
    return (lit->tile == NULL);
}