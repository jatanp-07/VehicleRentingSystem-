#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <vector>
#include <ctime>
using namespace std;

class Model
{
    string modelname, modelnumber, modelcolour;
    double modelprice;

public:
    Model(string nameOfModel = "", double priceOfModel = 0.0, string phonenumberOfModel = "", string colourOfModel = "")
        : modelname(nameOfModel), modelprice(priceOfModel), modelnumber(phonenumberOfModel), modelcolour(colourOfModel) {}

    friend void displayModel(const Model &m);

    void showModel() const
    {
        displayModel(*this);
    }
};

class Company
{
    string companyname;
    vector<Model *> models;

public:
    Company(string nameOfCompany = "") : companyname(nameOfCompany) {}
    vector<Model *> &getModels() { return models; }
    string getCompanyName() const { return companyname; }

    void addModel(Model *m) { models.push_back(m); }
    void showCompany() const
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
class Variety
{
    string vname;
    vector<Company *> companies;

public:
    Variety(string varietyname = "") : vname(varietyname) {};
    vector<Company *> &getCompanies() { return companies; }
    void addCompany(Company *c) { companies.push_back(c); };
    void showVariety() const
    {
        cout << "\n  Variety: " << vname << "\n";
        for (auto c : companies)
            c->showCompany();
    }
    ~Variety()
    {
        for (auto c : companies)
            delete c;
    }
};

class Enterprises
{
    string Enterprisename, ownerName, OwnerPhonenumber;
    vector<Company *> companies;
    vector<Variety *> varieties;

public:
    Enterprises(string nameOfEnterprise = "", string nameOfOwner = "", string phoneOfOwner = "")
        : Enterprisename(nameOfEnterprise), ownerName(nameOfOwner), OwnerPhonenumber(phoneOfOwner) {}
    vector<Variety *> &getVarieties() { return varieties; }
    void addCompany(Company *c) { companies.push_back(c); }
    void addVariety(Variety *v) { varieties.push_back(v); }
    void getEnterpriseName() const { cout << "-> " << Enterprisename; }
    void show() const
    {
        cout << "\nEnterprise: " << Enterprisename
             << "\nOwner: " << ownerName
             << "\nPhone: " << OwnerPhonenumber << "\n";
        for (auto v : varieties)
            v->showVariety();
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
        cerr << "Cannot open file\n";
        return enterprises;
    }

    string line;
    Enterprises *currentE = nullptr;
    Variety *currentV = nullptr;
    Company *currentC = nullptr;

