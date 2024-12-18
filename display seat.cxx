#include <iostream>
#include <vector>

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

int main() {
    Bus bus("Express Bus", 20, 15.00);

    cout << "--- Welcome to the Bus Reservation System ---\n";
    bus.viewSeats();
    cout << "Fare per seat: $" << bus.getFare() << "\n";

    return 0;
}