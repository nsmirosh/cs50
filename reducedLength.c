#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int intArray[] = {1, 2, 3, 4, 5, 6, 7};
float factor;
float getModifiedLengthFactor(int originalWidth) {

	return originalWidth / originalWidth * factor;

}

int getModifiedSize(int original) {
	return (int) original * factor;
}

int main(int argc, char* argv[])
{
	factor = 2.4;
	float modifiedFactor = getModifiedLengthFactor(5);
	int newSize = (int) 5 * factor;
	int resultArray[newSize];

	float factorCounter = 0;
	int linesWritten = 0;
	for (int i = 0; i < 5; i++) {
		factorCounter += modifiedFactor;

		int amountOfLinesToWrite = (int) factorCounter - linesWritten;
		while (amountOfLinesToWrite > 0) {
			resultArray[linesWritten] = i;
			amountOfLinesToWrite--;
			linesWritten++;
		}

	}


	for (int i = 0; i < newSize; i++) {
		printf("resultArray[i] = %i\n", resultArray[i]);

	}



	/*	float f = 5.9;
		printf ("float to int = %i", (int) f);*/
}