#include "Hasher.h"

char userData[MAX_USERS][MAX_USERNAME_LENGTH];
char passData[MAX_USERS][MAX_PASS_LENGTH];
int users = 0;

void existingUser(char* username, int index);
char* randomXOR(char* hash, int r);
void XorIt(char* in, char* out, int r);
void newUser(char* username);

int CRA()
{
	initData(userData, passData);
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
