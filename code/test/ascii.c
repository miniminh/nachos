#include "syscall.h"

int main() {
    
    
    char buffer[1000];
    int count;
    int i;
    int tmp;
    int id;
    
    char space = ' ';
    char breakline = '\n';
    char fileName[] = "ascii.txt";

    if (CreateFile(fileName) == 0) {
        PrintString("File ");
        PrintString(fileName);
        PrintString(" created successfully!\n");
    }


    
    
    id = Open(fileName, 0);
    count = 0;
    for (i = 32; i <= 126; i++) {
        tmp = i;
        while (tmp > 0) {
            buffer[count++] = (tmp % 10) + '0';
            tmp = tmp / 10;
        }
        if (i >= 100) {
            tmp = buffer[count - 1];
            buffer[count - 1] = buffer[count - 3];
            buffer[count - 3] = tmp;
        }
        else {
            tmp = buffer[count - 1];
            buffer[count - 1] = buffer[count - 2];
            buffer[count - 2] = tmp;
        }
        buffer[count++] = space;
        buffer[count++] = i;
        buffer[count++] = breakline;
        
    }
    PrintString(buffer);
    Write(buffer, count, id);
    Close(id);
}


