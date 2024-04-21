#include "syscall.h"
#include "copyright.h"

void main()
{
	// Khai bao
	int f_Success; // Bien dung de kiem tra thanh cong
	SpaceId si_passenger, si_scanner;	// Bien id cho file
	char buffer;	// Bien ki tu luu ki tu doc tu file
	int flag_Scanner;		// Bien co de nhay den tien trinh scanner
	int flag_MAIN;		// Bien co de nhay den tien trinh main
	int lengthFile;		// Luu do dai file
	int i_File;		// Luu con tro file
	//-----------------------------------------------------------
	Up("m_vn");	

	while(1)
	{
		lengthFile = 0;

		Down("passenger");
		

		// Tao file result.txt de ghi scanner nao su dung
		f_Success = CreateFile("result.txt");
		if(f_Success == -1)
		{
			Up("main"); // tro ve tien trinh chinh
			return;
		}

		// Mo file passenger.txt len de doc
		si_passenger = Open("passenger.txt", 1);
		if(si_passenger == -1)
		{
			Up("main"); // tro ve tien trinh chinh
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
			Up("main"); // tro ve tien trinh chinh
			return;
		}
		

		// Mo file scanner.txt de ghi tung so luong hanh ly cua passenger
		si_scanner = Open("scanner.txt", 0);
		if(si_scanner == -1)
		{
			Close(si_passenger);
			Up("main"); // tro ve tien trinh chinh
			return;
		}
		
		// Ghi so luong hanh ly vao file scanner.txt tu file passenger.txt
		while(i_File < lengthFile)
		{
			flag_Scanner = 0;
			Read(&buffer, 1, si_passenger);
			if(buffer != ' ')
			{
				Write(&buffer, 1, si_scanner);
			}
			else
			{
				flag_Scanner = 1;
			}
			if(i_File == lengthFile - 1)
			{
				Write("*", 1, si_scanner);
				flag_Scanner = 1;
			}
			
				
			if(flag_Scanner == 1)
			{
				Close(si_scanner);
				Up("scanner");
				// Dung chuong trinh passenger lai de scanner thuc thi
				Down("passenger");
				
				// Tao file scanner.txt
				f_Success = CreateFile("scanner.txt");
				if(f_Success == -1)
				{
					Close(si_passenger);
					Up("main"); // tro ve tien trinh chinh
					return;
				}
		

				// Mo file scanner.txt de ghi tung so luong hanh ly cua passenger
				si_scanner = Open("scanner.txt", 0);
				if(si_scanner == -1)
				{
					Close(si_passenger);
					Up("main"); // tro ve tien trinh chinh
					return;
				}
				
			}
			i_File++;			
							
		}				
		// Ket thuc tien trinh passenger va scanner quay lai main
		Up("main");			
	}
	// Quay lai main	
}
