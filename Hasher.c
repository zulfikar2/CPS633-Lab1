#include "Hasher.h"

/**
  * @desc Initializes the user/pass array using the userData.txt file
  * @return int - success or failure of initialization
*/
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
				//adds username to userData[userindex]
				strncpy(userData[counter/2], token, MAX_USERNAME_LENGTH);
				users++;
			}
			else {
				sscanf(token, "%12s", token);
				//adds password to passData[userindex]
				strncpy(passData[counter/2], token, MAX_PASS_LENGTH);
			}
			token = strtok(NULL, splitChar);
			counter++;
		}
	}

	fclose(data);
	return 1;
}

/**
  * @desc Compares the username to the userData array
  * @param char* check - the username to compare
  * @return int - if match is found or not in array
*/
int cmprUser(char* check) {
	//search for stdin username to see if it matches any in array. return 1 if found. return -1
	for(int i =0; i < users ; i++){
		if(strcmp(check,userData[i]) == 0){
			printf("Match found!\n");
			return i;
		}
	}
	printf("Match not found!\n");
	return -1;
}

/**
  * @desc compares the password to the current password in passData array
  * @param char* check - the password to check
  *	@param int index - the index of the username to check against
  * @return int - if the passwords match or not
*/
int cmprPass(char* check, int index) {
	if(strcmp(check,passData[index]) == 0){
		return index;
	}
	return -1;
}

/**
  * @desc gets the username from the command input
  * @return char* - the username from scanf
*/
char* getUser() {
	char* username = (char*)calloc(255, sizeof(char));
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

/**
  * @desc gets the password from the command input
  * @param int passFlag - the flag to indicate which password is being inputted
  * @return char* - the password from scanf
*/
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



