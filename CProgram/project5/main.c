#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* line  = (char*)malloc(255);

    if(line == NULL){
        printf("%s","Allocation failed.");fflush(stdout);
        exit(1);
    }

    printf("%s","Please input a line of number divided by whitespace.");
    scanf("%s", line);
    int i;
    for(i = 0;i < strlen(line);i++){

//------------------------------------------------------------
    }
    return 0;
}