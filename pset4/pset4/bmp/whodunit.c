#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

LONG isPixelGreen(const RGBTRIPLE* const rgb) {
    if (rgb == NULL) { 
        return 0; 
    }
    return rgb->rgbtBlue  == 0   &&
           rgb->rgbtGreen == 255 &&
           rgb->rgbtRed   == 0;
}

LONG makePixelBlue(RGBTRIPLE* const rgb) {
    if (rgb == NULL) {
        return 1; 
    }
    rgb->rgbtBlue  = 255;
    rgb->rgbtGreen = 0;
    rgb->rgbtRed   = 0;
    return 0;
}

LONG isPixelRed(const RGBTRIPLE* const rgb) {
    if (rgb == NULL) {
        return 0;
    }
    return rgb->rgbtBlue  == 0 &&
           rgb->rgbtGreen == 0 &&
           rgb->rgbtRed   == 255;
}

LONG makePixelWhite(RGBTRIPLE* const rgb) {
    if (rgb == NULL) {
        return 1;
    }
    rgb->rgbtBlue  = 255;
    rgb->rgbtGreen = 255;
    rgb->rgbtRed   = 255;
    return 0;
}

LONG main(LONG argc, char** argv) {

    if (argc != 3) {
        printf("Usage: ./whodunit infile outfile\n");
        return 1;
    }
    
    FILE* fileIn = fopen(argv[1], "r");
    if (fileIn == NULL) {
        printf("Couldn't open %s.\n", argv[1]);
        return 2;
    }
    
    FILE* fileOut = fopen(argv[2], "w");
    if (fileOut == NULL) {
        printf("Unable to create %s. Please try again.\n", argv[2]);
        return 3;
    }
    
    // read FILEHEADER
    BITMAPFILEHEADER bmpFileHeader;
    fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fileIn);
    
    // read INFOHEADER
    BITMAPINFOHEADER bmpInfoHeader;
    fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fileIn);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bmpFileHeader.bfType != 0x4d42 || bmpFileHeader.bfOffBits != 54 || bmpInfoHeader.biSize != 40 || 
        bmpInfoHeader.biBitCount != 24 || bmpInfoHeader.biCompression != 0)
    {
        fclose(fileIn);
        fclose(fileOut);
        printf("Unsupported file format.\n");
        return 4;
    }
    
    // write FILEHEADER
    fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fileOut);
    
    // write INFOHEADER
    fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fileOut);
    
    // biWidth attribute of the BITMAPFILEHEADER type is meant to store
    // the number of pixels per row.
    LONG padding = (4 - ((bmpInfoHeader.biWidth * sizeof(RGBTRIPLE)) % 4)) % 4;
    
    for (LONG row = 0, biHeight = abs(bmpInfoHeader.biHeight); row < biHeight; ++row) {
        for (LONG col = 0; col < bmpInfoHeader.biWidth; ++col) {
            
            RGBTRIPLE rgbCol;
            
            fread(&rgbCol, sizeof(RGBTRIPLE), 1, fileIn);
            
            if (isPixelRed(&rgbCol)) {
                makePixelWhite(&rgbCol);
            }
            
            fwrite(&rgbCol, sizeof(RGBTRIPLE), 1, fileOut);
        }
        
        fseek(fileIn, padding, SEEK_CUR);
            
        for (LONG k = 0; k < padding; ++k) {
            fputc(0x00, fileOut);
        }
    }
    
    fclose(fileIn);
    fclose(fileOut);
    
    return 0;
}