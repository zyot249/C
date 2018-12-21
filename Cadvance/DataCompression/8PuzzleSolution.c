#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printTable(int table[9]){
	for (int i = 0; i < 9; ++i)
	{
		if(i % 3 == 0) printf("|");
		printf(" %d |",table[i] );
		if(i % 3 == 2) printf("\n" );
	}
}

void moveLeft(int table[9]){
	
	//find blank position
	int blank_position;
	for (int i = 0; i < 9; ++i)
	{
		if(table[i] == 0) {
			blank_position = i;
			break;
		}
	}

	if(blank_position % 3 == 0) return;
	else{
		table[blank_position] = table[blank_position-1];
		table[blank_position-1] = 0;
	}
}

int main()
{
	int table[9] = {3,4,5,1,2,6,8,7,0};
	printTable(table);
	//moveLeft(table);
	printTable(table);
	return 0;
}


