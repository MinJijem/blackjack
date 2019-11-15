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


//calculate real number of card
int SumCard(int card,int i) {

	if(card%13==11||card%13==12||card%13==0)	//Jack,Queen,King --> 10
		cardSum[i]+=10;

	else if(card%13>=2 && card%13<=10)			//2~10 --> same
		cardSum[i]+=card%13;
		
	else if(card%13==1)							//A --> 1 or 11,  need to judge
		cardSum[i]+=1;
	

		
}

//card A calculation  
int AcardCalcul(i,k){
	
	int j;
	
	for(j=0;j<k;j++)
	{
		if(cardhold[i][j]%13==1)				//if player have card A
		{
			if(cardSum[i]<=11)					//if sum of Cardsum[i]+10<=21 , set A to 11
				cardSum[i]+=10;
		}
	}

	
}

