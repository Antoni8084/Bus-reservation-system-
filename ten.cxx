#include <iostream>
#include <vector>
#include <string>
#include <iomanip>  // For formatting output
#include <fstream>  // For file operations
#include <ctime>    // For time-based discounts

using namespace std;

class Passenger {
public:
    string firstName, middleName, lastName, contact;
    int seatNumber;
    string seatType;

    Passenger(string fName, string mName, string lName, string contactInfo, int seatNum, string type)
        : firstName(fName), middleName(mName), lastName(lName), contact(contactInfo), seatNumber(seatNum), seatType(type) {}
};

class Bus {
private:
    string busName;
    int totalSeats;
    float fare;
    vector<bool> seats;
    vector<Passenger> passengers;

public:
    Bus(string name, int seatsCount, float busFare) : busName(name), totalSeats(seatsCount), fare(busFare) {
        seats.resize(totalSeats, false);
        passengers.resize(totalSeats, Passenger("", "", "", "", -1, ""));
        loadReservationHistory(); // Load previous bookings from file
    }

    void loadReservationHistory() {
        ifstream inFile("reservation_history.txt");
        if (inFile) {
            string firstName, middleName, lastName, contact, seatType;
            int seatNumber;
            while (inFile >> firstName >> middleName >> lastName >> contact >> seatNumber >> seatType) {
                Passenger p(firstName, middleName, lastName, contact, seatNumber, seatType);
                if (seatNumber >= 1 && seatNumber <= totalSeats) {
                    seats[seatNumber - 1] = true;
                    passengers[seatNumber - 1] = p;
                }
            }
            inFile.close();
        }
    }

    void saveReservationHistory() {
        ofstream outFile("reservation_history.txt", ios::trunc);
        for (int i = 0; i < totalSeats; i++) {
            if (seats[i]) {
                Passenger p = passengers[i];
                outFile << p.firstName << " " << p.middleName << " " << p.lastName << " "
                        << p.contact << " " << p.seatNumber << " " << p.seatType << endl;
            }
        }
        outFile.close();
    }

    void viewSeats() {
        cout << "\nSeating arrangement for bus: " << busName << "\n";
        for (int i = 0; i < totalSeats; i++) {
            cout << (seats[i] ? "[X] " : "[ ] ");  // Show booked and empty seats
            if ((i + 1) % 5 == 0) cout << "\n";
        }
    }

    bool bookSeat(int seatNumber, Passenger passenger) {
        if (seatNumber < 1 || seatNumber > totalSeats) {
            cout << "Invalid seat number. Please try again.\n";
            return false;
        }
        if (seats[seatNumber - 1]) {
            cout << "Seat " << seatNumber << " is already booked. Please choose another.\n";
            return false;
        }
        seats[seatNumber - 1] = true;
        passengers[seatNumber - 1] = passenger;
        saveReservationHistory();  // Save after booking
        return true;
    }

    void cancelSeat(int seatNumber) {
        if (seatNumber < 1 || seatNumber > totalSeats) {
            cout << "Invalid seat number. Please try again.\n";
            return;
        }
        if (!seats[seatNumber - 1]) {
            cout << "Seat " << seatNumber << " is already vacant.\n";
        } else {
            seats[seatNumber - 1] = false;
            passengers[seatNumber - 1] = Passenger("", "", "", "", -1, ""); // Clear passenger details
            saveReservationHistory();  // Save after cancellation
            cout << "Seat " << seatNumber << " has been successfully canceled.\n";
        }
    }

    void showSummary() {
        cout << "\n--- Booking Summary ---\n";
        for (int i = 0; i < totalSeats; i++) {
            if (seats[i]) {
                Passenger p = passengers[i];
                cout << "Seat " << (i + 1) << " booked by " << p.firstName << " " << p.middleName << " " << p.lastName
                     << " (Contact: " << p.contact << ", Seat Type: " << p.seatType << ")\n";
            }
        }
    }

    void searchPassenger(string query) {
        bool found = false;
        cout << "\n--- Search Results ---\n";
        for (int i = 0; i < totalSeats; i++) {
            if (seats[i]) {
                Passenger p = passengers[i];
                string fullName = p.firstName + " " + p.middleName + " " + p.lastName;
                if (fullName.find(query) != string::npos || p.contact.find(query) != string::npos) {
                    cout << "Seat " << (i + 1) << " booked by " << fullName
                         << " (Contact: " << p.contact << ")\n";
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "No passengers found with the given details.\n";
        }
    }

    float getFare() {
        return fare;
    }

    void generateTicket(Passenger passenger) {
        cout << "\n--- Ticket ---\n";
        cout << "Name: " << passenger.firstName << " " << passenger.middleName << " " << passenger.lastName << "\n";
        cout << "Seat Number: " << passenger.seatNumber << "\n";
        cout << "Seat Type: " << passenger.seatType << "\n";
        cout << "Contact: " << passenger.contact << "\n";
        cout << "Fare: $" << fixed << setprecision(2) << fare << "\n";
        cout << "Thank you for choosing our service!\n";
    }

    void checkSeatAvailability() {
        int availableSeats = 0;
        for (int i = 0; i < totalSeats; i++) {
            if (!seats[i]) availableSeats++;
        }
        if (availableSeats < 5) {
            cout << "\nHurry! Only " << availableSeats << " seats left on this bus!\n";
        }
    }

    void offerDiscount() {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Apply a 20% discount in December (Holiday season)
        if (ltm->tm_mon == 11) {
            cout << "\nHoliday Discount! You get 20% off on your fare.\n";
            fare *= 0.80; // Apply 20% discount
        }
    }
};

Passenger collectPassengerDetails(int seatNumber) {
    string firstName, middleName, lastName, contact;
    string seatType;
    cout << "\nEnter your first name: ";
    cin >> firstName;
    cout << "Enter your middle name: ";
    cin >> middleName;
    cout << "Enter your last name: ";
    cin >> lastName;
    cout << "Enter your contact information: ";
    cin >> contact;
    cout << "Choose seat type (VIP/Standard): ";
    cin >> seatType;

    return Passenger(firstName, middleName, lastName, contact, seatNumber, seatType);
}

void displayMenu() {
    cout << "\n=== Bus Reservation System ===\n";
    cout << "1. View Available Seats\n";
    cout << "2. Book a Seat\n";
    cout << "3. Cancel a Booking\n";
    cout << "4. View Booking Summary\n";
    cout << "5. Search for a Passenger\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Bus bus("Express Bus", 20, 15.00);
    int choice, seatNumber;

    while (true) {
        bus.checkSeatAvailability();
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                bus.viewSeats();
                break;

            case 2: {
                bus.offerDiscount();
                cout << "Enter the seat number you want to book: ";
                cin >> seatNumber;
                Passenger passenger = collectPassengerDetails(seatNumber);
                if (bus.bookSeat(seatNumber, passenger)) {
                    bus.generateTicket(passenger);
                    cout << "Booking Successful!\n";
                }
                break;
            }

            case 3:
                cout << "Enter the seat number you want to cancel: ";
                cin >> seatNumber;
                bus.cancelSeat(seatNumber);
                break;

            case 4:
                bus.showSummary();
                break;

            case 5: {
                string query;
                cout << "Enter the name or contact of the passenger to search: ";
                cin.ignore(); // Clear input buffer
                getline(cin, query);
                bus.searchPassenger(query);
                break;
            }

            case 6:
                cout << "Thank you for using the Bus Reservation System. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}