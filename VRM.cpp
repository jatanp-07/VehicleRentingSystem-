#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

//====================userDetails===================================
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
            file << id << "," << username << "," << password << "," << phonenumber << "\n";
            file.close();
            cout << "\nRegistration successful!\n";
            cout << "-------------------------------------\n";
            cout << " Your Unique User ID: " << id << "\n";
            cout << " Save this ID carefully; you need it to login.\n";
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
                    cout << "\nLogin successful! Welcome, " << uuser << "!\n";
                    return true;
                }
            }
            cout << "ID not found.\n";
        }

        // Username + password login
        cout << "\nToo many failed ID attempts.\n";
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
                    cout << "\nLogin successful!\n";
                    cout << "Your User ID is: " << uid << endl;
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
                        cout << "\nMatch Found!\n";
                        cout << "Your details are:\n";
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

//=============================Enterprise======================================

class Model
{
    string modelname, modelnumber, modelcolour;
    double modelprice;

public:
    Model(string nameOfModel = "", double priceOfModel = 0.0, string phonenumberOfModel = "", string colourOfModel = "")
        : modelname(nameOfModel), modelprice(priceOfModel), modelnumber(phonenumberOfModel), modelcolour(colourOfModel) {}

    friend void displayModel(const Model &m);
};

class Company
{
    string companyname;
    vector<Model *> models;

public:
    Company(string nameOfCompany = "") : companyname(nameOfCompany) {}

    void addModel(Model *m) { models.push_back(m); }

    void showModels() const
    {
        cout << "\n Company: " << companyname << "\n";
        for (auto m : models)
            displayModel(*m);
    }

    ~Company()
    {
        for (auto m : models)
            delete m;
    }
};
class Enterprises
{
    string Enterprisename, ownerName, OwnerPhonenumber;
    vector<Company *> companies;

public:
    Enterprises(string nameOfEnterprise = "", string nameOfOwner = "", string phoneOfOwner = "")
        : Enterprisename(nameOfEnterprise), ownerName(nameOfOwner), OwnerPhonenumber(phoneOfOwner) {}

    void addCompany(Company *c) { companies.push_back(c); }

    void showEnterprise() const
    {
        cout << "\nEnterprise: " << Enterprisename
             << "\nOwner: " << ownerName
             << "\nPhone: " << OwnerPhonenumber << "\n";
        for (auto c : companies)
            c->showModels();
    }

    ~Enterprises()
    {
        for (auto c : companies)
            delete c;
    }
};

vector<Enterprises *> loadData(const string &filename)
{
    ifstream file(filename);
    vector<Enterprises *> enterprises;
    if (!file.is_open())
    {
        cerr << "Error opening file\n";
        return enterprises;
    }

    string line;
    Enterprises *currentEnterprise = nullptr;
    Company *currentCompany = nullptr;

    while (getline(file, line))
    {
        if (line.rfind("Enterprise:", 0) == 0)
        {
            // parsing enetrprise
            stringstream ss(line);
            string part, ename, eowner, ephone;
            while (getline(ss, part, '|'))
            {
                if (part.find("Enterprise:") != string::npos)
                {
                    ename = part.substr(11);
                }
                else if (part.find("Owner:") != string::npos)
                {
                    eowner = part.substr(6);
                }
                else if (part.find("Phone:") != string::npos)
                {
                    ephone = part.substr(6);
                }
            }
            currentEnterprise = new Enterprises(ename, eowner, ephone);
            enterprises.push_back(currentEnterprise);
        }
        else if (line.rfind("Company:", 0) == 0)
        {
            string cname = line.substr(8);
            currentCompany = new Company(cname);
            if (currentEnterprise)
                currentEnterprise->addCompany(currentCompany);
        }
        else if (line.rfind("Model:", 0) == 0)
        {
            stringstream ss(line);
            string part, mname, number, color;
            double price = 0;
            while (getline(ss, part, '|'))
            {
                if (part.find("Model:") != string::npos)
                {
                    mname = part.substr(6);
                }
                else if (part.find("Price:") != string::npos)
                {
                    price = stod(part.substr(6));
                }
                else if (part.find("Number:") != string::npos)
                {
                    number = part.substr(7);
                }
                else if (part.find("Color:") != string::npos)
                {
                    color = part.substr(6);
                }
            }
            if (currentCompany)
                currentCompany->addModel(new Model(mname, price, number, color));
        }
        else if (line == "END_ENTERPRISE")
        {
            currentEnterprise = nullptr;
            currentCompany = nullptr;
        }
    }
    return enterprises;
}

void displayModel(const Model &m)
{
    cout << "      Model: " << m.modelname
         << " | Price: " << m.modelprice
         << " | Number: " << m.modelnumber
         << " | Color: " << m.modelcolour << "\n";
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
            vector<Enterprises *> enterprises = loadData("sellerDetails.txt");
            cout << "\nAvailable Enterprises:\n";
            for (size_t i = 0; i < enterprises.size(); i++)
                cout << i + 1 << ". " << "Enterprise: " << i + 1 << " -> "
                     << "Select to view details\n";

            int choice;
            cout << "\nEnter Enterprise number to view details: ";
            cin >> choice;

            if (choice > 0 && choice <= (int)enterprises.size())
            {
                enterprises[choice - 1]->showEnterprise();
            }
            else
            {
                cout << "Invalid choice!\n";
            }

            // Cleanup
            for (auto e : enterprises)
                delete e;
            return 0;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
