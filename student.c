#include "bmp.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
// DO NOT EDIT ABOVE THIS LINE
// ============================

// ===== STUDENT TODO (BEGIN) =====
Pixel apply_filter(Pixel p){
    // add code
}

int count_nodes(TreeNode *root){
    // add code
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
