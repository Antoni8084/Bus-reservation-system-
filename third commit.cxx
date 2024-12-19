#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Bus {
private:
    string busName;
    int totalSeats;
    float fare;
    vector<bool> seats;

public:
    Bus(string name, int seatsCount, float busFare) : busName(name), totalSeats(seatsCount), fare(busFare) {
        seats.resize(totalSeats, false);
    }

    void viewSeats() {
        cout << "\nSeating arrangement for bus: " << busName << "\n";
        for (int i = 0; i < totalSeats; i++) {
            cout << (seats[i] ? "[X] " : "[ ] ");  // Show booked and empty seats
            if ((i + 1) % 5 == 0) cout << "\n";
        }
    }

    bool bookSeat(int seatNumber) {
        if (seatNumber < 1 || seatNumber > totalSeats) {
            cout << "Invalid seat number. Please try again.\n";
            return false;
        }
        if (seats[seatNumber - 1]) {
            cout << "Seat " << seatNumber << " is already booked. Please choose another.\n";
            return false;
        }
        seats[seatNumber - 1] = true;
        return true;
    }

    float getFare() {
        return fare;
    }
};

void collectPassengerDetails() {
    string firstName, middleName, lastName, contact;
    cout << "\nEnter your first name: ";
    cin >> firstName;
    cout << "Enter your middle name: ";
    cin >> middleName;
    cout << "Enter your last name: ";
    cin >> lastName;
    cout << "Enter your contact information: ";
    cin >> contact;

    cout << "\nPassenger Details:\n";
    cout << "Name: " << firstName << " " << middleName << " " << lastName << "\n";
    cout << "Contact: " << contact << "\n";
}

int main() {
    Bus bus("Express Bus", 20, 15.00);
    int seatNumber;

    cout << "--- Welcome to the Bus Reservation System ---\n";
    bus.viewSeats();
    cout << "Fare per seat: $" << bus.getFare() << "\n";

    collectPassengerDetails();

    cout << "Enter the seat number you want to book: ";
    cin >> seatNumber;
    if (bus.bookSeat(seatNumber)) {
        cout << "Seat " << seatNumber << " has been successfully booked!\n";
    }

    bus.viewSeats();  // Show updated seating arrangement
    return 0;
}