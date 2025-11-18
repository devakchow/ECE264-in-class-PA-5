#include "bmp.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
// DO NOT EDIT ABOVE THIS LINE
// ============================

// ===== STUDENT TODO (BEGIN) =====
Pixel apply_filter(Pixel p){
    Pixel result;
    
    result.r = p.r;
    int green_boosted = p.g + 50;
    result.g = (green_boosted > 255) ? 255 : green_boosted;
    
    result.b = p.b;
    
    return result;
}

int count_nodes(TreeNode *root){
    if (root == NULL) {
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}
// ===== STUDENT TODO (END) =====

// DO NOT EDIT BELOW THIS LINE
// ============================
int main(int argc,char**argv){
    if(argc!=4){printf("Usage: ./run_morning in.bmp out.bmp\n"); return 1;}

    BMPImage img=read_bmp(argv[1]);
    for(int i=0;i<img.width*img.height;i++)
        img.pixels[i]=apply_filter(img.pixels[i]);
    write_bmp(argv[2],&img);

    TreeNode *t=build_full_tree(atoi(argv[3]));
    printf("Node count: %d\n",count_nodes(t));

    free_tree(t);
    free_image(&img);
    return 0;
}
