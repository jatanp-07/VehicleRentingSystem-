#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;

class Vehicle {
    string brand;
    string model;
    double dailyPrice;
    int availableCount;
public:
    Vehicle(string b, string m, double p, int q)
        : brand(b), model(m), dailyPrice(p), availableCount(q) {}

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    double getPrice() const { return dailyPrice; }
    int getAvailable() const { return availableCount; }

    void book(int qty) { if (availableCount >= qty) availableCount -= qty; }
    void release(int qty) { availableCount += qty; }

    void show() const {
        cout << "Brand: " << brand
             << " | Model: " << model
             << " | Price/Day: " << dailyPrice
             << " | Available: " << availableCount << endl;
    }
};

class Enterprise {
    string name;
    double lateChargePerDay;
    vector<Vehicle> fleet;
public:
    Enterprise(string n, double fee) : name(n), lateChargePerDay(fee) {}

    string getName() const { return name; }
    double getLateCharge() const { return lateChargePerDay; }

    void addVehicle(const Vehicle& v) { fleet.push_back(v); }

    void showFleet() const {
        cout << "\nEnterprise: " << name << " | Late Fee/Day: " << lateChargePerDay << endl;
        for (size_t i = 0; i < fleet.size(); i++) {
            cout << i + 1 << ". ";
            fleet[i].show();
        }
    }

    Vehicle* pickVehicle(int index) {
        if (index > 0 && index <= fleet.size()) return &fleet[index - 1];
        return nullptr;
    }
};

struct Rental {
    string enterprise, brand, model;
    double price;
    string dueDate;
    int quantity;

    void save(const string& user, const string& id) {
        ofstream out("rental_records.txt", ios::app);
        out << user << " | " << id << " | " << enterprise
            << " | " << brand << " | " << model
            << " | " << price << " | " << dueDate
            << " | " << quantity << endl;
        out.close();
    }
};

class User {
    string name, id;
    vector<Rental> activeRentals;
public:
    User(string n, string uid) : name(n), id(uid) {}

    void rent(Enterprise& ent) {
        ent.showFleet();
        int choice, qty;
        cout << "\nSelect vehicle number (0 to cancel): ";
        cin >> choice;
        if (choice == 0) return;
        cout << "Enter quantity: ";
        cin >> qty;

        Vehicle* v = ent.pickVehicle(choice);
        if (v && v->getAvailable() >= qty) {
            v->book(qty);
            string due;
            cout << "Enter expected return date (YYYY-MM-DD): ";
            cin >> due;
            Rental r{ ent.getName(), v->getBrand(), v->getModel(), v->getPrice(), due, qty };
            r.save(name, id);
            activeRentals.push_back(r);
            cout << "\nBooking confirmed!\n";
        } else {
            cout << "Invalid choice or not enough stock.\n";
        }
    }

    void giveBack(const Enterprise& ent) {
        if (activeRentals.empty()) {
            cout << "You have no rentals.\n";
            return;
        }
        cout << "\nYour Rentals:\n";
        for (size_t i = 0; i < activeRentals.size(); i++) {
            cout << i + 1 << ". " << activeRentals[i].brand << " "
                 << activeRentals[i].model
                 << " | Due: " << activeRentals[i].dueDate
                 << " | Qty: " << activeRentals[i].quantity << endl;
        }
        int choice;
        cout << "\nSelect rental to return: ";
        cin >> choice;
        if (choice > 0 && choice <= activeRentals.size()) {
            string actual;
            cout << "Enter actual return date (YYYY-MM-DD): ";
            cin >> actual;
            d
