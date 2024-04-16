#include "syscall.h"

#define BUFFER_LEN 1

int main() {
    int file_input;
    char buffer[BUFFER_LEN];
    
    file_input = Open("passenger.txt", 0);
    if (file_input == -1) {
        PrintString("Cannot open file passenger.txt\n");
        return 1;
    }
    return 0;
}