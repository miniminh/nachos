#ifndef STABLE_H
#define STABLE_H

#include "bitmap.h"
#include "sem.h"
#define MAX_SEMAPHORE 10

class STable {
   private:
    Bitmap* bm;                         //Quản lý slot trống
    Sem* semTab[MAX_SEMAPHORE];         //Quản lý tối đa 110 đối tượng sem

   public:
    STable();                           //Khởi tạo đối tượng Sem để quản lý 10 Semaphore.
    ~STable();                          //Hủy
    int Create(char* name, int init);   //Kiểm tra Semaphore 'name' chưa tồn tại thì tạo
    int Wait(char* name);               //Nếu tồn tại Semaphore 'name' thì gọi this->P() để 
    //thực thi, ngược lại thì báo lỗi.
    int Signal(char* name);             //Nếu tồn tại Semaphore 'name' thì gọi this->V() để
    //thực thi, ngược lại thì báo lỗi.
    int FindFreeSlot();                 //Tìm slot trống
};

#endif