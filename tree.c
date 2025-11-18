
#include "tree.h"
#include <stdlib.h>

TreeNode* create(){ 
    TreeNode* n=malloc(sizeof(TreeNode));
    n->value=0; n->left=n->right=NULL; return n;
}

TreeNode* build_full_tree(int h){
    if(h<=0) return NULL;
    TreeNode* root=create();
    root->left=build_full_tree(h-1);
    root->right=build_full_tree(h-1);
    return root;
}

TreeNode* build_example_tree(){
    TreeNode *r=create(), *a=create(), *b=create(), *c=create();
    r->left=a;
    r->right=b;
    b->left=c;
    return r;
}

void free_tree(TreeNode *r){
    if(!r) return;
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}
