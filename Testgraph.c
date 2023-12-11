#include <stdio.h>

int main() {
    FILE *dataFile = fopen("data.txt", "w");

    // Generate some sample data
    int values[] = {10, 20, 15, 30, 25};
    int numValues = sizeof(values) / sizeof(values[0]);

    // Write the data to a file
    if (dataFile != NULL) {
        for (int i = 0; i < numValues; ++i) {
            fprintf(dataFile, "%d\n", values[i]);
        }
        fclose(dataFile);
        printf("Data written to data.txt\n");
    } else {
        printf("Error opening file!\n");
        return 1;
    }

    return 0;
}
