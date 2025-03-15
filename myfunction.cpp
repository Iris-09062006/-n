#include"myfuncion.h"
// data generator
template <class T>
void HoanVi(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}
// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand()%n;
	}
}
// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}
// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand()%n;
		int r2 = rand()%n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}
// Hàm đọc dữ liệu từ file
int* readInput(string filename, int &size) {
    ifstream file(filename);
    if (!file) {
        exit(1);
    }
    file >> size; // Đọc số lượng phần tử
    int *arr = new int [size];
    int i = 0;
    while(file >> arr[i++]){
    }
    file.close();
    return arr;
}
// Hàm ghi kết quả ra file
void writeOutput(string filename, int* arr, int size) {
    ofstream file(filename);
    if (!file) {
        return;
    }
    file << size << "\n";
    for (int i = 0; i < size; i++) {
        file << arr[i] << " ";
    }
    file << "\n";
    file.close();
}
// Thuật toán counting sort
int cnt[1000001]{0};
void counting_sort(int* arr, int n, ll& comparisons){
    int key = INT_MIN;
    for(int i = 0; ++comparisons && i < n; i++){
        cnt[arr[i]]++;
        if(++comparisons && arr[i] > key){
            key = arr[i];
        }
    }
    int k = 0;
    for(int i = 0; ++comparisons && i <= key; i++){
        if(cnt[i]){
            for(int j = 0; ++comparisons && j < cnt[i]; j++){
                arr[k++] = i;
            }
        }
    }
    memset(cnt, 0, 1000001 * sizeof(int));
}
// thuật toán merge sort
void Merge(int* arr, int l, int k, int r, ll &comparisons) {
    int n1 = k - l + 1;
    int n2 = r - k;
    int *a = new int[n1];
    int *b = new int[n2];
    for (int i = 0; ++comparisons && i < n1; i++) {
        a[i] = arr[l + i];
    }
    for (int i = 0; ++comparisons && i < n2; i++) {
        b[i] = arr[k + 1 + i];
    }
    int i = 0, j = 0, m = l;
    while (++comparisons && i < n1 && j < n2) {
        if (++comparisons && a[i] <= b[j]) {
            arr[m++] = a[i++];
        } else {
            arr[m++] = b[j++];
        }
    }
    while (++comparisons && i < n1) {
        arr[m++] = a[i++];
    }
    while (++comparisons && j < n2) {
        arr[m++] = b[j++];
    }
    delete[] a;
    delete[] b;
}
void merge_sort(int* arr, int l, int r, ll &comparisons) {
    if (++comparisons && l < r) {
        int k = l + (r - l) / 2;
        merge_sort(arr, l, k, comparisons);
        merge_sort(arr, k + 1, r, comparisons);
        Merge(arr, l, k, r, comparisons);
    }
}
// thuật toán radix sort
// tim max;
int FindMaxNumberOfDigits(int *a, int n, ll &comparisons ){
    int Max = INT_MIN;
    for(int j = 0; ++comparisons && j < n; j++){
        if(++comparisons && a[j] > Max){
            Max = a[j];
        } 
    }
    return Max;
}
// chuyen cac gia tri vao tung bucket va chuyen ra;
void Distribution(int * a, int n, int exp, ll &comparisons){
    int * b = new int [10] {0}; // mang dem 
    long long * c = new long long [n];
    // dem cac phan tu co chu so exp vao tung bucket
    for(int j = 0; ++comparisons && j < n; j++){
        b[(a[j] / exp) % 10]++;
    }
    // mang tich luy de xac dinh duoc vi tri cua tung phan tu trong a
    for(int j = 1; ++comparisons && j < 10; j++){
        b[j] += b[j - 1];
    }
    // xac dinh vi tri cua tung phan tu trong c theo exp (mang phai duyet tu n-1 den 0 vi dam bao cho phan tu vao truoc duoc xep truoc )
    for(int j = n - 1; ++comparisons && j >= 0; j--){
        int digit = a[j] / exp % 10;
        c[b[digit] - 1] = a[j]; // gan vi tri cua phan tu trong mang a vao c theo thu tu cua digit 
        b[digit]--;
    }
    // luu lai ket qua sau khi phan loai va sap xep
    for(int j = 0; ++comparisons && j < n; j++){
        a[j] = c[j];
    }
    delete[] b;
    delete[] c;
}
void radix_sort(int * a, int n, ll &comparisons ){

    int m = FindMaxNumberOfDigits(a, n, comparisons);
    for(int exp = 1; ++comparisons && m / exp > 0; exp *= 10){
        Distribution(a, n, exp, comparisons);
    }
}
// thuật toán bubble sort
void bubbleSort(int *a, int n, long long& comparisons) {
    for (int i = n - 1; ++comparisons && i >= 0; i--) {
        bool swapped = false;
        for (int j = 0; ++comparisons && j < i; j++) {
            if (++comparisons && a[j] > a[j + 1]) {
                swapped = true;
                HoanVi(a[j], a[j + 1]);
            }
        }
        if (++comparisons && !swapped)
            return;
    }
}
// thuật toán skaker sort
void shakerSort(int *a, int n, long long& comparisons) {
    int left = 0;
    int right = n - 1;
    int k = 0;
    while (++comparisons && left <= right) {
        bool swapped = false;
        for (int j = left; ++comparisons && j < right; j++) {
            if (++comparisons && a[j] > a[j + 1]) {
                swapped = true;
                HoanVi(a[j], a[j + 1]);
                k = j;
            }
        }
        if (++comparisons && !swapped)
            return;
        right = k;
        swapped = false;
        for (int j = right; ++comparisons && j > left; j--) {
            if (++comparisons && a[j] < a[j - 1]) {
                swapped = true;
                HoanVi(a[j], a[j - 1]);
                k = j;
            }
        }
        if (++comparisons && !swapped)
            return;
        left = k;
    }
}
// thuật toán selection sort
void selectionSort(int *a, int n, long long& comparisons) {
    for (int i = 0; ++comparisons && i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; ++comparisons && j < n; j++) {
            if (++comparisons && a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
        HoanVi(a[i], a[minIndex]);
    }
}
// thuật toán insertion sort
void insertionSort(int *a, int n, long long& comparisons) {
    for (int i = 1; ++comparisons && i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (++comparisons && j >= 0) {
            if (++comparisons && a[j] > key) {
                a[j + 1] = a[j];
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
    }
}
// thuật toán heap sort 
void heapRebuild(int *a, int pos, int n, long long& comparisons) {
    while (++comparisons && 2 * pos + 1 < n) {
        int j = 2 * pos + 1;
        if (++comparisons && j < n - 1) {
            if (++comparisons && a[j] < a[j + 1])
                j++;
        }
        if (++comparisons && a[pos] >= a[j])
            return;
        HoanVi(a[pos], a[j]);
        pos = j;
    }
}
void heapConstruct(int *a, int n, long long& comparisons) {
    for (int i = (n - 1) / 2; ++comparisons && i >= 0; i--) {
        heapRebuild(a, i, n, comparisons);
    }
}
void heapSort(int *a, int n, long long& comparisons) {
    heapConstruct(a, n, comparisons);
    int r = n - 1;
    while (++comparisons && r > 0) {
        HoanVi(a[0], a[r]);
        heapRebuild(a, 0, r, comparisons);
        r--;
    }
}
// thuật toán shell sort
void shellSort(int *a, int n, long long& comparisons) {
    for (int interval = n / 2; ++comparisons && interval > 0; interval /= 2) {
        for (int i = interval; ++comparisons && i < n; i++) {
            int temp = a[i];
            int j = i;
            while (++comparisons && j >= interval) {
                if (++comparisons && a[j - interval] > temp) {
                    a[j] = a[j - interval];
                    j -= interval;
                } else {
                    break;
                }
            }
            a[j] = temp;
        }
    }
}
// thuật toán binartInsertion sort
int binarySearch(int *a, int first, int item, int last, long long& comparisons) {
    while (++comparisons && true) {
        if (++comparisons && first >= last) {
            return (++comparisons && a[first] > item) ? first : first + 1;
        }
        int mid = (first + last) / 2;
        if (++comparisons && a[mid] == item)
            return mid + 1;
        if (++comparisons && a[mid] < item)
            first = mid + 1;
        else
            last = mid - 1;
    }
    return -1;
}
void binaryInsertionSort(int *a, int n, long long& comparisons) {
    int i, loc, j, k, selected;
    for (i = 1; ++comparisons && i < n; ++i) {
        j = i - 1;
        selected = a[i];
        loc = binarySearch(a, 0, selected, j, comparisons);
        while (++comparisons && j >= loc) {
            a[j + 1] = a[j];
            j--;
        }
        a[loc] = selected;
    }
}
// thuật toán quick sort
int partition(int *a, int first, int last, long long& comparisons) {
    int pivot = a[(first + last) / 2];
    int i = first;
    int j = last;
    while (++comparisons, i <= j) {
        while (++comparisons, a[i] < pivot) {
            i++;
        }
        while (++comparisons, a[j] > pivot) {
            j--;
        }
        if (++comparisons, i <= j) {
            HoanVi(a[i], a[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quickSort(int *a, int first, int last, long long& comparisons) {
    int index = partition(a, first, last, comparisons);
    if (++comparisons, first < index - 1)
        quickSort(a, first, index - 1, comparisons);
    if (++comparisons, index < last)
        quickSort(a, index, last, comparisons);
}

// thuật toán flash sort
void flashSort(int *a, int n, long long& comparisons) {
    int minVal = a[0];
    int max = 0;
    int m = int(0.45 * n);
    int* l = new int[m];
    for (int i = 0; ++comparisons && i < m; i++) {
        l[i] = 0;
    }
    for (int i = 1; ++comparisons && i < n; i++) {
        if (++comparisons && a[i] < minVal)
            minVal = a[i];
        if (++comparisons && a[i] > a[max])
            max = i;
    }
    if (++comparisons && a[max] == minVal)
        return;
    double c1 = (double)(m - 1) / (a[max] - minVal);
    for (int i = 0; ++comparisons && i < n; i++) {
        int k = int(c1 * (a[i] - minVal));
        ++l[k];
    }
    for (int i = 1; ++comparisons && i < m; i++) {
        l[i] += l[i - 1];
    }
    HoanVi(a[max], a[0]);
    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;
    while (++comparisons && nmove < n - 1) {
        while (++comparisons && j > l[k] - 1) {
            j++;
            k = int(c1*(a[j] - minVal));
        }
        flash = a[j];
        if (++comparisons && k < 0) break;
        while (++comparisons && j != l[k]) {
            k = int(c1*(flash - minVal));
            int hold = a[t = --l[k]];
            a[t] = flash;
            flash = hold;
            ++nmove;
        }
    }
    delete[] l;
    insertionSort(a, n, comparisons);
}
//command 1
void command1(int argc, char* argv[]){
    string algorithm = argv[2]; // Tên thuật toán
    string inputFile = argv[3]; // File input
    string outputParam = argv[4]; // Tham số đầu ra
    // khới tạo các tham số
    int size = 0;
    int * data = readInput(inputFile, size);
    ll comparisons = 0;
    // giao diện 
    cout << "ALGORITHM MODE" << endl;
    cout << "Algorithm: " << algorithm << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Input size: " << size << endl;
    auto start = chrono::high_resolution_clock::now();
    //Chạy thuật toán theo lựa chọn
    if (algorithm == "radix-sort") {
        radix_sort(data, size, comparisons);
    }
    else if(algorithm == "counting-sort"){
        counting_sort(data, size, comparisons);
    }
    else if(algorithm == "merge-sort"){
        merge_sort(data, 0, size - 1, comparisons);
    }
    else if(algorithm == "selection-sort"){
        selectionSort(data, size, comparisons);
    }
    else if(algorithm == "insertion-sort"){
        insertionSort(data, size, comparisons);
    }
    else if(algorithm == "binary-insertion-sort"){
        binaryInsertionSort(data, size, comparisons);
    }
    else if(algorithm == "bubble-sort"){
        bubbleSort(data, size, comparisons);
    }
    else if(algorithm == "shaker-sort"){
        shakerSort(data, size, comparisons);
    }
    else if(algorithm == "shell-sort"){
        shellSort(data, size, comparisons);
    }
    else if(algorithm == "heap-sort"){
        heapSort(data, size, comparisons);
    }
    else if(algorithm == "flash-sort"){
        flashSort(data, size, comparisons);
    }
    else if(algorithm == "quick-sort"){
        quickSort(data, 0, size - 1, comparisons);
    }
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double, milli>(end - start).count();

    //Ghi kết quả ra file
    writeOutput("output.txt", data, size);
    
    // Xuất kết quả ra console
    if (outputParam == "-time") {
        cout << "Running time: " << duration << " ms" << endl;
    } else if (outputParam == "-comp") {
        cout << "Comparisons: " << comparisons << endl;
    } else if(outputParam == "-both"){
        cout << "Running time: " << duration << " ms" << endl;
        cout << "Comparisons: " << comparisons << endl;
    }
}
// command 2
void command2(int argc, char* argv[]) {
	string algorithm = argv[2];// ten thuat toan
	string Input_size = argv[3];// kich co cua mang
	string Input_order = argv[4];// kieu du lieu
	string Output_parameter = argv[5];// ket qua dau ra
	int size = stoi(Input_size);
	int* data = new int[size];
	long long comparisons = 0;
	
	if (Input_order == "-rand") {
		GenerateData(data, size, 0);
	}
	else if (Input_order == "-nsorted") {
		GenerateData(data, size, 3);
	}
	else if (Input_order == "-sorted") {
		GenerateData(data, size, 1);
	}
	else if (Input_order == "-rev") {
		GenerateData(data, size, 2);
	}
	else {
		cout <<"Error: unknown data type!\n";
	}
	writeOutput("input.txt", data, size);
    auto start = chrono::high_resolution_clock::now();
    //Chạy thuật toán theo lựa chọn
    if (algorithm == "radix-sort") {
        radix_sort(data, size, comparisons);
    }
    else if(algorithm == "counting-sort"){
        counting_sort(data, size, comparisons);
    }
    else if(algorithm == "merge-sort"){
        merge_sort(data, 0, size - 1, comparisons);
    }
    else if(algorithm == "selection-sort"){
        selectionSort(data, size, comparisons);
    }
    else if(algorithm == "insertion-sort"){
        insertionSort(data, size, comparisons);
    }
    else if(algorithm == "binary-insertion-sort"){
        binaryInsertionSort(data, size, comparisons);
    }
    else if(algorithm == "bubble-sort"){
        bubbleSort(data, size, comparisons);
    }
    else if(algorithm == "shaker-sort"){
        shakerSort(data, size, comparisons);
    }
    else if(algorithm == "shell-sort"){
        shellSort(data, size, comparisons);
    }
    else if(algorithm == "heap-sort"){
        heapSort(data, size, comparisons);
    }
    else if(algorithm == "flash-sort"){
        flashSort(data, size, comparisons);
    }
    else if(algorithm == "quick-sort"){
        quickSort(data, 0, size - 1, comparisons);
    }
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double, milli>(end - start).count();
	writeOutput("output.txt", data, size);
	// giao dien
	cout << "ALGORITHM MODE\n";
	cout << "Algorithm: " << algorithm<<'\n';
	cout << "Input size: " << size<<'\n';
	cout << "Input order: " << Input_order<<'\n';
	cout << "------------------------\n";
    if (Output_parameter == "-time") {
        cout << "Running time: " << duration << " ms" << endl;
    } else if (Output_parameter == "-comp") {
        cout << "Comparisons: " << comparisons << endl;
    } else if(Output_parameter == "-both"){
        cout << "Running time: " << duration << " ms" << endl;
        cout << "Comparisons: " << comparisons << endl;
    }
}
// command 3
void command3(int argc, char* argv[]){
    string algorithm = argv[2]; // Tên thuật toán
    string inputSize = argv[3]; // File input
    string outputParam = argv[4]; // Tham số đầu ra
    // khới tạo các tham số
    int size = stoi(inputSize);
    int* data = new int[size];
    GenerateData(data, size, 0); 
    writeOutput("input1.txt", data, size);
    ll comparisons = 0;
    // giao diện 
    cout << "ALGORITHM MODE" << endl;
    cout << "Algorithm: " << algorithm << endl;
    cout << "Input size: " << size << endl;
    cout << "Input order: Radomize"<< endl;
    auto start = chrono::high_resolution_clock::now();
    //Chạy thuật toán theo lựa chọn
    if (algorithm == "radix-sort") {
        radix_sort(data, size, comparisons);
    }
    else if(algorithm == "counting-sort"){
        counting_sort(data, size, comparisons);
    }
    else if(algorithm == "merge-sort"){
        merge_sort(data, 0, size - 1, comparisons);
    }
    else if(algorithm == "selection-sort"){
        selectionSort(data, size, comparisons);
    }
    else if(algorithm == "insertion-sort"){
        insertionSort(data, size, comparisons);
    }
    else if(algorithm == "binary-insertion-sort"){
        binaryInsertionSort(data, size, comparisons);
    }
    else if(algorithm == "bubble-sort"){
        bubbleSort(data, size, comparisons);
    }
    else if(algorithm == "shaker-sort"){
        shakerSort(data, size, comparisons);
    }
    else if(algorithm == "shell-sort"){
        shellSort(data, size, comparisons);
    }
    else if(algorithm == "heap-sort"){
        heapSort(data, size, comparisons);
    }
    else if(algorithm == "flash-sort"){
        flashSort(data, size, comparisons);
    }
    else if(algorithm == "quick-sort"){
        quickSort(data, 0, size - 1, comparisons);
    }
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double, milli>(end - start).count();

    // Xuất kết quả ra console
    if (outputParam == "-time") {
        cout << "Running time: " << duration << " ms" << endl;
    } else if (outputParam == "-comp") {
        cout << "Comparisons: " << comparisons << endl;
    } else if(outputParam == "-both"){
        cout << "Running time: " << duration << " ms" << endl;
        cout << "Comparisons: " << comparisons << endl;
    }
    cout << "-------------------------------------------------------" << endl;
    cout << endl;
    cout << "Input order: Nearly Sorted"<< endl;

    delete[] data;
    data = new int[size];
    GenerateData(data, size, 3); 
    writeOutput("input2.txt", data, size);
    comparisons = 0;
    auto start1 = chrono::high_resolution_clock::now();
    //Chạy thuật toán theo lựa chọn
    if (algorithm == "radix-sort") {
        radix_sort(data, size, comparisons);
    }
    else if(algorithm == "counting-sort"){
        counting_sort(data, size, comparisons);
    }
    else if(algorithm == "merge-sort"){
        merge_sort(data, 0, size - 1, comparisons);
    }
    else if(algorithm == "selection-sort"){
        selectionSort(data, size, comparisons);
    }
    else if(algorithm == "insertion-sort"){
        insertionSort(data, size, comparisons);
    }
    else if(algorithm == "binary-insertion-sort"){
        binaryInsertionSort(data, size, comparisons);
    }
    else if(algorithm == "bubble-sort"){
        bubbleSort(data, size, comparisons);
    }
    else if(algorithm == "shaker-sort"){
        shakerSort(data, size, comparisons);
    }
    else if(algorithm == "shell-sort"){
        shellSort(data, size, comparisons);
    }
    else if(algorithm == "heap-sort"){
        heapSort(data, size, comparisons);
    }
    else if(algorithm == "flash-sort"){
        flashSort(data, size, comparisons);
    }
    else if(algorithm == "quick-sort"){
        quickSort(data, 0, size - 1, comparisons);
    }
    auto end1 = chrono::high_resolution_clock::now();
    double duration1 = chrono::duration<double, milli>(end1 - start1).count();

    if (outputParam == "-time") {
        cout << "Running time: " << duration1 << " ms" << endl;
    } else if (outputParam == "-comp") {
        cout << "Comparisons: " << comparisons << endl;
    } else if(outputParam == "-both"){
        cout << "Running time: " << duration1 << " ms" << endl;
        cout << "Comparisons: " << comparisons << endl;
    }
    cout << "-------------------------------------------------------" << endl;
    cout << endl;
    cout << "Input order: Sorted"<< endl;

    delete[] data;
    data = new int[size];
    GenerateData(data, size, 1); 
    writeOutput("input3.txt", data, size);
    comparisons = 0;
    auto start2 = chrono::high_resolution_clock::now();
    //Chạy thuật toán theo lựa chọn
    if (algorithm == "radix-sort") {
        radix_sort(data, size, comparisons);
    }
    else if(algorithm == "counting-sort"){
        counting_sort(data, size, comparisons);
    }
    else if(algorithm == "merge-sort"){
        merge_sort(data, 0, size - 1, comparisons);
    }
    else if(algorithm == "selection-sort"){
        selectionSort(data, size, comparisons);
    }
    else if(algorithm == "insertion-sort"){
        insertionSort(data, size, comparisons);
    }
    else if(algorithm == "binary-insertion-sort"){
        binaryInsertionSort(data, size, comparisons);
    }
    else if(algorithm == "bubble-sort"){
        bubbleSort(data, size, comparisons);
    }
    else if(algorithm == "shaker-sort"){
        shakerSort(data, size, comparisons);
    }
    else if(algorithm == "shell-sort"){
        shellSort(data, size, comparisons);
    }
    else if(algorithm == "heap-sort"){
        heapSort(data, size, comparisons);
    }
    else if(algorithm == "flash-sort"){
        flashSort(data, size, comparisons);
    }
    else if(algorithm == "quick-sort"){
        quickSort(data, 0, size - 1, comparisons);
    }
    auto end2 = chrono::high_resolution_clock::now();
    double duration2 = chrono::duration<double, milli>(end2 - start2).count();

    if (outputParam == "-time") {
        cout << "Running time: " << duration2 << " ms" << endl;
    } else if (outputParam == "-comp") {
        cout << "Comparisons: " << comparisons << endl;
    } else if(outputParam == "-both"){
        cout << "Running time: " << duration2 << " ms" << endl;
        cout << "Comparisons: " << comparisons << endl;
    }
    cout << "-------------------------------------------------------" << endl;
    cout << endl;
    cout << "Input order: Reversed"<< endl;

    delete[] data;
    data = new int[size];
    GenerateData(data, size, 2); 
    writeOutput("input4.txt", data, size);
    comparisons = 0;
    auto start3 = chrono::high_resolution_clock::now();
    //Chạy thuật toán theo lựa chọn
    if (algorithm == "radix-sort") {
        radix_sort(data, size, comparisons);
    }
    else if(algorithm == "counting-sort"){
        counting_sort(data, size, comparisons);
    }
    else if(algorithm == "merge-sort"){
        merge_sort(data, 0, size - 1, comparisons);
    }
    else if(algorithm == "selection-sort"){
        selectionSort(data, size, comparisons);
    }
    else if(algorithm == "insertion-sort"){
        insertionSort(data, size, comparisons);
    }
    else if(algorithm == "binary-insertion-sort"){
        binaryInsertionSort(data, size, comparisons);
    }
    else if(algorithm == "bubble-sort"){
        bubbleSort(data, size, comparisons);
    }
    else if(algorithm == "shaker-sort"){
        shakerSort(data, size, comparisons);
    }
    else if(algorithm == "shell-sort"){
        shellSort(data, size, comparisons);
    }
    else if(algorithm == "heap-sort"){
        heapSort(data, size, comparisons);
    }
    else if(algorithm == "flash-sort"){
        flashSort(data, size, comparisons);
    }
    else if(algorithm == "quick-sort"){
        quickSort(data, 0, size - 1, comparisons);
    }
    auto end3 = chrono::high_resolution_clock::now();
    double duration3 = chrono::duration<double, milli>(end3 - start3).count();

    if (outputParam == "-time") {
        cout << "Running time: " << duration3 << " ms" << endl;
    } else if (outputParam == "-comp") {
        cout << "Comparisons: " << comparisons << endl;
    } else if(outputParam == "-both"){
        cout << "Running time: " << duration3 << " ms" << endl;
        cout << "Comparisons: " << comparisons << endl;
    }
}
// command 4
void command4(int argc, char *argv[])
{
    string algorithm1 = argv[2]; // Tên thuật toán 1
    string algorithm2 = argv[3]; // Tên thuật toán 2
    string inputfile = argv[4];  // File input
    int inputSize = 0;
    long long comparisions1 = 0;
    long long comparisions2 = 0;
    cout << "COMPARE MODE" << endl;
    cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << endl;
    cout << "Input file: " << inputfile << endl;
    int * data = readInput(inputfile, inputSize);
    int *a = new int[inputSize];
    cout << "Input size: " << inputSize << endl;
    cout << "-----------------" << endl;
    auto start1 = chrono::high_resolution_clock::now();
    // Run algorithm 1
    if (algorithm1 == "selection-sort")
    {
        selectionSort(a, inputSize,comparisions1);
    }
    else if (algorithm1 == "insertion-sort")
    {
        insertionSort(a, inputSize,comparisions1);
    }
    else if (algorithm1 == "bubble-sort")
    {
        bubbleSort(a, inputSize,comparisions1);
    }
    else if (algorithm1 == "quick-sort")
    {
        quickSort(a, 0, inputSize - 1,comparisions1);
    }
    else if (algorithm1 == "heap-sort")
    {
        heapSort(a, inputSize,comparisions1);
    }
    else if (algorithm1 == "merge-sort")
    {
        merge_sort(a, 0, inputSize - 1,comparisions1);
    }
    else if (algorithm1 == "radix-sort")
    {
        radix_sort(a, inputSize,comparisions1);
    }
    else if (algorithm1 == "flash-sort")
    {
        flashSort(a, inputSize,comparisions1);
    }
    else if (algorithm1 == "shell-sort")
    {
        shellSort(a, inputSize,comparisions1);
    }
    else if (algorithm1 == "counting-sort")
    {
        counting_sort(a, inputSize,comparisions1);
    }
    else if (algorithm1 == "binary-insertion-sort")
    {
        binaryInsertionSort(a, inputSize,comparisions1);
    }
    else if(algorithm1 == "shaker-sort")
    {
        shakerSort(a, inputSize,comparisions1);
    }
    else
    {
        cout << "Invalid algorithm" << endl;
        return;
    }
    auto end1 = chrono::high_resolution_clock::now();
    double duration1 = chrono::duration<double, milli>(end1 - start1).count();
    auto start2 = chrono::high_resolution_clock::now();
    if (algorithm2 == "selection-sort")
    {
        selectionSort(a, inputSize,comparisions2);
    }
    else if (algorithm2 == "insertion-sort")
    {
        insertionSort(a, inputSize,comparisions2);
    }
    else if (algorithm2 == "bubble-sort")
    {
        bubbleSort(a, inputSize,comparisions2);
    }
    else if (algorithm2 == "quick-sort")
    {
        quickSort(a, 0, inputSize - 1,comparisions2);
    }
    else if (algorithm2 == "heap-sort")
    {
        heapSort(a, inputSize,comparisions2);
    }
    else if (algorithm2 == "merge-sort")
    {
        merge_sort(a, 0, inputSize - 1,comparisions2);
    }
    else if (algorithm2 == "radix-sort")
    {
        radix_sort(a, inputSize,comparisions2);
    }
    else if (algorithm2 == "flash-sort")
    {
        flashSort(a, inputSize,comparisions2);
    }
    else if (algorithm2 == "shell-sort")
    {
        shellSort(a, inputSize,comparisions2);
    }
    else if (algorithm2 == "counting-sort")
    {
        counting_sort(a, inputSize,comparisions2);
    }
    else if (algorithm2 == "binary-insertion-sort")
    {
        binaryInsertionSort(a, inputSize,comparisions2);
    }
    else if(algorithm2 == "shaker-sort")
    {
        shakerSort(a, inputSize,comparisions2);
    }
    else
    {
        cout << "Invalid algorithm" << endl;
        return;
    }
    auto end2 = chrono::high_resolution_clock::now();
    double duration2 = chrono::duration<double, milli>(end2 - start2).count();
    cout << "Running time: " << duration1 << " | " << duration2 << endl;
    cout << "Comparisons: " << comparisions1 << " | " << comparisions2 << endl;
}
// command 5
void command5(int argc, char *argv[])
{
    string algorithm1 = argv[2]; // Tên thuật toán 1
    string algorithm2 = argv[3]; // Tên thuật toán 2
    string inputsize = argv[4];  // Kích thước dữ liệu
    string inputoder = argv[5];   // Loại dữ liệu
    long long comparisions1 = 0;
    long long comparisions2 = 0;
    int size = stoi(inputsize);
    int *a = new int[size];
    cout << "COMPARE MODE" << endl;
    cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << endl;
    cout << "Input size: " << inputsize << endl;
    cout << "Input oder: " << inputoder << endl;
    cout << "-----------------" << endl;
    if (inputoder == "-random")
    {
        GenerateRandomData(a, size);
    }
    else if (inputoder == "-sorted")
    {
        GenerateSortedData(a, size);
    }
    else if (inputoder == "-reverse")
    {
        GenerateReverseData(a, size);
    }
    else if (inputoder == "-nsorted")
    {
        GenerateNearlySortedData(a, size);
    }
    else
    {
        cout << "Invalid input oder" << endl;
        return;
    }
    writeOutput("input.txt", a, size);
    auto start = chrono::steady_clock::now();
    if (algorithm1 == "selection-sort")
    {
        selectionSort(a, size, comparisions1);
    }
    else if (algorithm1 == "insertion-sort")
    {
        insertionSort(a, size, comparisions1);
    }
    else if (algorithm1 == "bubble-sort")
    {
        bubbleSort(a, size, comparisions1);
    }
    else if (algorithm1 == "quick-sort")
    {
        quickSort(a, 0, size - 1, comparisions1);
    }
    else if (algorithm1 == "heap-sort")
    {
        heapSort(a, size, comparisions1);
    }
    else if (algorithm1 == "merge-sort")
    {
        merge_sort(a, 0, size - 1, comparisions1);
    }
    else if (algorithm1 == "radix-sort")
    {
        radix_sort(a, size, comparisions1);
    }
    else if (algorithm1 == "flash-sort")
    {
        flashSort(a, size, comparisions1);
    }
    else if (algorithm1 == "shell-sort")
    {
        shellSort(a, size, comparisions1);
    }
    else if (algorithm1 == "counting-sort")
    {
        counting_sort(a, size, comparisions1);
    }
    else if (algorithm1 == "binary-insertion-sort")
    {
        binaryInsertionSort(a, size, comparisions1);
    }
    else if (algorithm1 == "shaker-sort")
    {
        shakerSort(a, size, comparisions1);
    }
    else
    {
        cout << "Invalid algorithm" << endl;
        return;
    }
    auto end = chrono::steady_clock::now();
    double Sorttime1 = chrono::duration<double, milli>(end - start).count();
    if (algorithm2 == "selection-sort")
    {
        selectionSort(a, size, comparisions2);
    }
    else if (algorithm2 == "insertion-sort")
    {
        insertionSort(a, size, comparisions2);
    }
    else if (algorithm2 == "bubble-sort")
    {
        bubbleSort(a, size, comparisions2);
    }
    else if (algorithm2 == "quick-sort")
    {
        quickSort(a, 0, size - 1, comparisions2);
    }
    else if (algorithm2 == "heap-sort")
    {
        heapSort(a, size, comparisions2);
    }
    else if (algorithm2 == "merge-sort")
    {
        merge_sort(a, 0, size - 1, comparisions2);
    }
    else if (algorithm2 == "radix-sort")
    {
        radix_sort(a, size, comparisions2);
    }
    else if (algorithm2 == "flash-sort")
    {
        flashSort(a, size, comparisions2);
    }
    else if (algorithm2 == "shell-sort")
    {
        shellSort(a, size, comparisions2);
    }
    else if (algorithm2 == "counting-sort")
    {
        counting_sort(a, size, comparisions2);
    }
    else if (algorithm2 == "binary-insertion-sort")
    {
        binaryInsertionSort(a, size, comparisions2);
    }
    else if (algorithm2 == "shaker-sort")
    {
        shakerSort(a, size, comparisions2);
    }
    else
    {
        cout << "Invalid algorithm" << endl;
        return;
    }
    auto end2 = chrono::steady_clock::now();
    double Sorttime2 = chrono::duration<double, milli>(end2 - end).count();
    cout << "Running time: " << Sorttime1 << " | " << Sorttime2 << endl;
    cout << "Comparisons: " << comparisions1 << " | " << comparisions2 << endl;
    delete[] a;
    return;    
}
// menu
void menu(int argc, char* argv[]) {
    string check = argv[3];
    if (argc == 5 && argv[1] == string("-a") && check.find(".txt") != string::npos) {
        command1(argc, argv);
        return;
    } else if (argc == 6 && argv[1] == string("-a")) {
        command2(argc, argv);
        return;
    } else if (argc == 5 && argv[1] == string("-a")) {
        command3(argc, argv);
        return;
    } else if (argc == 5 && argv[1] == string("-c")) {
        command4(argc, argv);
        return;
    } else if (argc == 6 && argv[1] == string("-c")) {
        command5(argc, argv);
        return;
    }
}