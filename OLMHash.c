#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 32
#define MAX_TRIES 3

int main() {
	FILE* data;
	data = fopen("userData.txt", "r+");
	if(!data) {
		fprintf(stderr, "Error opening userData.txt");
		return -1;
	}
	
	char username[MAX_LENGTH];
	char passHash[MAX_LENGTH];
	char buffer[MAX_LENGTH];
	char search[MAX_LENGTH];
	int userLength = 1;
	int tries = 0;
	//fprintf(data, "username : password\n");
	//printf("%s\n", passHash);    PRINT GIVEN
	
	while(userLength == 1) {
		printf("Please give user thx\n");
		scanf("%s", search);
		for(userLength=0; search[userLength]!='\0'; userLength++);
		if(userLength < 4 || userLength > MAX_LENGTH)
			userLength = 0;
		if(userLength == 0) {
			fprintf(stderr,"Invalid username length\n");
			tries++;
			userLength = 1;
		}
		else
			userLength = 1;
		if(tries >= MAX_TRIES) {
			fprintf(stderr, "Too many unsuccessful attempts - your account is locked\0");
			return -2;
		}
	}
	
	while (fgets(buffer, MAX_LENGTH, data) != NULL) {
		if((strstr(buffer, search)) != NULL) {
			printf("%s\n", buffer);
			for(int x = 0; x < MAX_LENGTH; x++) {
				if(buffer[x] == ':')
					break;
				username[x] = buffer[x];
				username[x+1] = '\0';
			}
			printf("%s%s\n", username, " found in database");
		}
	}
	
	fclose(data);
	return 0;
}