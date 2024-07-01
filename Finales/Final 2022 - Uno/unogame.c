#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame {
    unsigned int size;
    struct c_node *top;
};

struct c_node{
    player_t player;
    card_t card;
    struct c_node *next;
};

typedef struct c_node *node;

static node create_node(player_t player, card_t card){
    node new_node = malloc(sizeof(struct c_node));
    assert(new_node != NULL);
    new_node->player = player;
    new_node->card = card;
    new_node->next = NULL;
    return new_node;
}   


unogame_t
uno_newgame(card_t card) {
    unogame_t new_game = malloc(sizeof(struct s_ugame));
    assert(new_game != NULL);
    new_game->size = 1;
    new_game->top = create_node(-1, card);   
    return new_game;
}

card_t
uno_topcard(unogame_t uno) {
    return (uno->top->card);
}

unogame_t
uno_addcard(unogame_t uno, card_t c) {
    player_t player = uno_nextplayer(uno);
    node new_card = create_node(player, c);
    new_card->next = uno->top;
    uno->top = new_card;
    uno->size++;
    return uno;
}

unsigned int
uno_count(unogame_t uno) {
    return uno->size;
}

bool
uno_validpile(unogame_t uno) {
    bool valid = true;
    node aux = uno->top;
    while(aux->next != NULL){
        valid = card_compatible((aux->next)->card, aux->card);
        aux = aux->next;
    }
    return valid;
}

color_t
uno_currentcolor(unogame_t uno) {
    return (card_get_color(uno->top->card));
}

player_t
uno_nextplayer(unogame_t uno) {
    assert(uno!=NULL);
    
    player_t next_player = -1 ;
    if(uno != NULL){
        next_player = (uno->size % 3)  ;
    }
    return next_player;
}




card_t *
uno_pile_to_array(unogame_t uno) {
    card_t *array = calloc(sizeof(card_t), uno->size);
    assert(array != NULL);
    unsigned int length = uno->size-1;
    node aux = uno->top;
    for (unsigned int i = 0; i < uno->size; i++){
        array[length-i] = aux->card;
        aux = aux->next;
    }
    return array;
}

unogame_t
uno_destroy(unogame_t uno) {
    while (uno->top != NULL){
        node aux = uno->top;
        uno->top = uno->top->next;
        free(aux);
        aux = NULL;
    }
    free(uno);
    uno = NULL;
    return uno;
}

