#ifndef LINKEDLIST_H
#define LINKEDLIST_H
    
    typedef struct Node{
        int id;
        void *data;
        struct Node *next;
    } Node;
    typedef struct Rectangle{
        int x;
        int y;
        int width;
        int height;
    } Rectangle;

    typedef struct Foo{
        int a;
        int b;
    } Foo;
    Node *create_head(void *value);
    bool empty(Node *node);
    void append(Node *head, void *value);
    void free_list(Node *head);
#endif