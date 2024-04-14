#include "syscall.h"

int main() {
    char fileName[] = "mota.txt";
    int pos = 0, id;
    char* buffer;
    int x;
    while ((id = Open(fileName, 0)) != -1) {
        Seek(pos, id);
        x = Read(buffer, 1, id);
        if (x != 1) break;
        pos = pos + 1;
        PrintString(buffer);
        buffer = "";
        Close(id);
    }
    
}
