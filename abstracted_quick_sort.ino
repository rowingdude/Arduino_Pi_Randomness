#include <Arduino.h>

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

void quickSort(int arr[], int low, int high, int size) {
  if (low < high) {
    int pi = partition(arr, low, high);
    
    Serial.print("Partition around ");
    Serial.print(arr[pi]);
    Serial.print(": ");
    printArray(arr, size);

    quickSort(arr, low, pi - 1, size);
    quickSort(arr, pi + 1, high, size);
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  }
  
  randomSeed(analogRead(0));

  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = sizeof(arr) / sizeof(arr[0]);

  Serial.println("Original array:");
  printArray(arr, n);

  Serial.println("\nSorting process:");
  quickSort(arr, 0, n - 1, n);

  Serial.println("\nSorted array:");
  printArray(arr, n);
}

void loop() {
  // Empty
}