
#ifndef TREE_H
#define TREE_H

typedef struct TreeNode{
    int value;
    struct TreeNode *left,*right;
}TreeNode;

TreeNode* build_full_tree(int h);
TreeNode* build_example_tree();
void free_tree(TreeNode *r);

#endif
