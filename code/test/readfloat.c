#include "syscall.h"

int main() {
    float* f;
    PrintString("Nhap vao mot so thap phan: ");
    f = ReadFloat();
    PrintFloat(f);
    PrintChar('\n');
}

