#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定義page table結構
typedef struct {
    int page_number;
    int reference_bits; 
    unsigned char arb_register; // 8位移位暫存器
} PageTableEntry;

// 初始化page table
PageTableEntry* initializePageTable(int num_frames) {
    PageTableEntry* page_table = (PageTableEntry*)malloc(sizeof(PageTableEntry) * num_frames);
    for (int i = 0; i < num_frames; i++) {
        page_table[i].page_number = -1; // page_number初始化為-1表示memory frame為空閒
        page_table[i].reference_bits = 0; // reference_bits初始化為0表示page還沒有被訪問過
        page_table[i].arb_register = 0; // 初始化移位寄存器為0
    }
    return page_table;
}

// 產生隨機的DirtyBits，使用 reference_string 作為測試字串
void generateRandomDirtyBits(int num_references, int reference_string[], int dirty_bits[]) {
    srand(time(NULL));
    for (int i = 0; i < num_references; i++) {
        int page = reference_string[i];
        if (rand() % 10 == 0) { // 以10%的機率設定DirtyBits
            
            dirty_bits[page] = 1;
        }
        else{
            dirty_bits[page] = 0;
        }
    }
}

// 重置reference_bits和page number
void resetReferenceBits(PageTableEntry* page_table, int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        page_table[i].page_number = -1; // page_number初始化為-1表示memory frame為空閒
        page_table[i].reference_bits = 0;
    }
}


// FIFO algorithm
int fifo(PageTableEntry* page_table, int num_frames, int reference_string[], int num_references,int dirty_bits[]) {
    int page_faults = 0;
    int interrupts = 0;
    int disk_writes = 0;
    int oldest_index = 0;

    for (int i = 0; i < num_references; i++) {
        int page = reference_string[i];
        int page_found = 0;

        // 檢查page是否已在記憶體中
        for (int j = 0; j < num_frames; j++) {
            if (page_table[j].page_number == page) {
                page_found = 1;
                break;
            }
        }

        if (!page_found) {
            page_faults++;

            // 找到最老的page並替換
            page_table[oldest_index].page_number = page;
            oldest_index = (oldest_index + 1) % num_frames;

            // 檢查page是否有dirty bits並更新interrupts和disk_writes
            if (dirty_bits[page_table[oldest_index].page_number] == 1) {
                interrupts++;
                disk_writes++;
            }
        }
    }

    printf("FIFO Page Faults: %-10d Interrupts: %-10d Disk Writes: %-10d\n", page_faults, interrupts, disk_writes);
    return page_faults;
}

// ARB algorithm (8-bit information)
int arb(PageTableEntry* page_table, int num_frames, int reference_string[], int num_references,int dirty_bits[]) {
    int page_faults = 0;
    int interrupts = 0;
    int disk_writes = 0;

    for (int i = 0; i < num_references; i++) {
        int page = reference_string[i];
        int page_found = 0;

        // 檢查page是否已在記憶體中
        for (int j = 0; j < num_frames; j++) {
            if (page_table[j].page_number == page) {
                page_found = 1;
                // 设置参考位
                page_table[j].reference_bits = 1;

                // 中斷發生，1並將參考位的值每個位元向右移動一個位置，並將最高位元設為1
                page_table[j].arb_register = (page_table[j].arb_register >> 1) | 0x80;
                interrupts++;

                break;
            }
        }

        if (!page_found) {
            page_faults++;

           // 找出具有最小參考位元的page（移位暫存器最小）
            int victim_index = 0;
            unsigned char min_arb = page_table[0].arb_register;
            for (int j = 1; j < num_frames; j++) {
                if (page_table[j].arb_register < min_arb) {
                    victim_index = j;
                    min_arb = page_table[j].arb_register;
                }
            }

            // 取代page並更新參考位元和移位暫存器
            page_table[victim_index].page_number = page;
            page_table[victim_index].reference_bits = 1;
            page_table[victim_index].arb_register = 0x80; // 新頁面的移位暫存器最高位元為1


           // 如果新page曾經被使用，根據參考位的值更新移位暫存器
            if (page_table[victim_index].reference_bits == 1) {
                page_table[victim_index].arb_register |= 0x80;
            }
            // 檢查page是否有dirty bits並更新interrupts和disk_writes
            if (dirty_bits[page_table[victim_index].page_number] == 1) {
                interrupts++;
                disk_writes++;
            }
        }
    }

    printf("ARB Page Faults: %-10d Interrupts: %-10d Disk Writes: %-10d\n", page_faults, interrupts, disk_writes);
    return page_faults;
}

