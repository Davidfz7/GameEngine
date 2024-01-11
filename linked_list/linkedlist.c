#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedlist.h"
//Linked list for the body

// int main(int argc, char *argv[]){
//     Node *head = NULL;
//     Rectangle rect =  {31, 32, 33, 34}; 
//     Rectangle rect2 = {35, 36, 37, 38};
//     Rectangle rect3 = {39, 40, 41, 42};
//     head = create_head(&rect);
//     append(head, &rect2);
//     append(head, &rect3);
//     free_list(head);
//     head = NULL;
//     if(head == NULL){
//         printf("Head is null now\n");
//     }
//     return 0;
// } 

Node *create_head(void *value){
    Node *newNode = (Node *) malloc(sizeof(Node));
    (*newNode).id = 0;
    (*newNode).data = value;
    (*newNode).next = NULL;
    return newNode;
}

void append(Node *head, void *value){
    int counter;
    while((*head).next != NULL){
        head = (*head).next;
    } 

    (*head).next = (Node *) malloc(sizeof(Node));
    (*(*head).next).id = (*head).id + 1;
    (*(*head).next).data = value;
    (*(*head).next).next = NULL;   
}

void free_list(Node *head){
    if(head != NULL){
        free_list((*head).next);
    }
    free(head);
}

bool empty(Node *node){
    if(node == NULL){
        return true;
    }
    return false;
}