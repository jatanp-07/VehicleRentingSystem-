#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
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
        cout << "Keep Format like yuvank_goyal (firstName_lastName)!!\n";
        cout << "Enter new username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        bool phoneCheck = false;

        do
        {
            cout << "Enter phonenumber: ";
            cin >> phonenumber;

            phoneCheck = true;
            if (phonenumber.size() != 10)
            {
                cout << "❌ Phone number must be exactly 10 digits.\n";
                phoneCheck = false;
                continue;
            }

            for (int i = 0; i < phonenumber.size(); i++)
            {
                if (phonenumber[i] < '0' || phonenumber[i] > '9')
                {
                    cout << "❌ Phone number can contain only digits.\n";
                    phoneCheck = false;
                    break;
                }
            }
        } while (!phoneCheck);



        string id = generateUniqueID();
        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            file  << username << "," << password << "," << phonenumber << "\n";
            file.close();
            cout << "\nRegistration successful!\n";
            cout << "-------------------------------------\n";
            UserEnterpriseDetailEntry();
        }
        else
        {
            cout << "Error opening file for registration.\n";
        }
    }

    /// member function of class userDetails to login the user
    bool loginUser()
    {
        string password, username, phonenumber;
        bool success = false;

        for (int attempts = 1; attempts <= 2; attempts++)
        {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            ifstream file(filename);
            string line, uuser, upass;
            while (getline(file, line))
            {
                stringstream ss(line);
                getline(ss, uuser, ',');
                getline(ss, upass, ',');

                if (uuser == username && upass == password)
                {
                    cout << "\nLogin successful!\n";
                    return true;
                }
            }

            cout << "\nInvalid username or password!\n";
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
                string line, uuname, uupass, uuphone;
                while (getline(file2, line))
                {
                    stringstream ss(line);
                    getline(ss, uuname, ',');
                    getline(ss, uupass, ',');
                    getline(ss, uuphone, ',');

                    if (phonechecknnumber == uuphone)
                    {
                        cout << "\nMatch Found!\n";
                        cout << "Your details are:\n";
                        cout << "Username: " << uuname << "\n";
                        cout << "Password: " << uupass << "\n";
                        cout << "Phone: " << uuphone << "\n";
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "\nPhone number not found in records.\n";
                }

                cout << "\nYou can try logging in again.\n";
            }
            else if (decision == 2)
            {
                cout << "\nNo details shown. Returning to login menu.\n";
            }
            else
            {
                cout << "\nInvalid choice. Skipping details.\n";
            }
        }

        return false;
    }
};

class EnterpriseDetails
{
private:
    string filePath;
    string entId, entName, entPass, entContact;

    // id generator :
    string createUniqueID()
    {
        srand(time(0));
        string newId;
        bool alreadyExists;
        do
        {
            alreadyExists = false;
            int number = 20000 + rand() % 80000;
            newId = "E" + to_string(number);

            ifstream fin(filePath);
            string line, idFromFile;
            while (getline(fin, line))
            {
                stringstream ss(line);
                getline(ss, idFromFile, ',');
                if (idFromFile == newId)
                {
                    alreadyExists = true;
                    break;
                }
            }
            fin.close();
        } while (alreadyExists);

        return newId;
    }

public:
    //default constructor 
    EnterpriseDetails(string fname = "EnterpriseDetails.txt") : filePath(fname) {}
    //verification of the details`
    friend bool verifyEnterprise(const EnterpriseDetails &obj, string givenId, string givenPass);
    // enterprise regis.
    void registerEnterprise()
    {
        cout << "Enter Enterprise Name: ";
        cin.ignore();
        getline(cin, entName);

        cout << "Create password: ";
        cin >> entPass;

        cout << "Enter 10-digit Contact Number: ";
        while (true)
        {
            cin >> entContact;
            bool valid = true;

            if (entContact.length() != 10)
                valid = false;
            else
            {
                for (char c : entContact)
                {
                    if (!isdigit(c))
                    {
                        valid = false;
                        break;
                    }
                }
            }

            if (valid)
                break;
            else
                cout << "Invalid contact number. Please enter again: ";
        }

        entId = createUniqueID();
        ofstream fout(filePath, ios::app);
        if (fout.is_open())
        {
            fout << entId << "," << entName << "," << entPass << "," << entContact << "\n";
            fout.close();
            cout << "\nRegistration Completed Successfully!\n";
            cout << "Your Enterprise ID: " << entId << "\n";
        }
        else
        {
            cout << "File error: Could not open storage file.\n";
        }
    }

    string getId() const { return entId; }
    string getPassword() const { return entPass; }

    // login for enterprise
    bool loginEnterprise()
    {
        string inputId, inputPass;
        cout << "Enter Enterprise ID: ";
        cin >> inputId;
        cout << "Enter password: ";
        cin >> inputPass;

        ifstream fin(filePath);
        string line, fid, fname, fpass, fcontact;

        while (getline(fin, line))
        {
            stringstream ss(line);
            getline(ss, fid, ',');
            getline(ss, fname, ',');
            getline(ss, fpass, ',');
            getline(ss, fcontact, ',');

            EnterpriseDetails temp(filePath);
            temp.entId = fid;
            temp.entName = fname;
            temp.entPass = fpass;
            temp.entContact = fcontact;

            if (verifyEnterprise(temp, inputId, inputPass))
            {
                cout << "\nLogin successful! Welcome, " << fname << ".\n";
                return true;
            }
        }

        cout << "Login failed: Invalid credentials.\n";
        return false;
    }
};

// friend func def using 
bool verifyEnterprise(const EnterpriseDetails &obj, string givenId, string givenPass)
{
    return (obj.entId == givenId && obj.entPass == givenPass);
}

int main()
{
    cout << "Welcome to Vehicle Rental System\n";
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