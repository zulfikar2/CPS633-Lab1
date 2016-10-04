#include "Hasher.h"

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

int cmprPass(char* check, int index) {
	//printf("Searching for matched for %s with %s\n", check, passData[index]);
	if(strcmp(check,passData[index]) == 0){
		//printf("Match found!\n");
		return index;
	}
	//printf("Match not found!\n");
	return -1;
}

char* getUser() {
	//printf("GET USER\n");
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



