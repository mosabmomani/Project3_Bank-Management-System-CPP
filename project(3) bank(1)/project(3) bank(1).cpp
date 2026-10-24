#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include<limits>
using namespace std;
const string filename = "clientdata.txt";
enum enMainMenueOption {
    eLestClients = 1, eAddnewClients = 2,
    eDeleteClient = 3, eUpdatClient = 4,
    eFindClient = 5,transactions=6 ,eExit = 7
};
enum enTransactions {
    edeposit=1,ewithdraw=2,etotalbalance=3,emainmenue=4
};
struct sClientInfo {
    string accountnumber;
    string pincode;
    string name;
    string phone;
    double accountbalance;
    bool findaccount = false;
};

short ReadNumber(short from,short to ) {
    short number;
    do {
        cout << "choose what do you want to do?["<<from<< " to "<<to<<"]?";
        cin >> number;
    } while (number > to || number < from);
    return number;

}
string ReadAccountNumber() {
    string accountnumber = "";
    cout << "please enter account number \n";
    getline(cin>>ws, accountnumber);
    return accountnumber;
}
sClientInfo ReadAccountInformtion(string accountenumber) {
    sClientInfo client;
    client.accountnumber = accountenumber;
    cout << "please enter pincode ?";
    getline(cin >> ws, client.pincode);
    cout << "please enter Name ?";
    getline(cin, client.name);
    cout << "please enter phone ?";
    getline(cin, client.phone);
    cout << "please enter  account balance ?";
    cin >> client.accountbalance;
    return client;
}
string ConvertRecordToLine(sClientInfo client, string spreter = "#//#") {
    string line = "";

    line += client.accountnumber + spreter;
    line += client.pincode + spreter;
    line += client.name + spreter;
    line += client.phone + spreter;
    line += to_string(client.accountbalance);
    return line;

}
vector<string>SpritDataLine(string line, string spreter = "#//#") {
    vector<string>clintdata;
    short pos = 0;
    string word;
    while ((pos = line.find(spreter)) != std::string::npos) {
        word = line.substr(0, pos);
        if (word != "") {
            clintdata.push_back(word);
        }
        line.erase(0, pos + spreter.length());
    }
    if (line != "") {
        clintdata.push_back(line);
    }
    return clintdata;
}
sClientInfo DataClientLineToRecord(string line) {
    sClientInfo cliendata;
    vector<string>clintdata = SpritDataLine(line);
    cliendata.accountnumber = clintdata[0];
    cliendata.pincode = clintdata[1];
    cliendata.name = clintdata[2];
    cliendata.phone = clintdata[3];
    cliendata.accountbalance = stod(clintdata[4]);
    return cliendata;
}
void PrintClientRecord(string line) {
    sClientInfo cliendata = DataClientLineToRecord(line);
    cout << "Account Number   :" << cliendata.accountnumber << endl;
    cout << "pincode          :" << cliendata.pincode << endl;
    cout << "Name             :" << cliendata.name << endl;
    cout << "phone            :" << cliendata.phone << endl;
    cout << "Account Balance  :" << cliendata.accountbalance << endl;
}
void PrintClientRecordByAccountNumber(sClientInfo client) {
    cout << "Account Number   :" << client.accountnumber << endl;
    cout << "pincode          :" << client.pincode << endl;
    cout << "Name             :" << client.name << endl;
    cout << "phone            :" << client.phone << endl;
    cout << "Account Balance  :" << client.accountbalance << endl;
}
void LoadDataToFile(string line) {
    fstream myfile;
    myfile.open("clientdata.txt", ios::out | ios::app);
    if (myfile.is_open()) {
        myfile << line << endl;
    }
    myfile.close();
}
vector<sClientInfo>LoadAllClientFromFileToVector() {
    vector<sClientInfo>allclientsdata;
    fstream myfile;
    sClientInfo client;
    myfile.open("clientdata.txt", ios::in);
    if (myfile.is_open()) {
        string line;
        while (getline(myfile, line)) {
            client = DataClientLineToRecord(line);
            allclientsdata.push_back(client);
        }
    }
    return allclientsdata;
}
bool FindClientByAccountNumber(vector<sClientInfo>& clients, string accountnumber) {
    for (sClientInfo& client : clients) {
        if (accountnumber == client.accountnumber) {
            client.findaccount = true;
            return true;
        }
    }
    return false;
}
void AddNewClinets( ) {
    vector<sClientInfo>allclientsdata = LoadAllClientFromFileToVector();
    cout << "----------------------------------------------\n";
    cout << "\t\t\tAdd New Clients Screen"<<endl;
    cout << "----------------------------------------------\n";
    cout << "add new client:\n\n";
    char m = 'y';
    string dataline;
    sClientInfo clientrecord;
    string accountenumber;
    do {
        accountenumber = ReadAccountNumber();

        while ((FindClientByAccountNumber(allclientsdata, accountenumber))) {
            
            cout << "account number (" << accountenumber << ") already exists ,Enter another account Number?";
            accountenumber = ReadAccountNumber();
        
        } 
        system("cls");
        clientrecord = ReadAccountInformtion(accountenumber);
        dataline = ConvertRecordToLine(clientrecord);
        LoadDataToFile(dataline);
        cout << "client added successfully, do you want add more client(y,n) ?";
        cin >> m;
    } while (tolower(m) == 'y');
}


