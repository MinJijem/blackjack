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


//check the Round result
int checkResult()
{	
	int i;
	
	for(i=0;i<n_user;i++)
	{	
		if(i==0)
			printf("  -> your result : ");
		else
			printf("  ->player %d result : ",i);
			
		
		
		if(cardSum[i]>21)
		{
			printf("lose due to overflow!  --> $%d\n",dollar[i]);		//if player have overflow card, player lose
		}
		else if(n_card[i]== 2&&cardSum[i]==21)
		{
			printf("blackjack! win!  --> $%d\n",dollar[i]);				//if player have blackjack, player win				
		}
		else if(cardSum[n_user]>21)
		{
			dollar[i]+=bet[i];
			printf("dealer overflow! win!  --> $%d\n",dollar[i]);
		}
		else if(cardSum[n_user]==21 && n_card[n_user]==2)
		{
			dollar[i]-=bet[i];
			printf("dealer blackhack! lose  --> $%d\n",dollar[i]);
		}
		else if(cardSum[i]>=cardSum[n_user])
		{
			dollar[i]+=bet[i];
			printf("win! (sum:%d)  --> $%d\n",cardSum[i],dollar[i]);
		}
		else if(cardSum[i]<cardSum[n_user])
		{
			dollar[i]-=bet[i];
			printf("lose  (sum:%d)  --> $%d\n",cardSum[i],dollar[i]);
		}	
	}		
}

//after finishing game, check winner
int checkWinner() {
	
	int i;
	int max=0;
	int winner=0;
	
	for(i=0;i<4;i++)
		printf("---------------------------------------\n\n");
			
	printf("your money $%d\n",dollar[0]);
	
	printf("players money : ");
	
	for(i=1;i<n_user;i++)
		printf("$%d ",dollar[i]);
	
	printf("\n");
		
		for(i=0;i<n_user;i++)
		{
			if(dollar[i]>max)
			{
				max=dollar[i];
				winner=i;
			}
				
		}
	
	if(winner==0)
		printf("You win! money : $%d\n",dollar[winner]);
	else
		printf("player %d win! money : $%d\n",winner,dollar[winner]);

}
