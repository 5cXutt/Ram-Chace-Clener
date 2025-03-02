#include <iostream>
#include <vector>
#include <windows.h>

#define BLOCK_SIZE (100 * 1024 * 1024) // 100 MB per blocco

int main() {
    std::cout << "=====================================\n";
    std::cout << "   RAM Cache Cleaner - Windows (C++)\n";
    std::cout << "=====================================\n";

    std::vector<void*> memoryBlocks;

    std::cout << "[+] Occupazione della RAM in corso...\n";

    while (true) {
        void* block = VirtualAlloc(NULL, BLOCK_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        if (!block) {
            std::cerr << "[-] Memoria esaurita! Stop all'allocazione.\n";
            break;
        }

        memset(block, rand() % 256, BLOCK_SIZE);
        memoryBlocks.push_back(block);

        std::cout << "[+] Allocati altri 100 MB. Totale: " << (memoryBlocks.size() * 100) << " MB\n";
        Sleep(50); 
    }

    std::cout << "[+] Attendere qualche secondo per stabilizzare il sistema...\n";
    Sleep(5000); 

    std::cout << "[+] Rilascio della memoria...\n";
    for (void* block : memoryBlocks) {
        VirtualFree(block, 0, MEM_RELEASE);
    }

    std::cout << "[+] Cache della RAM pulita con successo!\n";
    return 0;
}
