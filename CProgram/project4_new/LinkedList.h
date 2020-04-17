//
// Created by 昊 on 2019/5/8.
//

#ifndef PROJECT4_NEW_LINKEDLIST_H
#define PROJECT4_NEW_LINKEDLIST_H

#define NEW (struct node*)malloc(sizeof(struct node))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*
	This is a singular linkedlist.
*/
/*
Each node of such a list contains a string of length at most 255,
a positive integer (i.e., an integer value ≥ 1)
and a pointer to the next node of the list.
*/
struct node
{
    int index;
    char *text;
    struct node *pNext;
};

int size;

struct node* InitLinkedList(char* str){
    struct node* pHead = NEW;
    if(NULL == pHead){
        printf("%s\n","allocation failure");fflush(stdout);
        exit(-1);
    }
    pHead->text = (char*)malloc(255);

    strcpy(pHead->text,str);
    pHead->index = 1;
    pHead->pNext = NULL;
    size = 1;

    return pHead;
}

bool isEmpty(struct node* pNode){
    if(NULL == pNode){
        return true;
    }
    return false;
}

bool checkELeIndex(int num){
    return num >= 1 && num <= size;
}

bool checkEleContent(struct node* pNode, char* str){
    struct node* p = pNode;
//	char *temp = (char*)malloc(sizeof(char));
//	strcpy(temp,pNode->text);
    if(strcmp(pNode->text,str) == 0){
        printf("%s\n", "Such text exists already");fflush(stdout);
        return false;
    }else {
        while (NULL != p->pNext) {
            p = p->pNext;
            if (strcmp(p->text, str) == 0) {
                printf("%s\n", "Such text exists already");
                fflush(stdout);
                return false;
            }
        }
    }

    return true;
}

void correctOrder(struct node* pNode){
    if(pNode != NULL){
        if(pNode->index != 1){
            pNode->index = 1;
        }

        struct node* p = pNode;

        while(NULL!=p->pNext){
            struct node* temp = p;
            p = p->pNext;

            p->index = temp->index + 1;
        }
    }
}

struct node* InsertAfter(struct node* pNode,int num, char* str){
    if(num == 1){
        //printf("%s\n", "Text inserted at the End");fflush(stdout);
        return InitLinkedList(str);
    }

    //if(checkEleContent(pNode,str)){

        //if(!checkELeIndex(num)){
            struct node* p = pNode;

            while(NULL!=p->pNext){
                p = p->pNext;
            }

            struct node* q = NEW;
            q->text = (char*)malloc(255);
            strcpy(q->text,str);
            q->index = p->index + 1;
            q->pNext = NULL;
            p->pNext = q;

            size += 1;

            //printf("%s\n", "Text inserted at the End");fflush(stdout);

            return pNode;
}

struct node* InsertBefore(struct node* pNode, int num, char* str){
    if(isEmpty(pNode)){
        printf("%s\n", "Text inserted at the beginning");fflush(stdout);
        return InitLinkedList(str);
    }
    if(checkEleContent(pNode,str)){
        if(!checkELeIndex(num)){
            struct node* newNode = NEW;
            newNode->text = (char*)malloc(255);
            strcpy(newNode->text,str);
            newNode->index = 1;
            newNode->pNext = pNode;

            size += 1;

            correctOrder(newNode);
            printf("%s\n", "Text inserted at the beginning");fflush(stdout);
            return newNode;
        }else{
            //find the node that before node will be add node before
            int i = 1;
            struct node* p = pNode;

            while(NULL!=p->pNext&&i<(num-1)){
                p = p->pNext;
                ++i;
            }

            struct node* q = p->pNext;

            //add the node before the node
            struct node* newNode = NEW;
            newNode->text = (char*)malloc(255);
            strcpy(newNode->text,str);
            newNode->index = 0;

            p->pNext = newNode;
            newNode->pNext = q;

            size += 1;

            correctOrder(pNode);

            printf("%s\n", "OK");fflush(stdout);
            return pNode;
        }
    }

    printf("%s\n", "Such text exists already");fflush(stdout);
    return NULL;
}

struct node* Delete(struct node* pNode, int num){
    if(!checkELeIndex(num)){
        printf("%s\n", "No Such index");fflush(stdout);
        return NULL;
    }else{
        //find the node before the node that will be deleted
        int i = 1;
        struct node* p = pNode;

        while(NULL!=p->pNext&&i<(num-1)){
            p = p->pNext;
            ++i;
        }
        //delete node
        struct node* AimNode;
        if(size == 1){
            printf("%s\n", "Deleted");fflush(stdout);
            size = 0;
            return NULL;
        }else AimNode = p->pNext;

        if(AimNode->index == size){
            p->pNext = NULL;
            size -=1;
            printf("%s\n", "Deleted");fflush(stdout);
            return pNode;
        }else if(num == 1){
            correctOrder(pNode->pNext);
            size -= 1;
            printf("%s\n", "Deleted");fflush(stdout);
            return pNode->pNext;
        }

        struct node* restNode = AimNode->pNext;
        p->pNext = restNode;

        correctOrder(pNode);
        size -= 1;

        printf("%s\n", "Deleted");fflush(stdout);
        return pNode;
    }
}

struct node* Replace(struct node* pNode, int num, char* str){
    if(checkEleContent(pNode,str)){

        if(!checkELeIndex(num)){
            printf("%s\n", "No such index");fflush(stdout);
            return NULL;
        }else{
            //find the node
            int i = 0;
            struct node* p = pNode;

            while(NULL!=p->pNext&&i<num){
                p = p->pNext;
                ++i;
            }
            p->text = (char*)malloc(255);
            strcpy(p->text, str);
            printf("%s\n", "Replaced");fflush(stdout);
            return pNode;
        }
    }
    printf("%s\n", "Such text exists already");fflush(stdout);
    return NULL;
}

void PrintListCommand(struct node* pNode){
    if(isEmpty(pNode)){
        printf("%s\n", "The list is empty");fflush(stdout);
    }else{
        int i = 0;
        struct node* p = pNode;

        printf("%d %s\n",pNode->index,pNode->text);

        while(NULL!=p->pNext){
            p = p->pNext;
            printf("%d %s\n",p->index,p->text);
        }
    }
}

void PrintIntoFile(struct node* pNode, FILE* output){
        int i = 0;
        struct node* p = pNode;
        if(p != NULL){
            fprintf(output, "%s", p->text);

            while(NULL!=p->pNext){
                p = p->pNext;
                fprintf(output, "%s", p->text);
            }
        }
}

void end(){
    exit(0);
}
#endif //PROJECT4_NEW_LINKEDLIST_H
