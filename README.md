# LinkedList_OpenMP

This repository contains the implementation of a thread-safe linked list using C and OpenMP for synchronization. It demonstrates basic operations such as insertion, deletion, and search within a singly linked list structure, ensuring thread safety with the use of locks.

## Features

- **Thread-Safe Operations:** Utilizes `omp_lock_t` from OpenMP for mutex locks, ensuring thread-safe modifications and access to the list.
- **Sorted Insertion:** Inserts new nodes in a sorted order based on the integer value they hold.
- **Value Removal:** Removes nodes by value, ensuring the list remains sorted.
- **Value Search:** Searches the list for a node containing a specific value.
- **Length Retrieval:** Computes and returns the length of the list.
- **List Deallocation:** Properly frees all allocated memory used by the list, including node and lock structures.

## Usage

### Data Structure

The linked list is represented by `node_t` structures, containing:

- `value`: The integer value of the node.
- `next`: Pointer to the next node in the list.
- `lock`: An OpenMP lock used to ensure thread-safe modifications.

### Functions

- `node_t *init_list(void);` - Initialize an empty list.
- `void sorted_insert(node_t *head, int val);` - Insert a value into the list in a sorted manner.
- `void remove_val(node_t *head, int val);` - Remove a node with the specified value from the list.
- `int find_val(node_t *head, int val);` - Search for a value in the list.
- `int get_len(node_t *head);` - Retrieve the length of the list.
- `void free_list(node_t *head);` - Free the memory allocated for the list.
