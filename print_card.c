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
extern int CardTray[N_CARDSET*N_CARD];
extern int cardnum;								//Cardtray element number
extern int cardindex;

//player info
extern int n_card[N_MAX_USER];						//number of card players have
extern int dollar[N_MAX_USER];						//money of player
extern int n_user;									//number of player
				
//play yard information					
extern int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
extern int cardSum[N_MAX_USER+1];					//sum of the cards
extern int bet[N_MAX_USER];						//current betting 
extern int gameEnd;						    //game end flag

//  player's initial card print 
int printCardInitialStatus(int user,int cardcnt)
{
	int i;
	
	if(user==0)
		printf("   -> you        :");
	else
		printf("   -> player %d   :",user);
	
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\n");
	
}

// player's card print
void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}


//print dealer's Card
void serverCardPrint()
{
	printf("  server ->      :X     ");
	printCard(cardhold[n_user][1]);
	printf("\n");

}

//print the card information (e.g. DiaA)
int	printCard(int Card){
	
	if(Card<=13)						//print card shape
		printf("HRT");
	else if(Card<=26)
		printf("DIA");
	else if(Card<=39)
		printf("SPD");
	else if(Card<=52)
		printf("CLV");
	
	switch(Card%13)						//printf card number
	{
		case 11:
			printf("J  ");
			break;
		case 12:
			printf("Q  ");
			break;
		case 0:
			printf("K  ");
			break;
		case 1:
			printf("A  ");
			break;
		default:
			printf("%d  ",Card%13);
			break;
	
	}	
		
}

