#include "Hasher.h"

#define LENGTH 4 //length of all possible generated words
#define MAX 456976 //amount of passwords you can generate with LEN as 4 (26^4)
#define hashLength 12

    char passwords[MAX][LENGTH+1]; //array that contains all of generated posssible passwords
	char hashed[MAX][LENGTH+1];    // array that contains all of the hashed generated possible passwords
	int idx;
	char hashpass;
void findHash(char *str, int current, int end) {
    char c;
    if (current < (end - 1)) { //if current index is less than length then continue to add characters to string
        for (c = 'A'; c <= 'Z'; ++c) {
            str[current] = c; // add whatever letter from A to Z to str array on current index

            findHash(str, current + 1, end); //apply recursion to next index
        }
    } else { //if current index is equal to end which means just add one more char value from alphabet. 
        for (c = 'A'; c <= 'Z'; ++c) { //right now its at 4...
            str[current] = c; //add last letter to array
			
			str[current+1] = '\0'; //PROBLEM IS STRCPY DEPENDS ON TRAILING \0 WHICH MAY NOT ALWAYS OCCUR. DONT FORGET.
			//find a way to store generated string in pass array then pass str in hash function that will hash it and store in hash array
			strcpy(passwords[idx],str); //store str in passwords array
			//hashpass= hashIt(str,strlen(str)); //should take generated password and hash it then store it in hash array
			strcpy(hashed[idx],hashIt(str,strlen(str)));
			printf("%s : %s\n ",passwords[idx],hashed[idx]);
			idx++;
			
			
            //printf("%s\n", str); //print to test input
        }
    }
}



int OPC() {
    char str[LENGTH + 1];
    memset(str, 0, LENGTH + 1); // str is string to fill in, fill it in with zeros first and stop up to 5. since it is 4 characters and a null char.
    findHash(str, 0, LENGTH); //function that will print out all permutations of all capital letters with length set(4) in our case . store in str value
	char* userPass = (char*)calloc(hashLength+1, sizeof(char));//prompt user to ask for password
	int fflag=0;
	printf("Please input hash of password of length 4:");
	scanf("%s",userPass);
	for(int i =0; i<MAX;i++){ //compare each value in hash array with stdin
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
