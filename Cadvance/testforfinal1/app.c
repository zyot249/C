#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./api.h"

int main(int argc, char const *argv[])
{
	int mode = CheckMode(argc,argv);
	switch(mode){
		case -1:{
			ErrorSyntaxNotify();
			break;
		}
		case 1:{
			printf("C-Advanced, HK20182\n");
			break;
		}
		case 2:{
			ListProduct(argv);
			break;
		}
		case 3:{
			DistanceDepot(argv);
			break;
		}
		case 4:{
			CheckProductsInDepots(argv);
			break;
		}
		case 5:{
			CheckAmountProduct(argv);
			break;
		}
		case 6:{
			DoTransaction(argv);
			break;
		}
	}
	return 0;
}