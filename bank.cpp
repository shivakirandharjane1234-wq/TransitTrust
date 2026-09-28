#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class BankAcc
{
private:
    int pin;
    int accno;

public:
    string name;
    double initialBal;

    string securityQuestion;
    string securityAnswer;

    void setPin(int p)
    {
        pin = p;
    }

    int getPin() const
    {
        return pin;
    }

    void setAccNo(int num)
    {
        accno = num;
    }

    int getAccNo()
    {
        return accno;
    }
};

int mainmenu1();
void createacc();
void saveacc();
void loadAcctsToVec();
void login();
void loggedin(BankAcc *user);
void transferMoney(BankAcc *sender);
void forgotPIN();

vector<BankAcc> acc;
int lastAccNo = 10000;

int mainmenu1()
{

    cout << "= = = = = = = welcome in our bank = = = = = = =" << endl
         << endl;
    int choice;
    while (true)
    {

        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3.Forgot PIN" << endl;
        cout << "4. Exit" << endl;

        cout << "Enter the choice: ";
        cin >> choice;

        if (choice == 1)
        {
            createacc();
        }
        else if (choice == 2)
        {
            login();
        }
        else if (choice == 3)
        {
            forgotPIN();
        }
        else if (choice == 4)
        {
            cout << "Goodbye!" << endl;
            return 0;
        }
        else
        {
            cout << "Invalid choice, try again" << endl;
        }
    }
    return 0;
}

void createacc()
{
    BankAcc newAcc;

    newAcc.setAccNo(++lastAccNo); // give acc no

    cout << "Enter Your Name: ";
    cin.ignore();
    getline(cin, newAcc.name);

    // entering PIN
    int tempPin;
    while (true)
    {
        cout << "Enter 4-digit PIN: ";
        cin >> tempPin;
        if (tempPin >= 1000 && tempPin <= 9999)
        {
            newAcc.setPin(tempPin);
            break;
        }
        cout << "\n!! INVALID PIN, re-enter it !!\n\n";
    }

    // entering initial balance
    cout << "Enter the Initial Balance: ";
    cin >> newAcc.initialBal;

    // security questions and answers
    cout << "Enter Security Question: ";
    cin.ignore();
    getline(cin, newAcc.securityQuestion);

    cout << "Enter Security Answer: ";
    getline(cin, newAcc.securityAnswer);

    // store in vector
    acc.push_back(newAcc);
    cout << endl;
    cout << "-----Account created successfully-----" << endl;
    cout << "Your Acc No is: " << lastAccNo << endl
         << endl;
    saveacc();
    return;
}

void login()
{

    int accnum, accpin;
    cout << "Enter your ACC NO: ";
    cin >> accnum;
    cout << "Enter your PIN: ";
    cin >> accpin;

    bool found = false;
    BankAcc *user = nullptr;
    for (auto &a : acc)
    {
        if (a.getAccNo() == accnum)
        {
            found = true;
            if (a.getPin() == accpin)
            {
                user = &a;
                break;
            }
            else
            {
                cout << "Incorrect PIN. Returning to main menu." << endl
                     << endl;
                return;
            }
        }
    }

    if (!found)
    {
        cout << "Account number not found. Returning to main menu." << endl
             << endl;
        return;
    }

    else
    {
        loggedin(user);
    }
}

void forgotPIN()
{
    int accnum;

    cout << "Enter your Account Number: ";
    cin >> accnum;

    BankAcc *user = nullptr;
    for (int i = 0; i < acc.size(); i++)
    {
        if (acc[i].getAccNo() == accnum)
        {
            user = &acc[i];
            break;
        }
    }

    if (user == nullptr)
    {
        cout << "Account not found !" << endl
             << endl;
        return;
    }

    cout << "\n Security Question: " << user->securityQuestion << endl;
    string answer;
    cout << "Enter Answer: ";
    cin.ignore();
    getline(cin, answer);

    if (answer != user->securityAnswer)
    {
        cout << "Incorrect Answer!" << endl;
        cout << "Password cannot be changed." << endl
             << endl;
        return;
    }

    int newPin;
    while (true)
    {

        cout << "Enter new 4 digit PIN: ";
        cin >> newPin;

        if (newPin >= 1000 && newPin <= 9999)
        {
            break;
        }
        cout << "Invalid PIN! please enter 4-digit PIN." << endl;
    }
    user->setPin(newPin);
    saveacc();
    cout << "\nPIN changed successfully!" << endl
         << endl;
    ;
}