// Enhanced Second-Chance Algorithm
int enhancedSecondChance(PageTableEntry* page_table, int num_frames, int reference_string[], int num_references,int dirty_bits[]) {
    int page_faults = 0;
    int interrupts = 0;
    int disk_writes = 0;
    int current_pass = 0; // 目前搜尋順序的類別

    for (int i = 0; i < num_references ; i++) {
        int page = reference_string[i];
        int page_found = 0;

        // 檢查page是否已在記憶體中
        for (int j = 0; j < num_frames; j++) {
            if (page_table[j].page_number == page) {
                page_found = 1;
                // 设置参考位並interrupts
                page_table[j].reference_bits = 1;
                interrupts++;
                break;
            }
        }

        if (!page_found) {
            page_faults++;

            // 依照順序規則(00 -> 01 -> 10 -> 11)找到符合條件的頁面
            int victim_index = -1;
            for (int j = 0; j < num_frames; j++) {
                if (current_pass == 0 && page_table[j].reference_bits == 0 && dirty_bits[page] == 0) {
                    victim_index = j;
                    break;
                } else if (current_pass == 1 && page_table[j].reference_bits == 0 && dirty_bits[page] == 1) {
                    victim_index = j;
                    break;
                } else if (current_pass == 2 && page_table[j].reference_bits == 1 && dirty_bits[page] == 0) {
                    victim_index = j;
                    break;
                } else if (current_pass == 3 && page_table[j].reference_bits == 1 && dirty_bits[page] == 1) {
                    victim_index = j;
                    break;
                }
            } 
            if (victim_index != -1) {
                 // 找到符合的page並替換
                page_table[victim_index].page_number = page;
                page_table[victim_index].reference_bits = 1;

                // 檢查page是否有dirty bits並更新interrupts和disk_writes
                if (dirty_bits[page_table[victim_index].page_number] == 1) {
                    interrupts++;
                    disk_writes++;
                }
            }
            current_pass = (current_pass + 1) % 4;  // 循環在0到3之間切換
        }
    }
    printf("ESC Page Faults: %-10d Interrupts: %-10d Disk Writes: %-10d\n", page_faults, interrupts, disk_writes);
    return page_faults;
}


// CustomAlgorithm：Least recently used (LRU) algorithm + Dirty Bits
int customAlgorithm(PageTableEntry* page_table, int num_frames, int reference_string[], int num_references, int dirty_bits[]) {
    int page_faults = 0;
    int interrupts = 0;
    int disk_writes = 0;

    // 記錄每個頁面的最近使用時間，初始化為0表示從未使用過
    int* page_last_used = (int*)malloc(sizeof(int) * num_frames);
    for (int i = 0; i < num_frames; i++) {
        page_last_used[i] = 0;
    }

    for (int i = 0; i < num_references; i++) {
        int page = reference_string[i];
        int page_found = 0;

        // 檢查page是否已在記憶體中
        for (int j = 0; j < num_frames; j++) {
            if (page_table[j].page_number == page) {
                page_found = 1;
                // 设置参考位
                page_table[j].reference_bits = 1;

                // 更新最近使用时间
                page_last_used[j] = i;
                break;
            }
        }

        if (!page_found) {
            page_faults++;

            // 找到最近未被使用並且Dirty Bits=0(未被修改過)的page
            int victim_index = 0;
            int oldest_time = page_last_used[0];
            for (int j = 1; j < num_frames; j++) {
                if (page_last_used[j] < oldest_time && dirty_bits[page_table[victim_index].page_number] == 0 ) {   
                    victim_index = j;
                    oldest_time = page_last_used[j];
                }
            }

            // page替換並更新最近使用時間
            page_table[victim_index].page_number = page;
            page_table[victim_index].reference_bits = 1;
            page_last_used[victim_index] = i;

            // 檢查page是否有dirty bits並更新interrupts和disk_writes
            if (dirty_bits[page_table[victim_index].page_number] == 1) {
                interrupts++;
                disk_writes++;
            }
        }
    }

    // 釋放分配記錄每個頁面的最近使用時間的記憶體
    free(page_last_used);

    printf("LRUD Page Faults: %-10d Interrupts: %-10d Disk Writes: %-10d\n", page_faults, interrupts, disk_writes);
    return page_faults;
}



int main() {

    int num_references = 200000;  //200000個測試字串
    int num_frames[] = {20, 40, 60, 80, 100};
    PageTableEntry* page_table;

    int reference_string[num_references]; 
    int dirty_bits[num_references];

    // 定義三個不同測試字串的檔案
    const char* reference_files[] = {
        "random_reference_string.txt",
        "locality_reference_string.txt",
        "custom_reference_string.txt",
        
    };

    for (int test_case = 0; test_case < 3; test_case++) {
        // 開啟目前測試字串的檔案
        FILE* file = fopen(reference_files[test_case], "r");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        printf("\nTest Case %d: %s\n", test_case + 1, reference_files[test_case]);

        for (int i = 0; i < num_references; i++) {
            if (fscanf(file, "%d", &reference_string[i]) == EOF) {
                break;
            }
        }

        fclose(file);

        // 呼叫 generateRandomDirtyBits 函數取得10%的dirty bits
        generateRandomDirtyBits(num_references, reference_string, dirty_bits);

       //依序執行四種演算法，並記錄page_faults, interrupts, disk_writes次數進行比較
        for (int i = 0; i < sizeof(num_frames) / sizeof(num_frames[0]); i++) {
            int num_frame = num_frames[i];
            page_table = initializePageTable(num_frame);

            printf("\nNumber of Frames: %d\n", num_frame);
            resetReferenceBits(page_table, num_frame);
            fifo(page_table, num_frame, reference_string, num_references, dirty_bits);

            resetReferenceBits(page_table, num_frame);
            arb(page_table, num_frame, reference_string, num_references, dirty_bits);

            resetReferenceBits(page_table, num_frame);
            enhancedSecondChance(page_table, num_frame, reference_string, num_references, dirty_bits);

            resetReferenceBits(page_table, num_frame);
            customAlgorithm(page_table, num_frame, reference_string, num_references, dirty_bits);

            free(page_table);
        
        }
    }
    return 0;
}
