#include <stdio.h>

char *str1 = "salet" ;
char *str2 = "salty" ;

int str_len = 12;

// "what i should do": read a character, check to see if its null,
// print something that would tell me it is, flush std out, overwrite that
// memory location


void main (){
<<<<<<< HEAD

	char *str1 = "bingus";
	char *str2 = "thecat";
	str1[0] = "q";
	printf(str1) ;
	printf("\n");
	printf(str2) ; 
=======
	printf("pointer of str1: %p: \n", str1) ;
	printf("pointer of str2: %p:", str2) ;
	printf("\n");

	// iterate over a given string and print the character and its
	// specific location in memory
	int i;
	//str1[1] = "q";
	int offset = str2 - 1;
	* offset = "q";
	printf("\n");
	for (int i = 0; i < str_len; i++)  {
		printf("character %c: ,", str1[i]);
		printf("location %x: \n", str1[i]);
		}
	printf(str1);
>>>>>>> 31579eabbd3ca699cf92ea75a4a005e431a31ded
}