void PrintClientCard() {
    cout << "----------------------------------------------\n";
    cout << "\t\tshow Client Screen"<<endl;
    cout << "----------------------------------------------\n";
    string accountnumber = ReadAccountNumber();
    vector<sClientInfo>allclientsdata;
    allclientsdata = LoadAllClientFromFileToVector();
    for (sClientInfo& client : allclientsdata) {
        if (FindClientByAccountNumber(allclientsdata, accountnumber)) {
            if (client.findaccount == true) {
                PrintClientRecordByAccountNumber(client);
            }
        }
        else {
            cout << "account number(" << accountnumber << ") is not found.\n";
            break;
        }
    }
}
void LoadDataToFileAfterDelete(vector<sClientInfo> clienstdata) {
    fstream myfile;
    myfile.open("clientdata.txt", ios::out);
    if (myfile.is_open()) {
        for (sClientInfo client : clienstdata) {
            if (client.findaccount == false) {
                string line = ConvertRecordToLine(client);
                myfile << line << endl;
            }
        }
    }
}
void LoadDataToFileAfterUpdate(vector<sClientInfo> clienstdata) {
    fstream myfile;
    myfile.open("clientdata.txt", ios::out);
    if (myfile.is_open()) {
        for (sClientInfo client : clienstdata) {
            string line = ConvertRecordToLine(client);
            myfile << line << endl;
        }
    }
}
void DeleteAccountByAccountNumber() {
    vector<sClientInfo>allclientsdata;
    char m = 'n';
    cout << "----------------------------------------------\n";
    cout << "\t\tDelete Client Screen"<<endl;
    cout << "----------------------------------------------\n";
   string accountenumber = ReadAccountNumber();
    allclientsdata = LoadAllClientFromFileToVector();
    for (sClientInfo& client : allclientsdata) {
        if (FindClientByAccountNumber(allclientsdata, accountenumber)) {
            if (client.findaccount == true) {
                cout << "the following are the client details\n";
                PrintClientRecordByAccountNumber(client);
                cout << "are you sure you want delete this client?(y/n)?";
                cin >> m;
            }
            if (tolower(m) == 'y') {
                LoadDataToFileAfterDelete(allclientsdata);
                cout << "client deleted successfully.\n";
                break;
            }
        }
        else {
            cout << "account number(" << accountenumber << ") is not foind.\n";
            break;
        }
    }
}
sClientInfo updateClientDate(sClientInfo& client) {
    cout << "please enter pincode ?";
    getline(cin >> ws, client.pincode);
    cout << "please enter Name ?";
    getline(cin, client.name);
    cout << "please enter phone ?";
    getline(cin, client.phone);
    cout << "please enter  account balance ?";
    cin >> client.accountbalance;
    return client;
}
void UpdateAccountByAccountNumber() {
    vector<sClientInfo>allclientsdata;
    char m = 'n';
    cout << "----------------------------------------------\n";
    cout << "\t\tUpdate Client Screen"<<endl;
    cout << "----------------------------------------------\n";
   string accountenumber = ReadAccountNumber();
    allclientsdata = LoadAllClientFromFileToVector();
    for (sClientInfo& client : allclientsdata) {
        if (FindClientByAccountNumber(allclientsdata, accountenumber)) {
            if (client.findaccount == true) {
                cout << "the following are the client details\n";
                PrintClientRecordByAccountNumber(client);

                cout << "are you sure you want update this client?(y/n)?";
                cin >> m;

            }
            if (tolower(m) == 'y') {
                updateClientDate(client);
                LoadDataToFileAfterUpdate(allclientsdata);
                cout << "client Updated successfully.\n";
                break;
            }
        }
        else {
            cout << "account number(" << accountenumber << ") is not found.\n";
            break;
        }
    }
}
void PrintEachClientData(sClientInfo client) {
    cout << "|" << setw(19) << left << client.accountnumber;
    cout << "|" << setw(16) << left << client.pincode;
    cout << "|" << setw(34) << left << client.name;
    cout << "|" << setw(14) << left << client.phone;
    cout << "|" << setw(14) << left << client.accountbalance << endl;

}
void PrintEachClientDataTotrans(sClientInfo client) {
    cout << "account number:" << client.accountnumber<<endl;
    cout << "pinecode   :" << client.pincode<<endl;
    cout << " account name:"<< client.name<<endl;
    cout << "phone        :" <<  client.phone<<endl;
    cout << "Balance     :" << client.accountbalance << endl;

}
void PrintAllClientsData() {
    vector<sClientInfo>allclientsdata = LoadAllClientFromFileToVector();
    cout << "--------------------------------------clientlist(" << allclientsdata.size() << ")client(s)-------------------------------------------------\n";
    cout << setw(20) << left << "| account number";
    cout << setw(16) << left << "|pinecode";
    cout << setw(35) << left << " | account name";
    cout << setw(15) << left << " |phone";
    cout << setw(15) << left << " |Balance" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    for (sClientInfo& client : allclientsdata) {
        PrintEachClientData(client);
    }
    cout << "-------------------------------------------------------------------------------------------------------------\n";
}
void PrintMainMenueScreen() {
    cout << "-------------------------------------------------------------\n";
    cout << "-------------------------------------------------------------\n";
    cout << "\t\t\t\tMain Menu Screen "<<endl;
    cout << "-------------------------------------------------------------\n";
    cout << "-------------------------------------------------------------\n";
    cout << "\t\t\t[1]Show Client List." << endl;
    cout << "\t\t\t[2]Add New Client." << endl;
    cout << "\t\t\t[3]Delete Client." << endl;
    cout << "\t\t\t[4]Update Client info." << endl;
    cout << "\t\t\t[5]Find Client." << endl;
    cout << "\t\t\t[6]Transactions." << endl;
    cout << "\t\t\t[7]Exit." << endl;
    cout << "-------------------------------------------------------------\n";
    cout << "-------------------------------------------------------------\n";
}
void PrintEndScreen() {
    cout << "----------------------------------------------\n";
    cout << "\t\tProgram End" << endl;
    cout << "----------------------------------------------\n";
}
void NewBalance(string accountnumber, double transction, vector<sClientInfo>vclint) {
    char m;
    cout << "do you sure you want to do that transaction ?";
    cin >> m;
    if (m == 'y' || m == 'Y') {
        for (sClientInfo& client : vclint) {
            if (client.accountnumber == accountnumber) {
                client.accountbalance += transction;
                cout << "the new balance is   " << client.accountbalance;
                LoadDataToFileAfterUpdate(vclint);

            }

            }
        }
    }

