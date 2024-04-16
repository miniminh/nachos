#include "syscall.h"

#define NUM_SCANNER 3
#define BUFFER_LEN 2

int main() {
    int file_input;
    char buffer[BUFFER_LEN];
    int n;

    //Đọc yêu cầu từ đề bài
    file_input = Open("input.txt", 1);
    if (file_input == -1) {
        PrintString("Cannot open file input.txt\n");
        return 1;
    }

    //Đọc vào n thời điểm cần xét
    n = 0;
    while (1) {
        Read(buffer, 1, file_input);
        if (buffer[0] == '\n') break;

        n = n * 10 + buffer[0] - '0';
    }
    Close(file_input);

    PrintString("So luong thoi diem can xet: ");
    PrintInt(n);
    PrintString("\n");

    return 0;
}