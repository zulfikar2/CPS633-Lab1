#include "Hasher.h"

#define LENGTH 4
#define MAX 456976
#define hashLength 12

    char passwords[MAX][LENGTH+1];
	char hashed[MAX][LENGTH+1];
    char hashpass;
    int idx;
/**
  * @desc creates dictionary of all possible LENGTH-character long passwords made of upper-case letters only
  * @param char* str - the array where the hashed passwords will be temporarily stored
  *     @param int current - the current index of the array
  *         @param int end - the last index of the array
*/
void findHash(char *str, int current, int end) {

    char c;
    //if current index is less than length then continue to add characters to string
    if (current < (end - 1)) {
        for (c = 'A'; c <= 'Z'; ++c) {
            // add whatever letter from A to Z to str array on current index
            str[current] = c;
            //apply recursion to next index
            findHash(str, current + 1, end);
        }

    } else {
        for (c = 'A'; c <= 'Z'; ++c) {
            // add last character to str
            str[current] = c;

			str[current+1] = '\0';
			//store str in passwords array
			strcpy(passwords[idx],str);
			//should take generated password and hash it then store it in hash array
			strcpy(hashed[idx],hashIt(str,strlen(str)));
			idx++;



        }
    }
}



int OPC() {
    char str[LENGTH + 1];
    memset(str, 0, LENGTH + 1);
    findHash(str, 0, LENGTH);
    //allocate mem for password
	char* userPass = (char*)calloc(hashLength+1, sizeof(char));
	// found flag so that for loop knows when to stop searching
	int fflag=0;
	//prompt user to ask for password
	printf("Please input hash of password of length 4:");
	scanf("%s",userPass);
	for(int i =0; i<MAX;i++){
		if(strcmp(hashed[i],userPass)==0){
			printf("Hashed passwords found! Hashed password is %s and unhashed password is %s\n",userPass,passwords[i]); //print both hashed pass and pass
			fflag=1;
		}
	}
	if(fflag ==0){
		printf("Hashed password not found in table!\n");
	}
return 0;
}
