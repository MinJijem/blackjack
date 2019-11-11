#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_DOLLAR			50

#define N_MAX_USER			5



int dollar[N_MAX_USER];						//players' money
int n_user;									//number of users

int bet[N_MAX_USER];						//players' betting



int configUser(){
	
	do
	{
	printf("Input the number of players (MAX:5) : ");
	n_user=getIntegerInput();
	
	if(n_user>5)
		printf("Too many player!\n");
	else if(n_user<1)
		printf("invalid onput players!\n");
	
	}while(n_user>5||n_user<1);
	
}
int betDollar(void) {
	
	int i;
	int r;
	
	printf("\n--------- BETTING STRP ---------\n");
	//user betting
	do{
		
	printf("  -> your betting (total:$%d) :$ ",dollar[0]);
	bet[0]=getIntegerInput();
	
	if(bet[0]<0)
		printf("  -> invald input for betting ($%d)\n",bet[0]);
	else if(bet[0]>dollar[0])
		printf("  -> you only have $%d! bet again\n",dollar[0]);
	}while(bet[0]<0 || bet[0]>dollar[0]);
	
	for(i=1;i<n_user;i++) //plaers betting
	{
		r=1+rand() % dollar[i];
		bet[i]=r;
		printf("  -> player%d bets $%d (out of $%d)\n",i,bet[i],dollar[i]);
	}
	
	printf("--------------------------------\n");
	
}
