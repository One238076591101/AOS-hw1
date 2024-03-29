#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 生成介於min和max之間的隨機數
int generateRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}

// 生成和儲存Random參考字串
void generateAndStoreRandomReferenceString(int numReferences) {
    FILE *file = fopen("random_reference_string.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int totalReferences = 0;
    while (totalReferences < numReferences) {
        int length = generateRandom(1, 20);
        int start = generateRandom(1, 1000 - length + 1);

        for (int j = 0; j < length; j++) {
            fprintf(file, "%d ", start + j);
            totalReferences++;
            if (totalReferences >= numReferences) {
                break;
            }
        }
    }

    fclose(file);
}

// 生成和儲存Locality參考字串
void generateAndStoreLocalityReferenceString(int numReferences, int numCalls) {
    FILE *file = fopen("locality_reference_string.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int totalReferences = 0;
    while (totalReferences < numReferences) {
        int length = generateRandom(33, 50);
        int start = generateRandom(1, 1000 - length + 1);

        for (int j = 0; j < numCalls; j++) {
            int callStart = generateRandom(start, start + length - 1);
            fprintf(file, "%d ", callStart);
            totalReferences++;
            if (totalReferences >= numReferences) {
                break;
            }
        }
    }
    fclose(file);
}


void generateAndStoreCustomReferenceString(int numReferences) {
    FILE *file = fopen("custom_reference_string2.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    srand(time(NULL));

    int totalReferences = 0;

    while (totalReferences < numReferences) {
        int page;
        
        // 在前半部的引用中引用一組隨機頁面
        if (totalReferences < numReferences / 2) {
            page = 1 + rand() % 1000; // 隨機頁面範圍為1到1000
        }
         // 在後半部的引用中引用一組隨機頁面
        else {
            page = (totalReferences - numReferences / 2) % 1000 + 1;
        }

        fprintf(file, "%d ", page);
        totalReferences++;
    }

    fclose(file);
}




int main() {
    srand(time(NULL)); // 初始化隨機數生成器

    int numReferences = 200000; // 記憶體參考的數量
    int numCalls = 50; // "Locality"情況下的呼叫數量


    // 生成和存儲參考字串
    // generateAndStoreRandomReferenceString(numReferences);
    // generateAndStoreLocalityReferenceString(numReferences, numCalls);
    // generateAndStoreCustomReferenceString(numReferences);
    // generateAndStoreLFUReferenceString(numReferences);

    return 0;
}
