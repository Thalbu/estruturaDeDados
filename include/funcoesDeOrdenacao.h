// funcoesDeOrdenacao.h
#ifndef FUNCOES_DE_ORDENACAO_H
#define FUNCOES_DE_ORDENACAO_H

// radixSort
// bucketSort
// shellSort
// countingSort
// quickSort
// mergeSort
// bubbleSort
// insertionSort
// selectionSort

void bubbleSort(int arr[], int n);
void measureExecutionTime(int arr[], int n, void (*sortFunc)(int[], int));
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void quickSort(int arr[], int low, int high);
void shellSort(int arr[], int n);
void bucketSort(int arr[], int n);
void radixSort(int arr[], int n);

#endif // FUNCOES_DE_ORDENACAO_H
