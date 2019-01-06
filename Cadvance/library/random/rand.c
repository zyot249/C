#ifndef __RANDOM
#define __RANDOM

#include <stdlib.h>
#include <string.h>
#include <time.h>

char *randString(int length) {    
    static int mySeed = 25011984;
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size_t stringLen = strlen(string);        
    char *randomString = NULL;

    srand(time(NULL) * length + ++mySeed);

    if (length < 1) {
        length = 1;
    }

    randomString = malloc(sizeof(char) * (length +1));

    if (randomString) {
        short key = 0;

        for (int n = 0;n < length;n++) {            
            key = rand() % stringLen;          
            randomString[n] = string[key];
        }

        randomString[length] = '\0';

        return randomString;        
    }
    else {
        printf("No memory");
        exit(1);
    }
}

char *randPhoneNumber (int length) {
	static int mySeed = 25011984;
	srand(time(NULL) * length + ++mySeed);
	
	char *phoneNumber = (char *)malloc(length * sizeof(char));
	phoneNumber[0] = '0';
	for (int i = 1; i < length; i++) {
		int randNum = rand() % 10;
		phoneNumber[i] = '0' + randNum;
	}
	return phoneNumber;
}

#endif
