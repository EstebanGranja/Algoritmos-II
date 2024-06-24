#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct s_node {
    stack_elem *chunk[CHUNK_CAPACITY];
    unsigned int used;
    struct s_node *next;
};

struct _s_stack {
    struct s_node *top;
    unsigned int size;
};

static bool valid_chunks(stack s) {
    bool valid=true;
    struct s_node *check=s->top;
    if (check!=NULL) {
        valid = valid && (check->chunk != NULL) && (check->used <= CHUNK_CAPACITY);
    }
    return valid;
}

static bool invrep(stack s) {
    bool res = true;
    res = (s != NULL);
    unsigned int length = 0;
    if (s->top != NULL){
        struct s_node *aux = s->top;
        while(aux != NULL){
            aux = aux->next;
            length++;
        }
    }
    res = res && (s->size == length);
    return res;
}

static struct s_node *create_node(void) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->chunk[CHUNK_CAPACITY] = malloc(sizeof(stack_elem) * CHUNK_CAPACITY);
    new_node->used = 0;
    new_node->next = NULL;
}


static struct s_node *destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}

stack stack_empty(void) {
    stack new_stack = malloc(sizeof(struct _s_stack));
    assert(new_stack != NULL);
    new_stack->top = NULL;
    new_stack->size = 0;
    return new_stack;
}


stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    if ((s->top)->used < CHUNK_CAPACITY){
        (s->top)->chunk[(s->top)->used] = e;
        (s->top)->used++;
    }
    else{
        struct s_node *new_node = create_node();
        new_node->chunk[new_node->used] = e;
        new_node->next = s->top;
        s->top = new_node;
        new_node->used++;
    }
    s->size++;
    return s;
}


stack stack_pop(stack s) {
    assert(invrep(s));
    if((s->top)->used == 1){
        struct s_node *killme = s->top;
        s->top = (s->top)->next;
        destroy_node(killme);
    }
    else{
        (s->top)->used--;
    }
    s->size--;
    return s;
}


unsigned int stack_size(stack s) {
    return s->size;
}

void stack_top(stack s, stack_elem *top) {
    assert(invrep(s) && (s->top)->used != 0);
    *top = ((s->top)->chunk[(s->top)->used]);
}

bool stack_is_empty(stack s) {
    return (s->top == NULL);
}

stack_elem *stack_to_array(stack s) {
  stack_elem *array = NULL;
  array = malloc(sizeof(stack_elem)*s->size);
  struct s_node *aux = s->top;

  int i = s->size - 1; // O SEA, va desde el nodo N hasta el 0..

    if(s->size == 0){
        return array;
    }

    while(aux != NULL){
        for(int j = aux->used -1; j<=0; j--){
            array[i] = aux->chunk[j];
            i--;
        }
        aux = aux->next;
    }
}


stack stack_destroy(stack s) {
    assert(invrep(s));
    struct s_node *aux = NULL;
    while(s->top != NULL){
        aux = s->top;
        s->top = aux->next;
        aux = destroy_node(aux);
    }
    free(s);
    s = NULL;
    return s;
}

