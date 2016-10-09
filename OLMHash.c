#include "Hasher.h"

char userData[MAX_USERS][MAX_USERNAME_LENGTH];
char passData[MAX_USERS][MAX_PASS_LENGTH];
int users = 0;

int writeData();

int OLMHash() {
	//initialize userData and passData arrays.
	initData();
	
	//Initialize data
	char* username = (char*)calloc(255, sizeof(char));
	strncpy(username, "-1", strlen("-1"));
	char* password = (char*)calloc(255, sizeof(char));
	int tries = 0;

	//while username is empty or invalid
	while(strcmp(username, "-1") == 0) { 
		username = getUser();
		//username too long/invalid
		if(strcmp(username, "-1") == 0) {
			tries++;
			if(tries >= MAX_TRIES) {
			//ends program when max tries reached
			fprintf(stderr, "Too many unsuccessful attempts - your account is locked\0");
			return -1;
			}
		}
	}
	
	//real user should return index of username if it exists, otherwise -1
	int realUser = cmprUser(username);
	
	//if user exists, ask for old pass
	if(realUser != -1) {
			while(1) {
				password = getPass(1);
				password = hashIt(password,strlen(password));
				//if old pass matches whats inputted ask for new pass and replace old pass
				if(cmprPass(password, realUser) != -1) {
					password = getPass(3);
					password = hashIt(password,strlen(password));
					strncpy(passData[realUser], password, strlen(password));
					writeData();
					break;
				}
				tries++;
				if(tries >= MAX_TRIES) {
					//ends program when max tries reached
					fprintf(stderr, "Too many unsuccessful attempts - your account is locked\0");
					return -1;
				}
			}
		//}
	}
	else if (realUser == -1) {
		//User added to database, enter password
		password = getPass(2);
		password = hashIt(password,strlen(password));
		
		strncpy(userData[users], username, strlen(username));
		strncpy(passData[users], password, strlen(password));
		users++;
		writeData();
	}
	return 0;
}

/**
  * @desc writes the user/pass table to file
  * @return int - success or failure of write
*/
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


/**
  * @desc Hashes the entire password at once using the E function
  * @param char* pass - the password to be hashes
  *	@param int length - the length of the password
  * @return char* - the hashed password
*/
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
