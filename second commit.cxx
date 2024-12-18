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
            cout << "[ ] ";  // All seats are empty
            if ((i + 1) % 5 == 0) cout << "\n";
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

int main() {
    Bus bus("Express Bus", 20, 15.00);

    cout << "--- Welcome to the Bus Reservation System ---\n";
    bus.viewSeats();
    cout << "Fare per seat: $" << bus.getFare() << "\n";

    collectPassengerDetails();

    return 0;
}