#ifndef SEM_H
#define SEM_H

class Semaphore;

class Sem {
   private:
    Semaphore* sem;             //Tạo semaphore để quản lý
    char name[50];

   public:
    Sem(char* na, int i);       //Khởi tạo đối tượng
    ~Sem();                     //Hủy

    void wait();                //Thực hiện thao tác chờ

    void signal();              //Thực hiện thao tác giải phóng Semaphore

    char* GetName();            //Trả về tên của Semaphore
};

#endif