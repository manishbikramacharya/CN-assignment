#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string licenseKeyFormatting(string S, int K) {
    // Step 1: Remove all dashes and convert to uppercase
    string cleanString;
    for (char c : S) {
        if (c != '-') {
            cleanString += toupper(c);
        }
    }

    // Step 2: Initialize result string
    string result;
    int len = cleanString.size();
    
    // Step 3: Determine the size of the first group
    int firstGroupSize = len % K;
    
    // Step 4: Add the first group to the result
    if (firstGroupSize > 0) {
        result = cleanString.substr(0, firstGroupSize);
    }

    // Step 5: Add the remaining groups of size K
    for (int i = firstGroupSize; i < len; i += K) {
        if (!result.empty()) {
            result += '-';
        }
        result += cleanString.substr(i, K);
    }

    return result;
}

int main() {
    string S = "5F3Z-2e-9-w";
    int K = 4;

    string reformattedKey = licenseKeyFormatting(S, K);
    cout << "Reformatted License Key: " << reformattedKey << endl;

    return 0;
}
