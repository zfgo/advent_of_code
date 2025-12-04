#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    long long max = 0;
    long long current;
    string tmp;

    cin >> tmp;

    // cout << tmp << '\n';

    while (true) {
        cin >> tmp;
        // current += tmp;

        if (tmp != "\n") {
            long long tmpll;
            tmpll = stoll(tmp);
            current += tmpll;
        }
        else {
            if (current > max) {
                max = current;
                cout << max << '\n';
            }
            current = 0;
        }
    }

    return 0;
}