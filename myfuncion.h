#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>
#include <time.h>
using namespace std;
#define ll long long
template <class T>
void HoanVi(T &a, T &b);
void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateReverseData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);
void GenerateData(int a[], int n, int dataType);
int* readInput(string filename, int &size);
void writeOutput(string filename, int* arr, int size);
void counting_sort(int* arr, int n, ll& comparisons);
void Merge(int* arr, int l, int k, int r, ll &comparisons);
void merge_sort(int* arr, int l , int r, ll &comparisons);
int FindMaxNumberOfDigits(int *a, int n, ll &comparisons );
void Distribution(int * a, int n, int exp, ll &comparisons);
void radix_sort(int * a, int n, ll &comparisons );
void bubbleSort(int *a, int n, long long& comparisons);
void shakerSort(int *a, int n, long long& comparisons);
void selectionSort(int *a, int n, long long& comparisons);
void insertionSort(int *a, int n, long long& comparisons);
void heapConstruct(int *a, int n, long long& comparisons);
void heapSort(int *a, int n, long long& comparisons);
void shellSort(int *a, int n, long long& comparisons);
int binarySearch(int *a, int first, int item, int last, long long& comparisons);
void binaryInsertionSort(int *a, int n, long long& comparisons);
void countingSort(int *a, int n, long long& comparisons);
void flashSort(int *a, int n, long long& comparisons);
void quickSort(int *a, int l, int r, long long& comparisons);
void command1(int argc, char *argv[]);
void command2(int argc, char *argv[]);
void command3(int argc, char *argv[]);
void command4(int argc, char *argv[]);
void command5(int argc, char *argv[]);
void menu(int argc, char* argv[]);