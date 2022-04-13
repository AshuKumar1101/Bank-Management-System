#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class account
{
    int acno;
    char name[50];
    int deposit;
    char type;

public:
    void create_account();     //function to get data from user
    void show_account() const; //function to show data on screen
    void modify();             //function to add new data
    void dep(int);             //function to accept amount money and add to balance amount
    void draw(int);            // function to accept amount and subtract from balance amount
    void report() const;       // function to show data in tabular format
    int retacno() const;       // function to return account number
    int retdeposit() const;    // function to return balance amount
    char rettype() const;      // function to return type of account
};
void account::create_account()
{
    cout << "\n Enter the account no. : ";
    cin >> acno;
    cout << "\n\nEnter the name of the account holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter type of the account(C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter the initial amount(>=500 for saving and >=1000 for current) : ";
    cin >> deposit;
    cout << "\n\nAccount Created..";
}
void account ::show_account() const
{
    cout << "\nAccount No. : " << acno;
    cout << "\nAccount Holder Name : ";
    cout << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit;
}
void account ::modify()
{
    cout << "\nAccount No.: " << acno;
    cout << "\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of account: ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : ";
    cin >> deposit;
    cout<<"\n\nAccount modified...";
}
void account::dep(int x)
{
    deposit += x;
}
void account ::draw(int x)
{
    deposit -= x;
}
void account::report() const
{
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retacno() const
{
    return acno;
}
int account::retdeposit() const
{
    return deposit;
}
char account::rettype() const
{
    return type;
}

/*function declaration*/
void write_account1();//function to write about account detail
void display_sp(int);//function to display all account detail given by the user
void modify_account1(int);//function to modify the account
void delete_account1(int);//function to delete an account
void display_all();//function to display all account detail
void deposit_withdraw(int,int);//function to withdraw the money
void intro();//function for introduction

int main()
{
    char ch;
    int num;
    intro();
    do
    {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8)";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            write_account1();
            break;
        case '2':
            cout << "\n\n\tEnter the account no. : ";
            cin >> num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            cout << "\n\n\tEnter the account no. : ";
            cin >> num;
            deposit_withdraw(num, 2);
            break;
        case '4':
            cout << "\n\n\tEnter the account no: ";
            cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout << "\n\n\tEnter the account no.: ";
            cin >> num;
            delete_account1(num);
            break;
        case '7':
            cout << "\n\n\tEnter the account no.: ";
            cin >> num;
            modify_account1(num);
            break;
        case '8':
            cout << "Thanks for using My bank management system... ";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
}

void write_account1()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
    outFile.close();
}

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File can't be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount Number does not exist";
}

void modify_account1(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            cout << "\n\nEnter the new detail of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\n\tRecord updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\nRecord not found";
}

void delete_account1(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "accoutn.dat");
    cout << "\n\n\tRecord Deleted..";
}

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open!! Press any key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "===============================================\n";
    cout << "A/c no.    NAME         Type Balance\n";
    cout << "================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open!! Press any key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\tTo DEPOSIT AMOUNT";
                cout << "\n\nEnter the amount to be deposited";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2)
            {
                cout << "\n\n\tTO WITHDRAW AMOUNT";
                cout << "\n\nEnter the amount to be withdraw ";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
                    cout << "Insufficient bakance";
                else
                    ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\n\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\nRecord not found";
}

void intro()
{
    cout << "\n\n\n\t My BANK";
    cout << "\n\n\n\t MANAGEMENT";
    cout << "\n\n\n\t SYSTEM";
    cout << "\n\n\n\t MADE BY ASHU KUMAR";
    cout << "\n\n\n\t CGC JHANJHERI";
    cin.get();
}