    while (getline(file, line))
    {
        if (line.rfind("Enterprise:", 0) == 0)
        {
            string ename, owner, phone, part;
            stringstream ss(line);
            while (getline(ss, part, '|'))
            {
                if (part.find("Enterprise:") != string::npos)
                    ename = part.substr(11);
                else if (part.find("Owner:") != string::npos)
                    owner = part.substr(6);
                else if (part.find("Phone:") != string::npos)
                    phone = part.substr(6);
            }
            currentE = new Enterprises(ename, owner, phone);
            enterprises.push_back(currentE);
        }
        else if (line.rfind("Variety:", 0) == 0)
        {
            string vname = line.substr(8);
            currentV = new Variety(vname);
            if (currentE)
                currentE->addVariety(currentV);
        }
        else if (line.rfind("Company:", 0) == 0)
        {
            string cname = line.substr(8);
            currentC = new Company(cname);
            if (currentV)
                currentV->addCompany(currentC);
        }
        else if (line.rfind("Model:", 0) == 0)
        {
            string mname, number, color, part;
            double price = 0;
            stringstream ss(line);
            while (getline(ss, part, '|'))
            {
                if (part.find("Model:") != string::npos)
                    mname = part.substr(6);
                else if (part.find("Price:") != string::npos)
                    price = stod(part.substr(6));
                else if (part.find("Number:") != string::npos)
                    number = part.substr(7);
                else if (part.find("Color:") != string::npos)
                    color = part.substr(6);
            }
            if (currentC)
                currentC->addModel(new Model(mname, price, number, color));
        }
        else if (line == "END_ENTERPRISE")
        {
            currentE = nullptr;
            currentV = nullptr;
            currentC = nullptr;
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

//====================userDetails===================================
class UserDetails
{
private:
    string filename;

public:
    UserDetails(string fname = "userDetails.txt") : filename(fname) {}
    // member function of class userDetails to register the user

    void UserEnterpriseDetailEntry()
    {
        vector<Enterprises *> enterprises = loadData("sellerDetails.txt");
        cout << "\nWELCOME TO THE USER PORTAL\n";
        cout << "====================================\n";
        cout << "Available Enterprises:\n";

        // Show all enterprises
        for (size_t i = 0; i < enterprises.size(); i++)
        {
            cout << i + 1 << ". ";
            enterprises[i]->getEnterpriseName();
            cout << "\n";
        }

        int eChoice;
        cout << "\nSelect Enterprise number: ";
        cin >> eChoice;

        if (eChoice <= 0 || eChoice > (int)enterprises.size())
        {
            cout << "Invalid enterprise choice!\n";
            for (auto e : enterprises)
                delete e;
            return;
        }
        Enterprises *selectedEnterprise = enterprises[eChoice - 1];
        selectedEnterprise->show();

        //---------------- Step 2: Choose Variety ----------------
        cout << "\nSelect Variety:\n";
        vector<Variety *> &varieties = *(new vector<Variety *>);
        // We need access to the private varieties of Enterprises
        // so let's add a getter in Enterprises (shown below).

        varieties = selectedEnterprise->getVarieties(); // <-- new getter

        if (varieties.empty())
        {
            cout << "No varieties available in this enterprise.\n";
            for (auto e : enterprises)
                delete e;
            return;
        }

        for (size_t i = 0; i < varieties.size(); i++)
            cout << i + 1 << ". " << "[ " << i + 1 << " ] " << "\n";

        int vChoice;
        cout << "\nEnter Variety number: ";
        cin >> vChoice;

        if (vChoice <= 0 || vChoice > (int)varieties.size())
        {
            cout << "Invalid variety choice!\n";
            for (auto e : enterprises)
                delete e;
            return;
        }
        Variety *selectedVariety = varieties[vChoice - 1];

        //---------------- Step 3: Choose Company ----------------
        cout << "\nSelect Company:\n";
        vector<Company *> &companies = selectedVariety->getCompanies(); // <-- new getter

        if (companies.empty())
        {
            cout << "No companies available in this variety.\n";
            for (auto e : enterprises)
                delete e;
            return;
        }

        for (size_t i = 0; i < companies.size(); i++)
            cout << i + 1 << ". Company: " << companies[i]->getCompanyName() << "\n";

        int cChoice;
        cout << "\nEnter Company number: ";
        cin >> cChoice;

        if (cChoice <= 0 || cChoice > (int)companies.size())
        {
            cout << "Invalid company choice!\n";
            for (auto e : enterprises)
                delete e;
            return;
        }
        Company *selectedCompany = companies[cChoice - 1];

        //---------------- Step 4: Choose Model ----------------
        cout << "\nSelect Model:\n";
        vector<Model *> &models = selectedCompany->getModels(); // <-- new getter

        if (models.empty())
        {
            cout << "No models available in this company.\n";
            for (auto e : enterprises)
                delete e;
            return;
        }

        for (size_t i = 0; i < models.size(); i++)
        {
            cout << i + 1 << ". ";
            displayModel(*models[i]);
        }

        int mChoice;
        cout << "\nEnter Model number: ";
        cin >> mChoice;

        if (mChoice <= 0 || mChoice > (int)models.size())
        {
            cout << "Invalid model choice!\n";
            for (auto e : enterprises)
                delete e;
            return;
        }

        Model *selectedModel = models[mChoice - 1];
        cout << "\n✅ You Selected:\n";
        displayModel(*selectedModel);

        // Cleanup memory
        for (auto e : enterprises)
            delete e;
    }

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

        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            file << username << "," << password << "," << phonenumber << "\n";
            file << username << "," << password << "," << phonenumber << "\n";
            file.close();
            cout << "\nRegistration successful!\n";
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
        string password, username, phonenumber;
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
    // default constructor
    EnterpriseDetails(string fname = "EnterpriseDetails.txt") : filePath(fname) {}
    // verification of the details`
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
            // vector<Enterprises *> enterprises = loadData("sellerDetails.txt");

            // for (auto e : enterprises)
            // {
            //     e->showEnterprise();
            //     delete e; // cleanup
            // }
            // return 0;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}