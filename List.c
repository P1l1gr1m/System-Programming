#pragma once
#include "list.h"
#include<malloc.h>

void push(Node** head, int ipAdress, const char* hostName) {
    if (head != NULL)
    {
        Node* tmp = (Node*)malloc(sizeof(Node));
        if (tmp != NULL)
        {
            tmp->IPadress = ipAdress;
            tmp->HostName = hostName;
            tmp->next = (*head);
            (*head) = tmp;
        }
    }
    else
        exit(-1);
}

void pop(Node** head) {
    Node* prev = NULL;
    if (head == NULL) {
        exit(-1);
    }
    else
    {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev->HostName);
        free(prev);
    }
}

void deleteList(Node** head) {
    Node* prev = NULL;
    if (head != NULL && (*head) != NULL)
    {
        while ((*head)->next != NULL) {
            prev = (*head);
            (*head) = (*head)->next;
            free(prev->HostName);
            free(prev);
        }
        free(*head);
    }
    else
        exit(-1);
}