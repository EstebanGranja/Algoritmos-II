#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include "key_value.h"  /* key_t               */
#include "dict.h"       /* intarface           */

struct _s_dict {
    size_t size;
    struct _node_t *first;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};


struct _node_t * create_node(key_t k, value_t v) {
    struct _node_t *new_node=malloc(sizeof(struct _node_t));
    new_node->key=k;
    new_node->value=v;
    new_node->next=NULL;
    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    node=NULL;
    return node;
}

static bool invrep(dict_t dict) {
    bool res = true;
    res = (dict != NULL);
    unsigned int length = 0u;
    struct _node_t *aux = dict->first;
    while(aux != NULL){
        length++;
        aux = aux->next;
        }
    res = res && (dict->size == length);
    return res;
}
// --- Interface functions ---

dict_t dict_empty(void) {
    dict_t dict = malloc(sizeof(struct _s_dict));

    dict->first = NULL;
    dict->size = 0;
    assert(dict->size == 0);

    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    struct _node_t *aux = dict->first;

    if (dict_exists(dict, word)){ 
        while(aux->next != NULL){
            if(aux->key == word){
                aux->value = def;
                return dict;
            }
            aux = aux->next;
            }
    }

    struct _node_t *new_node = create_node(string_clone(word), string_clone(def));
    new_node->next = dict->first;
    dict->first = new_node;
    dict->size++;

    assert(invrep(dict));
    return dict;
}



value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    struct _node_t *aux = dict->first;
    while(aux!=NULL){
        if(string_eq(aux->key, word)){
            return string_clone(aux->value);
        }
        aux = aux->next;
    }
    return NULL;
}



bool dict_exists(dict_t dict, key_t word) {
    // COMPLETAR
    assert(invrep(dict));
    bool existe = false;
    struct _node_t *aux = dict->first;
    
    while(aux!=NULL && !existe){
        existe = string_eq(aux->key, word);
        aux = aux->next;
    }
    
    return existe;
}



unsigned int dict_length(dict_t dict) {
    return (dict->size);
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));

    if(!dict_exists(dict, word)){
        return dict;
    }

    struct _node_t *aux = dict->first;
    while(aux->next != NULL){
        if ((aux->next)->key == word){
            struct _node_t *killme = aux->next;
            aux->next = killme->next;
            destroy_node(killme);
        }
        aux = aux->next;
    }

    dict->size--;

    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    for (struct _node_t *check=dict->first; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    struct _node_t *aux = dict->first;

    while(dict->first!=NULL){
        dict->first = aux->next;
        struct _node_t *killme = aux;
        aux = aux->next;
        destroy_node(killme);
        dict->size--;
    }
    return dict;
}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict=NULL;
    assert(dict==NULL);
    return dict;
}

