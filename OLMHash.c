#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRIES 3
#define MAX_PASS_LENGTH 13
#define MAX_USERNAME_LENGTH 33
#define MAX_USERS 50

char userData[MAX_USERS][MAX_USERNAME_LENGTH];
char passData[MAX_USERS][MAX_PASS_LENGTH];

void E(char *in, char *out);
int initData();
char* getUser();
char* getPass(int passFlag);
int compare(char* username);
char* hashIt(char* pass, int length);

int main() {
	
	//initialize userData and passData arrays.
	initData();

	//char* username = (char*)calloc(MAX_USERNAME_LENGTH, sizeof(char));
	
	//Initialize data
	char* username =0;
	char* password=(char*)calloc(MAX_PASS_LENGTH, sizeof(char));
	int tries = 0;

	while(username == 0) {
		username = getUser();
		//printf("%s",username);
		if(username == "-1") {
			username = 0;
			tries++;
		}
		if(tries >= MAX_TRIES) {
			//ends program when max tries reached
			fprintf(stderr, "Too many unsuccessful attempts - your account is locked\0");
			return -1;
		}
		//if(userExist(username))
			//getPass
	}

	int realUser= compare(username);
	return 0;

}


int initData() {
	FILE* data = fopen("userData.txt", "r+");
	if(!data) {
		fprintf(stderr, "Error opening userData.txt");
		return -1;
	}

	const size_t BUFFER = 255;
	char* buffer = (char*)calloc(BUFFER, sizeof(char));
	const char splitChar[2] = ":";
	int counter = 0;
	char* token;

	while(fgets(buffer, BUFFER, data) != NULL) {
		token = strtok(buffer, splitChar);
		while(token != NULL) {
			if(counter%2 == 0) {
				strncpy(userData[counter/2], token, 12);
				printf("%s Added User\n", userData[counter/2]);
			}
			else {
				strncpy(passData[counter/2], token, 12);
				printf("%s Added Pass\n", passData[counter/2]);
			}
			token = strtok(NULL, splitChar);
			counter++;
		}
	}
	//printf("END INIT\n");
}

int compare(char* username) {
    //search for stdin username to see if it matches any in array. return 1 if found. return -1
    for(int i =0; i < MAX_USERS ; i++){
		printf("Searching for matches for %s with %s\n", username, userData[i]);
        if(strcmp(username,userData[i]) == 0){
			printf("Match found!\n");
			return 1;
		}
	}
	printf("Match not found!\n");
	return 0;
}

char* getUser() {
	printf("GET USER\n");
	char* username = (char*)calloc(MAX_USERNAME_LENGTH, sizeof(char));
	int userLength = 0;
	printf("Please give user thx\n");
	scanf("%s", username);
	
	userLength = strlen(username);

	if(userLength < 4 || userLength > MAX_USERNAME_LENGTH) {
		fprintf(stderr,"Invalid username length\n");
		free(username);
		return "-1";
	}
	
	return username;
}

char* getPass(int passFlag){
    char* password= (char*)calloc(MAX_PASS_LENGTH,sizeof(char));
    int passlength = 0;
	if(passFlag == 1)
		printf("User was found in database, enter old password:\n");
	else if (passFlag == 2)
		printf("User added to database, enter password for username:\n");
	else if (passFlag == 3)
		printf("Passwords match, enter new password for username:\n");
	scanf("%s", password);
	passlength = strlen(password);
	if(passlength > MAX_PASS_LENGTH) {
		for(int passlength; passlength > MAX_PASS_LENGTH; passlength--)
		{
			password[passlength] = '\0';
		}
		return password;
	}
	return password;

}




char* hashIt(char* pass, int length) {
	char* hashed = calloc(MAX_PASS_LENGTH,sizeof(char));
	for(int i = 0; pass[i] != '\0'; i++)
		E(&pass[4*i], &hashed[4*i]);
	return hashed;
}
/********************* E function *************************/
// DES replacement cipher
// The function E takes 4 bytes from *in as input and
// writes 4 bytes to *out
void E(char *in, char *out)
{
out[0]=(in[0]&0x80)^(((in[0]>>1)&0x7F)^((in[0])&0x7F));
out[1]=((in[1]&0x80)^((in[0]<<7)&0x80))^(((in[1]>>1)&0x7F)^((in[1])&0x7F));
out[2]=((in[2]&0x80)^((in[1]<<7)&0x80))^(((in[2]>>1)&0x7F)^((in[2])&0x7F));
out[3]=((in[3]&0x80)^((in[2]<<7)&0x80))^(((in[3]>>1)&0x7F)^((in[3])&0x7F));
}
