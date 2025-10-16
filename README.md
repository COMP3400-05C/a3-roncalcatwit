[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/2Sm1Jsaz)
# Assignment 3

## Introduction

In this assignment, you will be writing a basic linked-list in the C language.

To get started, first clone from GitHub. You may need to "close" the existing folder first.

### Build Instructions

In the terminal, run the following command in the terminal, run the following command to compile and
build the programs:

    make

### Running Unit Tests

To run the unit tests, run the following command for `ll_head`:

    ./test_head

For this assignment, there are lots of test files. For example:

- test_head
- test_tail
- test_size
- test_find
- test_remove

and so on.

### Commit Instructions

After completing each function first add the file called `parta.c` to staging:

    git add parta.c

Then do the actual commit:

    git commit -m 'Completed function ll_head'

When you have completed all functions and are ready to submit the assignment, run the following command:

    git push

## Instructions

The linked list struct we'll be using contains two member variables: `data` and `next`, and is defined as such:

    struct ll_node {
        int data;
        struct ll_node *next;
    };

### Part 1

For this part, you will implement the following functions. The first function is `ll_head`, and returns the head of a
list. The second function is `ll_tail`, and returns the tail of the list. The third function is `ll_size` and returns
the number of elements in the list.

The function definitions look like the following:

    struct ll_node *ll_head(struct ll_node *head);
    struct ll_node *ll_tail(struct ll_node *head);
    int             ll_size(struct ll_node *head);

Remember, just like arrays, a pointer to the first node is equivalent to pointing to the entire list. And as always,
make sure `list` is chacked against a NULL pointer.

Note. Make sure you don't just use `node++`. To move to the next node, you need
to do `node = node ->next`.

### Part 2

For this part, you will implement a function that takes two arguments: a list and a number. The function searches
through the list, and returns the node when the number is found. If not found, return NULL.

The function definition looks like the following:

    struct ll_node *ll_find(struct ll_node *head, int value);

### Part 3

For this part, you will implement a function that takes one arguments: the list.
The function converts the linked list into an array. The array needs to be
created by you (using `malloc`). If the linked list contains nothing, return
`NULL`. The test framework will call `free`, so you don't need to.

The function definition looks like the following:

    int *ll_toarray(struct ll_node *head);

### Part 4

For this part, you will implement a function that creates and destroys a linked list node. 

    struct ll_node *ll_create(int data);
    void ll_destroy(struct ll_node *head);

The `ll_create` function should malloc a new linked list with a single node. The newly created node will be returned as
a return value. The `ll_destroy` function will take in a list, and call `free` on each node of the list.

You need to implement both functions for the test cases to pass.

### Part 5

For this part, you will implement a function that creates new nodes and appends them to an existing linked list. 
The function signature looks like the following:

    void ll_append(struct ll_node *head, int data);

The `ll_append` function will add to the *tail* a new node with the specified value.

The test file for this function is called `test_create_append`. `ll_create` and `ll_append` need to be completed for the test cases to pass.

### Part 6

For this part, you will implement a function that creates a linked list from an array (you can think of
this as opposive of `ll_toarray`). The function signature looks like the following:

    struct ll_node *ll_fromarray(int* data, int len);

Note: Although you can repeatedly call `ll_append`, it is not recommended. Instead, it's best to keep track of the tail, and 
after appending the new node, update the tail. This will make the function more efficient (although not required).

### Part 7

For this part, you will implement a function that destroys a single node. The function signature looks like
the following:

    struct ll_node *ll_remove(struct ll_node *head, int value);

This function will take in a list, and call `free` on a specific node that has the same value.

> [!NOTE]
> If you call `ll_destroy`, it will free all nodes in the list, not just the one you want to delete.

The function will return the new head of the list (which will be same as the old one if a middle/end node was deleted). For example,
if the list contained `{11, 12, 13}` and you deleted 11, the *new head* needs to be 12. However, if the 12 or
13 was deleted, the head is still 11.

If the item doesn't exist, do nothing and return the old head.

## Troubleshooting

For this level you might also see the following error message:

    =================================================================
    ==4160==ERROR: LeakSanitizer: detected memory leaks

    Indirect leak of 16 byte(s) in 1 object(s) allocated from:
        #0 0x7f7b96fddbc8 in malloc (/lib/x86_64-linux-gnu/libasan.so.5+0x10dbc8)
        #1 0x7f7b9794864b in ll_append parta.c:28

This means you forgot to call `free` on some object. The object was created using `malloc` at line 28 in
list.c, but was never freed.

To solve this problem, try adding `printf` functions in strategic locations (i.e. before line 28 of list.c) and see if
you see them in your program output.

Or you can use VSCode's debugger to step through the code (set the "Debug" target to the
test file you want to debug (say test_remove), add a breakpoint somewhere in that file, and run the test).
