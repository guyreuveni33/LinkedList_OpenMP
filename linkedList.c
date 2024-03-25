/* 206398596 Guy Reuveni
   208189126 Niv Swisa */
#include "linkedList.h"
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

#include <stdio.h>

// Initialize a new list
node_t *init_list(void) {
    node_t *head = malloc(sizeof(node_t));
    if (!head)
        return NULL;
    head->value = INT_MIN;
    head->next = NULL;
    head->lock = malloc(sizeof(omp_lock_t));
    if (!head->lock) {
        free(head);
        return NULL;
    }
    omp_init_lock(head->lock);
    return head;
}

void sorted_insert(node_t *head, int val) {
    /* Find the right place to insert */
    node_t *ptr = head->next;
    node_t *prev = head;

    while (ptr != NULL && ptr->value < val) {
        prev = ptr;
        ptr = ptr->next;
    }

    /* Lock the elment that may be modified */
    omp_set_lock(prev->lock);

    /* Confirm that the element is still in the right place */
    if (prev->next != ptr) {
        ptr = prev->next;
        while (ptr != NULL && ptr->value < val) {
            omp_set_lock(ptr->lock);
            omp_unset_lock(prev->lock);
            prev = ptr;
            ptr = ptr->next;
        }
    }

    /* Insert the new node */
    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = val;
    new_node->next = ptr;
    new_node->lock = malloc(sizeof(omp_lock_t));
    omp_init_lock(new_node->lock);
    prev->next = new_node;
    omp_unset_lock(prev->lock);
}

// Remove a value from the list
void remove_val(node_t *head, int val) {
    node_t *prev = head;
    omp_set_lock(prev->lock);
    node_t *current = prev->next;

    while (current != NULL) {
        omp_set_lock(current->lock);
        if (current->value == val) {
            prev->next = current->next;
            omp_unset_lock(current->lock);
            omp_destroy_lock(current->lock);
            free(current->lock);
            free(current);
            omp_unset_lock(prev->lock);
            return;
        }
        omp_unset_lock(prev->lock);
        prev = current;
        current = current->next;
    }
    omp_unset_lock(prev->lock);
}

// Find a value in the list
int find_val(node_t *head, int val) {
    node_t *current = head->next;
    while (current != NULL) {
        if (current->value == val) {
            return 1; // Found
        }
        current = current->next;
    }
    return 0;
}


// Get the length of the list
int get_len(node_t *head) {
    int length = 0;
    node_t *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length -1;
}

// Free the list and its resources
void free_list(node_t *head) {
    node_t *current = head;
    while (current != NULL) {
        node_t *temp = current;
        current = current->next;
        omp_destroy_lock(temp->lock);
        free(temp->lock);
        free(temp);
    }
}