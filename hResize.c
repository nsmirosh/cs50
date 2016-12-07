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

int factor;
FILE* inptr;
FILE* outptr;

int main(int argc, char* argv[])
{

    void setUpInfoHeader(BITMAPINFOHEADER * originalIH, BITMAPINFOHEADER * outputIF, int *originalPadding, int *outputPadding);
    void writeBMP(BITMAPINFOHEADER * bi, int originalPadding, int outputPadding);
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file
    inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    outptr = fopen(outfile, "w");
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
    BITMAPINFOHEADER *bi = malloc(sizeof(BITMAPINFOHEADER));
    fread(bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi ->biSize != 40 ||
            bi ->biBitCount != 24 || bi ->biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        free(bi);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    rewind(inptr);
    BITMAPFILEHEADER outputFileHeader;
    fread(&outputFileHeader, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER *outputInfoHeader = malloc(sizeof(BITMAPINFOHEADER));
    fread(outputInfoHeader, sizeof(BITMAPINFOHEADER), 1, inptr);

    int originalPadding;
    int outputPadding;

    setUpInfoHeader(bi, outputInfoHeader, &originalPadding, &outputPadding);

    fseek(outptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), SEEK_SET);

    writeBMP(bi, originalPadding, outputPadding);

    outputFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + outputInfoHeader -> biSizeImage;
    rewind(outptr);

    fwrite(&outputFileHeader, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(outputInfoHeader, sizeof(BITMAPINFOHEADER), 1, outptr);


    free(outputInfoHeader);
    free(bi);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

void setUpInfoHeader(BITMAPINFOHEADER *originalIH, BITMAPINFOHEADER *outputIF, int *originalPadding, int *outputPadding) {

    outputIF->biHeight = originalIH -> biHeight * factor;
    outputIF->biWidth = originalIH -> biWidth * factor;

    // // determine padding for scanlines
    *originalPadding =  (4 - (originalIH -> biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    *outputPadding =  (4 - (outputIF -> biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    outputIF ->biSizeImage = (outputIF -> biWidth * sizeof(RGBTRIPLE) + *outputPadding) * abs(outputIF ->biHeight);
}

void writeBMP(BITMAPINFOHEADER *bi, int originalPadding, int outputPadding) {
    // iterate over infile's scanlines
    void writeHorizontally(int originalWidth, int outputPadding);
    for (int i = 0, biHeight = abs(bi -> biHeight); i < biHeight; i++)
    {
        writeHorizontally(bi -> biWidth, outputPadding);

        for (int n = 1; n < factor; n++) {
            fseek(inptr, (-(bi -> biWidth * sizeof(RGBTRIPLE)) - originalPadding), SEEK_CUR);
            writeHorizontally(bi -> biWidth, outputPadding);
            fseek(inptr, originalPadding, SEEK_CUR);
        }
    }
}


void writeHorizontally(int originalWidth, int outputPadding) {
    for (int j = 0; j < originalWidth; j++)
    {
        RGBTRIPLE triple;
        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
        for (int n = 0; n < factor; n++) {
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
    }

    for (int k = 0; k < outputPadding; k++)
    {
        fputc(0x00, outptr);
    }
}

