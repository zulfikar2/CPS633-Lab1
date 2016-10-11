#include "Hasher.h"

char userData[MAX_USERS][MAX_USERNAME_LENGTH];
char passData[MAX_USERS][MAX_PASS_LENGTH];

void existingUser(char* username, int index);
char* randomXOR(char* hash, int r);
void XorIt(char* in, char* out, int r);

//Initiates CRA functionality.
int CRA()
{
	initData(userData, passData);
	srand(time(NULL));
	char* username = 0;
	//Asks for userinput from user.
	username = getUser();

	//real user should return index of username if it exists, otherwise -1
	int realUser = cmprUser(username);

	if(realUser != -1) {
		existingUser(username, realUser);
	}
	else {
		printf("User does not exist.");
		return -1;
	}
}

/**
  * @desc Runs when existing user is found in the database.
  * @param char* username - the username found in the database.
  *	@param int index - the index in the table where the password is found.
  * Prints "Access Granted" if randomXOR(pass, r) is equal to the result sent by the user, and "access denied" if otherwise.
*/
void existingUser(char* username, int index)
{
	char* pass = getPass(1);
	pass = hashIt(pass, strlen(pass));
	int r = rand();
	char* client = randomXOR(pass, r);
	char* server = randomXOR(passData[index], r);
	int clientCompare = strcmp(client, server);

	if(clientCompare == 8)
	{
		printf("Access granted!\n");
	}
	else
	{
		printf("Access denied!\n");
	}
}

/**
  * @desc Splits 32-bit number into 4 sections of 8-bits each and performs a bitwise shift right 8 bits.(>>)
  * @param char* in - the password to use XOR function on.
  *	@param char* out - the char array to fill with the 32-bit number.
  *	@param int r - the randomly generated number.
*/
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

/**
  * @desc Runs the XOR function on indexes of the password.
  * @param char* pass - the password to use XOR function on.
  *	@param int r - the randomly generated number.
  * @return char* out - f(r, h').
*/
char* randomXOR(char* pass, int r)
{
	char * out = (char*)calloc(MAX_PASS_LENGTH, sizeof(char));
	XorIt(pass, out, r);
	XorIt(&pass[4], &out[4], r);
	XorIt(&pass[8], &out[8], r);
	return out;
}
