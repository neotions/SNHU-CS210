//============================================================================
// Name        : GroceryTracker.H
// Author      : John St Hilaire
// Version     : 1.0
// Project     : Chada Grocery Tracking System
// Description : header file for GroceryTracker class
//============================================================================

#pragma once
#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <string>
#include <map>

// Declaration of the GroceryTracker class
class GroceryTracker {
private:
    std::map<std::string, int> itemFrequencies; // Map to store item frequencies

public:
    GroceryTracker(); // Constructor declaration

    // Member function declarations
    void readItemsFromFile(const std::string& filename);
    void displaySpecificItemFrequency(const std::string& item) const;
    void displayAllFrequencies() const;
    void displayHistogram() const;
    void writeFrequenciesToFile(const std::string& filename) const;
};

#endif // GROCERY_TRACKER_H
