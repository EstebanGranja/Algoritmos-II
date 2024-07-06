#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"

typedef int elem_t;



static void elem_dump(elem_t e, FILE *fd) {
    fprintf(fd, "%d", e);
}

struct node_t_ {
    elem_t elem;
    struct node_t_ *next;
};

struct set_t_ {
    unsigned int size;
    struct node_t_ *fst;
};

typedef struct node_t_ *node_t;

static node_t create_node(elem_t elem, node_t next) {
    node_t new_node = NULL;
    new_node = malloc(sizeof(struct node_t_));
    assert(new_node != NULL);
    new_node->elem = elem;
    new_node->next = next;
    return new_node;
}

static node_t destroy_node(node_t node) {
    free(node);
    node = NULL;
    return node;
}


/**
 * Creates an empty set.
 * 
 * @return The newly created set.
 */
set_t set_empty(void) {
    set_t new_set = NULL;
    new_set = malloc(sizeof(struct set_t_));
    assert(new_set != NULL);
    new_set->size = 0;
    new_set->fst = NULL;
    return new_set;
}

set_t set_add(set_t set, int element) {
    node_t aux = set->fst;
    while(aux != NULL){
        if(aux->elem == element){
            return set;
        }
        aux = aux->next;
    }
    node_t new_node = create_node(element, set->fst);
    set->fst = new_node;
    set->size++;
    return set;
}

bool set_is_empty(set_t set) {
    return (set->size == 0);
}

bool set_belongs(set_t set, int element) {
    node_t aux = set->fst;
    while(aux != NULL){
        if(aux->elem == element){
            return true;
        }
        aux = aux->next;
    }
    return false;
}

unsigned int set_size(set_t set) {
    return (set->size);
}

/**
 * Adds a clone of the given element to the set or frees the element if it already exists in the set.
 * 
 * @param set The set to add the element to.
 * @param elem The element to add to the set.
 * @return The updated set after adding the element.
 */
/*static set_t add_clone_or_free(set_t set, elem_t elem) {

    // if the element already exists -> free
    if(set_belongs(set, elem)){      
        node_t aux = set->fst;

        // deletes the first elem of the set
        if(set->fst->elem == elem){  
            set->fst = set->fst->next;
            destroy_node(aux);
            return set;
        }

        // else it goes from the second to the last
        else{
            node_t prev = aux;  
            aux = aux->next;
            while(aux != NULL){
                if(aux->elem == elem){
                    prev->next = aux->next;
                    destroy_node(aux);
                    return set;
                }
                prev = aux;
                aux = aux->next;
            }
        }
        set->size--;   
    }

    // if it doesnt belong -> adds the element to the set
    else{              
        node_t new_node = create_node(elem, set->fst);
        set->fst = new_node;
        set->size++;
        return set;
    }

    return set;
}
*/

static set_t set_clone(set_t set) {
    set_t copy = set_empty();
    node_t aux = set->fst;
    while(aux != NULL){
        set_add(copy, aux->elem);
        aux = aux->next;
    }
    return copy;
}

set_t set_union(set_t set1, set_t set2) {

    // if both sets are empty
    if(set_is_empty(set1) && set_is_empty(set2)){
        set_t union_set = set_empty();
        return union_set;
    }

    // if just one of them is empty
    if(set_is_empty(set1) && !set_is_empty(set2)){
        set_t union_set = set_clone(set2);
        return union_set;
    }
    if(set_is_empty(set2) && !set_is_empty(set1)){
        set_t union_set = set_clone(set1);
        return union_set;
    }

    // if none of them are empty
    else{
        set_t union_set = set_clone(set1);
        node_t aux = set2->fst;

        while(aux != NULL){
            set_add(union_set, aux->elem);
            aux = aux->next;
        }
        
        return union_set;
    }
}

set_t set_intersect(set_t set1, set_t set2) {
    set_t inter_set = set_empty();

    if(!set_is_empty(set1) && !set_is_empty(set2)){
        node_t aux = set1->fst;
        while(aux != NULL){ 
            if(set_belongs(set2, aux->elem)){
                set_add(inter_set, aux->elem);
            }
            aux = aux->next;
        }
    }
    
    return inter_set;
}

set_t set_destroy(set_t set) {
    node_t aux = set->fst;
    while(aux != NULL){
        node_t killme = aux;
        aux = aux->next;
        destroy_node(killme);
    }
    free(set);
    set = NULL;
    return set;
}

void set_dump(set_t set, FILE *fd) {
    assert(set != NULL);
    node_t current = set->fst;
    fprintf(fd, "{");
    while (current != NULL) {
        elem_dump(current->elem, fd);
        current = current->next;
        if (current != NULL) {
            fprintf(fd, ",");
        }
    }
    fprintf(fd, "}");
}
