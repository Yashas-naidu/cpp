#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Class to represent the TempleBookingSystem
class TempleBookingSystem {
private:
    // Structure to represent a booking
    struct Booking {
        string name;
        string date;
        string time;
        int price;
        string specialDarshan;
    };

    vector<Booking> bookings;

    // Function to update the "bookings.txt" file with the current bookings
    void updateBookingsFile() {
        ofstream outFile("bookings.txt");
        if (outFile.is_open()) {
            for (const Booking& booking : bookings) {
                outFile << booking.name << "," << booking.date << "," << booking.time << "," << booking.price << "," << booking.specialDarshan << endl;
            }
            outFile.close();
        } else {
            cout << "Error: Unable to open the file for writing." << endl;
        }
    }

public:
    // Function to book a slot
    void bookSlot() {
        do {
            Booking booking;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, booking.name);
            cout << "Enter the date (DD/MM/YYYY): ";
            cin >> booking.date;

            cout << "Choose a special darshan:" << endl;
            cout << "1. Special Darshan (200 Rupees)" << endl;
            cout << "2. VIP Darshan (500 Rupees)" << endl;
            cout << "3. Platinum Darshan (1000 Rupees)" << endl;
            int darshanChoice;
            cout << "Enter the special darshan choice (1-3): ";
            cin >> darshanChoice;

            switch (darshanChoice) {
                case 1:
                    booking.specialDarshan = "Special Darshan";
                    booking.price = 200;
                    break;
                case 2:
                    booking.specialDarshan = "VIP Darshan";
                    booking.price = 500;
                    break;
                case 3:
                    booking.specialDarshan = "Platinum Darshan";
                    booking.price = 1000;
                    break;
                default:
                    cout << "Invalid special darshan choice. Booking canceled." << endl;
                    return;
            }

            cout << "Available time slots for darshana:" << endl;
            cout << "1. 09:00 AM - 10:00 AM" << endl;
            cout << "2. 10:30 AM - 11:30 AM" << endl;
            cout << "3. 12:00 PM - 01:00 PM" << endl;
            cout << "4. 02:00 PM - 03:00 PM" << endl;
            cout << "5. 03:30 PM - 04:30 PM" << endl;
            cout << "6. 05:00 PM - 06:00 PM" << endl;
            int slotChoice;
            cout << "Enter the slot number you want to book (1-6): ";
            cin >> slotChoice;

            switch (slotChoice) {
                case 1:
                    booking.time = "09:00 AM - 10:00 AM";
                    break;
                case 2:
                    booking.time = "10:30 AM - 11:30 AM";
                    break;
                case 3:
                    booking.time = "12:00 PM - 01:00 PM";
                    break;
                case 4:
                    booking.time = "02:00 PM - 03:00 PM";
                    break;
                case 5:
                    booking.time = "03:30 PM - 04:30 PM";
                    break;
                case 6:
                    booking.time = "05:00 PM - 06:00 PM";
                    break;
                default:
                    cout << "Invalid slot choice. Booking canceled." << endl;
                    return;
            }

            bookings.push_back(booking);

            ofstream outFile("bookings.txt", ios::app);
            if (outFile.is_open()) {
                outFile << booking.name << "," << booking.date << "," << booking.time << "," << booking.price << "," << booking.specialDarshan << endl;
                outFile.close();
                cout << "Booking successful!" << endl;
            } else {
                cout << "Error: Unable to open the file for writing." << endl;
            }

            cout << "Do you want to book one more slot? (1 for Yes, 0 for No): ";
            int moreBooking;
            cin >> moreBooking;
            if (moreBooking == 0) {
                break; // Exit the booking loop
            }
        } while (true);
    }

    // Function to display booked slots
    void displayBookedSlots() {
        cout << "Booked slots for darshana:" << endl;
        for (const Booking& booking : bookings) {
            cout << "Name: " << booking.name << ", Date: " << booking.date << ", Time: " << booking.time << ", Special Darshan: " << booking.specialDarshan << ", Price: " << booking.price << " Rupees" << endl;
        }
    }

    // Function to delete a booking
    void deleteBooking() {
        string name, date;
        cout << "Enter the name of the person whose booking you want to delete: ";
        cin.ignore();
        getline(cin,name);
        cout << "Enter the date of the booking to be deleted (DD/MM/YYYY): ";
        cin >> date;

        for (auto it = bookings.begin(); it != bookings.end(); ++it) {
            if (it->name == name && it->date == date) {
                bookings.erase(it);
                cout << "Booking deleted successfully!" << endl;
                updateBookingsFile(); // Update the "bookings.txt" file
                return;
            }
        }

        cout << "Booking not found. No changes made." << endl;
    }

    // Function to search for bookings based on criteria
    void searchBookings() {
        int searchChoice;
        cout << "Search for bookings by:" << endl;
        cout << "1. Name" << endl;
        cout << "2. Date" << endl;
        cout << "Enter your choice (1-2): ";
        cin >> searchChoice;

        if (searchChoice == 1) {
            string name;
            cout << "Enter the name to search for: ";
            cin.ignore();
            getline(cin, name);

            cout << "Matching bookings by name:" << endl;
            for (const Booking& booking : bookings) {
                if (booking.name == name) {
                    cout << "Name: " << booking.name << ", Date: " << booking.date << ", Time: " << booking.time << ", Special Darshan: " << booking.specialDarshan << ", Price: " << booking.price << " Rupees" << endl;
                }
            }
        } else if (searchChoice == 2) {
            string date;
            cout << "Enter the date to search for (DD/MM/YYYY): ";
            cin >> date;

            cout << "Matching bookings by date:" << endl;
            for (const Booking& booking : bookings) {
                if (booking.date == date) {
                    cout << "Name: " << booking.name << ", Date: " << booking.date << ", Time: " << booking.time << ", Special Darshan: " << booking.specialDarshan << ", Price: " << booking.price << " Rupees" << endl;
                }
            }
        } else {
            cout << "Invalid search choice. Please try again." << endl;
        }
    }

    // Function to load existing bookings from the file
    void loadBookingsFromFile() {
        ifstream inFile("bookings.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                Booking booking;
                size_t commaPos = line.find(',');
                if (commaPos != string::npos) {
                    booking.name = line.substr(0, commaPos);
                    line = line.substr(commaPos + 1);
                    commaPos = line.find(',');
                    if (commaPos != string::npos) {
                        booking.date = line.substr(0, commaPos);
                        line = line.substr(commaPos + 1);
                        commaPos = line.find(',');
                        if (commaPos != string::npos) {
                            booking.time = line.substr(0, commaPos);
                            line = line.substr(commaPos + 1);
                            commaPos = line.find(',');
                            if (commaPos != string::npos) {
                                booking.price = stoi(line.substr(0, commaPos));
                                booking.specialDarshan = line.substr(commaPos + 1);
                                bookings.push_back(booking);
                            }
                        }
                    }
                }
            }
            inFile.close();
        } else {
            cout << "Error: Unable to open the file for reading." << endl;
        }
    }

    // Function to run the booking system
    void run() {
        int choice;
        do {
            cout << "Temple Darshana Booking System" << endl;
            cout << "1. Book a slot" << endl;
            cout << "2. Display booked slots" << endl;
            cout << "3. Delete a booking" << endl;
            cout << "4. Search for bookings" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    bookSlot();
                    break;
                case 2:
                    displayBookedSlots();
                    break;
                case 3:
                    deleteBooking();
                    break;
                case 4:
                    searchBookings();
                    break;
                case 5:
                    cout << "Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 5);
    }
};

int main() {
    TempleBookingSystem bookingSystem;
    bookingSystem.loadBookingsFromFile();
    bookingSystem.run();

    return 0;
}