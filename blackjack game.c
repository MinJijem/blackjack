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

//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)

int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}
//playing game functions -----------------------------

//player settiing
int configUser()
{	
	do
	{
	printf("Input the number of players (MAX:5) : ");
	scanf("%d",&n_user);
	
	if(n_user>5)
		printf("Too many player!\n");
	else if(n_user<1)
		printf("invalid onput players!\n");
	
	}while(n_user>5||n_user<1);
	
}

//betting
int betDollar(void)
{
	int i;
	int r;
	
	printf("\n--------- BETTING STRP ---------\n");
	do{
		
	printf("  -> your betting (total:$%d) :$",dollar[0]);
	scanf("%d",&bet[0]);
	
	if(bet[0]<0)
		printf("  -> invald input for betting ($%d)\n",bet[0]);
	else if(bet[0]>dollar[0])
		printf("  -> you only have $%d! bet again\n",dollar[0]);
	}while(bet[0]<0 || bet[0]>dollar[0]);
	
	for(i=1;i<n_user;i++)
	{
		r=1+rand() % N_MAX_BET;
		bet[i]=r;
		printf("  -> player%d bets $%d (out of $%d)\n",i,bet[i],dollar[i]);
	}
	
	printf("--------------------------------\n");
	
}
//card array controllers -------------------------------

//mix the card sets and put in the array

int mixCardTray()
{
	int i,j;
	int r;

	for(i=0;i<N_CARD*N_CARDSET;i++)
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
		if(CardTray[i]>=52)					//if cardset>1
			CardTray[i]=CardTray[i]%N_CARDSET+1;
	}

}

//get one card from the tray
int pullCard(void)
{
	
	cardnum++;
	
	if(cardnum==N_CARDSET*N_CARD)			//if card ran out of tray, game end
		gameEnd=1;
		
	else
		return CardTray[cardnum];
		
}

//offering initial 2 cards
//offer rule : dealer - you - player N - dealer - you - player N
void offerCards(void)
{
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

//  player's initial card print 
void printCardInitialStatus(int user, int cardcnt)
{	
	if(gameEnd==1)
	return;

	int i;

	if(user==0)
		printf("   -> you        :");
	else
		printf("   -> player %d   :",user);
	
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\n");
}

//print dealer's second card
void serverCardPrint()
{
	printf("   -> server     :X     ");
	printCard(cardhold[n_user][1]);
	printf("\n");

}

// player's card print
void printUserCardStatus(int user, int cardcnt)
{
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}

//calculation card number--------------------------
//player's card sum
int SumCard(int card,int i)
{
	if(card%13==11||card%13==12||card%13==0)
		cardSum[i]+=10;

	else if(card%13>=2 && card%13<=10)
		cardSum[i]+=card%13;
		
	else if(card%13==1)
		cardSum[i]+=1;
}
//A card calculation
int AcardCalcul(i,k)
{	
	int j;
	
	for(j=0;j<k;j++)
	{
		if(cardhold[i][j]%13==1)
		{
			if(cardSum[i]<=11)
				cardSum[i]+=10;
		}
	}
}

//ask GO or STAY?
int getAction(void) {
	
	int reply;
	
	printf("Action? ( 0 - go , others - stay ) : ");
	reply=getIntegerInput();
	
	if(reply==0)
		return 0;
	
	else
		return 1;
	
}

//check game result---------------------------------
//check game 1 round result
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
		else if(n_card[i]=2&&cardSum[i]==21)
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

//check final winner
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
	
	


