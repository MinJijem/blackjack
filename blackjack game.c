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
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag

//some utility functions

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


//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	
}


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {

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
	return CardTray[cardnum];
}


//playing game functions -----------------------------

//player settiing
int configUser(void) {
	
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
int betDollar(void) {
	
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

int printCard(int Card);

//print initial card status
void printCardInitialStatus(int user,int cardcnt) {
	
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

int getAction(void) {
	
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
}

int checkResult() {
	
}

int checkWinner() {
	
}



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for () //each player
		{
			while () //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
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
