#include"myfuncion.h"
// g++ a.cpp myfunction.cpp -o a.exe
//.\a.exe -a radix-sort input.txt -both
//.\a.exe -a selection-sort 50 -rand -time
//.\a.exe -a radix-sort 70000 -both     
//.\a.exe -c heap-sort merge-sort input.txt
//.\a.exe -c quick-sort merge-sort 100000 -nsorted
int main(int argc, char* argv[]) {
    menu(argc, argv);
    return 0;
}
