#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdint>

using namespace std;

int main() {
	string inputPassword;
	cout << "Enter password to search for: ";
	cin >> inputPassword;

	ifstream fin("CommonPasswordList.txt");
	if(!fin.is_open()) {
		cerr << "Failed to open password list: CommonPasswordList.txt" << endl;
		return 1;
	}

	string line;
	long long attempts = 0;
	auto t0 = chrono::high_resolution_clock::now();

	while (getline(fin, line)) {
		++attempts;
		// Remove CR on Windows-formatted files
		if(!line.empty() && line.back() == '\r') line.pop_back();
		if (line == inputPassword) {
			auto t1 = chrono::high_resolution_clock::now();
			chrono::duration<double> diff = t1 - t0;
			cout << "Found password: '" << line << "' after " << attempts << " attempts" << endl;
			cout << "Time taken: " << diff.count() << " seconds" << endl;
			fin.close();
			return 0;
		}
	}

	auto t1 = chrono::high_resolution_clock::now();
	chrono::duration<double> diff = t1 - t0;
	cout << "Password not found after " << attempts << " attempts." << endl;
	cout << "Time taken: " << diff.count() << " seconds" << endl;
	fin.close();
	return 0;
}