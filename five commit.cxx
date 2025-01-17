#include <iostream>
#include <vector>
#include <string>
#include <iomanip>  // For formatting output

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

    void cancelSeat(int seatNumber) {
        if (seatNumber < 1 || seatNumber > totalSeats) {
            cout << "Invalid seat number. Please try again.\n";
            return;
        }
        if (!seats[seatNumber - 1]) {
            cout << "Seat " << seatNumber << " is already vacant.\n";
        } else {
            seats[seatNumber - 1] = false;
            cout << "Seat " << seatNumber << " has been successfully canceled.\n";
        }
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

void processPayment(float fare) {
    cout << "\nThe total fare is: $" << fixed << setprecision(2) << fare << "\n";
    cout << "Payment successful. Thank you for your booking!\n";
}

int main() {
    Bus bus("Express Bus", 20, 15.00);
    int choice, seatNumber;

    while (true) {
        cout << "\n--- Bus Reservation System ---\n";
        cout << "1. View Available Seats\n";
        cout << "2. Book a Seat\n";
        cout << "3. Cancel a Booking\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bus.viewSeats();
                break;

            case 2:
                cout << "Enter the seat number you want to book: ";
                cin >> seatNumber;
                if (bus.bookSeat(seatNumber)) {
                    cout << "Seat " << seatNumber << " successfully booked!\n";
                    collectPassengerDetails();
                    processPayment(bus.getFare());
                }
                break;

            case 3:
                cout << "Enter the seat number you want to cancel: ";
                cin >> seatNumber;
                bus.cancelSeat(seatNumber);
                break;

            case 4:
                cout << "Thank you for using the Bus Reservation System. Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}