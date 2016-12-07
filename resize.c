/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    printf("bi.biWidth = %i \n", bi.biWidth);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    
    // BITMAPINFOHEADER* outputInfoHeader = malloc(sizeof(BITMAPINFOHEADER));
    // if (outputInfoHeader == NULL) {
    //     fclose(inptr);
    //     printf("no more memory");
    //     return 6;
    // }
    
    
    rewind(inptr);
    BITMAPFILEHEADER outputFileHeader;
    fread(&outputFileHeader, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    BITMAPINFOHEADER outputInfoHeader;
    fread(&outputInfoHeader, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    
    outputInfoHeader.biHeight = bi.biHeight * factor;
    outputInfoHeader.biWidth = bi.biWidth * factor;


    // // determine padding for scanlines
    int originalPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("originalPadding = %i bytes \n", originalPadding);

    int outputPadding =  (4 - (outputInfoHeader.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("outputPadding = %i bytes \n", outputPadding);
    
    outputInfoHeader.biSizeImage = (outputInfoHeader.biWidth * sizeof(RGBTRIPLE) + outputPadding) * abs(outputInfoHeader.biHeight);

    fseek(outptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), SEEK_SET);
    printf("ftell(outptr) %lu \n", ftell(outptr));
    

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        printf("in file position %lu \n", ftell(inptr));

        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            for (int n = 0; n < factor; n++) {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        
        fseek(inptr, originalPadding, SEEK_CUR);
        printf("in file position after padding = %lu \n", ftell(inptr));

         // then add it back (to demonstrate how)
        for (int k = 0; k < outputPadding; k++)
        {
            fputc(0x00, outptr);
        }
        printf("out file position after padding = %lu \n", ftell(outptr));
        printf("bi.biWidth * sizeof(RGBTRIPLE) * 2 + 54 + outputPadding = %lu  \n", bi.biWidth * sizeof(RGBTRIPLE) * 2 + 54 + outputPadding);

        // assert(ftell(outptr) == (bi.biWidth * sizeof(RGBTRIPLE) * 2 + 54 + outputPadding));
        
         for (int n = 1; n < factor; n++) {
                fseek(inptr, (-(bi.biWidth * sizeof(RGBTRIPLE)) - originalPadding), SEEK_CUR);

                printf("inner loop in file position %lu \n", ftell(inptr));

                for (int j = 0; j < bi.biWidth; j++)
                {

                    RGBTRIPLE triple;

                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // fwrite(&triple, sizeof(RGBTRIPLE), factor, outptr);
                    for (int n = 0; n < factor; n++) {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
            
                for (int k = 0; k < outputPadding; k++)
                {
                  fputc(0x00, outptr);
                }
                fseek(inptr, originalPadding, SEEK_CUR);
                  

                printf("inner loop in file position %lu \n", ftell(inptr));
            }
    }
    
    
  

    outputFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + outputInfoHeader.biSizeImage;
    
    
    printf("outer position before first rewind %lu \n", ftell(outptr));

    rewind(outptr);
    printf("rewind(outptr) %lu \n", ftell(outptr));
    
    fwrite(&outputFileHeader, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    printf("Info header position to write %lu \n", ftell(outptr));


    fwrite(&outputInfoHeader, sizeof(BITMAPINFOHEADER), 1, outptr);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
