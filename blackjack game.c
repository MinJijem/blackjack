#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50

#define N_MAX_USER			5
#define N_MAX_BET			5
#define N_MAX_CARDHOLD		10

//getaction
int action=0;

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

//definition functions----------------------------
extern int getIntegerInput(void);
extern int mixCardTray();
extern int configUser();
extern int betDollar(void);
extern int getAction(void);
extern int pullCard(void);
extern void offerCards(void);
extern int printCardInitialStatus(int user,int cardcnt);
extern void printUserCardStatus(int user, int cardcnt);
extern void serverCardPrint();
extern int	printCard(int Card);
extern int checkResult();
extern int checkWinner();
extern int SumCard(int card,int i);
extern int AcardCalcul(int i,int k);
//-------------------------------------------------



int main(int argc, char *argv[]) {
	int round = 1;
	int i;
	int j;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();
	
	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	
	for(i=0;i<n_user;i++)
	{
		dollar[i]=N_DOLLAR; // give players money 
	}
	
		mixCardTray();
		
	//GAME START--------------------------------
	//do until the player dies or card ran out of the tray
	
	do{
		
		printf("\n------------------------------------------\n");
		printf("---------  ROUND %d (cardIndex:%d) ---------\n",round,cardindex);
		printf("------------------------------------------\n");
		
		betDollar();
		offerCards();			//1. give cards to all the players
		
		if(gameEnd==1)			//if card ran out of the tray in offering card, immediately End game
		{
		printf("card ran out of the tray! finishing the game\n");
		break;
		}

		
		for(i=0;i<=n_user;i++)	//initialize with 2card player and dealer have
		{
			n_card[i]=2;
		}
		
		for(i=0;i<=n_user;i++)	//initialize cardSum
		{
			cardSum[i]=0;
		}
		
		printf("---------- CARD OFFERING ----------\n");
		
		serverCardPrint();
		
		for(i=0;i<n_user;i++)
			printCardInitialStatus(i,n_card[i]); //print card 
			

		
		printf("-----------------------------------\n");
			
		printf("\n------------------ GAME start --------------------------\n");

			printf(">>> my turn! <<<\n");
			
			printUserCardStatus(0,2);
			
		//my turn------------------
		while(1)				
		{
			cardSum[0]=0;
		
			for(i=0;i<n_card[0];i++)
				SumCard(cardhold[0][i],0);
		
			AcardCalcul(0,n_card[0]);
		
			if(cardSum[0]>21) 			//if cardsum > 21, immediately dead
			{
				dollar[0]-=bet[0];
				printf("DEAD  -> -$%d ($%d)\n",bet[0],dollar[0]);
				break;
			}
			else if(n_card[0]==2 && cardSum[0]==21)		//if cardsum = 21, immediately win
			{
				dollar[0]+=2*bet[0];
				printf("blackjack!  ->$%d  ($%d)\n",2*bet[0],dollar[0]);
				break;					

			}
		
			action=getAction();
		
			if(action!=0)
				break;
	
			cardhold[0][n_card[0]]=pullCard();
			
			if(gameEnd==1)				//if card ran out of the tray, immediately End game
			{
				printf("card ran out of the tray! finishing the game\n");		
				goto EXIT;
			}

		
			printUserCardStatus(0,n_card[0]+1); 
		
			n_card[0]++;				//number of card you have increase	

		}
				
			
		//player,dealer turn-----------------
		for(i=1;i<=n_user;i++)
		{
			if(i==n_user)
				printf("\n>>> server turn! <<<\n");
			else
				printf("\n>>> player %d turn! <<<\n",i);

			while(1)
			{
				printUserCardStatus(i,n_card[i]);
				
				for(j=1;j<=n_user;j++)
				{
					cardSum[i]=0;
				}
				
				for(j=0;j<n_card[i];j++)
					SumCard(cardhold[i][j],i);		//player i's cardSum
					 
				 AcardCalcul(i,n_card[i]);
				 
				if(cardSum[i]<17)
				{
					printf("go");
					cardhold[i][n_card[i]]=pullCard();
					
					if(gameEnd==1)					//if card ran out of the tray, immediately ENd game
					{
						printf("\ncard ran out of the tray! finishing the game\n");
						goto EXIT;
					}
					
					
					n_card[i]++;
					cardSum[i]=0;			//initialization cardSum
				}
				
				else if(n_card[i]==2 && cardSum[i]==21)
				{
					printf("black jack! ");
					
					if(i==n_user)
						break;
					
					else
					{
					dollar[i]=dollar[i]+2*bet[i];
					printf("  -> +$%d  ($%d)\n",2*bet[i],dollar[i]);
					break;
					}						

				}
					
				else if(cardSum[i]>=17 && cardSum[i]<=21)
				{
					printf("stay\n");
					break;
				}

						
				else if(cardSum[i]>21)
				{
					
					printf("DEAD (sum:%d)",cardSum[i]);
					if(i==n_user)
						break;
					else
					{
					dollar[i]=dollar[i]-bet[i];
					printf("  -> -$%d  ($%d)\n",bet[i],dollar[i]);
					break;
					}
				}
				printf("\n");
				
			}
		
		
		}
		

		printf("\n--------------------ROUND %d result-----------------\n",round);
		checkResult();
		
		round++;
		cardindex=cardnum;
		
		for(i=0;i<n_user;i++) //if Someone money=0, immediately End game
		{
			if(dollar[i]==0)
			{
			printf("\nSomeone bankrupt  game end!\n");
			gameEnd=1;
			break;	
			}
			
		}
		

		
	}while(gameEnd==0);

	EXIT:
		
	checkWinner();
		
	return 0;
	
	}
	

