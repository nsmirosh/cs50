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
#include <math.h>
#include <string.h>

#include "bmp.h"

float factor;
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
    factor = atof(argv[1]);
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

    outputIF->biHeight = (int) originalIH -> biHeight * factor;
    outputIF->biWidth = (int) originalIH -> biWidth * factor;

    // // determine padding for scanlines
    *originalPadding =  (4 - (originalIH -> biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    *outputPadding =  (4 - (outputIF -> biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    outputIF ->biSizeImage = (outputIF -> biWidth * sizeof(RGBTRIPLE) + *outputPadding) * abs(outputIF ->biHeight);
}

void writeBMP(BITMAPINFOHEADER *bi, int originalPadding, int outputPadding) {
    // iterate over infile's scanlines
    void writeRow(int originalWidth, int outputPadding, int* reducedArray);
    int getModifiedSize(int original);
    void fillModifiedArray (int originalSize, int reducedSize, int result[]);
    void skipRow(int originalWidth);
    void writeRowWithResultArray(int originalWidth, int outputPadding, int pixelPositionArray[], RGBTRIPLE resultArray[]);
    void writePixelRow(RGBTRIPLE tripleArray[], int size, int padding);

    int newWidth = getModifiedSize(bi -> biWidth);
    int newHeight = getModifiedSize(abs(bi -> biHeight));
    int widthPixels[newWidth];
    fillModifiedArray(bi -> biWidth, newWidth, widthPixels);

    int heightPixels[newHeight];
    fillModifiedArray(abs(bi -> biHeight), newHeight, heightPixels);
    int absHeight = abs(bi -> biHeight);
    int heightIndex = 0;


    if (factor < 1) {
        for (int i = 0;  i < absHeight; i++) {
            if (i == heightPixels[heightIndex]) {
                writeRow(bi -> biWidth, outputPadding, widthPixels);
                heightIndex++;
            }
            else {
                skipRow(bi -> biWidth);
            }
        }
    }
    else {
        for (int i = 0; i < absHeight; i++) {

            RGBTRIPLE resultArray[newWidth];
            memset(resultArray, 0, sizeof(RGBTRIPLE) * newWidth);

            writeRowWithResultArray(bi -> biWidth, outputPadding, widthPixels, resultArray);
            heightIndex++;

            while (heightPixels[heightIndex] == i) {
                writePixelRow(resultArray, newWidth, outputPadding);
                heightIndex++;
            }
            memset(resultArray, 0, sizeof(RGBTRIPLE) * newWidth);

        }
    }
}




float getModifiedLengthFactor(int originalWidth) {

    return originalWidth / originalWidth * factor;

}


void writeRow(int originalWidth, int outputPadding, int pixelPositionArray[]) {

    void readPixel();
    void writePixel();
    void putPadding();

    int i = 0;
    for (int j = 0; j < originalWidth; j++)
    {
        RGBTRIPLE triple;
        readPixel(&triple);
        if (j == *(pixelPositionArray + i)) {
            writePixel(&triple);
            i++;
        }
    }
    putPadding(outputPadding);
}




void writeRowWithResultArray(int originalWidth, int outputPadding, int pixelPositionArray[], RGBTRIPLE resultArray[]) {

    void readPixel();
    void writePixel();
    void putPadding();


    int i = 0;
    for (int j = 0; j < originalWidth; j++)
    {
        RGBTRIPLE triple;
        readPixel(&triple);
        while (j == *(pixelPositionArray + i)) {
            writePixel(&triple);
            resultArray[i] = triple;
            i++;
        }
    }
    putPadding(outputPadding);
}


void readPixel(RGBTRIPLE* triple) {
    fread(triple, sizeof(RGBTRIPLE), 1, inptr);
}

void writePixel(RGBTRIPLE* triple) {
    fwrite(triple, sizeof(RGBTRIPLE), 1, outptr);
}

void putPadding(int outputPadding) {
    for (int k = 0; k < outputPadding; k++)
    {
        fputc(0x00, outptr);
    }
}

void writePixelRow(RGBTRIPLE tripleArray[], int size, int padding) {
    fwrite(tripleArray, sizeof(RGBTRIPLE) * size, 1, outptr);
    putPadding(padding);

}


int getModifiedSize(int original) {
    return (int) original * factor;
}

void skipRow(int originalWidth) {

    for (int i = 0; i < originalWidth; i++) {
        RGBTRIPLE triple;
        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    }

}

void fillModifiedArray (int originalSize, int newSize, int result[]) {

    float factorCounter = 0;

    if (factor < 1) {
        float factorIncrement = originalSize / (originalSize * factor);
        for (int i = 0; i < newSize; i++) {
            result[i] = floor(factorCounter + 1);
            factorCounter += factorIncrement;
            // printf("result[%i] = %i\n", i, result[i]);
        }
    }
    else {
        int lastPixel = 0;
        for (int i = 0; i < originalSize; i++) {
            factorCounter += factor;
            int pixelsToWrite = (int) factorCounter - lastPixel;
            while (pixelsToWrite > 0) {
                result[lastPixel] = i;
                pixelsToWrite--;
                lastPixel++;
            }
        }


    }

}








