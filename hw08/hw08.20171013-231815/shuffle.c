#include "shuffle.h"
#include<stdlib.h>
#include<stdio.h>
#include<strings.h>
// You can add more functions to this file.
void  _recur(CardDeck,CardDeck,CardDeck,int,int,int);			//helper function
void divide(CardDeck, CardDeck*, CardDeck*);				//divide the deck into upper and lower deck
void interleave(CardDeck, CardDeck);					//interleave two decks
void _interleave(CardDeck, CardDeck, int);   				//interleave that can pass k
void shuffle(CardDeck orig_deck);					//shuffle 

void divide(CardDeck orig_deck, CardDeck* upper_deck, CardDeck* lower_deck) {
	for(int i = 0; i < orig_deck.size - 1; i++){                   //upper_deck size*/     
		int low_counter = 0;
		int up_counter = 0;
		for(int count=0; count<=i;count++){
			upper_deck[i].cards[count]=orig_deck.cards[count];
			upper_deck[i].size = i+1;
			up_counter++;
		}
		for(int j=0; j <= (orig_deck.size-upper_deck[i].size);j++){
			lower_deck[i].cards[low_counter]=orig_deck.cards[up_counter];
			lower_deck[i].size = orig_deck.size - upper_deck[i].size;
			low_counter++;
			up_counter++;
		}
	}
}

void _interleave(CardDeck upper_deck, CardDeck lower_deck, int k) {		//interleave helper that helps passing k through the recursion.
	int index_low = 0;
	int index_up = 0;
	CardDeck new_deck = {
		.size = upper_deck.size+lower_deck.size,
		.cards = {0}
	};
	_recur(upper_deck, lower_deck, new_deck, index_low, index_up, k);          //the recur function help the new deck filling itself
}

void interleave(CardDeck upper_deck, CardDeck lower_deck) {
	_interleave(upper_deck,lower_deck,1);
}

void _recur(CardDeck upper_deck, CardDeck lower_deck, CardDeck new_deck, int index_low, int index_up, int k){
	if((upper_deck.size == index_up)&&(lower_deck.size == index_low)){      //when both index are equal to the size of both decks, print
		k--;
		if(k==0){
			printDeck(new_deck);
		}
		else{
			repeat_shuffle(new_deck,k);
		}
	}

	else if((upper_deck.size == index_up)&&(lower_deck.size!=index_low)){           //when one is not eqaul, take elements from that one and assign it to the new deck
		new_deck.cards[index_low + index_up] = lower_deck.cards[index_low];
		_recur(upper_deck, lower_deck, new_deck, index_low+1, index_up, k);
	}
	else if((lower_deck.size == index_low)&&(upper_deck.size != index_up)){         //when one is not equal, take the elements from that one and assign it to the new deck
		new_deck.cards[index_low + index_up] = upper_deck.cards[index_up];
		_recur(upper_deck, lower_deck, new_deck, index_low, index_up+1,k);
	}
	else{
		new_deck.cards[index_low + index_up] = lower_deck.cards[index_low];     //when both are not equal, the default is talking the upper deck first.
		_recur(upper_deck, lower_deck, new_deck, index_low+1, index_up, k);
		new_deck.cards[index_low + index_up] = upper_deck.cards[index_up];
		_recur(upper_deck, lower_deck, new_deck, index_low, index_up+1, k);
	}
}

void shuffle(CardDeck orig_deck){		//only perform one round of shuffle
	repeat_shuffle(orig_deck,1);
}


void repeat_shuffle(CardDeck orig_deck, int k) {
	if(k<=0){
		printDeck(orig_deck);
	}
	else{
		CardDeck * upper_deck = NULL;
		CardDeck * lower_deck = NULL;

		int num_pairs = orig_deck.size - 1;
		upper_deck = malloc(sizeof(*upper_deck)*(orig_deck.size-1));
		lower_deck = malloc(sizeof(*lower_deck)*(orig_deck.size-1));
		if(upper_deck==NULL){
			return;
		}
		if(lower_deck==NULL){
			return;
		}
		divide(orig_deck, upper_deck, lower_deck);
		while(num_pairs>0){
			_interleave(upper_deck[num_pairs-1],lower_deck[num_pairs-1],k);
			num_pairs--;
		}
		free(upper_deck);
		free(lower_deck);
	}
}
