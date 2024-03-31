#include "syscall.h"


void Merge(float* arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
 	float* left[n1];
 	float* right[n2];
	for (i = 0; i < n1; i++)
		left[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		right[j] = arr[m + 1 + j];
    i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (FloatComp(left[i], right[j]) == -1) {
			arr[k] = left[i];
			i++;
		}
		else {
			arr[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		arr[k] = left[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = right[j];
		j++;
		k++;
	}
}
void MergeSort(float* arr[], int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;
		MergeSort(arr, l, m);
		MergeSort(arr, m + 1, r);
		Merge(arr, l, m, r);
	}
}

int
main()
{
	float* f[100];
	int n, i, id, buffer_size;
	
	char buffer[20];
    char fileName[] = "mergesort.txt";

    PrintString("Nhap n: ");
	n = ReadInt();
	
	PrintString("Xin hay nhap chuoi so thuc:\n");
	for (i = 0; i < n; ++i)
	{
		f[i] = ReadFloat();
	}
	MergeSort(f, 0, n - 1);
	if (CreateFile(fileName) == 0) {
        PrintString("File ");
        PrintString(fileName);
        PrintString(" created successfully!\n");
    }
    
    id = Open(fileName, 0);
    
    for(i = 0; i < n; i++) {
        buffer_size = FloatToString(buffer, f[i]);
        
        buffer[buffer_size++] = ' ';
        buffer[buffer_size] = '0';

        Write(buffer, buffer_size, id);
    }
    Close(id);
    Halt();
}

