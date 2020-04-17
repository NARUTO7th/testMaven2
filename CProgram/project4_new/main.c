/*
CSI 333.Programming at the Hardware-Software Interface
Spring 2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Project4_Struct.h"

void store(struct Pro4Node* arr[], int lengthOfArray,char* fname,char* flag);
void print(struct Pro4Node* arr[], char* outfName, char* flag, int lengthOfArray);

int main(int argc, char *argv[]) {
    if(argc != 4){
        fprintf(stderr, "parameters on the command line is not right.\n");
        exit(1);
    }

    FILE *finp;
    char* fileName = (char*)malloc(50);
    if(fileName == NULL){
        printf("Allocation failed.\n");fflush(stdout);
        exit(1);
    }

    strcpy(fileName,argv[2]);

    if((finp = fopen(argv[2],"r")) == NULL){
        fprintf(stderr, "%s\n", "The input file specified on the command line can't be opened!");
        exit(1);
    }
    char *line = (char*)malloc(255);
    if(line == NULL){
        printf("Allocation failed.\n");fflush(stdout);
        exit(1);
    }
//So we start doing array
    struct Pro4Node* array[100];
    int indexOfEle = 0;
    int flag1 = 0;
//You get each row,
// and you go through each of the characters in each row, if it's: the previous one is in the array
    while((fgets(line,255,finp)) != NULL){
        int i,len = strlen(line);
        for(i = 0;i < len;i++){
            //current = line[i];

            if(line[i] == '#'){
                break;
            }else if(line[i] == '\n'){
                break;
            }else if(line[i] == '.'){
                if(line[i+1] == 't'&&line[i+2] == 'e'&&line[i+3] == 'x'&&line[i+4] == 't'){
                    flag1 = 1;
                    break;
                }
            }else if(line[i] == ':'){
                //store
                char* identifier = (char*)malloc(11);
                if(identifier == NULL){
                    printf("Allocation failed.\n");fflush(stdout);
                    exit(1);
                }
                int j;
                for(j = 0;j < i;j++){
                    identifier[j] = line[j];
                }
                identifier[j] = '\0';

                array[indexOfEle] = (struct Pro4Node*)malloc(sizeof(struct Pro4Node));

                if(array[indexOfEle]== NULL){
                    printf("Allocation failed.\n");fflush(stdout);
                    exit(1);
                }

                array[indexOfEle]->name = (char*)malloc(11);
                if(array[indexOfEle]->name == NULL){
                    printf("Allocation failed.\n");fflush(stdout);
                    exit(1);
                }

                strcpy(array[indexOfEle]->name,identifier);
                array[indexOfEle]->flag = flag1;
                indexOfEle +=1;
                break;
            }
        }

        line = (char*)malloc(255);
        if(line == NULL){
            printf("Allocation failed.\n");fflush(stdout);
            exit(1);
        }
    }
//store
    store(array,indexOfEle,fileName,argv[1]);
//print
    print(array,argv[3],argv[1],indexOfEle);
    return 0;
}

int is_in(char *text, char *search_word)
{
    int i = 0, j = 0, flag = -1;
    while (i < strlen(text) && j < strlen(search_word))
    {
        if (text[i] == search_word[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
        if (j == strlen(search_word))
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

void StoreintoPro4Struct(struct Pro4Node* arr[], int i, char* fname){

    char *line = (char*)malloc(sizeof(char));
    if(line == NULL){
        printf("Allocation failed.\n");fflush(stdout);
        exit(1);
    }

    FILE *finp;

    if((finp = fopen(fname,"r")) == NULL){
        fprintf(stderr, "%s\n", "The input file specified on the command line can't be opened!");
        exit(1);
    }

    while((fgets(line,255,finp)) != NULL){
        int j,len = strlen(line);
        int signal = 0;
        for(j = 0;j < len;j++){
            if(line[j] == '#'){
                break;
            }else if(line[j] == '\n'){
                break;
            }else if(line[j] == '.'){
                if(line[j+1] == 't'&&line[j+2] == 'e'&&line[j+3] == 'x'&&line[j+4] == 't'){
                    signal = 1;
                    break;
                }
            }
        }
        if(signal == 1){
            break;
        }

        line = (char*)malloc(255);
        if(line == NULL){
            printf("Allocation failed.\n");fflush(stdout);
            exit(1);
        }
    }

    char *identifier = (char*)malloc(11);
    if(identifier == NULL){
        printf("Allocation failed.\n");fflush(stdout);
        exit(1);
    }
//***************************************************
    strcpy(identifier,arr[i]->name);
//****************************************************

    line = (char*)malloc(255);
    if(line == NULL){
        printf("Allocation failed.\n");fflush(stdout);
        exit(1);
    }
//========================================================================
    struct node *HeadNode = NULL;
    arr[i]->HeadNode = (struct node*)malloc(sizeof(struct node));


    if(arr[i]->HeadNode == NULL){
        printf("Allocation failed.\n");fflush(stdout);
        exit(1);
    }
//========================================================================
    int num = 1;

    while((fgets(line,255,finp)) != NULL){
        int j,hashtage = 0;
        int len = strlen(line);
        for(j = 0;j < len;j++){
            if(line[j] == '#'){
                hashtage = j;
                break;
            }
        }

        char *processedLine = (char*)malloc(100);
        if(processedLine == NULL){
            printf("Allocation failed.\n");fflush(stdout);
            exit(1);
        }

        const char *brainer = " ";
        char *token = (char*)malloc(100);
        if(token == NULL){
            printf("Allocation failed.\n");fflush(stdout);
            exit(1);
        }

        if((hashtage != 0)&&(j != 0)){
            int n;
            for(n = 0;n < hashtage;n++){
                processedLine[n] = line[n];
            }
            processedLine[n] = '\0';

            token = strtok(processedLine,brainer);
            while(token != NULL){
                int k,length = strlen(token);
                for(k = 0;k < length;k++){
                    if(token[k] == '#'){
                        break;
                    }else if(token[k] == ':'){
                        break;
                    }
                }

                if(k == length){
                    if((is_in(token,identifier)) == 1){
                        //write into struct-------------------------------------------------------------------------------
                        if(HeadNode == NULL){
                            HeadNode = (struct node*)malloc(sizeof(struct node));

                            if(HeadNode == NULL){
                                printf("Allocation failed.\n");fflush(stdout);
                                exit(1);
                            }
                        }
                        HeadNode = InsertAfter(HeadNode,num,line);
                        num++;

                        break;
                    }
                }
                token = strtok(NULL,brainer);
            }
        }else{
            int n;
            for(n = 0;n < len;n++){
                processedLine[n] = line[n];
            }
            processedLine[len - 1] = '\0';

            token = strtok(processedLine,brainer);
            while(token != NULL){
                int k,length = strlen(token);
                for(k = 0;k < length;k++){
                    if(token[k] == '#'){
                        break;
                    }else if(token[k] == ':'){
                        break;
                    }
                }

                if(k == length){
                    if((is_in(token,identifier)) == 1){
                        //writing---------------------------------------------------------------------------------
                        if(HeadNode == NULL){
                            HeadNode = (struct node*)malloc(sizeof(struct node));

                            if(HeadNode == NULL){
                                printf("Allocation failed.\n");fflush(stdout);
                                exit(1);
                            }
                        }
                        HeadNode = InsertAfter(HeadNode,num,line);
                        num++;

                        break;
                    }
                }
                token = strtok(NULL,brainer);
            }
        }

        line = (char*)malloc(255);
        if(line == NULL){
            printf("Allocation failed.\n");fflush(stdout);
            exit(1);
        }

    }

    arr[i]->HeadNode = HeadNode;

}

void store(struct Pro4Node* arr[], int lengthOfArray,char* fname,char* flag){
    int i;

    if(strcmp(flag,"-b") == 0) {
        for (i = 0; i < lengthOfArray; i++) {
            if (arr[i]->flag == 0) {
                StoreintoPro4Struct(arr, i, fname);
            } else if (arr[i]->flag == 1) {
                StoreintoPro4Struct(arr, i, fname);
            }
        }
    }else if(strcmp(flag,"-v") == 0){
        for (i = 0; i < lengthOfArray; i++) {
            if (arr[i]->flag == 0) {
                StoreintoPro4Struct(arr, i, fname);
            }else break;
        }
    }else if(strcmp(flag,"-f") == 0){
        for (i = 0; i < lengthOfArray; i++) {
            if (arr[i]->flag == 1) {
                StoreintoPro4Struct(arr, i, fname);
            }
        }
    }else {
        fprintf(stderr, "%s\n", "Parameters in command line exist error!");
        exit(1);
    }
}

void print(struct Pro4Node* arr[], char* outfName, char* flag, int lengthOfArray){

    FILE *outputFile;
    if((outputFile = fopen(outfName,"w")) == NULL){
        fprintf(stderr, "%s\n", "The output file specified on the command line can't be opened!");
        exit(1);
    }
    //=====================================================================
    int i;
    for(i = 0;i < lengthOfArray;i++){
        if(strcmp(flag,"-b") == 0) {
            if (arr[i]->flag == 0) {
                fprintf(outputFile,"Variable ID -%s-\n", arr[i]->name);
                PrintIntoFile(arr[i]->HeadNode,outputFile);

            } else if (arr[i]->flag == 1) {
                fprintf(outputFile,"Flow Control ID -%s-\n", arr[i]->name);
                PrintIntoFile(arr[i]->HeadNode,outputFile);
            }
        }else if(strcmp(flag,"-v") == 0){
            if (arr[i]->flag == 0) {
                fprintf(outputFile,"Variable ID -%s-\n", arr[i]->name);
                PrintIntoFile(arr[i]->HeadNode,outputFile);
            }
        }else if(strcmp(flag,"-f") == 0){
            if (arr[i]->flag == 1) {
                fprintf(outputFile,"Flow Control ID -%s-\n", arr[i]->name);
                PrintIntoFile(arr[i]->HeadNode,outputFile);
            }
        }
    }
//=================================================================================

}