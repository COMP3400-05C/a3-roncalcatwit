#include "list.h"
#include <stdlib.h>
#include <stdio.h> 

/**
 * Returns the head of the linked list.
 * 
 * @param head Pointer to the first node of the linked list.
 * @return The head of the linked list. If the list is empty (NULL), returns NULL.
 */
struct ll_node *ll_head(struct ll_node *head) {
    return head;
}

/**
 * Returns the tail (last node) of the linked list.
 *
 * @param head Pointer to the first node of the linked list.
 * @return Pointer to the last node, or NULL if head is NULL.
 */
struct ll_node *ll_tail(struct ll_node *head) {
    if (!head) return NULL;
    struct ll_node *cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    return cur;
}

/**
 * Returns the number of nodes in the linked list.
 *
 * @param head Pointer to the first node of the linked list.
 * @return The number of nodes. 0 if head is NULL.
 */
int ll_size(struct ll_node *head) {
    int count = 0;
    struct ll_node *cur = head;
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count;
}

/**
 * Finds the first node containing the given value.
 *
 * @param head Pointer to the first node of the linked list.
 * @param value The integer value to search for.
 * @return Pointer to the node containing value, or NULL if not found or head is NULL.
 */
struct ll_node *ll_find(struct ll_node *head, int value) {
    struct ll_node *cur = head;
    while (cur) {
        if (cur->data == value) return cur;
        cur = cur->next;
    }
    return NULL;
}

/**
 * Convert the linked list to a newly-allocated integer array.
 *
 * @param head Pointer to the first node of the linked list.
 * @return Pointer to malloc'd int array with list contents in order, or NULL if head is NULL.
 *         Caller is responsible for freeing the returned array.
 */
int *ll_toarray(struct ll_node *head) {
    if (!head) return NULL;

    int n = ll_size(head);
    if (n == 0) return NULL;

    int *arr = malloc(sizeof(int) * n);
    if (!arr) return NULL;

    struct ll_node *cur = head;
    int i = 0;
    while (cur && i < n) {
        arr[i++] = cur->data;
        cur = cur->next;
    }
    return arr;
}

/**
 * Create a new node (single-node list) with given data.
 *
 * @param data Value to store in the node.
 * @return Pointer to the newly allocated node, or NULL if malloc fails.
 */
struct ll_node *ll_create(int data) {
    struct ll_node *node = malloc(sizeof(struct ll_node));
    if (!node) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

/**
 * Free all nodes in the list.
 *
 * @param head Pointer to the first node of the linked list.
 *             If NULL nothing is done.
 */
void ll_destroy(struct ll_node *head) {
    struct ll_node *cur = head;
    while (cur) {
        struct ll_node *next = cur->next;
        free(cur);
        cur = next;
    }
}

/**
 * Append a new node with the given data to the tail of the list.
 *
 * Note: This function assumes `head` is non-NULL (per tests). If head is NULL, it does nothing.
 *
 * @param head Pointer to the first node of the linked list.
 * @param data Value to append.
 */
void ll_append(struct ll_node *head, int data) {
    if (!head) return; // cannot update caller's head since signature returns void
    struct ll_node *tail = ll_tail(head);
    if (!tail) return;
    struct ll_node *node = ll_create(data);
    if (!node) return; // allocation failure -> do nothing
    tail->next = node;
}

/**
 * Create a linked list from an integer array.
 *
 * @param data Pointer to integer array (may be NULL if len == 0).
 * @param len Number of elements in data.
 * @return Pointer to head of newly created list, or NULL if len == 0 or malloc fails.
 */
struct ll_node *ll_fromarray(int* data, int len) {
    if (!data || len <= 0) return NULL;

    struct ll_node *head = ll_create(data[0]);
    if (!head) return NULL;

    struct ll_node *tail = head;
    for (int i = 1; i < len; ++i) {
        struct ll_node *node = ll_create(data[i]);
        if (!node) {
            // allocation failed: clean up and return NULL
            ll_destroy(head);
            return NULL;
        }
        tail->next = node;
        tail = node;
    }
    return head;
}

/**
 * Remove the first node in the list that has the specified value.
 *
 * @param head Pointer to the first node of the linked list.
 * @param value Value to remove.
 * @return New head of the list (may be different if the original head was removed),
 *         or NULL if list becomes empty or was NULL.
 */
struct ll_node *ll_remove(struct ll_node *head, int value) {
    if (!head) return NULL;

    // If head is to be removed
    if (head->data == value) {
        struct ll_node *newhead = head->next;
        free(head);
        return newhead;
    }

    struct ll_node *prev = head;
    struct ll_node *cur = head->next;
    while (cur) {
        if (cur->data == value) {
            prev->next = cur->next;
            free(cur);
            return head;
        }
        prev = cur;
        cur = cur->next;
    }
    // not found
    return head;
}


int main(void) {
    printf("Quick manual test of linked list functions\n");

    struct ll_node *lst = ll_create(1);
    if (!lst) { printf("create failed\n"); return 1; }
    ll_append(lst, 2);
    ll_append(lst, 3);
    printf("size = %d\n", ll_size(lst));
    int *arr = ll_toarray(lst);
    if (arr) {
        printf("array: ");
        for (int i = 0; i < ll_size(lst); ++i) printf("%d ", arr[i]);
        printf("\n");
        free(arr);
    }
    struct ll_node *f = ll_find(lst, 2);
    printf("find 2: %s\n", f ? "found" : "not found");

    lst = ll_remove(lst, 1);
    printf("after remove head, size = %d\n", ll_size(lst));

    ll_destroy(lst);
    return 0;
}

