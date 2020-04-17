#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Struct for each node in the linked list. */
struct node {
    int value;
    struct node *next;
};

void print_list(struct node *h,int size) {
/* Prints the values stored in the nodes of the list */
/* pointed to by h. */
    if (h == NULL) {
        printf("The list is empty.\n");
    }
    else {
        printf("The size of the list is: %d\n",size);
        printf("The list are:\n");
        while (h != NULL) {
            printf("%d\n", h->value);
            h = h->next;
        }
    }
} /* End of print_list */

void insert_node (struct node **h, struct node **t, int v) {
/* Creates a new node with value given by parameter v */
/* and inserts that node at the end of the list whose */
/* first and last nodes are pointed to by *h and *t */
/* respectively. */
    struct node *temp;
    if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL) {
        printf("Node allocation failed. \n");
        exit(1); /* Stop program */
    }
/* Space for node obtained. Copy the value v into the node */
/* and insert the node at the end of the list. */
    temp->value = v; temp->next = NULL;
    if (*h == NULL) {
/* List is currently empty. */
        *h = *t = temp;
    }
    else { /* The list is not empty. Use *t to add the node */
/* at the end. */
        (*t)->next = temp; *t = (*t)->next;
    }
} /* End of insert_node. */

int Random(int x){
    /*To generate random seed*/
    srand((unsigned)time(NULL));
    return rand()%x;
}

struct node *search_list(struct node *h, int x)
{
    /* Returns a pointer to the first node which contains the value */
    /* given by x. If there is no such node, the function returns */
    /* NULL. */
    struct node *p = NULL;
    while (h != NULL)
    {
        if (h->value == x){
            //return h;//错误1
            /* End of search_list */
            p = h;
            printf("%p\n" , p);

            h = h->next;
        }
        h = h->next;
    }
    if(p == NULL)
        return NULL;
    else
        return p;
    /* Here, there is no node with value x. */
    /*判断是否找到value*/
    //return NULL;

}
int main() {

    /* Pointers to the first and last nodes of list are used */
    /* to facilitate insertion at the end of list. */

    struct node *head, *tail,*model;
    head = NULL;
    tail = NULL;

    /*int ran = Random(24);
    int size = 0;
    while(ran != 8){
        insert_node(&head,&tail,ran);
        size++;
        ran = rand()%24;
    }
    print_list(head,size);*/
    insert_node(&head,&tail,1);
    insert_node(&head,&tail,2);
    insert_node(&head,&tail,3);
    insert_node(&head,&tail,4);
    insert_node(&head,&tail,1);
    insert_node(&head,&tail,5);

    printf("%s\n", "The list is :");
    print_list(head,6);
    printf("%s\n", "The address of 1 :");
    search_list(head,1);

    return 0;
}/* End of main. */





