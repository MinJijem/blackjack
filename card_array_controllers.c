#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50

#define N_MAX_USER			5
#define N_MAX_BET			5
#define N_MAX_CARDHOLD		10


int CardTray[N_CARDSET*N_CARD];
int cardnum=-1;	

int dollar[N_MAX_USER];
int n_user;	
								
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int bet[N_MAX_USER];

int gameEnd = 0; 


//card array controllers -------------------------------

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

int pullCard(void) {
	
	cardnum++;
	return CardTray[cardnum];
}



//offering initial 2 cards
void offerCards(void) {
	int i;
	
	cardhold[n_user][0] = pullCard();
	
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
	}

	cardhold[n_user][1] = pullCard();
	
	for(i=0;i<n_user;i++)
	{
		cardhold[i][1] = pullCard();
	}

	
	return;
}



