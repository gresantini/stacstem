// a code that assign seats on an airplane creating a seating chart that shows 
// you in which order the seats were assigned
//author: Greta Santini
// date: 9/23/2024



#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Constants for max rows and seats per row
const int MAX_ROWS = 5;
const int MAX_SEATS_PER_ROW = 4;

// Function to initialize seating chart with 0s (available seats)
void initializeSeatingChart(vector<vector<char>>& seatingChart) {
    for (int i = 0; i < MAX_ROWS; i++) {
        vector<char> row(MAX_SEATS_PER_ROW, '0');  // Initialize each seat as '0' (available)
        seatingChart.push_back(row);
    }
}

// Function to display seating chart
void displaySeatingChart(const vector<vector<char>>& seatingChart) {
    cout << "\nSeating Chart:\n";
    cout << "  A B C D\n";  // Seat labels
    for (int i = 0; i < seatingChart.size(); i++) {
        cout << i + 1 << " ";  // Row number
        for (char seat : seatingChart[i]) {
            cout << seat << " ";
        }
        cout << endl;
    }
}

// Function to assign a seat
bool assignSeat(vector<vector<char>>& seatingChart, int row, char seat, vector<pair<int, char>>& takenSeats) {
    int rowIndex = row - 1;
    int seatIndex = seat - 'A';

    if (rowIndex < 0 || rowIndex >= MAX_ROWS) {
        throw out_of_range("Invalid row number. Please enter a row between 1 and 5.");
    }

    if (seatIndex < 0 || seatIndex >= MAX_SEATS_PER_ROW) {
        throw out_of_range("Invalid seat letter. Please enter a letter between A and D.");
    }

    if (seatingChart[rowIndex][seatIndex] == 'X') {
        throw runtime_error("Seat already taken.");
    }

    seatingChart[rowIndex][seatIndex] = 'X';  // Mark seat as taken
    takenSeats.push_back(make_pair(row, seat));  // Log taken seat
    return true;
}

// Function to count available seats
int availableSeatsCount(const vector<vector<char>>& seatingChart) {
    int count = 0;
    for (const auto& row : seatingChart) {
        for (char seat : row) {
            if (seat == '0') {  // Count available seats
                count++;
            }
        }
    }
    return count;
}

// Function to show taken seats
void showTakenSeats(const vector<pair<int, char>>& takenSeats) {
    cout << "\nSeats taken (in order of assignment): ";
    for (const auto& seat : takenSeats) {
        cout << "Row " << seat.first << seat.second << ", ";
    }
    cout << endl;
}

int main() {
    vector<vector<char>> seatingChart;
    vector<pair<int, char>> takenSeats;

    // Initialize the seating chart
    initializeSeatingChart(seatingChart);
    displaySeatingChart(seatingChart);

    // Loop for seat assignment
    while (true) {
        int availableSeats = availableSeatsCount(seatingChart);
        if (availableSeats == 0) {
            cout << "No seats available.\n";
            break;
        }

        char continueAssigning;
        cout << "Do you want to assign a seat? (y/n): ";
        cin >> continueAssigning;
        if (continueAssigning == 'n' || continueAssigning == 'N') {
            break;
        }

        //Ask user for seat assignment
        int row;
        char seat;
        cout << "Enter the row number (1 to 5): ";
        cin >> row;
        cout << "Enter the seat letter (A, B, C, D): ";
        cin >> seat;

        // Try assigning seat with exception handling
        try {
            if (assignSeat(seatingChart, row, seat, takenSeats)) {
                cout << "Seat " << row << seat << " assigned successfully!\n";
            }
        }
        catch (const out_of_range& e) {
            cout << "Error: " << e.what() << " Please enter valid seat information.\n";
        }
        catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }

        // Display updated seating chart
        displaySeatingChart(seatingChart);
    }

    // Final results
    displaySeatingChart(seatingChart);
    cout << "\nTotal available seats: " << availableSeatsCount(seatingChart) << endl;
    showTakenSeats(takenSeats);

    return 0;
}
