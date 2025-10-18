#include <iostream>
#include <string>
#include <chrono>

using namespace std;

int main() {
    string inputPassword;
    cout << "Enter password (1-4 lowercase letters): ";
    cin >> inputPassword;

    // as we will only deal with lowercase alphabets for now
    for(char c: inputPassword) {
        if(c < 'a' || c > 'z') {
            cerr << "Password must contain only lowercase letters a-z." << endl;
            return 1;
        }
    }

    if(inputPassword.size() < 1 || inputPassword.size() > 4) {
        cerr << "Password length must be between 1 and 4." << endl;
        return 1;
    }

    const string letters = "abcdefghijklmnopqrstuvwxyz";
    long long attempts = 0;

    auto t0 = chrono::high_resolution_clock::now();

    for(char a: letters) {
        ++attempts;
        string s = string(1, a); 
        
        if(s == inputPassword) {
            auto t1 = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = t1 - t0;
            cout << "Found: " << s << " after " << attempts << " attempts" << endl;
            cout << "Time taken: " << diff.count() << " seconds" << endl;
            return 0;
        }
    }

    // length = 2
    for(char a: letters) for(char b: letters) {
        ++attempts;
        string s = string(1, a) + string(1, b);
        if(s == inputPassword) {
            auto t1 = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = t1 - t0;
            cout << "Found: " << s << " after " << attempts << " attempts" << endl;
            cout << "Time taken: " << diff.count() << " seconds" << endl;
            return 0;
        }
    }

    // length = 3
    for(char a: letters) for(char b: letters) for(char c: letters) {
        ++attempts;
        string s = string(1, a) + string(1, b) + string(1, c);
        if(s == inputPassword) {
            auto t1 = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = t1 - t0;
            cout << "Found: " << s << " after " << attempts << " attempts" << endl;
            cout << "Time taken: " << diff.count() << " seconds" << endl;
            return 0;
        }
    }

    // length = 4
    for(char a: letters) for(char b: letters) for(char c: letters) for(char d: letters) {
        ++attempts;
        string s = string(1, a) + string(1, b) + string(1, c) + string(1, d);
        if(s == inputPassword) {
            auto t1 = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = t1 - t0;
            cout << "Found: " << s << " after " << attempts << " attempts" << endl;
            cout << "Time taken: " << diff.count() << " seconds" << endl;
            return 0;
        }
    }

    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = t1 - t0;
    cout << "Password not found (exhausted 1-4 letter space). Attempts: " << attempts << endl;
    cout << "Time taken: " << diff.count() << " seconds" << endl;
    return 0;
}
