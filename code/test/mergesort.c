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
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1+1], R[n2+1];


    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];

    }


    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + ((r - l) / 2);

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


int main()
{
    int n, i, buffer_size;
    int array[99];
    char buffer[20];

    OpenFileId op;

    PrintString("Nhap n: ");
    n = ReadInt();

    PrintString("Xin hay nhap chuoi so nguyen:\n");
    for(i = 0; i < n; i++) {
        array[i] = ReadInt();
    }

    mergeSort(array, 0, n-1);

    op = Open("quicksort.txt", 0);

    for(i = 0; i < n; i++) {
        buffer_size = int_to_string(array[i], buffer);

        buffer[buffer_size++] = ' ';
        buffer[buffer_size] = '0';

        Write(buffer, buffer_size, op);
    }


    Close(op);
    Halt();
}



