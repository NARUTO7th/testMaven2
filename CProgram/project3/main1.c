/*
CSI 333.Programming at the Hardware-Software Interface
Spring 2019
supervisor: Huang Ying
class: ZR1704
id: 2017215193
name: Tang Hao
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#define Len 4


struct node* Process(struct node* headnode, char arr[4], int num, char *str);
int ReadTheCommand(char arr1[4], int number, char* string);
int isnumber(char *a);

int main(){
	char command[Len],*text;
	int num = 0;
	struct node* HeadNode = NULL;
	text = (char*)malloc(sizeof(char));
	//test whether allocated memorary for text
    if(text == NULL){
        printf("Allocation failed.\n");fflush(stdout);
        exit(1);
    }
    printf("%s", "Command? ");fflush(stdout);
    num = ReadTheCommand(command, num, text);


    while(strcmp(command,"end") != 0){
    	HeadNode = Process(HeadNode, command, num, text);
		text = (char*)malloc(sizeof(char));
		//test whether allocated memorary for text
		if(text == NULL){
			printf("Allocation failed.\n");fflush(stdout);
			exit(1);
		}
		num = 0;
    	do{
    		printf("%s", "Command? ");fflush(stdout);

    		num = ReadTheCommand(command, num, text);
    	}while(command[0] =='\0');
    }

	return 0;

}
//This method will switch a method according to command
struct node* Process(struct node* headnode, char arr[Len], int num, char *str){
	if(strcmp(arr,"ina\0") == 0){
		struct node *temp = InsertAfter(headnode, num, str);
		if(temp != NULL){
			headnode = temp;
		}
	}else if(strcmp(arr,"inb\0") == 0){
		struct node *temp = InsertBefore(headnode, num, str);
		if(temp != NULL){
			headnode = temp;
		}
	}else if(strcmp(arr,"del\0") == 0){
		struct node *temp = Delete(headnode, num);
		if(temp != NULL){
			headnode = temp;
		}
	}else if(strcmp(arr,"rep\0") == 0){
		struct node *temp = Replace(headnode, num, str);
		if(temp != NULL){
			headnode = temp;
		}
	}else if(strcmp(arr,"prn\0") == 0){
		PrintListCommand(headnode);
	}else if(strcmp(arr,"end\0") == 0){
		end();
	}

	return headnode;
}

//This method need to consider the validity of command
//(implement this after build whole program)!!!
int ReadTheCommand(char arr1[Len], int number, char* string){
	//get a string
	char* str;
	str = (char*)malloc(sizeof(char));
	if(str == NULL){
        printf("Allocation failed.\n");fflush(stdout);
        exit(1);
	}
    scanf("%[^\n]",str);
	getchar();

	//split the string by whitespace
	const char s[1] = " ";
	char *token;
	//get the first token
	token = strtok(str, s);
	if(strlen(token) == 3){
		int i;
		for(i = 0;i < 3;i++){
			arr1[i] = token[i];
		}
		arr1[3] = '\0';
		//to continue the program, there should be replace with other method
	}else printf("%s\n", "command syntax error");fflush(stdout);
	//get other token
	while(token != NULL){
		if(isnumber(token) == 1){
			number = atoi(token);
		}else if(strlen(token) > 3){
		    strcpy(string, token);
		}

		token = strtok(NULL,s);
	}

    return number;
}

int isnumber(char *a){
    int len = strlen(a);
    int j =0;
    for(int i =0;i<len;i++)
    {
        if(a[i]<=57&&a[i]>=48)
        {j++;}
    }
    if (j==len){   
        return 1;
    }
    return 0;
}