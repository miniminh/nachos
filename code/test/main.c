#include "syscall.h"
#include "copyright.h"

#define MAX_LENGTH 32


int main()
{
	// KHAI BAO
	int f_Success; // Bien dung de kiem tra thanh cong
	SpaceId si_input, si_output, si_passenger, si_result;	// Bien id cho file
	int n;	// Luu so luong thoi diem xet
	char buffer;	// Bien ki tu luu ki tu doc tu file

	//-----------------------------------------------------------
	
	// Khoi tao 4 Semaphore de quan ly 3 tien trinh
	f_Success = CreateSemaphore("main",0);
	if(f_Success == -1)
		return 1;
	f_Success = CreateSemaphore("passenger", 0);
	if(f_Success == -1)
		return 1;
	f_Success = CreateSemaphore("scanner", 0);
	if(f_Success == -1)
		return 1;
	f_Success = CreateSemaphore("m_vn", 0);
	if(f_Success == -1)
		return 1;
	
	// Tao file output.txt de ghi ket qua cuoi cung	
	f_Success = CreateFile("output.txt");
	if(f_Success == -1)
		return 1;
	
	// Mo file input.txt chi de doc
	si_input = Open("input.txt", 1);
	if(si_input == -1)
		return 1;
	
	// Mo file output.txt de doc va ghi
	si_output = Open("output.txt", 0);
	if(si_output == -1)
	{
		Close(si_input);
		return 1;
	}

	// Doc so luong thoi diem xet o file input.txt
	n = 0;
	while(1)
	{
		Read(&buffer, 1, si_input);
		if(buffer != '\n')
		{
			if(buffer >= '0' && buffer <= '9')
				n = n * 10 + (buffer - 48);
		}
		else
			break;
	}

	PrintString("So luong thoi diem can xu ly: ");
	PrintInt(n);
	PrintString("\n");

	// Goi thuc thi tien trinh passenger.c
	f_Success = Exec("passenger");
	if(f_Success == -1)
	{
		PrintString("Exec khong thanh cong passenger\n");

		Close(si_input);
		Close(si_output);
		return 1;
	}

	PrintString("Exec thanh cong passenger\n");

	// Goi thuc thi tien trinh scanner.c
	f_Success = Exec("scanner");
	if(f_Success == -1)
	{
		PrintString("Exec khong thanh cong scanner\n");

		Close(si_input);
		Close(si_output);
		return 1;
	}

	PrintString("Exec thanh cong scanner\n");

	// Thuc hien xu ly khi nao het thoi diem xet thi thoi
	while(n--)
	{
		PrintString("So luong thoi diem con lai: ");
		PrintInt(n);
		PrintString("\n");

		// Tao file passenger.txt
		f_Success = CreateFile("passenger.txt");
		if(f_Success == -1)
		{
			Close(si_input);
			Close(si_output);
			return 1;
		}
		
		// Mo file passenger.txt de ghi tung dong passenger tu file input.txt
		si_passenger = Open("passenger.txt", 0);
		if(si_passenger == -1)
		{
			Close(si_input);
			Close(si_output);
			return 1;
		}
		while(1)
		{
			if(Read(&buffer, 1, si_input) < 1)
			{
				break;
			}
			if(buffer != '\n')
			{
				Write(&buffer, 1, si_passenger);				
			}
			else
				break;
						
		}

		Close(si_passenger);

		PrintString("Xu ly xong file passenger\n");
		
		// Goi tien trinh passenger hoat dong
		Up("passenger");

		PrintString("Passenger xu ly thoai\n");

		Down("main");	
		
		// Thuc hien doc file tu result va ghi vao ket qua o output.txt
		si_result = Open("result.txt", 1);
		if(si_result == -1)
		{
			Close(si_input);
			Close(si_output);
			return 1;
		}

		// Doc cac hanh ly vao output.txt		
		si_passenger = Open("passenger.txt", 0);

		PrintString("Ghi vao file output\n");

		while(1)
		{
			PrintString("Hanh khach: ");
			while (1){
				if (Read(&buffer,1,si_passenger) < 1){
					Write(" ", 1, si_output);
					break;
				}
				if (buffer < '0' || buffer > '9'){
					PrintChar('\n');
					Write(" ", 1, si_output);
					break;
				}
				PrintChar(buffer);
				Write(&buffer, 1, si_output);
			}
			if(Read(&buffer, 1, si_result)  < 1)
			{
				Write("\r\n", 2, si_output);
				Close(si_result);
				Up("m_vn");
				break;
			}
			PrintString("May quet: ");
			Write(&buffer, 1, si_output);
			PrintChar(buffer);
			PrintChar('\n');
			Write("     ", 5, si_output);	
		}
		
	}

	PrintString("Done!\n");
	
	Close(si_passenger);
	Close(si_input);
	Close(si_output);
	return 0;	
	
}

