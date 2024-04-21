#include "syscall.h"
#include "copyright.h"

void main()
{
	// Khai bao
	int f_Success;				   // Bien co dung de kiem tra thanh cong
	SpaceId si_scanner, si_result; // Bien id cho file
	char buffer;			   // Bien ki tu luu ki tu doc tu file
	int s1, s2, s3;				   // scanner 1, scanner 2
	int v;						   // Dung tich nuoc cua sinh vien
	int flag_done_result;		   // Bien co luu dau hieu doc xong file result

	//-----------------------------------------------------------

	s1 = s2 = s3 = 0;
	while (1)
	{
		Down("m_vn");

		// Mo file result.txt de ghi scanner nao su dung
		si_result = Open("result.txt", 0);
		if (si_result == -1)
		{ //?
			Up("passenger");
			return;
		}

		while (1)
		{
			Down("scanner");
			buffer = 0;
			// Mo file scanner.txt de doc so luong hanh ly
			si_scanner = Open("scanner.txt", 1);
			if (si_scanner == -1)
			{
				Close(si_result);
				Up("passenger");

				return;
			}

			v = 0;
			flag_done_result = 0;

			while (1)
			{
				if (Read(&buffer, 1, si_scanner) == -2)
				{
					Close(si_scanner);
					break;
				}
				if (buffer != '*')
				{
					v = v * 10 + (buffer - 48);
				}
				else
				{
					flag_done_result = 1;
					Close(si_scanner);
					break;
				}
			}

			if (v != 0)
			{
				// Dung scanner 1
				if (s1 <= s2)
				{
					s1 += v;
					Write("1", 1, si_result);
				}
				else // Dung scanner 2
				{
					if (s2 <= s3)
					{
						s2 += v;
						Write("2", 1, si_result);
					}
					else // Dung scanner 2
					{
						s3 += v;
						Write("3", 1, si_result);
					}
				}
			}

			if (flag_done_result == 1)
			{
				s1 = s2 = s3 = 0;
				Close(si_result);
				Up("passenger");
				break;
			}

			Up("passenger");
		}
	}
}
