#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50

#define N_MAX_USER			5
#define N_MAX_BET			5
#define N_MAX_CARDHOLD		10


//card tray object	
int CardTray[N_CARDSET*N_CARD];
int cardnum=-1;								//Cardtray element number
int cardindex=0;

//player info
int n_card[N_MAX_USER];						//number of card players have
int dollar[N_MAX_USER];						//money of player
int n_user;									//number of player
				
//play yard information					
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER+1];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0;						    //game end flag


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray() {
	
	int i,j;
	int r;


	for(i=0;i<N_CARD;i++)
	{	
		r=1+rand()%N_CARD;
		CardTray[i]=r;
		{
			for(j=0;j<i;j++)
			{
				if(CardTray[i]==CardTray[j]) // remove same card
				{
					i--;
					break;
				}
			}
		}
	}


}

//get one card from the tray
int pullCard(void) {
	
	cardnum++;
	
	if(cardnum==N_CARDSET*N_CARD)			//if card ran out of tray, game end
		gameEnd=1;
		
	else
		return CardTray[cardnum];
}



//offering initial 2 cards
//offer rule : dealer - you - player N - dealer - you - player N
void offerCards(void) {
	
	int i;
	
	cardhold[n_user][0] = pullCard();		//offer first card to dealer
	
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();		// offer first card to players
	}

	cardhold[n_user][1] = pullCard();		//offer secaond card to  dealer
	
	for(i=0;i<n_user;i++)
	{
		cardhold[i][1] = pullCard();		//offer second card to players
	}

	
	return;
}



