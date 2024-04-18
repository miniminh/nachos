#ifndef PCB_H
#define PCB_H

class PCB {
   private:
    Semaphore *joinsem;                 //Semaphore cho join
    Semaphore *exitsem;                 //Semaphore cho exit
    Semaphore *multex;                  //Semaphore cho truy xuất độc quyền

    int exitcode;
    int numwait;                        //Số tiến trình đã join

    Thread *thread;
    char filename[128];

   public:
    int parentID;                       //ID của tiến trình cha
    int processID;
    PCB();
    PCB(int id);
    ~PCB();

    int Exec(char *filename, int pid);  //Tạo 1 thread mới có tên là filename và process là pid 
    int GetID();                        //Trả về ProcessID của tiến trình gọi thực hiện
    int GetNumWait();                   //Trả về số lượng tiến trình chờ
    
    void JoinWait();                    //Tiến trình cha đợi tiến trình con kết thúc
    void ExitWait();                    //Tiến trình con kết thúc
    void JoinRelease();                 //Báo cho tiến trình cha thực thi tiếp
    void ExitRelease();                 //Cho phép tiến trình con kết thúc

    void IncNumWait();                  //Tăng số tiến trình chờ
    void DecNumWait();                  //Giảm số tiến trình chờ

    void SetExitCode(int ec);           //Đặt exitcode của tiến trình
    int GetExitCode();                  //Trả về exitcode

    void SetFileName(char *fn);         //Đặt tên của tiến trình
    char *GetFileName();
};

#endif
