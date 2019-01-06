#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void PrintMenu(){
	printf("\n--------------Your Option--------------\n");
	printf("1. Function1\n");
	printf("2. Function2\n");
	printf("3. Function3\n");
	printf("4. Function4\n");
	printf("5. Function5\n");
	printf("6. Exit\n");
	printf("Your choice: \n");
}

// Get Max On Priority Queue
// int GetMaxId(Dllist pQueue){
// 	Dllist ptr,maxNode;
// 	double max = 0;
// 	int id;
// 	dll_traverse(ptr,pQueue){
// 		double* table = jval_v(ptr->val);
// 		if(table[1] > max){
// 			id = (int)table[0];
// 			max = table[1];
// 			maxNode = ptr;
// 		}
// 	}
// 	dll_delete_node(maxNode);
// 	return id;
// }

int ReadData(char* fileName){
	FILE *fin = fopen(fileName,"r");
	if(fin == NULL){
		printf("Cannot Open File %s !\n",fileName);
		return -1;
	}
}

void UsingStrtok(){
	char str[80] = "Hoc C - co ban va nang cao - tai VietJack";
  const char s[2] = "-";
  char *token;
   
   /* lay token dau tien */
  token = strtok(str, s);
   
  /* duyet qua cac token con lai */
  while( token != NULL ) 
  {
    printf( " %s\n", token );
    
    token = strtok(NULL, s);
  }
}

int GenerateRandomNumber(){
	time_t t;
	/* Khoi tao bo sinh so ngau nhien */
  srand((unsigned) time(&t));
  // Gen Number
  int randomNumber = rand()%50; // range 0->49
  return randomNumber;
}

// Quick Sort of C library
// void qsort(
// 		void *buf,
// 		size_t num,
// 		size_t size,
// 		int (*compare)(void const *, void  const *)
// );

void TimeMeasureBySeconds(){
	time_t start,end;
	volatile long unsigned t;
	start = time(NULL);
	/* your algorithm to check the performance */
	
	end = time(NULL);
	printf("Run in %g seconds.\n",difftime(end,start));
}

void TimeMeasureByClock(){
	clock_t start_t, end_t;
	start_t = clock();
	/*
	Do sth
	*/
	end_t = clock();
	printf("time = %g seconds\n",(double)(start_t - end_t)/CLOCKS_PER_SEC);
}
int main(int argc, char const *argv[])
{
	
	// menu
	char input[100];
	int opt;

	time_t start,end;
	volatile long unsigned t;
	//
	start = time(NULL);
	printf("Welcome to The Strongest Application!!\n");
	do{
		PrintMenu();
		scanf("%s",input);
		if(strlen(input) > 1){
			printf("Wrong Input\n");
			printf("PLEASE choose from 1-6 Option!!\n");
			continue;
		}
		opt = atoi(input);
		switch(opt){
			case 1:{
				break;
			}
			case 2:{
				break;
			}
			case 3:{
				break;
			}
			case 4:{
				break;
			}
			case 5:{
				break;
			}
			case 6:{
				printf("Thank You For Using!!\nGoodbye!\n");
				break;
			}
			default: printf("PLEASE choose from 1-6 Option!!\n");
		}
	}while(opt != 6);
	end = time(NULL);
	printf("Run in %g seconds.\n",difftime(end,start));
	return 0;
}