#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class UserDetails
{
private:
    string filename;
    string generateUniqueID()
    {
        srand(time(0));
        string id;
        bool exists;
        do
        {
            exists = false;
            int num = 10000 + rand() % 90000; // genarte the random unique id
            id = to_string(num);
            ifstream file(filename);
            string line, uid, uname, upass;
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, uid, ',');
                if (uid == id)
                {
                    exists = true;
                    break;
                }
            }
            file.close();
        } while (exists);
        return id;
    }

public:
    UserDetails(string fname = "userDetails.txt") : filename(fname) {}
    // member function of class userDetails to register the user
    void registerUser()
    {
        string username, password, phonenumber;
        cout << "Enter new username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter phonenumber: ";
        cin >> phonenumber;

        string id = generateUniqueID();
        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            file << id << "," << username << "," << password << "," << phonenumber << "\n";
            file.close();
            cout << "\n✅ Registration successful!\n";
            cout << "-------------------------------------\n";
            cout << " 🎯 Your Unique User ID: " << id << "\n";
            cout << " ⚠️  Save this ID carefully; you need it to login.\n";
            cout << "-------------------------------------\n";
        }
        else
        {
            cout << "Error opening file for registration.\n";
        }
    }

    /// member function of class userDetails to login the user
    bool loginUser()
    {
        string id, password, username, phonenumber;
        bool success = false;

        // 2 attempts for ID login
        for (int attempt = 1; attempt <= 2; attempt++)
        {
            cout << "Enter your 5-digit User ID (Attempt " << attempt << "/2): ";
            cin >> id;

            ifstream file(filename);
            string line, uid, uuser, upass, uphone;
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, uid, ',');
                getline(ss, uuser, ',');
                getline(ss, upass, ',');
                getline(ss, uphone, ',');

                if (uid == id)
                {
                    cout << "\n✅ Login successful! Welcome, " << uuser << "!\n";
                    return true;
                }
            }
            cout << "❌ ID not found.\n";
        }

        // Username + password login
        cout << "\n⚠️ Too many failed ID attempts.\n";
        cout << "You can login with username and password to retrieve your User ID.\n";

        for (int attempts = 1; attempts <= 2; attempts++)
        {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            ifstream file(filename);
            string line, uid, uuser, upass;
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, uid, ',');
                getline(ss, uuser, ',');
                getline(ss, upass, ',');

                if (uuser == username && upass == password)
                {
                    cout << "\n✅ Login successful!\n";
                    cout << "🎯 Your User ID is: " << uid << endl;
                    return true;
                }
            }

            cout << "\n❌ Invalid username or password!\n";
            cout << "Do you want to view all registered details?\n";
            cout << "1. YES\n2. NO\nEnter choice (1 or 2): ";

            int decision;
            cin >> decision;

            if (decision == 1)
            {
                cout << "\nEnter Your phonenumber: \n";
                string phonechecknnumber;
                cin >> phonechecknnumber;

                bool found = false;

                ifstream file2(filename);
                string line, uuid, uuname, uupass, uuphone;
                while (getline(file2, line))
                {
                    stringstream ss(line);
                    getline(ss, uuid, ',');
                    getline(ss, uuname, ',');
                    getline(ss, uupass, ',');
                    getline(ss, uuphone, ',');

                    if (phonechecknnumber == uuphone)
                    {
                        cout << "\n🎯 Match Found!\n";
                        cout << "✅ Your details are:\n";
                        cout << "User ID: " << uuid << "\n";
                        cout << "Username: " << uuname << "\n";
                        cout << "Password: " << uupass << "\n";
                        cout << "Phone: " << uuphone << "\n";
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "\n❌ Phone number not found in records.\n";
                }

                cout << "\nYou can try logging in again.\n";
            }
            else if (decision == 2)
            {
                cout << "\nNo details shown. Returning to login menu.\n";
            }
            else
            {
                cout << "\n⚠️ Invalid choice. Skipping details.\n";
            }
        }

        return false;
    }
};

int main()
{
    cout << "🚗 Welcome to Vehicle Rental System 🚗\n";
    cout << "-------------------------------------\n";
    cout << "Which Portal You Want To Access?\n";
    cout << "1. User Portal\n";
    cout << "2. Service Provider Portal\n";
    cout << "Enter your choice (1 or 2): ";
    int portalChoice;
    cin >> portalChoice;
    // validation of the portal choice
    if (portalChoice != 1 && portalChoice != 2)
    {
        cout << "Invalid choice! Exiting...\n";
        return 0;
    }

    // using try catch block to handle any unexpected errors
    try
    {
        // Accessing the chosen portal
        if (portalChoice == 1)
        {
            cout << "You have accessed the User Portal.\n";
            cout << "==============================\n";
            cout << "1. login\n";
            cout << "2. Register\n";
            cout << "Enter your choice (1 or 2): ";
            int userChoice;
            cin >> userChoice;
            if (userChoice != 1 && userChoice != 2)
            {
                cout << "Invalid choice! Exiting...\n";
                return 0;
            }
            if (userChoice == 2)
            {
                UserDetails user;
                user.registerUser();
            }
            if (userChoice == 1)
            {
                UserDetails user;
                user.loginUser();
            }
        }

        if (portalChoice == 2)
        {
            cout << "You have accessed the Service Provider Portal.\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
