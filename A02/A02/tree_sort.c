#include "sorting_methods.h"
#include <stdlib.h>

struct tree_node
{
    struct tree_node *left;
    T data;
    struct tree_node *right;
};
void insert ( struct tree_node **, T) ;
//void order ( int*,struct tree_node *, int ) ;

void insert(struct tree_node **tr, T data)
{
    if( *tr == NULL)
    {
        (*tr)=malloc(sizeof(struct tree_node));
        (*tr)->left = NULL;
        (*tr)->right = NULL;
        (*tr)->data = data;
    }
    else
    {
        if(data < (*tr)->data)
            insert( &((*tr)->left),data);
        else
            insert( &((*tr)->right),data);
    }
}

int counter_insert;

void order(int *data,struct tree_node *link)
{    
    if(link != NULL)
    {
        order(data,link->left);
        data[counter_insert++] = link->data;
        order(data,link->right);
    }
}

void tree_sort(T *data, int first, int one_after_last)
{
    struct tree_node *root;
    root = NULL;
    
    for(int i=first; i<one_after_last;i++)
    {
        insert(&root,data[i]);
    }
    counter_insert = first;
    order(data,root);
}
