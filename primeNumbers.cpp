#include <iostream>
using namespace std;

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    // Check odd numbers up to square root of num
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int count = 0;
    int number = 2;
    
    cout << "The first 100 prime numbers are:\n";
    
    while (count < 100) {
        if (isPrime(number)) {
            cout << number << " ";
            count++;
            
            // Formatting: new line after every 10 numbers
            if (count % 10 == 0) {
                cout << "\n";
            }
        }
        number++;
    }
    
    cout << "\nTotal prime numbers found: " << count << endl;
    return 0;
}