#include "Hasher.h"

int main() {
	printf("Seperate files plz chuse run\n");
	printf(" 1 : OLMHash Password Scheme");
	printf(" 2 : Challenge-Response (Online) Authentication\n");
	printf(" 3 : OPassword Cracker");
	
	int input = -1;
	
	while(input == -1) {
		scanf("%d", &input);
		switch(input) {
			case 1:
				OLMHash();
				break;
			case 2:
				CRA();
				break;
			case 3:
				OPC();
				break;
			default:
				printf("Error in selecting input. Please type 1, 2 or 3 from the options below\n");
				printf("Seperate files plz chuse run\n");
				printf(" 1 : OLMHash Password Scheme");
				printf(" 2 : Challenge-Response (Online) Authentication\n");
				printf(" 3 : OPassword Cracker");
				break;
		}
	}
	return 0;
}