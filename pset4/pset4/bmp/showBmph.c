#include <stdio.h>
#include "bmp.h"

int main(int argc, char** argv) {
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./showBmph infile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[1];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    printf("bfOffBits:   %d", bf.bfOffBits);
    printf("\n");
    printf("bfReserved1: %d", bf.bfReserved1);
    printf("\n");
    printf("bfReserved2: %d", bf.bfReserved2);
    printf("\n");
    printf("bfSize:      %d", bf.bfSize);
    printf("\n");
    printf("bfType:      %d", bf.bfType);
    printf("\n\n");
    
    
    printf("biBitCount:      %d", bi.biBitCount);
    printf("\n");
    printf("biClrImportant:  %d", bi.biClrImportant);
    printf("\n");
    printf("biClrUsed:       %d", bi.biClrUsed);
    printf("\n");
    printf("biCompression:   %d", bi.biCompression);
    printf("\n");
    printf("biHeight:        %d", bi.biHeight);
    printf("\n");
    printf("biPlanes:        %d", bi.biPlanes);
    printf("\n");
    printf("biSize:          %d", bi.biSize);
    printf("\n");
    printf("biSizeImage:     %d", bi.biSizeImage);
    printf("\n");
    printf("biWidth:         %d", bi.biWidth);
    printf("\n");
    printf("biXPelsPerMeter: %d", bi.biXPelsPerMeter);
    printf("\n");
    printf("biYPelsPerMeter: %d", bi.biYPelsPerMeter);
    printf("\n");
    
    fclose(inptr);
    
    return 0;
}