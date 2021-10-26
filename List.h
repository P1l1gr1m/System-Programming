#pragma once

typedef struct Node {
    int IPadress;
    const char* HostName;
    struct Node* next;
} Node;

// Pointer to the beginning of the list(to the first element)
Node* head;

/*************************************************************************
 FUNCTION:
    pop()
 DESCRIPTION:
    Deletes the first element of the list
 PARAMETERS:
    head: Node** - pointer to pointer that adresses the head node of the list
 RETURN VALUE:
    None
************************************************************************/
void pop(Node** head);

/*************************************************************************
 FUNCTION:
    push()
 DESCRIPTION:
     Adds the element to the list
 PARAMETERS:
    head: Node** - pointer to pointer that adresses the head node of the list
    ipAdress: int - IP of the element to add
    hostName: const char* - the hostname of the element to add
 RETURN VALUE:
    None
************************************************************************/
void push(Node** head, int ipAdress, const char* hostName);

/*************************************************************************
 FUNCTION:
    deleteList()
 DESCRIPTION:
    Deletes all elements of the list
 PARAMETERS:
    head: Node** - pointer to pointer that adresses the head node of the list
 RETURN VALUE:
    None
************************************************************************/
void deleteList(Node** head);