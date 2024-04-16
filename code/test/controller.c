#include "syscall.h"

#define NUM_SCANNER 3
#define BUFFER_LEN 1

int main() {
    int file_input, file_passenger;
    char buffer[BUFFER_LEN];
    int scanners[NUM_SCANNER];
    int i;
    int n;
    int tmp;
    int last_customer;
    int passenger;

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

    PrintString("Number of considering time: ");
    PrintInt(n);
    PrintString("\n");

    //Tạo file kết quả
    if (CreateFile("output.txt")) {
        PrintString("Cannot create file output.txt\n");
        return 1;
    }

    //Tạo file giá trị trung gian để đẩy vào máy scan
    if (CreateFile("scan.txt")) {
        PrintString("Cannot create file scan.txt\n");
        return 1;
    }

    //Tạo file giá trị trung gian để lưu trữ số lượng hành lý của khách
    if (CreateFile("passenger.txt")) {
        PrintString("Cannot create file passenger.txt\n");
        return 1;
    }

    //Tạo semaphore cho máy scan thứ 1
    tmp = CreateSemaphore("scan1", 0);
    if (tmp == -1) {
        PrintString("Create Semaphore for scan1 failed\n");
        return 1;
    }
    //Tạo semaphore cho máy scan thứ 2
    tmp = CreateSemaphore("scan2", 0);
    if (tmp == -1) {
        PrintString("Create Semaphore for scan2 failed\n");
        return 1;
    }
    //Tạo semaphore cho máy scan thứ 3
    tmp = CreateSemaphore("scan3", 0);
    if (tmp == -1) {
        PrintString("Create Semaphore for scan3 failed\n");
        return 1;
    }
    //Tạo semaphore cho hành khách
    tmp = CreateSemaphore("passenger", 0);
    if (tmp == -1) {
        PrintString("Create Semaphore for passenger failed\n");
        return 1;
    }
    //Tạo semaphore cho hành khách
    tmp = CreateSemaphore("main", 0);
    if (tmp == -1) {
        PrintString("Create Semaphore for main failed\n");
        return 1;
    }

    for (i = 0; i < NUM_SCANNER; i++) {
        scanners[i] = Exec("scanner");
        if (scanners[i] == -1) {
            PrintString("Create scanner failed\n");
            return 1;
        }
    }
    passenger = Exec("passenger");
    if (passenger == 1) {
        PrintString("Create passenger failed\n");
        return 1;
    }

    file_passenger = Open("passenger.txt", 2);

    //Xử lý n thời điểm
    //Ứng với mỗi thời điểm, đẩy số lượng hành lý cho khách hàng ở file passenger.txt
    while (n--) {
        last_customer = 0;
        while (!last_customer) {
            while (1) {
                Read(buffer, 1, file_input);
                if (buffer[0] == ' ') break;
                if (buffer[0] == '\n') {
                    last_customer = 1;
                    break;
                }
                Write(buffer, 1, file_passenger);
            }

        }
        
        //Chờ xử lý xong ở mỗi thời điểm mới đẩy hành lý tiếp
        Wait("main");
    }
    
    Close(file_input);

    return 0;
}