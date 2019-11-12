#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardnum=-1;							


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold


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

void serverCardPrint()
{
	printf("  server ->      :X     ");
	printCard(cardhold[n_user][1]);
	printf("\n");

}

int	printCard(int Card){
	
	if(Card<=13)
	{
		switch(Card){
			case 1:
				printf("HRTA  ");
				break;
			case 11:
				printf("HRTJ  ");
				break;
			case 12:
				printf("HRTQ  ");
				break;
			case 13:
				printf("HRTK  ");
				break;
			default:
				printf("HRT%d  ",Card);
				break;
		}
	}
	else if(Card<=26)
	{
		switch(Card){
			case 14:
				printf("DIAA  ");
				break;
			case 24:
				printf("DIAJ  ");
				break;
			case 25:
				printf("DIAQ  ");
				break;
			case 26:
				printf("DIAK  ");
				break;
			default:
				printf("DIA%d  ",Card-13);
				break;
		}
	}
	else if(Card<=39)
	{
		switch(Card){
			case 27:
				printf("SPDA  ");
				break;
			case 37:
				printf("SPDJ  ");
				break;
			case 38:
				printf("SPDQ  ");
				break;
			case 39:
				printf("SPDK  ");
				break;
			default:
				printf("SPD%d  ",Card-26);
				break;
		}
	}
	else if(Card<=52)
	{
		switch(Card){
			case 40:
				printf("CLVA  ");
				break;
			case 50:
				printf("CLVJ  ");
				break;
			case 51:
				printf("CLVQ  ");
				break;
			case 52:
				printf("CLVK  ");
				break;
			default:
				printf("CLV%d  ",Card-39);
				break;
		}
	}
		
}
