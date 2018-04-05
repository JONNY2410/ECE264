#include "shuffle.h"
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

void _recur(CardDeck,CardDeck,CardDeck,int,int);			//function that shuffle the deck until it reaches all possibility for one divide
void divide(CardDeck orig_deck, CardDeck *upper_decks, CardDeck *lower_decks) {
	for(int i = 0; i < orig_deck.size - 1; i++){			//upper_deck size*/	
		int low_counter = 0, up_counter = 0;
		for(int k=0; k<=i;k++){
			upper_decks[i].cards[k]=orig_deck.cards[k];
			upper_decks[i].size = i+1;
			up_counter++;
		}
		for(int j=0; j <= (orig_deck.size - upper_decks[i].size);j++){
			lower_decks[i].cards[low_counter]=orig_deck.cards[up_counter];
			lower_decks[i].size = orig_deck.size - upper_decks[i].size;
			up_counter++;
			low_counter++;
		}
	}
}

void interleave(CardDeck upper_deck, CardDeck lower_deck) {
	int index_low = 0, index_up = 0;
	CardDeck new_deck = {
		.size = upper_deck.size+lower_deck.size,
		.cards = {0} 			 
	};
	_recur(upper_deck, lower_deck, new_deck, index_low, index_up);		//the recur function help the new deck filling itself
}

void _recur(CardDeck upper_deck, CardDeck lower_deck, CardDeck new_deck, int index_low, int index_up){
	if((upper_deck.size == index_up)&&(lower_deck.size == index_low)){	//when both index are equal to the size of both decks, print
		print_deck(new_deck);
		printf("\n");
	}
	else if((upper_deck.size == index_up)&&(lower_deck.size!=index_low)){		//when one is not eqaul, take elements from that one and assign it to the new deck
		new_deck.cards[index_low + index_up] = lower_deck.cards[index_low];
		_recur(upper_deck, lower_deck, new_deck, index_low+1, index_up);
	}
	else if((lower_deck.size == index_low)&&(upper_deck.size != index_up)){		//when one is not equal, take the elements from that one and assign it to the new deck
		new_deck.cards[index_low + index_up] = upper_deck.cards[index_up];
		_recur(upper_deck, lower_deck, new_deck, index_low, index_up+1);
	}
	else{
		new_deck.cards[index_low + index_up] = lower_deck.cards[index_low];	//when both are not equal, the default is talking the upper deck first.
		_recur(upper_deck, lower_deck, new_deck, index_low+1, index_up);
		new_deck.cards[index_low + index_up] = upper_deck.cards[index_up];
		_recur(upper_deck, lower_deck, new_deck, index_low, index_up+1);
	}		
}

void shuffle(CardDeck orig_deck) {
	CardDeck * upper_deck = NULL;
	CardDeck * lower_deck = NULL;
	int num_pairs = orig_deck.size - 1;
	upper_deck = malloc(sizeof(orig_deck)*(orig_deck.size-1));
	lower_deck = malloc(sizeof(orig_deck)*(orig_deck.size-1));
	if(upper_deck==NULL||lower_deck==NULL){
		return;
	}
	divide(orig_deck, upper_deck, lower_deck);
	for(int i = num_pairs; i>0;i--){
		interleave(upper_deck[i-1],lower_deck[i-1]);
	}
	free(upper_deck);
	free(lower_deck);
} 
