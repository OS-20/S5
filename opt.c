#include <stdio.h>

int main() {
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f];
    for (int i = 0; i < f; i++)
        frames[i] = -1; 

    int faults = 0;

    printf("\nPage\tFrames\n-----------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        // Check if page already exists
        for (int j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            faults++;
            int replace_index = -1;

            // Check for empty frame
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    replace_index = j;
                    break;
                }
            }

            // If no empty frame, find optimal replacement
            if (replace_index == -1) {
                int farthest = -1, index = -1;
                for (int j = 0; j < f; j++) {
                    int next_use = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            next_use = k;
                            break;
                        }
                    }
                    if (next_use == -1) { // page not used again
                        index = j;
                        break;
                    }
                    if (next_use > farthest) {
                        farthest = next_use;
                        index = j;
                    }
                }
                replace_index = index;
            }

            frames[replace_index] = page;
        }

        // Display current frames
        printf("%d\t", page);
        for (int j = 0; j < f; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("-----------------\nTotal Page Faults = %d\n", faults);
    return 0;
}
