# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct node_t { // defines an element
    double data;
    struct node_t * next;
} node;

node * newList (){ // returns a head which points to an empty list
    node * a = NULL;
    a = (node *)malloc(sizeof(node));
    return a;
}

// void clear

void printlist(node * head){ // prints the entire list
    node * current = head;
    while (current != NULL) {
        printf("%lf", current->data);
        printf("\n");
        current = current->next;
    }
    return;
}

// void slice

void app(node * head, double data) { // appends a value to the end of the list
    node * current = head;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = newList();
    current->next->data = data;
    current->next->next = NULL;
    return;
}

void extend(node * head, node * head1){
    node * current = head;
    while (current->next != NULL){
        current = current->next;
    }
}

node * prp(node * head, double data){ // prepends a value to the beginning of the list an returns the new head
    node * temp = newList();
    temp->data = data;
    temp->next = head;

    return temp;
}

// void pop

// node * shift

double atIndex(node * head, int index){ // returns the value at a given index
    int i;
    for (i = 0; i < index+1; i++){
        if(head->next != NULL){
            head = head->next;
        } else {
            printf("Index %d is not in he range of this list.", index);
            return NAN;
        }
    }
    return head->data;
}

int indexOf(node * head, double val){ // returns the index of the first value in the list with the given value
    int i = 0;
    int c = -1;
    while (1){
        c++;
        if (head->data == val){
            break;
        } else {
            head = head->next;   
        }

        if (head->next = NULL){
            printf("Found no such element as %lf in this list.", val);
            return -1;
        }
    }
    return c;
}

// int very

// int some

void changeAtIndex(node * head, int index, double data){ // changes the value at the given index to the given value
    int i;
    for (i = 0; i < index; i++){
        head = head->next;
    }
    head->data = data;
    return;
}

int len(node * head){ // returns the length of the list
    int i = 0;
    while (head != NULL){
        i++;
        head = head->next;
    }
    return i;
}

void insert(node * head, double data, int index){ // inserts the given value at the given index (prepend values)
    if (index == 0){
        printf("to insert at the biginning of the list, use prp(node * head, double data) which will return the new head");
        return;
    }
    // task: make it able to prepend

    node * current = head;
    for (int i = 0; i < index; i++){
        if (current->next != NULL){
            current = current->next;
        } else if (i+1 == index){
            break;
        } else {
            printf("The index is not in this list");
            return;
        }
    }
    node * temp = current->next;
    current->next = newList();
    current->next->data = data;
    current->next->next = temp;
    return;
}

node * removeAtIndex(node * head, int index){
    // if (index == 0){
    //     printf("to remove at the biginning of the list, use prp(node * head, double data) which will return the new head");
    //     return;
    // }
    node * current = head;
    node * previous;

    if (index == 0){
        return current->next;
    }

    for (int i = 0; i < index; i++){
        if (current->next != NULL){
            previous = current;
            current = current->next;
        } else if (i+1 == index){
            break;
        } else {
            printf("The index is not in this list");
            return newList();
        }
    }
    previous->next = current->next;
    return newList();
}

// void removeValue

int sign(node * head){ //returns 1 if there are any signed numbers, otherwise it returns 0
    node * temp = head;
    while (temp != NULL) {
        if (abs(temp->data) != temp->data){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// int unsign

double average(node * head){ // returns the average of all elements
    double a;
    node * temp = head;
    while (temp != NULL){
        a += temp->data;
        temp = temp->next;
    }
    return a/len(head);
}

// double median

// double mode

double min (node * head){ // returns the smallest value in the list
    node * temp = head;
    double a = temp->data;
    while (temp != NULL){
        if (temp->data < a){
            a = temp->data;
        }
        temp = temp->next;
    }
    return a;
}

double max(node * head){ // returns the largest value in the list
    node * temp = head;
    double a = temp->data;
    while (temp != NULL){
        if (temp->data > a){
            a = temp->data;
        }
        temp = temp->next;
    }
    return a;
}

// void sort