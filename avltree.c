#include <stdio.h>
#include <stdlib.h>

typedef struct avl_node{
    int key,value;
    struct avl_node *left,*right;
    int height;
}avl_node;

#define avl_node_height(n) ((n)?(n)->height:0)
#define max2(a,b) ((a)>(b)?(a):(b))

#define avl_node_balance(n) ((n)?\
        avl_node_height((n)->left)-avl_node_height((n)->right):\
        0)
avl_node * avl_node_new(int k,int v){
    avl_node *res=malloc(sizeof(avl_node));
    res->key=k;
    res->value=v;
    res->left=res->right=NULL;
    res->height=1;
    return res;
}
avl_node *avl_node_right_rotate(avl_node *y){
    avl_node* x,*t2;
    x=y->left;
    t2=x->right;
    x->right=y;
    y->left=t2;
    
    y->height=max2(avl_node_height(y->left),
            avl_node_height(y->right))+1;

    x->height=max2(avl_node_height(x->left),
            avl_node_height(x->right))+1;
    return x;
}
avl_node *avl_node_left_rotate(avl_node *y){
    avl_node* x,*t2;
    x=y->right;
    t2=x->left;
    x->right=y;
    y->left=t2;
    
    y->height=max2(avl_node_height(y->left),
            avl_node_height(y->right))+1;

    x->height=max2(avl_node_height(x->left),
            avl_node_height(x->right))+1;
    return x;
}

avl_node * avl_node_insert(avl_node* node,int k,int v){
    if(node==NULL){
        return avl_node_new(k,v);
    }else if(k<node->key){
        node->left=avl_node_insert(node->left,k,v);
    }else{
        node->right=avl_node_insert(node->right,k,v);
    }
    int balance=avl_node_balance(node);
    if(balance>1 && k <node->left->key)
        return avl_node_right_rotate(node);
    if(balance<-1 && k > node->right->key)
        return avl_node_left_rotate(node);
    
    if(balance>1 && k>node->left->key){
        node->left=avl_node_left_rotate(node->left);
        return avl_node_right_rotate(node);
    }
    if(balance<-1 && k< node->right->key){
        node->right=avl_node_right_rotate(node->right);
        return avl_node_left_rotate(node);
    }
    return node;
}

typedef void(* avl_walk_fn)(avl_node *);
void avl_node_preorder(avl_node *node,avl_walk_fn fn){
    if(node==NULL) return;
    avl_node_preorder(node->left,fn);
    fn(node);
    avl_node_preorder(node->right,fn);
}   
void walk(avl_node *n){
    printf("#node{key: %d ,value: %d,height: %d}\n",n->key,n->value,
            n->height);
}
#include <time.h>
int main(){
    int i,n=100;
    avl_node *node=NULL;
    srand(time(NULL));
    for(i=0;i<10000;++i){
        node=avl_node_insert(node,rand()%10,i);
    }
    avl_node_preorder(node,walk);
    return 0;
}