void loggedin(BankAcc *user)
{

    cout << "= = = = = = = = You Are Successfully LOGGED IN = = = = = = = =" << endl;
    cout << "1. check bank balance" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. withdraw Money" << endl;
    cout << "4. Transfer Money" << endl;
    cout << "5. LOG OUT " << endl;
    int choice;
    cout << "Enter the choice: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Your Balance is: " << user->initialBal << endl
             << endl;
        loggedin(user);
    }
    else if (choice == 2)
    {
        int deposit;
        cout << "Enter amount to Deposit: ";
        cin >> deposit;
        user->initialBal += deposit;
        saveacc();
        cout << endl;
        cout << "Deposit of " << deposit << " completed successfully. !!" << endl
             << endl;

        loggedin(user);
    }
    else if (choice == 3)
    {
        int withdraw;
        cout << "Enter amount to Withdraw:  ";
        cin >> withdraw;
        if (withdraw > user->initialBal)
        {
            cout << "!! Insufficient balance !! " << endl
                 << endl;

            loggedin(user);
        }
        else
        {
            user->initialBal -= withdraw;
            saveacc();
            cout << "Withdrawal of " << withdraw << " completed successfully. !! " << endl
                 << endl;

            loggedin(user);
        }
    }
    else if (choice == 4)
    {
        transferMoney(user);
        loggedin(user);
    }
    else if (choice == 5)
    {
        cout << "Logged out successfully !!" << endl
             << endl;
        return;
    }
    else
    {
        cout << "Invalid choice!" << endl
             << endl;
        loggedin(user);
    }
}

void transferMoney(BankAcc *sender)
{
    int receiverAccNo;
    double amount;

    cout << "Enter Receiver Account NO: ";
    cin >> receiverAccNo;

    // check if sender sending money to himelf
    if (receiverAccNo == sender->getAccNo())
    {
        cout << "!! YOU CAN NOT TRANSFER MONEY TO SELFACCOUNT !!" << endl
             << endl;
        return;
    }
    // find receiver account
    BankAcc *receiver = nullptr;
    for (int i = 0; i < acc.size(); i++)
    {
        if (receiverAccNo == acc[i].getAccNo())
        {
            receiver = &acc[i];
            break;
        }
    }
    // receiver not found
    if (receiver == nullptr)
    {
        cout << "!! Receiver Not Found check the account Number !!" << endl
             << endl;
        return;
    }

    cout << "Enter Amount to Transfer: " << endl;
    cin >> amount;
    if (amount <= 0)
    {
        cout << "Enter the valid Amount,please." << endl
             << endl;
        return;
    }
    if (amount > sender->initialBal)
    {
        cout << "!! Insufficient Balance !!" << endl
             << endl;
        return;
    }
    sender->initialBal = sender->initialBal - amount;
    receiver->initialBal = receiver->initialBal + amount;

    // save
    saveacc();

    cout << endl;
    cout << "Transfer Successful !!" << endl;
    cout << "Amount Transferred: " << amount << endl;
    cout << "To Account No: " << receiverAccNo << endl;
    cout << "Your Remaining Balance: "
         << sender->initialBal << endl
         << endl;
}

void saveacc()
{

    ofstream file("accounts.txt");

    for (auto &a : acc)
    {
        file << a.getAccNo() << "|" << a.name << "|" << a.getPin() << "|" << a.initialBal << "|" << a.securityQuestion << "|" << a.securityAnswer << endl;
    }

    file.close();
}

void loadAcctsToVec()
{
    ifstream file("accounts.txt");

    string line;

    while (getline(file, line))
    {
        // run upto end of strings in file

        int pos1 = line.find("|");
        int pos2 = line.find("|", pos1 + 1);
        int pos3 = line.find("|", pos2 + 1);
        int pos4 = line.find("|", pos3 + 1);
        int pos5 = line.find("|", pos4 + 1);

        if (pos1 == -1 || pos2 == -1 || pos3 == -1 || pos4 == -1 || pos5 == -1)
        {
            // if wrong string (i.e., | not present)
            continue;
        }

        // getting those name pin & balance
        int accno = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        int pin = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        double balance = stod(line.substr(pos3 + 1));
        string question = line.substr(pos4+1,pos5-pos4-1);
        string answer=line.substr(pos5+1);

        // object created to put in vector
        BankAcc temp;
        temp.setAccNo(accno);
        temp.name = name;
        temp.setPin(pin);
        temp.initialBal = balance;
        temp.securityQuestion=question;
        temp.securityAnswer=answer;

        acc.push_back(temp);
        if (accno > lastAccNo)
        {
            lastAccNo = accno;
        }
    }

    file.close();
}

int main()
{
    loadAcctsToVec();
    mainmenu1();
    return 0;
}