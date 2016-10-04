#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_PASS_LENGTH 13
#define MAX_USERNAME_LENGTH 33
#define MAX_USERS 50

char userData[MAX_USERS][MAX_USERNAME_LENGTH];
char passData[MAX_USERS][MAX_PASS_LENGTH];
int users = 0;


void existingUser(char* username, int index);
char* randomXOR(char* hash, int r);
void XorIt(char* in, char* out, int r);
int writeData();
int initData();
char* getUser();
int cmprUser(char* check);
void newUser(char* username);
char* getPass(int passFlag);
void E(char *in, char *out);
char* hashIt(char* pass, int length);

int main()
{
	initData();
	srand(time(NULL));
	char* username = 0;
	//Asks for userinput from user.
	while(username == 0)
	{
		username = getUser();
	}
	
	int realUser = cmprUser(username);
	if(realUser == -1)
	{
		newUser(username);
	}
	else
	{
		existingUser(username, realUser);
	}
}

int writeData() {
	FILE* data = fopen("userData.txt", "w+");

	if(!data) {
		fprintf(stderr, "Error opening userData.txt to append\n");
		return -1;
	}
	for(int i = 0; i < users; i++)
		fprintf(data, "%s:%s\n", userData[i], passData[i]);
	fclose(data);
	return 1;
}

int initData() {
	FILE* data = fopen("userData.txt", "r+");
	if(!data) {
		fprintf(stderr, "Error opening userData.txt to read or no database found\n");
		return -1;
	}

	const size_t BUFFER = 255;
	char* buffer = (char*)calloc(BUFFER, sizeof(char));
	const char splitChar[2] = ":";
	int counter = 0;
	char* token;
	int length;
	
	while(fgets(buffer, BUFFER, data) != NULL) {
		token = strtok(buffer, splitChar);
		while(token != NULL) {
			if(counter%2 == 0) {
				strncpy(userData[counter/2], token, MAX_USERNAME_LENGTH);
				printf("%s Added User\n", userData[counter/2]);
				users++;
			}
			else {
				sscanf(token, "%12s", token);
				strncpy(passData[counter/2], token, MAX_PASS_LENGTH);
				printf("%s Added Pass\n", passData[counter/2]);
			}
			token = strtok(NULL, splitChar);
			counter++;
		}
	}
	
	fclose(data);
	return 1;
}

char* getUser() {
	//printf("GET USER\n");
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

int cmprUser(char* check) {
	//search for stdin username to see if it matches any in array. return 1 if found. return -1
	for(int i =0; i < users ; i++){
		//printf("Searching for matches for %s with %s\n", check, userData[i]);
		if(strcmp(check,userData[i]) == 0){
			printf("Match found!\n");
			return i;
		}
	}
	printf("Match not found!\n");
	return -1;
}
`
char* getPass(int passFlag){
    char* password= (char*)calloc(255,sizeof(char));
    int passlength = 0;
	if(passFlag == 1)
		printf("User was found in database, enter old password:\n");
	else if (passFlag == 2)
		printf("User added to database, enter password:\n");
	else if (passFlag == 3)
		printf("Passwords match, enter new password for username:\n");
	scanf("%s", password);
	passlength = strlen(password);
	if (passlength > MAX_PASS_LENGTH) {
		char* substr;
		strncpy(substr, password, 12);
		substr[12] = '\0';
		return substr;
	}
	else if(passlength < MAX_PASS_LENGTH-1) {
		for(; passlength < MAX_PASS_LENGTH-1; passlength++)
		{
			password[passlength] = '\0';
		}
		return password;
	}
	return password;
}

char* hashIt(char* pass, int length) {
	char* hashed = calloc(MAX_PASS_LENGTH,sizeof(char));
	for(int i = 0; i < length; i++)
		E(&pass[4*i], &hashed[4*i]);
	return hashed;
}
/********************* E function *************************/
// DES replacement cipher
// The function E takes 4 bytes from *in as input and
// writes 4 bytes to *out
void E(char *in, char *out)
{
	char in0 = toupper(in[0]);
	char in1 = toupper(in[1]);
	char in2 = toupper(in[2]);
	char in3 = toupper(in[3]);
	
out[0]=(in0&0x80)^(((in0>>1)&0x7F)^((in0)&0x7F));
out[1]=((in1&0x80)^((in0<<7)&0x80))^(((in1>>1)&0x7F)^((in1)&0x7F));
out[2]=((in2&0x80)^((in1<<7)&0x80))^(((in2>>1)&0x7F)^((in2)&0x7F));
out[3]=((in3&0x80)^((in2<<7)&0x80))^(((in3>>1)&0x7F)^((in3)&0x7F));
}

void newUser(char* username)
{
	char* pass = getPass(2);
	pass = hashIt(pass, strlen(pass));
	strncpy(userData[users], username, strlen(username));
	strncpy(passData[users], pass, strlen(pass));
	users++;
	writeData();
	printf("User added.\n");
}

void existingUser(char* username, int index)
{
	char* pass = getPass(1);
	pass = hashIt(pass, strlen(pass));	
	int r = rand();
	char* client = randomXOR(pass, r);
	char* server = randomXOR(passData[index], r);
	
	if(strcmp(client, server) == 0)
	{
		printf("Access granted!\n");
	}
	else
	{
		printf("Access denied!\n");	
	}
}

void XorIt(char* in, char* out, int r)
{
	out[3] = in[3] ^ (r & 255);
	r = r >> 8; 
	out[2] = in[2] ^ (r & 255);
	r = r >> 8;
	out[1] = in[1] ^ (r & 255);
	r = r >> 8;
	out[0] = in[0] ^ (r & 255);
}

char* randomXOR(char* pass, int r)
{
	char * out = (char*)calloc(MAX_PASS_LENGTH, sizeof(char));
	XorIt(pass, out, r);
	XorIt(&pass[4], &out[4], r);
	XorIt(&pass[8], &out[8], r);
	return out;	
}
