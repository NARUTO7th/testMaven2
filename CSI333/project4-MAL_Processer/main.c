/*



*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct element{
    char *name;
    int flag;
};

void print(struct element* arr[], int lengthOfArray,char* fname,char* flag,char* outfName);

//int main() {
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

    char *line = (char*)malloc(sizeof(char));
    if(line == NULL){
        printf("Allocation failed.\n");fflush(stdout);
        exit(1);
    }



    struct element* array[100];
    int indexOfEle = 0;
    int flag1 = 0;
//得到每一行，遍历每一行的每一个字符，如果是：之前的存入array中
    while((fgets(line,255,finp)) != NULL){
        int i,len = strlen(line);
        for(i = 0;i < len;i++){
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
                //存入操作
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

                array[indexOfEle] = (struct element*)malloc(sizeof(struct element));
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
//用得到的array，来在.text以下搜索
    print(array,indexOfEle,fileName,argv[1],argv[3]);
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

int getNextLinePos(FILE *p){
    int ch;
    int curpos = 0;
    while(ch != EOF){
        putchar(ch);
        ch=getc(p);
        if(ch == '\n'){
            break;
        }
    }
    return(ftell(p) - curpos + 1);
}

void SearchAndPrint(struct element* arr[], int i, char* fname, char* flag, char* outfName){

    char *line = (char*)malloc(sizeof(char));
    if(line == NULL){
        printf("Allocation failed.\n");fflush(stdout);
        exit(1);
    }

    FILE *finp;
    FILE *outputFile;
    /*if((finp = fopen(argv[1],"r")) == NULL){
        fprintf(stderr, "%s\n", "The input file specified on the command line can't be opened!");
        exit(1);
    }*/
    if((finp = fopen(fname,"r")) == NULL){
        fprintf(stderr, "%s\n", "The input file specified on the command line can't be opened!");
        exit(1);
    }
    if((outputFile = fopen(outfName,"w")) == NULL){
        fprintf(stderr, "%s\n", "The output file specified on the command line can't be opened!");
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

    //this is a flag to check whether the program should print variable or flow control only
    int VaOrFlow = 0;
    int flagForVaOrFlow = arr[i]->flag;  
//=====================================================================
    if(strcmp(flag,"-b") == 0) {
            if (arr[i]->flag == 0) {
                // fprintf(outputFile, "Variable ID -%s-\n", arr[i]->name);
                // fprintf(outputFile,"\n");
                fputs("Variable ID -",outputFile);
                fputs(arr[i]->name,outputFile);
                fputs("-\n",outputFile);
                fputs("",outputFile);

                fseek(outputFile, getNextLinePos(outputFile),SEEK_SET);//point to next line
            } else if (arr[i]->flag == 1) {
                // fprintf(outputFile, "Flow Control ID -%s-\n", arr[i]->name);
                // fprintf(outputFile,"\n");
                fputs("Flow Control ID -",outputFile);
                fputs(arr[i]->name,outputFile);
                fputs("-\n",outputFile);
                fputs("",outputFile);

                fseek(outputFile, getNextLinePos(outputFile),SEEK_SET);//point to next line
            }
    }else if(strcmp(flag,"-v") == 0){
            if (arr[i]->flag == 0) {
                // fprintf(outputFile, "Variable ID -%s-\n", arr[i]->name);
                // fprintf(outputFile,"\n");
                fputs("Variable ID -",outputFile);
                fputs(arr[i]->name,outputFile);
                fputs("-\n",outputFile);
                fputs("",outputFile);

                fseek(outputFile, getNextLinePos(outputFile),SEEK_SET);//point to next line

                VaOrFlow = 1;
            }
    }else if(strcmp(flag,"-f") == 0){
            if (arr[i]->flag == 1) {
                // fprintf(outputFile, "Flow Control ID -%s-\n", arr[i]->name);
                // fprintf(outputFile,"\n");

                fputs("Flow Control ID -",outputFile);
                fputs(arr[i]->name,outputFile);
                fputs("-\n",outputFile);
                fputs("",outputFile);

                fseek(outputFile, getNextLinePos(outputFile),SEEK_SET);//point to next line                

                VaOrFlow = 2;
            }
    }
//=================================================================================
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
                        //writing-------------------------------------------------------------------------------
                        // if(VaOrFlow == 0){
                        //     fputs(line,outputFile);
                        // }else if((VaOrFlow == 1)&&(flagForVaOrFlow == 0)){
                        //     fputs(line,outputFile);
                        // }else if((VaOrFlow == 2)&&(flagForVaOrFlow == 1)){
                        //     fputs(line,outputFile);
                        // }
                        fputs(line,outputFile);
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
                        // if(VaOrFlow == 0){
                        //     fputs(line,outputFile);
                        // }else if((VaOrFlow == 1)&&(flagForVaOrFlow == 0)){
                        //     fputs(line,outputFile);
                        // }else if((VaOrFlow == 2)&&(flagForVaOrFlow == 1)){
                        //     fputs(line,outputFile);
                        // }
                        fputs(line,outputFile);
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
}

void print(struct element* arr[], int lengthOfArray,char* fname,char* flag,char* outfName){
    int i;
    
    if(strcmp(flag,"-b") == 0) {
        for (i = 0; i < lengthOfArray; i++) {
            if (arr[i]->flag == 0) {
                SearchAndPrint(arr, i, fname, flag, outfName);

            } else if (arr[i]->flag == 1) {
                SearchAndPrint(arr, i, fname, flag, outfName);
            }
        }
    }else if(strcmp(flag,"-v") == 0){
        for (i = 0; i < lengthOfArray; i++) {
            if (arr[i]->flag == 0) {
                SearchAndPrint(arr, i, fname, flag, outfName);
            }else break;
        }
    }else if(strcmp(flag,"-f") == 0){
        for (i = 0; i < lengthOfArray; i++) {
            if (arr[i]->flag == 1) {
                SearchAndPrint(arr, i, fname, flag, outfName);
            }
        }
    }else {
        fprintf(stderr, "%s\n", "Parameters in command line exist error!");
        exit(1);
    }
}
