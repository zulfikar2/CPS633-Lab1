#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRIES 3
#define MAX_PASS_LENGTH 13
#define MAX_USERNAME_LENGTH 33
#define MAX_USERS 50

char Userdata[MAX_USERS][MAX_USERNAME_LENGTH];
char Passdata[MAX_USERS][MAX_PASS_LENGTH];

void E(char *in, char *out);
int initData();
char* getUser();
char* getPass(int passFlag);
int userExist(char* username);
char* hashIt(char* pass, int length);

int main() {
	/*FILE* data;
	data = fopen("userData.txt", "r+");
	if(!data) {
		fprintf(stderr, "Error opening userData.txt");
		return -1;
	}*/

	/*char username[MAX_USERNAME_LENGTH];

	char passHash[MAX_PASS_LENGTH];
	char buffer[MAX_USERNAME_LENGTH];
	char search[MAX_USERNAME_LENGTH];
	char *ret;
	int userLength = 1;
	int tries = 0;
	int userFlag=0; // 0 for new user 1 for registered user
	//fprintf(data, "username : password\n");
	//printf("%s\n", passHash);    PRINT GIVEN*/

	initData();

	char* username = (char*)calloc(MAX_USERNAME_LENGTH, sizeof(char));
	char* password=(char*)calloc(MAX_PASS_LENGTH, sizeof(char));
	int tries = 0;

	while(1) {
		/*printf("Please give user thx\n");
		//printf("tries: %d ",tries);
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
		}*/

		username = getUser();
		if(username == "-1")
			tries++;
		if(tries >= MAX_TRIES) {
			//ends program when max tries reached
			fprintf(stderr, "Too many unsuccessful attempts - your account is locked\0");
			return -1;
		}
		//if(userExist(username))
			//getPass
	}
/*
	while (fgets(buffer, MAX_LENGTH, data) != NULL) { //read text file. read EACH LINE. while txt file isnt empty
		if((strstr(buffer, search)) != NULL) { //search text file for username(search). if it is found
			//printf("%s\n", buffer);
			userFlag=1;
			ret=strstr(buffer,search); //store line from buffer
			//printf("Username is: %s",ret); //doesnt search so far. prints out whole file.
			for(int x = 0; x < MAX_LENGTH; x++) {
				if(ret[x] == ':')  {
					int index = 0;
					for(int y = x+1; y < MAX_PASS_LENGTH + x; y++) {
						if(ret[y] == '\0')
							break;
						passHash[index] = ret[y];
						passHash[index+1] = '\0';
						index++;
					}
					break;
				}
				username[x] = ret[x];
				username[x+1] = '\0';
			}

			printf("%s%s\n", username, " found in database");
			printf("%s%s\n", passHash, " found in database");
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
                    fprintf(data, "%s:%s\n",search,pass);
                    //write new user and pass into database
                    //write(data,)
                }
	fclose(data);*/
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
			printf("%s\n", token);
			token = strtok(NULL, splitChar);
		}
	}
}

int userExist(char* username) {

	return 0;
}
char* getUser() {
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