void TransactionsScreen() {
    cout << "================================================\n";
    cout << "\tTransactions Menu Screen \n";
    cout << "================================================\n";
    cout << "\t\t[1]Deposit\n";
    cout << "\t\t[2]withdraw\n";
    cout << "\t\t[3]Total Balance\n";
    cout << "\t\t[4]Main Menu" << endl;
}
void PrintDepositScreen() {
    cout << "================================================\n";
    cout << "\tDeposit Screen \n";
    cout << "================================================\n";

}
void Deposise() {
    string accountnumber = ReadAccountNumber();
    vector<sClientInfo> clients = LoadAllClientFromFileToVector();
    while (!FindClientByAccountNumber(clients, accountnumber)) {
        cout << "the account number (" << accountnumber << ")is not found\n";
        accountnumber = ReadAccountNumber();
    }
    int dep;
    
    for (sClientInfo& client: clients) {
        if (client.accountnumber == accountnumber) {
            PrintEachClientDataTotrans(client);
            cout << "how match you want to deposit?";
            cin >> dep;
            NewBalance(client.accountnumber, dep, clients);
        }
    }
    
}
void PrintWithdrawScreen() {
    cout << "================================================\n";
    cout << "\tWithdraw Screen \n";
    cout << "================================================\n";

}
void Withdraw() {
    string accountnumber = ReadAccountNumber();
    vector<sClientInfo> clients = LoadAllClientFromFileToVector();
    while (!FindClientByAccountNumber(clients, accountnumber)) {
        cout << "the account number (" << accountnumber << "is not found\n";
        accountnumber = ReadAccountNumber();
    }
    int wethdraw;
    
   
    for (sClientInfo& client : clients) {
        if (client.accountnumber == accountnumber) {
            PrintEachClientDataTotrans(client);
            cout << "how match you want to Withdraw?";
            cin >> wethdraw;
                while (client.accountbalance < wethdraw) {
                    
                    cout << "we can't do that because  the all balance you have is " << client.accountbalance << endl;;
                    cout << "please enter a new withdraw ";
                    cin >> wethdraw;
               
                }

                    NewBalance(client.accountnumber, wethdraw*-1, clients);

        }
     
    }
    
}
double CountBalance(vector<sClientInfo>allclientsdata) {
    double balance=0;

    for (sClientInfo& client : allclientsdata) {
        balance += client.accountbalance;

    }
    return balance;
}
void PrintDataClientBalanceScreen(vector<sClientInfo>allclientsdata) {
    
    for (sClientInfo& client : allclientsdata) {
        cout << "|" << setw(19) << left << client.accountnumber;
        cout << "|" << setw(34) << left << client.name;
        cout << "|" << setw(14) << left << client.accountbalance << endl;
    }
}
void PrintBalanceScreen() {
    vector<sClientInfo>allclientsdata = LoadAllClientFromFileToVector();
    cout << "--------------------------------------clientlist(" << allclientsdata.size() << ")client(s)-------------------------------------------------\n";
    cout << setw(20) << left << "|account number";
    cout << setw(35) << left << "|account name";
    cout << setw(15) << left << "|Balance" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    PrintDataClientBalanceScreen(allclientsdata);
    cout << "\n\n\t\t\tthe total balance is   " <<CountBalance(allclientsdata)<<endl ;
}
void TransactionsPerformanceOption() {
    short choic;
    do {
       
        system("cls");
        TransactionsScreen();
        choic = ReadNumber(1, 4);
        switch (enTransactions(choic)) {
        case enTransactions::edeposit: {
            system("cls");
            PrintDepositScreen();
            Deposise();
            break;
        }
        case enTransactions::ewithdraw: {
            system("cls");
            PrintWithdrawScreen();
            Withdraw();
            break;
        }
        case enTransactions::etotalbalance: {
            system("cls");
            PrintBalanceScreen();
            break;
        }

        }
        if (choic != 4) {
            cout << "\npress any key to back to transactionsScreen";
            system("pause>0");
        }
    } while (choic != 4);
}
void PriformanceOption(enMainMenueOption enoption) {
    switch (enoption) {
    case enMainMenueOption::eLestClients: {
        system("cls");
        PrintAllClientsData();
        break;
    }
    case enMainMenueOption::eAddnewClients: {
        system("cls");
        AddNewClinets();

        break;
    }
    case enMainMenueOption::eDeleteClient: {
        system("cls");

        DeleteAccountByAccountNumber();
        break;
    }
    case enMainMenueOption::eUpdatClient: {
        system("cls");

        UpdateAccountByAccountNumber();
        break;
    }
    case enMainMenueOption::eFindClient: {
        system("cls");

        PrintClientCard();

        break;
    }
    case enMainMenueOption::transactions: {
        
        TransactionsPerformanceOption();
        break;
    }
    case enMainMenueOption::eExit: {
        system("cls");
        PrintEndScreen();
        break;
    }
    }

}

void Start() {
    short choicenumber;
    string accountenumber;
    
    do {
        system("cls");
        PrintMainMenueScreen();
        choicenumber = ReadNumber(1,7);
        enMainMenueOption enoption = enMainMenueOption(choicenumber);
        
        PriformanceOption(enoption);
        
        if (choicenumber != 7) {
            cout << "\n press any key to go back to main menu.";
            system("pause>0");
        }

    } while (choicenumber != 7);
}
int main()
{
    Start();
    return 0;
}
