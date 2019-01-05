#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./compress.h"

int main()
{
	int freTable[256];
	char nameFile[20];
	printf("Enter the name of file: \n");
	scanf("%s",nameFile);
	get_frequence_table(nameFile,freTable);
	for (int i = 0; i < 256; ++i)
	{
		if (freTable[i] != 0)
		{
			printf("%c = %d\n",(char)i,freTable[i]);
		}
		
	}
	return 0;
}