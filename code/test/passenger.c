#include "syscall.h"
#include "copyright.h"

void main()
{
	// Khai bao
	int f_Success; // Bien co dung de kiem tra thanh cong
	SpaceId si_passenger, si_voinuoc;	// Bien id cho file
	char c_readFile;	// Bien ki tu luu ki tu doc tu file
	int flag_VN;		// Bien co de nhay den tien trinh scanner
	int flag_MAIN;		// Bien co de nhay den tien trinh main
	int lengthFile;		// Luu do dai file
	int i_File;		// Luu con tro file
	//-----------------------------------------------------------
	Signal("m_vn");	

	while(1)
	{
		lengthFile = 0;

		Wait("passenger");
		

		// Tao file result.txt de ghi voi nao su dung
		f_Success = CreateFile("result.txt");
		if(f_Success == -1)
		{
			Signal("main"); // tro ve tien trinh chinh
			return;
		}

		// Mo file passenger.txt len de doc
		si_passenger = Open("passenger.txt", 1);
		if(si_passenger == -1)
		{
			Signal("main"); // tro ve tien trinh chinh
			return;
		}
		
		lengthFile = Seek(-1, si_passenger);
		Seek(0, si_passenger);
		i_File = 0;
	
		// Tao file scanner.txt
		f_Success = CreateFile("scanner.txt");
		if(f_Success == -1)
		{
			Close(si_passenger);
			Signal("main"); // tro ve tien trinh chinh
			return;
		}
		

		// Mo file scanner.txt de ghi tung dung tich nuoc cua passenger
		si_voinuoc = Open("scanner.txt", 0);
		if(si_voinuoc == -1)
		{
			Close(si_passenger);
			Signal("main"); // tro ve tien trinh chinh
			return;
		}
		
		// Ghi dung tich vao file scanner.txt tu file passenger.txt
		while(i_File < lengthFile)
		{
			flag_VN = 0;
			Read(&c_readFile, 1, si_passenger);
			if(c_readFile != ' ')
			{
				Write(&c_readFile, 1, si_voinuoc);
			}
			else
			{
				flag_VN = 1;
			}
			if(i_File == lengthFile - 1)
			{
				Write("*", 1, si_voinuoc);
				flag_VN = 1;
			}
			
				
			if(flag_VN == 1)
			{
				Close(si_voinuoc);
				Signal("scanner");
				// Dung chuong trinh passenger lai de scanner thuc thi
				Wait("passenger");
				
				// Tao file scanner.txt
				f_Success = CreateFile("scanner.txt");
				if(f_Success == -1)
				{
					Close(si_passenger);
					Signal("main"); // tro ve tien trinh chinh
					return;
				}
		

				// Mo file scanner.txt de ghi tung dung tich nuoc cua passenger
				si_voinuoc = Open("scanner.txt", 0);
				if(si_voinuoc == -1)
				{
					Close(si_passenger);
					Signal("main"); // tro ve tien trinh chinh
					return;
				}
				
			}
			i_File++;			
							
		}				
		// Ket thuc tien trinh passenger va scanner quay lai ham SvVn
		Signal("main");			
	}
	// Quay lai ham Svvn	
}
