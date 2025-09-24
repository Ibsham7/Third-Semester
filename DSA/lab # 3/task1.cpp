// recursion lab


#include <iostream>
using namespace std;

int factorial (int n){
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int fabioncii (int n){
    if (n <= 1) return n;
    return fabioncii(n - 1) + fabioncii(n - 2);
}


int main() {
    int num;
    cout << "Enter a positive integer: ";
    cin >> num;
    cout << "Fabioncii series of " << num << " is " << factorial(num) << endl;
    return 0;
}