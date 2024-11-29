#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
int readPGMText(const char *filename, int *width, int *height, int *maxVal, unsigned char **pixels);
int writePGMText(const char *filename, int width, int height, int maxVal, unsigned char *pixels);
int writePGMBinary(const char *filename, int width, int height, int maxVal, unsigned char *pixels);
void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, unsigned char *stegoPixels, int totalPixels);
void extractLSB(unsigned char *stegoPixels, unsigned char *outputPixels, int totalPixels);

int main() {
    const char *coverFile = "baboon.pgm";
    const char *secretFile = "farm.pgm";
    const char *stegoBinaryFile = "stego_image_bin.pgm";
    const char *extractedSecretFile = "extracted_secret.pgm";

    int width, height, maxVal, totalPixels;

    unsigned char *coverPixels = NULL;
    unsigned char *secretPixels = NULL;
    unsigned char *stegoPixels = NULL;
    unsigned char *outputPixels = NULL;

    // Read cover image
    if (readPGMText(coverFile, &width, &height, &maxVal, &coverPixels) != 0) {
        printf("Error reading cover image.\n");
        return EXIT_FAILURE;
    }

    // Read secret image
    if (readPGMText(secretFile, &width, &height, &maxVal, &secretPixels) != 0) {
        printf("Error reading secret image.\n");
        free(coverPixels);
        return EXIT_FAILURE;
    }

    totalPixels = width * height;

    // Allocate memory for stego and extracted secret images
    stegoPixels = (unsigned char *)malloc(totalPixels * sizeof(unsigned char));
    outputPixels = (unsigned char *)malloc(totalPixels * sizeof(unsigned char));
    if (!stegoPixels || !outputPixels) {
        printf("Memory allocation failed.\n");
        free(coverPixels);
        free(secretPixels);
        return EXIT_FAILURE;
    }

    // Embed secret image into cover image
    embedLSB(coverPixels, secretPixels, stegoPixels, totalPixels);

    // Save the stego image in binary format
    if (writePGMBinary(stegoBinaryFile, width, height, maxVal, stegoPixels) != 0) {
        printf("Error writing stego image.\n");
        free(coverPixels);
        free(secretPixels);
        free(stegoPixels);
        free(outputPixels);
        return EXIT_FAILURE;
    }

    // Extract the secret image from stego image
    extractLSB(stegoPixels, outputPixels, totalPixels);

    // Save the extracted secret image in text format
    if (writePGMText(extractedSecretFile, width, height, maxVal, outputPixels) != 0) {
        printf("Error writing extracted secret image.\n");
        free(coverPixels);
        free(secretPixels);
        free(stegoPixels);
        free(outputPixels);
        return EXIT_FAILURE;
    }

    // Free allocated memory
    free(coverPixels);
    free(secretPixels);
    free(stegoPixels);
    free(outputPixels);

    printf("Steganography processing completed successfully.\n");
    return EXIT_SUCCESS;
}

// Function to read an ASCII PGM file
int readPGMText(const char *filename, int *width, int *height, int *maxVal, unsigned char **pixels) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    char format[3];
    fscanf(file, "%2s", format);
    if (strcmp(format, "P2") != 0) {
        fclose(file);
        return -1;
    }

    fscanf(file, "%d %d %d", width, height, maxVal);

    int totalPixels = (*width) * (*height);
    *pixels = (unsigned char *)malloc(totalPixels * sizeof(unsigned char));
    if (!(*pixels)) {
        fclose(file);
        return -1;
    }

    for (int i = 0; i < totalPixels; i++) {
        int pixel;
        fscanf(file, "%d", &pixel);
        *(*pixels + i) = (unsigned char)pixel;
    }

    fclose(file);
    return 0;
}

// Function to write an ASCII PGM file
int writePGMText(const char *filename, int width, int height, int maxVal, unsigned char *pixels) {
    FILE *file = fopen(filename, "w");
    if (!file) return -1;

    fprintf(file, "P2\n%d %d\n%d\n", width, height, maxVal);
    for (int i = 0; i < width * height; i++) {
        fprintf(file, "%d\n", *(pixels + i));
    }

    fclose(file);
    return 0;
}

// Function to write a binary PGM file
int writePGMBinary(const char *filename, int width, int height, int maxVal, unsigned char *pixels) {
    FILE *file = fopen(filename, "wb");
    if (!file) return -1;

    fprintf(file, "P5\n%d %d\n%d\n", width, height, maxVal);
    fwrite(pixels, sizeof(unsigned char), width * height, file);

    fclose(file);
    return 0;
}

// Function to embed a secret image into a cover image using LSB
void embedLSB(unsigned char *coverPixels, unsigned char *secretPixels, unsigned char *stegoPixels, int totalPixels) {
    for (int i = 0; i < totalPixels; i++) {
        unsigned char coverMSB = *(coverPixels + i) & 0xF0;  // Get upper 4 bits of cover
        unsigned char secretMSB = (*(secretPixels + i) & 0xF0) >> 4; // Get upper 4 bits of secret
        *(stegoPixels + i) = coverMSB | secretMSB; // Combine into stego pixel
    }
}

// Function to extract a secret image from a stego image
void extractLSB(unsigned char *stegoPixels, unsigned char *outputPixels, int totalPixels) {
    for (int i = 0; i < totalPixels; i++) {
        unsigned char secretMSB = (*(stegoPixels + i) & 0x0F) << 4; // Extract lower 4 bits and shift
        *(outputPixels + i) = secretMSB;  // Set as extracted pixel
    }
}
