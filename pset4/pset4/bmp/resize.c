#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "bmp.h"

LONG main(LONG argc, char** argv) {
    
    if (argc != 4) {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    LONG multiplier = (LONG)strtol(argv[1], NULL, 10);
    
    if (argv[1] != 0 && multiplier == 0) {
        printf("The first argument should be the multiplier greater than zero of how much you want to resize.\n");
        printf("Usage: ./resize n infile outfile\n");
        return 2;
    }
    const char* fileInName  = argv[2];
    const char* fileOutName = argv[3];

    FILE* fileIn = fopen(fileInName, "r");
    if (fileIn == NULL) {
        printf("Unable to open %s.\n", fileInName);
        return 3;
    }
    
    FILE* fileOut = fopen(fileOutName, "w+");
    if (fileOut == NULL) {
        printf("Unable to create %s.\n", fileOutName);
        return 4;
    }
    
    // read the bmp file header
    BITMAPFILEHEADER bmpFileHeader;
    fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fileIn);
    
    // read the bmp info header
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
    
    // copy the bmp info header and mutate the required variables
    // since we are only working with primitive types on the stack,
    // we won't have to concern ourselves for reference issues that might
    // otherwise arise
    BITMAPINFOHEADER bmpInfoHeaderBig = bmpInfoHeader;
    bmpInfoHeaderBig.biWidth     *= multiplier;
    bmpInfoHeaderBig.biHeight    *= multiplier;
    
    LONG bigPadding  = (4 - ((bmpInfoHeaderBig.biWidth * sizeof(RGBTRIPLE)) % 4)) % 4;
    
    bmpInfoHeaderBig.biSizeImage =  bmpInfoHeaderBig.biWidth * 
                                    abs(bmpInfoHeaderBig.biHeight) * 
                                    bmpInfoHeaderBig.biBitCount / 8 + 
                                    bigPadding * 
                                    abs(bmpInfoHeaderBig.biHeight);
    
    
    // copy the bmp file header and mutate the required variables
    // since we are only working with primitive types on the stack,
    // we won't have to concern ourselves for reference issues that might
    // otherwise arise 
    BITMAPFILEHEADER bmpFileHeaderBig = bmpFileHeader;
    bmpFileHeaderBig.bfSize =   bmpInfoHeaderBig.biSizeImage +
                                54;
    
    fwrite(&bmpFileHeaderBig, sizeof(BITMAPFILEHEADER), 1, fileOut);
    fwrite(&bmpInfoHeaderBig, sizeof(BITMAPINFOHEADER), 1, fileOut);
    
    LONG origPadding = (4 - ((bmpInfoHeader.biWidth * sizeof(RGBTRIPLE)) % 4)) % 4;
    
    RGBTRIPLE rgb;
    
    size_t bufferSize = sizeof(BYTE) * ((bigPadding + sizeof(RGBTRIPLE) * bmpInfoHeaderBig.biWidth));
    BYTE* buffer = malloc(bufferSize);
    
    if (buffer == NULL) {
        printf("Internal error has occured.\n");
        return 5;
    }
    
    for (LONG row = 0, rowCount = abs(bmpInfoHeader.biHeight); row < rowCount; ++row) 
    {
        size_t bufferOffset = 0;
        
        for (LONG col = 0; col < bmpInfoHeader.biWidth; ++col) 
        {
        
            fread(&rgb, sizeof(RGBTRIPLE), 1, fileIn);
            
            for (LONG m = 0; m < multiplier; ++m) {
                memcpy(buffer + bufferOffset, &rgb, sizeof(RGBTRIPLE));
                bufferOffset += sizeof(RGBTRIPLE);
            }
            
        }
        
        // add big padding here
        for (LONG bigPad = 0; bigPad < bigPadding; ++bigPad) {
            *(buffer + bufferOffset) = 0x00;
            bufferOffset += sizeof(BYTE);
        }
        
        for (LONG m = 0; m < multiplier; ++m) {
            fwrite(buffer, bufferSize, 1, fileOut);
        }

        // jump over orig padding
        fseek(fileIn, origPadding, SEEK_CUR);
    }
    
    free(buffer);

    fclose(fileIn);
    fclose(fileOut);
    
    return 0;
}