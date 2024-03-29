#include "syscall.h"

int int_to_string(int number, char buffer[]) {
    int isNegative = 0;
    int numberSize = 0;
    int temp = number;
    int i, k;
    if(number == 0){
        buffer[0] = '0';
        return 1;
    }
    if(number < 0){
        isNegative = 1;
        number = number * (-1);
    }
    while(temp > 0){
        numberSize++;
        temp = temp / 10;
    }
    temp = number;
	if (isNegative) {
		buffer[0] = '-';
		numberSize = numberSize + 1;
	}
	for (i = numberSize - 1; i >= 0; i--) {
		if (isNegative && i == 0) break;
		k = temp % 10;
		buffer[i] = k + 48;
		temp = temp / 10;
	}
	buffer[numberSize] = 0;
    return numberSize;
}
void swap_int(int* p1, int* p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    int j;
    for (j = low; j <= high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap_int(&arr[i], &arr[j]);
        }
    }
    swap_int(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    int n, i, buffer_size, id;
    int array[200];
    char buffer[10];
    char fileName[] = "quicksort.txt";
    
    PrintString("Nhap n: ");
    n = ReadInt();
    
    PrintString("Xin hay nhap chuoi so nguyen:\n");
    for(i = 0; i < n; i++) {
        array[i] = ReadInt();
    }

    quickSort(array, 0, n - 1);

    if (CreateFile(fileName) == 0) {
        PrintString("File ");
        PrintString(fileName);
        PrintString(" created successfully!\n");
    }
    
    id = Open(fileName, 0);
    
    for(i = 0; i < n; i++) {
        buffer_size = int_to_string(array[i], buffer);
        
        buffer[buffer_size++] = ' ';
        buffer[buffer_size] = '0';
        
        Write(buffer, buffer_size, id);
    }
    
    Close(id);
    Halt();
}




