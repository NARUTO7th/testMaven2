/*#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char *whichChar(int num);
bool isNumber(char num);
bool isOperater(char operater);
int whichNum(char num);
int calculation();

int main(){
    //----------task1---------------
    int result = calculation();
    //int result = 10;
    bool mark = false;

    char *cardinal;
    cardinal = (char*)malloc(sizeof(char));

    if(cardinal == NULL){
        printf("%s\n","Allocation failed.");
        exit(1);
    }

    printf("Please enter the radix (2~16)\n");
    scanf("%s",cardinal);

    printf("%s\n",cardinal);

    if(result < 0){
        mark = true;
        result = result * (-1);
    }else if(result == 0){
        printf("Answer : %d\n",0);
        exit(1);
    }

    int radix = atoi(cardinal);
//get the reminder
    char reminder[100] = "";

    while(result >= radix && result != 0){
        int reminder1;
        char temp[10] = "";

        reminder1 = result - ((result / radix) * radix);

        if(reminder1 > 9){
            strcpy(temp,whichChar(reminder1));
        }else sprintf(temp,"%d",reminder1);


        strcat(reminder,temp);

        result = result / radix;

        int last = result;

        if(last < radix){
            if(last > 9){
                strcpy(temp,whichChar(last));
            }else sprintf(temp,"%d",last);

            strcat(reminder,temp);
        }
    }
//depends on the size of radix
    char b[100] = "";
    strcpy(b,reminder);
    int i;
    char t;
    for(i=0;i<strlen(b)/2;i++)
    {
        t=b[i];

        b[i]=b[strlen(b)-i-1];

        b[strlen(b)-i-1]=t;
    }

    if(mark){
        printf("Answer : -%s\n", b);
    } else printf("Answer : %s\n", b);

    return 0;
}

int calculation(){
    char *expression;
    expression = (char*)malloc(sizeof(char));

    printf("Please enter the valid expression\n");
    scanf("%s",expression);
    printf("%s\n",expression);

    int i;
    int j = 0;
    int first = 0;
    int second = 0;
    char oper;
    char temp1[20] = "";
    char temp2[20] = "";


    int resultNum;

    for(i = 0; i < strlen(expression);i++){
        sprintf(temp1,"%d",first);
        sprintf(temp2,"%d",second);

        if(isNumber(expression[i])){
            if(strcmp(temp1,"0") == 0){
                first = whichNum(expression[i]);
                j++;
            }else if(strcmp(temp2,"0") == 0){
                second = whichNum(expression[i]);
                j++;
            }
        }else if(isOperater(expression[i])){
            if(oper == '\0'){
                oper = expression[i];
                j++;
            }
        }

        if(j == 3){
            if(oper == '-'){
                resultNum = first - second;
                first = resultNum;
                second = 0;
                strcpy(temp1,"");
                strcpy(temp2,"0");
                oper = '\0';
                j = 1;
            }else if(oper == '+'){
                resultNum = first + second;
                first = resultNum;
                second = 0;
                strcpy(temp1,"");
                strcpy(temp2,"0");
                oper = '\0';
                j = 1;

                //result may be more than 1 digits,still don't know how to fix it---------------------------------------
            }else if(oper == '*'){
                resultNum = first * second;
                first = resultNum;
                second = 0;
                strcpy(temp1,"");
                strcpy(temp2,"0");
                oper = '\0';
                j = 1;
            }else if(oper == '/'){
                resultNum = first / second;
                first = resultNum;
                second = 0;
                strcpy(temp1,"");
                strcpy(temp2,"0");
                oper = '\0';
                j = 1;
            }
        }
    }
    printf("The result only have %d\n", j);
    if(j == 1){
        printf("The value is : %d\n",first);
    }

    return first;
}

bool isNumber(char num){
    switch(num) {
        case '0' :
            return true;

        case '1' :
            return true;

        case '2' :
            return true;

        case '3' :
            return true;

        case '4' :
            return true;

        case '5' :
            return true;

        case '6' :
            return true;

        case '7' :
            return true;

        case '8' :
            return true;

        case '9' :
            return true;

        default :
            return false;
    }
}

bool isOperater(char operater){
    switch(operater){
        case '+' :
            return true;

        case '-' :
            return true;

        case '*' :
            return true;

        case '/' :
            return true;

        default :
            return false;
    }
}

int whichNum(char num){
    switch(num){
        case '0' :
            return 0;

        case '1' :
            return 1;

        case '2' :
            return 2;

        case '3' :
            return 3;

        case '4' :
            return 4;

        case '5' :
            return 5;

        case '6' :
            return 6;

        case '7' :
            return 7;

        case '8' :
            return 8;

        case '9' :
            return 9;

        default :
            return 0;
    }
}

char *whichChar(int num){
    switch (num){
        case 10 :
            return "A";

        case 11 :
            return "B";

        case 12 :
            return "C";

        case 13 :
            return "D";

        case 14 :
            return "E";

        case 15 :
            return "F";

        case 16 :
            return "G";

        default:
            return "";
    }
}*/
#include <stdio.h>

char *deS(char forM[]);
int transformation(char forM[]);
int *change(int number,int basis);

int main(){
    printf("Please enter the formula:\n");
    char formula[100] = "";

    char *outPut = deS(formula);
    int answer = transformation(outPut);
    int answer1 = answer;
    printf("\nThe formula is:");
    printf("%d",answer);
    printf("\nPlease enter the Basis:");
    int basis = 0;
    scanf("%d",basis);
    int *last;
    last = change(answer1 , basis);
    printf("\nThe last answer is:");
    int i = 0;
    while(last[i] != '\0') {
        printf("%d", last[i]);
        i++;
    }
}
int transformation(char *forM){
    int i = 0;
    int count = 0;
    count = forM[0];
    while(forM[i] != '\0'){
        if(forM[i] == '+'){
            count = (int)count + (int)forM[i+1];
        }
        else if(forM[i] == '-'){
            count = (int)count - (int)forM[i+1];
        }
        else if(forM[i] == '*'){
            count = (int)count * (int)forM[i+1];
        }
        else if(forM[i] == '/'){
            count = (int)count / (int)forM[i+1];
        }
        i++;
    }
    int answer = count;
    return answer;
}

char *deS(char *forMa, char *answer){
    char localAnswer[100] = "";
    int i = 0;
    int j = 0;
    if(forMa[i] != '\0'){
        if(forMa[i] != ' '){
            answer[j] = forMa[i];
            j++;
        }
        i++;
    }
    return answer;
}
int *change(int number,int basis){
    int count[100] = {0};
    int temp = number;
    int i = 0;
    while(temp != 0){
        count[i] = temp % basis;
        temp = temp / basis;
        i++;
    }
    return count;
}