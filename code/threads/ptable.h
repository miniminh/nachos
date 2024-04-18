#ifndef PTABLE_H
#define PTABLE_H

#include "bitmap.h"
#include "pcb.h"

#define MAX_PROCESS 10

class PTable {
   private:
    Bitmap* bm;                         //đánh dấu các vị trí đã được sử dụng trong pcb
    PCB* pcb[MAX_PROCESS];              
    int psize;              
    Semaphore* bmsem;                   //Dùng để ngăn chặn trường hợp nạp 2 tiến trình cùng lúc            

   public:
   //khởi tạo size đối tượng PCB để lưu size process. Gán giá trị ban đầu là null
    PTable(int size);
    ~PTable();                          //Hủy
    int ExecUpdate(char* name);         //Xử lí SC_Exec
    int ExitUpdate(int ec);             //Xử lí SC_Exit
    int JoinUpdate(int id);             //Xử lí SC_Join
    int GetFreeSlot();                  //Tìm free slot để lưu thông tin cho tiến trình mới
    bool IsExist(int pid);              //Kiểm tra tồn tại processID này không
    void Remove(int pid);               //Khi tiến trình kết thúc, delete processID ra khỏi 
    //mảng quản lý nó     
    char* GetFileName(int id);          //Trả về tên tiến trình
};

#endif