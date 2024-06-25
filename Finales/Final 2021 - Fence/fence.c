#include <stdlib.h>
#include "fence.h"

struct _fence_t {
    unsigned int size;
    type_t type;
    fence_t next;
};

fence_t fence_P(){
    struct _fence_t *new_fence = malloc(sizeof(struct _fence_t));
    assert(new_fence!=NULL);
    new_fence->size = 1;
    new_fence->next = NULL;
    new_fence->type = P;
    return new_fence;
}

fence_t fence_add_P(fence_t fence){
    struct _fence_t *new_fence = malloc(sizeof(struct _fence_t));
    assert(new_fence!=NULL);
    new_fence->type = P;
    new_fence->next = NULL;

    if(fence == NULL){
        new_fence->size = 1;
        return new_fence;
    }

    fence_t aux = fence;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = new_fence;
    fence->size++;
    return fence;
}

fence_t fence_add_A(fence_t fence){
    struct _fence_t *new_fence = malloc(sizeof(struct _fence_t));
    assert(new_fence!=NULL);
    new_fence->type = A;
    new_fence->next = NULL;

    if(fence == NULL){
        new_fence->size = 1;
        return new_fence;
    }

    fence_t aux = fence;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = new_fence;
    fence->size++;
    return fence;
}

fence_t fence_add_H(fence_t fence){
    struct _fence_t *new_fence = malloc(sizeof(struct _fence_t));
    assert(new_fence!=NULL);
    new_fence->type = H;
    new_fence->next = NULL;

    if(fence == NULL){
        new_fence->size = 1;
        return new_fence;
    }

    fence_t aux = fence;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = new_fence;
    fence->size++;
    return fence;
}

fence_t fence_add_T(fence_t fence){
    struct _fence_t *new_fence = malloc(sizeof(struct _fence_t));
    assert(new_fence!=NULL);
    new_fence->type = T;
    new_fence->next = NULL;

    if(fence == NULL){
        new_fence->size = 1;
        return new_fence;
    }

    fence_t aux = fence;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = new_fence;
    fence->size++;
    return fence;
}


bool fence_is_correct(fence_t fence){
    bool is_correct = false;
    fence_t aux = fence;
    fence_t prev = NULL;
    while(aux != NULL){
        if (aux->type == T){
            is_correct = true;

            if (prev->type != P){
                is_correct = false;
            }

            if (prev == NULL || aux->next == NULL){
                is_correct = false;
            }
        prev = aux;
        aux = aux->next;
        }
    } 
    return is_correct;
}



unsigned int fence_perimeter(fence_t fence){
    unsigned int perimeter = 0;
    fence_t aux = fence;

    while(aux != NULL){
        if(aux->type != P){
            perimeter = perimeter + 3;
        }
        aux = aux->next;
    }

    return perimeter;
}   


unsigned int fence_size(fence_t fence){
    return (fence->size);
}


type_t *fence_to_array(fence_t fence){
    type_t *array = malloc(sizeof(type_t) * fence->size);
    assert(array != NULL);
    unsigned int length = fence->size;
    fence_t aux = fence;
    for(unsigned int i = 0; i < length; i++){
        array[i] = aux->type;
        aux = aux->next;
    }
    return array;
}


fence_t fence_destroy(fence_t fence){
    fence_t aux = fence;
    while(aux != NULL){
        fence_t killme = aux;
        aux = aux->next;
        free(killme);
        killme = NULL;
    }
    free(fence);
    fence = NULL;
    return fence;
}

