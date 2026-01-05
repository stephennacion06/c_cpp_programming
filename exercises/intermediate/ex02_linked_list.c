/**
 * ex02_linked_list.c
 * 
 * Exercise: Implement a singly linked list with basic operations.
 * 
 * Requirements:
 * 1. Define node structure with data and next pointer
 * 2. Implement functions:
 *    - insert_front() - Add node at beginning
 *    - insert_end() - Add node at end
 *    - delete_node() - Remove node with specific value
 *    - search() - Find node with value
 *    - print_list() - Display all nodes
 *    - free_list() - Free all nodes
 * 3. Handle empty list cases
 * 4. Avoid memory leaks
 * 
 * Memory Implications:
 * - Each node: data + pointer overhead (typically 8-16 bytes)
 * - Non-contiguous memory: poor cache locality
 * - O(1) insertion/deletion at known position
 * - O(n) traversal and search
 * 
 * Learning objectives:
 * - Pointer manipulation
 * - Dynamic memory per node
 * - List traversal patterns
 * - Memory leak prevention
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Windows UTF-8 console setup */
#ifdef _WIN32
#include <windows.h>
void setup_utf8_console(void) {
    SetConsoleOutputCP(CP_UTF8);
}
#else
void setup_utf8_console(void) {}
#endif

/**
 * Node structure for singly linked list
 */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/**
 * Create a new node
 * Time complexity: O(1)
 */
Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    new_node->data = data;
    new_node->next = NULL;
    
    return new_node;
}

/**
 * Insert node at the front of the list
 * Time complexity: O(1)
 */
void insert_front(Node **head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    
    new_node->next = *head;
    *head = new_node;
}

/**
 * Insert node at the end of the list
 * Time complexity: O(n) - must traverse to end
 */
void insert_end(Node **head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    
    /* If list is empty, new node becomes head */
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    /* Traverse to last node */
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
}

/**
 * Insert node after a node with specific value
 * Time complexity: O(n)
 */
bool insert_after(Node *head, int target, int data) {
    /* Find target node */
    Node *current = head;
    while (current != NULL && current->data != target) {
        current = current->next;
    }
    
    /* Target not found */
    if (current == NULL) {
        return false;
    }
    
    /* Create and insert new node */
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return false;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    
    return true;
}

/**
 * Delete first node with specific value
 * Time complexity: O(n)
 */
bool delete_node(Node **head, int data) {
    if (*head == NULL) {
        return false;
    }
    
    /* If head node contains the data */
    if ((*head)->data == data) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return true;
    }
    
    /* Search for node to delete */
    Node *current = *head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    
    /* Node not found */
    if (current->next == NULL) {
        return false;
    }
    
    /* Delete node */
    Node *temp = current->next;
    current->next = current->next->next;
    free(temp);
    
    return true;
}

/**
 * Search for a node with specific value
 * Time complexity: O(n)
 */
Node* search(Node *head, int data) {
    Node *current = head;
    
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/**
 * Get length of list
 * Time complexity: O(n)
 */
size_t get_length(Node *head) {
    size_t count = 0;
    Node *current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

/**
 * Print all nodes in the list
 * Time complexity: O(n)
 */
void print_list(Node *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    printf("List: ");
    Node *current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}

/**
 * Free all nodes in the list
 * Time complexity: O(n)
 * CRITICAL: Must free all nodes to prevent memory leaks
 */
void free_list(Node **head) {
    Node *current = *head;
    Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
}

/**
 * Reverse the linked list
 * Time complexity: O(n)
 * Space complexity: O(1) - in-place reversal
 */
void reverse_list(Node **head) {
    Node *prev = NULL;
    Node *current = *head;
    Node *next = NULL;
    
    while (current != NULL) {
        next = current->next;  /* Save next */
        current->next = prev;  /* Reverse link */
        prev = current;        /* Move prev forward */
        current = next;        /* Move current forward */
    }
    
    *head = prev;
}

/**
 * Main function with test cases
 */
int main(void) {
    setup_utf8_console();
    
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║        Singly Linked List Implementation                   ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    Node *head = NULL;
    
    /* Test insert_front */
    printf("\n1. Inserting at front: 30, 20, 10\n");
    insert_front(&head, 30);
    print_list(head);
    
    insert_front(&head, 20);
    print_list(head);
    
    insert_front(&head, 10);
    print_list(head);
    
    /* Test insert_end */
    printf("\n2. Inserting at end: 40, 50\n");
    insert_end(&head, 40);
    print_list(head);
    
    insert_end(&head, 50);
    print_list(head);
    
    /* Test insert_after */
    printf("\n3. Inserting 25 after 20\n");
    if (insert_after(head, 20, 25)) {
        print_list(head);
    }
    
    /* Test search */
    printf("\n4. Searching for 25\n");
    Node *found = search(head, 25);
    if (found != NULL) {
        printf("   Found node with value: %d\n", found->data);
    }
    
    printf("   Searching for 100\n");
    found = search(head, 100);
    if (found == NULL) {
        printf("   Node with value 100 not found\n");
    }
    
    /* Test length */
    printf("\n5. List length: %zu\n", get_length(head));
    print_list(head);
    
    /* Test delete */
    printf("\n6. Deleting 25\n");
    if (delete_node(&head, 25)) {
        print_list(head);
    }
    
    printf("   Deleting 10 (head)\n");
    if (delete_node(&head, 10)) {
        print_list(head);
    }
    
    printf("   Deleting 50 (tail)\n");
    if (delete_node(&head, 50)) {
        print_list(head);
    }
    
    /* Test reverse */
    printf("\n7. Reversing list\n");
    printf("   Before: ");
    print_list(head);
    
    reverse_list(&head);
    
    printf("   After:  ");
    print_list(head);
    
    /* Clean up */
    printf("\n8. Freeing all nodes\n");
    free_list(&head);
    print_list(head);
    
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║ Performance Analysis:                                      ║\n");
    printf("║ - Insert front: O(1)                                       ║\n");
    printf("║ - Insert end: O(n)                                         ║\n");
    printf("║ - Delete: O(n)                                             ║\n");
    printf("║ - Search: O(n)                                             ║\n");
    printf("║ - Reverse: O(n) time, O(1) space                           ║\n");
    printf("║                                                            ║\n");
    printf("║ Memory Overhead:                                           ║\n");
    printf("║ - Per node: 8 bytes (pointer) + data size                 ║\n");
    printf("║ - Poor cache locality vs. arrays                           ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    return 0;
}
