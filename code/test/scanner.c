#include "syscall.h"
#include "copyright.h"

void main()
{
	// Khai bao
	int f_Success;				   // Bien co dung de kiem tra thanh cong
	SpaceId si_voinuoc, si_result; // Bien id cho file
	char c_readFile;			   // Bien ki tu luu ki tu doc tu file
	int v1, v2, v3;				   // Voi 1, voi 2
	int v;						   // Dung tich nuoc cua sinh vien
	int flag_done_result;		   // Bien co luu dau hieu doc xong file result

	//-----------------------------------------------------------

	v1 = v2 = v3 = 0;
	// Xu ly voi nuoc
	// WHILE(11111111111111111111111111111111111111)
	while (1)
	{
		Down("m_vn");

		// Mo file result.txt de ghi voi nao su dung
		si_result = Open("result.txt", 0);
		if (si_result == -1)
		{ //?
			Up("passenger");
			return;
		}
		// WHILE(2222222222222222222222222222222222222222)
		while (1)
		{
			Down("scanner");
			c_readFile = 0;
			// Mo file voi nuoc .txt de doc dung tich
			si_voinuoc = Open("scanner.txt", 1);
			if (si_voinuoc == -1)
			{
				//?
				Close(si_result);
				Up("passenger");

				return;
			}

			v = 0;
			flag_done_result = 0;
			// WHILE(3333333333333333333333333333333333333333333333)
			while (1)
			{
				if (Read(&c_readFile, 1, si_voinuoc) == -2)
				{
					Close(si_voinuoc);
					break;
				}
				if (c_readFile != '*')
				{
					v = v * 10 + (c_readFile - 48);
				}
				else
				{
					flag_done_result = 1;
					Close(si_voinuoc);
					break;
				}
			}
			// WHILE(3333333333333333333333333333333333333333333333)
			if (v != 0)
			{
				// Dung voi 1
				if (v1 <= v2)
				{
					v1 += v;
					Write("1", 1, si_result);
				}
				else // Dung voi 2
				{
					if (v2 <= v3)
					{
						v2 += v;
						Write("2", 1, si_result);
					}
					else
					{
						v3 += v;
						Write("3", 1, si_result);
					}
				}
			}

			if (flag_done_result == 1)
			{
				v1 = v2 = 0;
				v3 = 0;
				Close(si_result);
				Up("passenger");
				break;
			}

			Up("passenger");
		}
		// WHILE(2222222222222222222222222222222222222222)
	}
	// WHILE(11111111111111111111111111111111111111)
}
