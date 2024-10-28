
/*
Matthew Winter
CSC 275
Assignment File IO
October 27 2024

Overview
    Persisting data is an essential skill in Computer Science. Using C++ you build a C++ version of the Google Home device to remember things for you.

Objectives
    Demonstrate how to read the contents of a text file using C++.
    Demonstrate how to search the data in a file (Optional).
    Demonstrate how to create a new file using C++.
    Demonstrate how to write to a file using C++.
    Demonstrate how to write the contents from a file to the display.
    Demonstrate how to write the contents from the display to a file.

Expectations
    Watch these videos as a guide to building your own google home.
    Your google home does not have to speak or listen, it only needs to use text Input and Output via a console window.
    Your google home should be able to remember something you tell it to by typing it in.
    Your google home should be able to recall something for you on the display from a file you had told it to remember.
    Your google home should be able to recall everything you have told and display this at once.
    Your google home should have a personality, either funny, or serious, or sci-fi themed, etc.
    Your google home should have another name instead of Google Home, make this clever!
    Your google home should have a good user experience.
    The only skills your google home needs are to remember and recall things for you.


Submission Deliverables
    Submit your source code files.
    Submit  a video of your program in action.  Show all functionality.


*/
#include <iostream> // Basic input and output
#include <fstream> // File handling for reading and writing
#include <string> // String handling
#include <ctime> // Date and time for timestamps
#include <cstdlib> // Random number generation

using namespace std; // Use standard namespace

// Function to get current time as a string
string getTimestamp() {
    time_t now = time(0); // Get the current time
    tm timeInfo; // Create a struct to hold time details
    localtime_s(&timeInfo, &now); // Fill timeInfo with current local time
    char timestamp[20]; // Array to hold the formatted timestamp
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeInfo); // Format timestamp as a string
    return string(timestamp); // Return the formatted timestamp
}

// Function to log sensor data
void logSensorData(const string& sensorName, float value) {
    ofstream file("sensor_data.csv", ios::app); // Open file in append mode (add to the end)
    if (file.is_open()) { // Check if file is open
        file << getTimestamp() << "," << sensorName << "," << value << endl; // Write data to file
        file.close(); // Close the file
        cout << "DataLogger: Sensor data logged.\n"; // Success message
    }
    else {
        cout << "DataLogger: Error opening the file.\n"; // Error if file can't be opened
    }
}

// Function to display all data from the file
void displayAllData() {
    ifstream file("sensor_data.csv"); // Open file in read mode
    if (file.is_open()) { // Check if file is open
        string line; // String to hold each line from the file
        cout << "DataLogger: Displaying all sensor data:\n"; // Header
        while (getline(file, line)) { // Read each line
            cout << line << endl; // Print each line
        }
        file.close(); // Close the file
    }
    else {
        cout << "DataLogger: Error accessing the file.\n"; // Error if file can't be opened
    }
}

// Function to clear all data from the file
void clearData() {
    ofstream file("sensor_data.csv", ios::trunc); // Open file in truncation mode (erase contents)
    if (file.is_open()) { // Check if file is open
        file.close(); // Close file to complete clearing
        cout << "DataLogger: All data has been cleared.\n"; // Confirm clear
    }
    else {
        cout << "DataLogger: Error clearing the file.\n"; // Error if file can't be opened
    }
}

// Function to get user's menu choice with basic error handling
int getUserChoice() {
    int choice; // Variable to hold user choice
    cout << "Enter your choice (number): "; // Ask user for input
    cin >> choice; // Try to read the user's choice
    if (cin.fail()) { // Check if input was invalid (not a number)
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); // Ignore any extra characters in the input
        cout << "Invalid input. Please enter a number.\n"; // Error message
        return -1; // Return an invalid choice
    }
    cin.ignore(1000, '\n'); // Clear extra characters for valid input
    return choice; // Return user's choice
}

// Main program
int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator
    cout << "Welcome to DataLogger: Your Embedded Configuration Assistant\n"; // Welcome message

    while (true) { // Main loop
        // Display menu options
        cout << "\nOptions:\n";
        cout << "1. Log simulated sensor data\n";
        cout << "2. Display all sensor data\n";
        cout << "3. Clear all data\n";
        cout << "4. Exit\n";

        int choice = getUserChoice(); // Get user's menu choice

        // Check the user's choice and call the right function
        if (choice == 1) {
            cout << "Enter sensor name: "; // Ask for sensor name
            string sensorName; // Variable for sensor name
            getline(cin, sensorName); // Get full sensor name line

            if (sensorName.empty()) { // Check if the input was empty
                cout << "Error: Sensor name cannot be empty.\n"; // Error for empty name
            }
            else {
                float value = static_cast<float>(rand() % 1000) / 10.0f; // Generate random value
                logSensorData(sensorName, value); // Call function to log data
            }
        }
        else if (choice == 2) {
            displayAllData(); // Call function to display data
        }
        else if (choice == 3) {
            clearData(); // Call function to clear data
        }
        else if (choice == 4) {
            cout << "DataLogger: Exiting. Goodbye!\n"; // Exit message
            break; // Break loop to exit program
        }
        else {
            cout << "Invalid option. Please try again.\n"; // Error for invalid choice
        }
    }

    return 0; // Return 0 to indicate successful termination
}

