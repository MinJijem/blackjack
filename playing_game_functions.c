#include <stdio.h>
#include <stdlib.h>

#define N_DOLLAR			50

#define N_MAX_USER			5



int dollar[N_MAX_USER];
int n_user;									//number of users

int bet[N_MAX_USER];

int configUser(){
	
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
int betDollar(void) {
	
	printf("\n------- BETTING STRP -------\n");
	do{
		
	printf("  -> your betting (total:$%d) : ",dollar[0]);
	scanf("%d",&bet[0]);
	
	if(bet[0]<0)
		printf("  -> invald input for betting ($%d)\n",bet[0]);
	else if(bet[0]>dollar[0])
		printf("  -> you only have $%d! bet again\n",dollar[0]);
	}while(bet[0]<0 || bet[0]>dollar[0]);
	
	printf("----------------------------\n");
	
}



