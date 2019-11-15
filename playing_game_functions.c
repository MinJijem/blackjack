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
int configUser(){
	
	do
	{
	printf("Input the number of players (MAX:5) : ");
	n_user=getIntegerInput;
	
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
	bet[0]=getIntegerInput;
	
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

