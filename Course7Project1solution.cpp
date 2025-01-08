#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowMainMenu();

struct stClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double Balance = 0;
    bool MarkForDelete = false;
};

enum enChoice
{
    eClientList = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eExit = 6
};

vector <string> SplitString(string UserString, string Delem)
{

    short Pos = 0;
    string Word = "";
    vector<string> vWords;

    while ((Pos = UserString.find(Delem)) != std::string::npos)
    {

        Word = UserString.substr(0, Pos);

        if (Word != "")
        {
            vWords.push_back(Word);
        }

        UserString.erase(0, Pos + Delem.length());

    }

    if (UserString != "")
    {
        vWords.push_back(UserString);
    }

    return vWords;

}

stClient ConvertLineToRecord(string Line)
{

    vector <string> vClients = SplitString(Line , "#//#");

    stClient Client;

    Client.AccountNumber = vClients[0];
    Client.PinCode = vClients[1];
    Client.Name = vClients[2];
    Client.Phone = vClients[3];
    Client.Balance = stod(vClients[4]);

    return Client;
}

vector <stClient> LoadFileDataToVector(string FileName)
{

    fstream MyFile;

    vector <stClient> vClients;

    MyFile.open(FileName , ios::in);

    if (MyFile.is_open())
    {

        string Line = "";
        stClient Client;

       while(getline(MyFile , Line))
       { 

           Client = ConvertLineToRecord(Line);
           vClients.push_back(Client);
       }

       MyFile.close();
    }
    return vClients;

}

string ReadAccountNumber()
{
    string AccountNumber = "";
    cout << "Enter account number ?";
    cin >> AccountNumber;
    return AccountNumber;
}

short ReadUserChoice()
{
    short Number;
    cout << "\nEnter a choice [1 - 6] ? \n";
    cin >> Number;
    return Number;
}

void GoBackToMainMenu()
{
    cout << "\nPress any key to go back to Maim Menu...";
    system("pause>0");
    ShowMainMenu();
}

void PrintClient(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.Balance;

}

bool ClientExistsByAccountNumber(string AccountNumber , string FileName)
{

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }

        MyFile.close();

    }
    return false;

}

stClient ReadNewClient()
{

    stClient Client;
    cout << "Enter Account Number? ";

    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.Balance;

    return Client;

}

void AddDataLineToFile(string FileName , string DataLine)
{

    fstream MyFile;

    MyFile.open(FileName , ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << DataLine << "\n";

        MyFile.close();
    }


}

string ConvertRecordToLine(stClient Client)
{

    string Line = "";

    Line += Client.AccountNumber + "#//#";
    Line += Client.PinCode + "#//#";
    Line += Client.Name + "#//#";
    Line += Client.Phone + "#//#";
    Line += to_string(Client.Balance) + "#//#";
    return Line;
}

void AddNewClient()
{

    stClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName , ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';

    do
    {
        cout << "\nAdding new client :\n";

        AddNewClient();

        cout << "\nClient added succsesfully, do you want to add more clients y/n ?\n";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');


}

void ShowAddNewClientScreen()
{

    cout << "\n------------------------------------\n";
    cout << "\tAdd New Client Screen";
    cout << "\n------------------------------------\n";

    AddNewClients();

}

void ShowAllClientsScreen()
{
    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (stClient Client : vClients)
        {

            PrintClient(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

bool FindClientByAccountNumber(string AccountNumber , vector <stClient> vClients , stClient & Client)
{

    for (stClient & C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }

    return false;
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.Balance;
    cout << "\n-----------------------------------\n";
}

void LoadDataToFile(string FileName, vector <stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (stClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

}

void MarkClientForDeleteByAccountNumber(string AccountNumber , vector <stClient> & vClients)
{

    for (stClient & Client : vClients)
    {

        if (Client.AccountNumber == AccountNumber)
        {
            Client.MarkForDelete = true;
        }

    }


}

bool DeleteClientByAccountNumber(string AccountNumber , vector <stClient> & vClients)
{

    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            LoadDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadFileDataToVector(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}

void ShowDeleteClientScreen()
{

    cout << "\n--------------------------------\n";
    cout << "\tDetete Client Screen";
    cout << "\n--------------------------------\n";

    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(AccountNumber , vClients);
}

stClient ChangeClientRecord(string AccountNumber)
{

    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.Balance;

    return Client;


}

bool UpdateClientByAccountNumber(string AccountNumber , vector <stClient> & vClients)
{

    stClient Client;

    if (FindClientByAccountNumber(AccountNumber , vClients , Client))
    {
        PrintClientCard(Client);

        char AskForUpdate = 'n';
        cout << "\nAre you sure you want to edit this client info y/n ?\n";
        cin >> AskForUpdate;

        if (AskForUpdate == 'y' || AskForUpdate == 'Y')
        {

            for (stClient & C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
               
            }
            LoadDataToFile(ClientsFileName , vClients);
        }

        cout << "Client updated succesfully\n";
        return true;
    }
    else
    {
        cout << "Client with account number [" << AccountNumber << "] is not exist\n";
        return false;
    }
    

}

void ShowUpdateClientScreen()
{
    cout << "\n--------------------------------\n";
    cout << "\tUpdate Client Screen";
    cout << "\n--------------------------------\n";

    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    UpdateClientByAccountNumber(AccountNumber , vClients);

}

void ShowFindClientScreen()
{

    cout << "\n--------------------------------\n";
    cout << "\Find Client Screen";
    cout << "\n--------------------------------\n";

    stClient Client;
    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);
    string AccountNumber = ReadAccountNumber();

    if (FindClientByAccountNumber(AccountNumber , vClients , Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nAccount with number [" << AccountNumber << "] is not found\n";
    }

}

void ShowExitScreen()
{

    cout << "\n------------------------------\n";
    cout << "\tExit Screen";
    cout << "\n------------------------------\n";
}

void PerformMainMenuOption(enChoice Choice)
{

    switch (Choice)
    {
    case eClientList:
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenu();
        break;
    case eAddNewClient:
        system("cls");
        ShowAddNewClientScreen();
        GoBackToMainMenu();
        break;
    case eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenu();
        break;
    case eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenu();
        break;
    case eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenu();
        break;
    case eExit:
        system("cls");
        ShowExitScreen();
        break;
    
    }

}

void ShowMainMenu()
{

    cout << "\n===================================\n";
    cout << right << setw(25) << "Main Menu Screen";
    cout << "\n===================================\n";
    cout << right << setw(5) << "[1]" << " Show Clients List." << "\n";
    cout << right << setw(5) << "[2]" << " Add New Client." << "\n";
    cout << right << setw(5) << "[3]" << " Delete Client." << "\n";
    cout << right << setw(5) << "[4]" << " Update Client Info." << "\n";
    cout << right << setw(5) << "[5]" << " Find Client." << "\n";
    cout << right << setw(5) << "[6]" << " Exit." << "\n";
    PerformMainMenuOption((enChoice)ReadUserChoice());
}


int main()
{

    ShowMainMenu();

	return 0;
}
