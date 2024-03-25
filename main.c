#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <omp.h>
#include "linkedList.h"

int main() {
    node_t *head = init_list();
    printf("Initialize the list head. Expected length: 0, Actual length: %d\n\n", get_len(head));

    int num_inputs;
    scanf("%d", &num_inputs);

    int *arr = (int *)malloc(sizeof(int) * num_inputs);
    if (!arr) {
        perror("Could not allocate enough for testing.");
        return -1;
    }
    for (int i = 0; i < num_inputs; i++) scanf("%d", &arr[i]);
    printf("Inserting to list...\n");

    #pragma omp parallel for
        for (int i = 0; i < num_inputs; i++) sorted_insert(head, arr[i]);
    #pragma omp barrier
    printf("Done inserting.\n\n");

    printf("Actual list: \n");
    node_t *current = head;
    while (current) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n\n");

    if (num_inputs > 1) {
        int num_half = num_inputs / 2;
        int *arr2 = (int *)malloc(sizeof(int) * num_half);
        if (!arr2) {
            perror("Could not allocate enough for testing.");
            return -1;
        }
        printf("Checking list len:\n");

        #pragma omp parallel for
            for (int i = 0; i < num_half; i++) arr2[i] = get_len(head);
        #pragma omp barrier

        printf("Results, should be all %d's:\n", num_inputs);
        for (int i = 0; i < num_half; i++) printf("%d ", arr2[i]);
        printf("\n\n");

        printf("Checking if half exists:\n");
        #pragma omp parallel for
            for (int i = 0; i < num_half; i++) arr2[i] = find_val(head, arr[i]);
        #pragma omp barrier

        printf("Results, should all be 1's:\n");
        for (int i = 0; i < num_half; i++) printf("%d ", arr2[i]);
        printf("\n\n");
        
        printf("Removing the [%d] number %d times:\n", arr[0], num_half);
        #pragma omp parallel for
            for (int i = 0; i < num_half; i++) remove_val(head, arr[0]);
        #pragma omp barrier
        printf("Done removing same number.\n");
        printf("New list len is %d, should be %d. The list: \n", get_len(head), num_inputs - 1);
        current = head;
        while (current) {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("NULL\n\n");

        printf("Removing half the list:\n");
        #pragma omp parallel for
            for (int i = 1; i < num_half; i++) remove_val(head, arr[i]);
        #pragma omp barrier
        printf("Done removing half the list.\n");
        if (num_inputs & 1) printf("New list len is %d, should be %d. The list: \n", get_len(head), num_half + 1);
        else printf("New list len is %d, should be %d. The list: \n", get_len(head), num_half);
        current = head;
        while (current) {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("NULL\n\n");

        printf("Checking not exists:\n");
        #pragma omp parallel for
            for (int i = 0; i < num_half; i++) arr2[i] = find_val(head, (INT_MAX - i - 1));
        #pragma omp barrier
        printf("Results, should all be 0's:\n");
        for (int i = 0; i < num_half; i++) printf("%d ", arr2[i]);
        printf("\n\n");

        free(arr2);

    } else if (num_inputs == 1) {
        int num_half = 50;
        int *arr2 = (int *)malloc(sizeof(int) * num_half);
        if (!arr2) {
            perror("Could not allocate enough for testing.");
            return -1;
        }
        printf("Checking list len:\n");
        #pragma omp parallel for
            for (int i = 0; i < num_half; i++) arr2[i] = get_len(head);
        #pragma omp barrier
        printf("Results, should be all %d's:\n", num_inputs);
        for (int i = 0; i < num_half; i++) printf("%d ", arr2[i]);
        printf("\n\n");

        printf("Checking if %d exists:\n", arr[0]);
        #pragma omp parallel for
            for (int i = 0; i < num_half; i++) arr2[i] = find_val(head, arr[0]);
        #pragma omp barrier
        printf("Results, should all be 1's:\n");
        for (int i = 0; i < num_half; i++) printf("%d ", arr2[i]);
        printf("\n\n");

        printf("Checking not exists:\n");
        #pragma omp parallel for
            for (int i = 0; i < num_half; i++) arr2[i] = find_val(head, (INT_MAX - i - 1));
        #pragma omp barrier
        printf("Results, should all be 0's:\n");
        for (int i = 0; i < num_half; i++) printf("%d ", arr2[i]);
        printf("\n\n");

        free(arr2);

    } else printf("List is empty.\n");

    free_list(head);
    printf("Freed the list, make sure to check memory leaks\n");
    free(arr);
    return 0;
}