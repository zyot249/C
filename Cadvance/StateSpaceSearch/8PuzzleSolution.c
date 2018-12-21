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

int main()
{
	int table[9] = {3,4,5,1,2,6,8,7,0};
	printTable(table);
	return 0;
}


