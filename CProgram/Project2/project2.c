/*CSI 333. Programming at the Hardware-Software Interface
    Spring 2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GenerateResult(FILE *inFile,FILE *outFile){
/*split every word and output them ordered backward*/
    char a,*str,*temp,result[255];
    int i,len,start,end,tempLen;
    end = -1;
    start = -1;
    //--------------------------------
    str = (char*)malloc(255);
    if(str == NULL){
        printf("Allocation failed.\n");
        exit(1);
    }
    //-------------
    while(fgets(str, 255, inFile) != NULL){
        len = strlen(str);
        /*travel every characters in this string. If meet ' ','\t',
         * this program will output word between ' 'or'\t',separately*/
        for(i = len - 1;i >= 0;i--){
            //----------------------------------
            temp = (char*)malloc(sizeof(char));
            if(temp == NULL){
                printf("Allocation failed.\n");
                exit(1);
            }
            //----------------
            a = str[i];
            if(a != ' '&&a != '\t'&&a != '\n'){
                if(end == -1){
                    end = i;
                }
                if(i == 0){
                    start = 0;
                }
            }
            if(end != -1){
                if(a == ' '||a == '\t'||a == '\n'){
                    if(start == -1){
                        start = i;
                    }
                }
            }
            if(end !=-1&&start!=-1){
                if(start == 0){
                    strncpy(temp,str, (size_t) (end - start + 1));
                }
                else{
                    strncpy(temp,str + start + 1, (size_t) (end - start));
                }
                fprintf(outFile,"%s ",temp);
                start = -1;
                end = -1;
            }
        }
        fprintf(outFile,"\n");
    }
    printf("%s\n","Finished.");fflush(stdout);
}

int main(int argc,char *argv[])
{
    /*find the input file and creat output file*/
    char *inputf = argv[1];
    char *outputf = argv[2];
    FILE *inFile, *outFile;

    if((inFile = fopen(inputf, "r"))== NULL){
        printf("%s\n","Input file cannot found!" );
        exit(-1);
    }
    if((outFile = fopen(outputf, "a")) == NULL){
        printf("%s\n","Output file cannot open!" );
        exit(-1);
    }
    GenerateResult(inFile,outFile);
    if (fclose(inFile) == EOF || fclose(outFile) == EOF) {
        perror("File close failed!");
    }
    return 0;
}
