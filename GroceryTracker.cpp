//============================================================================
// Name        : GroceryTracker.cpp
// Author      : John St Hilaire
// Version     : 1.0
// Project     : Chada Grocery Tracking System
// Description : Grocery tracker class implimentations for tracking system
//============================================================================

#include "GroceryTracker.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <windows.h>  // Include Windows.h for accessing the Windows API for console commands
#include <iomanip>    // Include iomanip for output formatting

// Constructor of the GroceryTracker class
GroceryTracker::GroceryTracker() {
    // Read items from the input file and populate the frequency map
    readItemsFromFile("CS210_Project_Three_Input_File.txt");
    // Write the initial frequencies to the backup file
    writeFrequenciesToFile("frequency.dat");
}

// Reads item frequencies from a file and stores them in a map
void GroceryTracker::readItemsFromFile(const std::string& filename) {
    std::ifstream file(filename); // Input file stream
    // Check if the file can be opened
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string item; // Variable to store each item read from the file
    // Read items and update their frequencies
    while (file >> item) {
        itemFrequencies[item]++;
    }
    file.close(); // Close the file stream
}

// Displays the frequency of a specific item
void GroceryTracker::displaySpecificItemFrequency(const std::string& item) const {

    std::cout << "\n" << std::endl; // Padding before frequency

    // Search for the item in the frequency map
    auto it = itemFrequencies.find(item);
    // If found, print the item and its frequency
    if (it != itemFrequencies.end()) {
        std::cout << item << ": " << it->second << std::endl;
    }
    else { // If not found, inform the user
        std::cout << "Item not found." << std::endl;
    }
}

// Displays all item frequencies in a list
void GroceryTracker::displayAllFrequencies() const {
    std::cout << "\n" << std::endl; // Padding before frequencies

    // Iterate through the map and print each item's frequency
    for (const auto& pair : itemFrequencies) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

// Displays a histogram of item frequencies with a heat map color scheme
void GroceryTracker::displayHistogram() const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Handle to the console

    // Determine the longest item name for formatting
    size_t longestNameLength = 0;
    for (const auto& pair : itemFrequencies) {
        if (pair.first.length() > longestNameLength) {
            longestNameLength = pair.first.length();
        }
    }

    // Find the maximum frequency for scaling the heat map
    int maxFrequency = 0;
    for (const auto& pair : itemFrequencies) {
        if (pair.second > maxFrequency) {
            maxFrequency = pair.second;
        }
    }

    std::cout << "\n" << std::endl; // Padding before histogram

    // Display each item's frequency with color coding representing the heat map
    for (const auto& pair : itemFrequencies) {
        double ratio = pair.second / (double)maxFrequency;

        // Assign a color code based on the frequency
        int colorCode;
        if (ratio < 0.2) {
            colorCode = 1; // Blue for the lowest frequencies
        }
        else if (ratio < 0.4) {
            colorCode = 3; // Cyan for lower frequencies
        }
        else if (ratio < 0.6) {
            colorCode = 6; // Yellow for medium frequencies
        }
        else if (ratio < 0.8) {
            colorCode = 12; // Light red (orange) for higher frequencies
        }
        else {
            colorCode = 4; // Dark red for the highest frequencies
        }

        SetConsoleTextAttribute(hConsole, colorCode); // Apply the color setting
        // Output the item name, padded for alignment, followed by its histogram
        std::cout << std::left << std::setw(longestNameLength) << pair.first << " : ";
        for (int i = 0; i < pair.second; ++i) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }

    SetConsoleTextAttribute(hConsole, 7); // Reset the console to default color
}

// Writes the item frequencies to a backup file
void GroceryTracker::writeFrequenciesToFile(const std::string& filename) const {
    std::ofstream file(filename); // Output file stream
    // Check if the file can be opened
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    // Write each item and its frequency to the file
    for (const auto& pair : itemFrequencies) {
        file << pair.first << " " << pair.second << std::endl;
    }
    file.close(); // Close the file stream
}
