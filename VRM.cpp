#include <iostream>
#include <string>
using namespace std;

class Vehicle {
private:
    string brand;
    string model;
    double rentPerDay;
    bool isRented;

public:
    Vehicle(string b, string m, double rent)
        : brand(b), model(m), rentPerDay(rent), isRented(false) {
        cout << "Vehicle " << brand << " " << model << " created.\n";
    }

    ~Vehicle() {
        cout << "Vehicle " << brand << " " << model << " removed from system.\n";
    }

    void displayDetails() {
        cout << "\nVehicle Details:\n";
        cout << "Brand: " << brand << "\n";
        cout << "Model: " << model << "\n";
        cout << "Rent per day: ₹" << rentPerDay << "\n";
        cout << "Status: " << (isRented ? "Rented" : "Available") << "\n";
    }

    void rentVehicle(int days) {
        if (!isRented) {
            double totalCost = rentPerDay * days;
            isRented = true;
            cout << "✅ Vehicle rented successfully for " << days
                 << " days. Total cost: ₹" << totalCost << "\n";
        } else {
            cout << "❌ Vehicle is already rented.\n";
        }
    }

    void returnVehicle() {
        if (isRented) {
            isRented = false;
            cout << "✅ Vehicle returned successfully.\n";
        } else {
            cout << "❌ This vehicle was not rented.\n";
        }
    }
};

int main() {
    cout << "🚗 Welcome to Vehicle Rental System 🚗\n";
    Vehicle v1("Toyota", "Fortuner", 2000);
    Vehicle v2("Honda", "City", 1500);

    int choice, days;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. View Vehicle 1 Details\n";
        cout << "2. View Vehicle 2 Details\n";
        cout << "3. Rent Vehicle 1\n";
        cout << "4. Rent Vehicle 2\n";
        cout << "5. Return Vehicle 1\n";
        cout << "6. Return Vehicle 2\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: v1.displayDetails(); break;
            case 2: v2.displayDetails(); break;
            case 3:
                cout << "Enter number of days: ";
                cin >> days;
                v1.rentVehicle(days);
                break;
            case 4:
                cout << "Enter number of days: ";
                cin >> days;
                v2.rentVehicle(days);
                break;
            case 5: v1.returnVehicle(); break;
            case 6: v2.returnVehicle(); break;
            case 7: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
