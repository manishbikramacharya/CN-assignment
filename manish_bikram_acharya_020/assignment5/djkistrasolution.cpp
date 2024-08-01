#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to count the number of senior citizens
int countSeniorCitizens(const vector<string>& details) {
    int seniorCount = 0; // Initialize the count of senior citizens to 0

    // Loop through each detail string
    for (const auto& detail : details) {
        // Extract the age part from the string (characters at index 11 and 12)
        string ageStr = detail.substr(11, 2);
        // Convert the extracted substring to an integer
        int age = stoi(ageStr);

        // Check if the age is strictly more than 60
        if (age > 60) {
            seniorCount++; // Increment the senior count
        }
    }

    return seniorCount; // Return the total count of senior citizens
}

int main() {
    // Example list of passenger details
    vector<string> details = {
        "0123456789M60123", // Age is 60 (not a senior citizen)
        "0123456789F61123", // Age is 61 (senior citizen)
        "0123456789M59123"  // Age is 59 (not a senior citizen)
        
    };

    // Call the function to count senior citizens and store the result
    int result = countSeniorCitizens(details);

    // Print the result
    cout << "Number of senior citizens: " << result << endl;

    return 0; 
}
