/*
Jessica Sjostrom <sjostrom@sheridan.desire2learn.com>
----------------------------------------------------------------------
 */

/* 
 * File:   main.c
 * Author: Jessica Sjostrom <sjostrom@sheridan.desire2learn.com>
 *
 * Created on June 19, 2019, 3:51 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLUSH stdin=freopen(NULL,"r",stdin)
#define MAX_LEN 100

typedef struct node {
    size_t id;
    char* name;
    float gpa;
    struct node*next;
} student_t;

student_t *createList(); // function to create the linked list
student_t *createNode(); // function to create the node
void displayList(student_t* head); // function to display the list of students
void insertNode(student_t** head, student_t* node); // insert node into the sorted list
void deleteList(student_t** head); // delete the linked list.

/*
 * 
 */
int main() {
    printf("\nCreating List of students:\n\n");
    student_t *head = createList();
    displayList(head);
    deleteList(&head);
    return 0;
}

student_t *createList() {
    student_t *node = NULL, *current = NULL, *head = NULL;

    while ((node = createNode()) != NULL) {
        if (current == NULL && node->gpa > 0.00 && node->gpa <= 100.00 ) {
            head = node;
        } else if (node->gpa > 0.00 && node->gpa <= 100.00){
            insertNode(&head, node);
        }
        current = head;
    }
    return head;
}

student_t *createNode() {
    student_t* node = NULL;

    char tmpName[MAX_LEN] = {0};
    char tmpGPA[MAX_LEN] = {0};
    float tmpGPA2 = 0;

    static int id = 1000;

    printf("Insert student's name (id=%d): ", id);
    fgets(tmpName, sizeof (tmpName), stdin);
    tmpName[strcspn(tmpName, "\n")] = 0;
    FLUSH;

    if (strlen(tmpName) > 1) {
        node = (student_t*) malloc(sizeof (student_t));
        if (node == NULL) {
            printf("Cannot allocate memory for node\n");
            return node;
        }

        node->name = (char*) calloc(strlen(tmpName) + 1, sizeof (char));
        if (node->name == NULL) {
            printf("Cannot allocate memory for name\n");
            return node;
        }
        strcpy(node->name, tmpName);

        printf("Insert student's GPA (0-100): ");
        fgets(tmpGPA, sizeof (tmpGPA), stdin);
        tmpGPA[strcspn(tmpGPA, "\n")] = 0;
        char* pend;

        tmpGPA2 = strtof(tmpGPA, &pend);
        FLUSH;

        if (tmpGPA2 > 0.00 && tmpGPA2 <= 100.00) {
            node->gpa = tmpGPA2;
        } else {
            printf("Incorrect value of GPA! Ignore student input!\n\n");
            free(node->name);
            free(node);
            node->gpa = -1;
            return node;
        }

        node->id = id;
        node->next = NULL;
    }

    id++;
    printf("\n");

    return node;
}

void insertNode(student_t** head, student_t* node) {
    student_t* current = *head;

    if (node->gpa > (*head)->gpa) {
        node->next = *head;
        *head = node;
        return;
    }

    while (current->next != NULL) {
        if (node->gpa < current->next->gpa) {
            current = current->next;
        }
    }
    if (current->next == NULL) {
        current->next = node;
    } else {
        node->next = current->next;
        current->next = node;
    }
}

void displayList(student_t* head) {
    student_t *pos = head;
    register int i = 1;

    printf("============== List of Students: ==============\n");
    printf("  No\t GPA\t  ID\t Name\n");
    printf("-----------------------------------------------\n");
    if (pos == NULL) {
        printf("List of students is empty");
    } else {
        while (pos != NULL) {
            printf("%3d.\t%5.2f\t %zu\t %s\n", i++, pos->gpa, pos->id, pos->name);
            pos = pos->next;
        }
    }
}


void deleteList(student_t** head) {

    // The following code modified from midterm feedback received from Alex Babanski
    student_t* toDelete;
    
    while (*head != NULL) {
        toDelete = *head;
        
        *head = (*head) -> next;
        
        if (toDelete->name) {
            free(toDelete->name);
        }
        free(toDelete);
    }
}