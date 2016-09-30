#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

#define MAX_LENGTH 32
#define MAX_TRIES 3
#define MAX_PASS_LENGTH 13

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
	char password[MAX_PASS_LENGTH];
	char *ret;
	int userLength = 1;
	int tries = 0;
	int found = 0;
	int userFlag=0; // 0 for new user 1 for registered user
	//fprintf(data, "username : password\n");
	//printf("%s\n", passHash);    PRINT GIVEN

	while(userLength == 1) {
		printf("Please give user thx\n");
		printf("tries: %d ",tries);
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
			userLength = 2; //infinite loop due to userLength always being 1 regardless of correct length
		if(tries >= MAX_TRIES) {
			fprintf(stderr, "Too many unsuccessful attempts - your account is locked\0"); //kicks you out of program
			return -2;
		}
	}

	while (fgets(buffer, MAX_LENGTH, data) != NULL) { //read text file. read EACH LINE. while txt file isnt empty
		if((strstr(buffer, search)) != NULL) { //search text file for username(search). if it is found
			//printf("%s\n", buffer);
			userFlag=1;
			ret=strstr(buffer,search); //store line from buffer
			//printf("Username is: %s",ret); //doesnt search so far. prints out whole file.
			for(int x = 0; x < MAX_LENGTH; x++) {
				if(ret[x] == ':') //stop right before password
					break;
				username[x] = ret[x];
				username[x+1] = '\0';
				if(ret[x] == ':') //stop right before password
					break;
			}
			printf("%s%s\n", username, " found in database");
			printf("password is: %s\n",)
		}


			//ask for old password and then hash it and check it against database
			//If the hashes match, the user is prompted for a new
			//password. The hash of the new password then replaces that of
			//the old password
		}
		 //if user doesnt exist add username
                if((strstr(buffer, search))== NULL && userFlag==0){ //searched username doesnt exist. but buffer still runs
                    printf("Username doesn't exist. Username created.\n");
                    char *pass=(char *)calloc(MAX_PASS_LENGTH, sizeof(char)); //allocate space  pass variable
                    printf("Enter Password: "); // prompt
                    scanf("%s",pass); // take stdin put in pass
                    printf(" new User and Pass : %s:%s",search,pass);
                    fprintf(data, "%s:%s\n",search,pass); //write user and pass into text file
                    printf("User was added to the table!");





                }






	fclose(data);
	return 0;
}
