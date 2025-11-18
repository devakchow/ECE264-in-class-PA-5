
#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push,1)
typedef struct {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
} BMPHeader;

typedef struct {
    unsigned int header_size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int img_size;
    int xppm;
    int yppm;
    unsigned int colors;
    unsigned int important_colors;
} DIBHeader;
#pragma pack(pop)

BMPImage read_bmp(const char *path){
    BMPImage img={0,0,NULL};
    FILE *f=fopen(path,"rb");
    if(!f){printf("Cannot open %s\n",path); return img;}

    BMPHeader hdr;
    fread(&hdr,sizeof(hdr),1,f);
    if(hdr.type!=0x4D42){printf("Not BMP\n"); fclose(f); return img;}

    DIBHeader dib;
    fread(&dib,sizeof(dib),1,f);

    img.width=dib.width;
    img.height=dib.height;
    img.pixels=malloc(img.width*img.height*sizeof(Pixel));

    fseek(f,hdr.offset,SEEK_SET);

    int row_padded=(img.width*3+3)&(~3);
    unsigned char *row=malloc(row_padded);

    for(int y=0;y<img.height;y++){
        fread(row,row_padded,1,f);
        for(int x=0;x<img.width;x++){
            unsigned char b=row[x*3+0];
            unsigned char g=row[x*3+1];
            unsigned char r=row[x*3+2];
            img.pixels[(img.height-1-y)*img.width+x]=(Pixel){r,g,b};
        }
    }
    free(row);
    fclose(f);
    return img;
}

void write_bmp(const char *path, BMPImage *img){
    FILE *f=fopen(path,"wb");
    if(!f){printf("Cannot write %s\n",path);return;}

    int row_padded=(img->width*3+3)&(~3);
    int img_size=row_padded*img->height;
    BMPHeader hdr={0x4D42,54+img_size,0,0,54};
    DIBHeader dib={40,img->width,img->height,1,24,0,img_size,2835,2835,0,0};

    fwrite(&hdr,sizeof(hdr),1,f);
    fwrite(&dib,sizeof(dib),1,f);

    unsigned char *row=calloc(1,row_padded);

    for(int y=0;y<img->height;y++){
        for(int x=0;x<img->width;x++){
            Pixel p=img->pixels[(img->height-1-y)*img->width+x];
            row[x*3+0]=p.b;
            row[x*3+1]=p.g;
            row[x*3+2]=p.r;
        }
        fwrite(row,row_padded,1,f);
    }
    free(row);
    fclose(f);
}

void free_image(BMPImage *img){
    free(img->pixels);
    img->pixels=NULL;
}
