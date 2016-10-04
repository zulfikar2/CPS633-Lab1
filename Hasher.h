#ifndef Hasher
#define Hasher

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 3
#define MAX_PASS_LENGTH 12
#define MAX_USERNAME_LENGTH 33
#define MAX_USERS 50

extern char userData[MAX_USERS][MAX_USERNAME_LENGTH];
extern char passData[MAX_USERS][MAX_PASS_LENGTH];
extern int users;

void E(char *in, char *out);
int initData();
char* getUser();
char* getPass(int);
int cmprUser(char*);
int cmprPass(char*, int);
char* hashIt(char*, int);

int OLMHash();
int	CRA();
int	OPC();

#endif
