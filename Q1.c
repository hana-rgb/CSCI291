#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Function to check if a string is a valid float
int is_float(const char *str) {
    char *endptr;
    strtod(str, &endptr);  // Try to convert string to a float
    return *endptr == '\0'; // If we reached the end of the string, it's a valid float
}

void process_file(const char *input_file, const char *valid_file, const char *invalid_file) {
    FILE *source = fopen(input_file, "r");
    FILE *valid = fopen(valid_file, "w");
    FILE *invalid = fopen(invalid_file, "w");
    if (!source || !valid || !invalid) {
        printf("Error opening files.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[100];
    int valid_count = 0, invalid_count = 0;

    // Read the file word by word
    while (fscanf(source, "%s", buffer) != EOF) {
        if (strcmp(buffer, "END") == 0) break;  // Stop processing if the word "END" is encountered
        
        // Check if the token is a valid float
        if (is_float(buffer)) {
            fprintf(valid, "%s\n", buffer);  // Write valid float to valid file
            valid_count++;
        } else {
            fprintf(invalid, "%s\n", buffer);  // Write invalid value to invalid file
            invalid_count++;
        }
    }

    fclose(source);
    fclose(valid);
    fclose(invalid);

    printf("Valid floats: %d\n", valid_count);
    printf("Invalid floats: %d\n", invalid_count);
}

int main() {
    process_file("floatCheck.txt", "valid_floats.txt", "invalid_floats.txt");
    return 0;
}
