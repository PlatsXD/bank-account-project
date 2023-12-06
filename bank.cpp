#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

class Bank_Account {
private:
    double balance;
    string historyFileName;

public:
    Bank_Account(string user_name) {
        balance = 0;
        historyFileName = "data.txt";
        readTransactionHistory();
    }

    double getBalance() {
        return balance;
    }

    void setBalance(double newBalance) {
        balance = newBalance;
    }

    void deposit(double amount) {
        if (amount < 0) {
            cout << "You cannot enter a negative amount. Please try again." << endl;
            return;
        }
        setBalance(getBalance() + amount);
        cout << "* Your deposit amount is $" << amount << ". Your new balance is $" << getBalance() << "." << endl;
        recordTransaction("Deposit", amount);
    }

    void withdrawal(double amount) {
        if (amount > getBalance()) {
            cout << "You cannot enter an amount more than your current balance." << endl;
            cout << "Enter your desired withdrawal amount: ";
            cin >> amount;
        }
        setBalance(getBalance() - amount);
        cout << "* Your withdrawal amount is $" << amount << ". Your new balance is $" << getBalance() << "." << endl;
        recordTransaction("Withdrawal", amount);
    }

    void recordTransaction(string type, double amount) {
        ofstream historyFile(historyFileName, ios::app);
        if (historyFile.is_open()) {
            time_t now;
            struct tm* local;
            time(&now);
            local = localtime(&now);
            historyFile << type << " $" << amount <<  " --- " << asctime(local);
            historyFile.close();
        }
        else {
            cout << "!! Error: Failed to see history." << endl;
        }
    }

    void readTransactionHistory() {
        ifstream historyFile(historyFileName);
        if (historyFile.is_open()) {
            string line;
            while (getline(historyFile, line)) {
                cout << line << endl;
            }
            historyFile.close();
        }
    }

    void readDepositHistory() {
        ifstream historyFile(historyFileName);
        if (historyFile.is_open()) {
            string line;
            while (getline(historyFile, line)) {
                if (line.find("Deposit") != string::npos) {
                    cout << line << endl;
                }
            }
            historyFile.close();
        }
    }

    void readWithdrawalHistory() {
        ifstream historyFile(historyFileName);
        if (historyFile.is_open()) {
            string line;
            while (getline(historyFile, line)) {
                if (line.find("Withdrawal") != string::npos) {
                    cout << line << endl;
                }
            }
            historyFile.close();
        }
    }
};

int main() {
    string user_name;
    double startingBalance = 0;
    double depositAmount = 0;
    double withdrawAmount = 0;
    int menu;

    cout << "Welcome to the Bank Account program!" << endl;
    cout << "Please enter your name: ";
    cin >> user_name;

    Bank_Account account(user_name);

    cout << "Please enter your balance: ";
    cin >> startingBalance;
    account.setBalance(startingBalance);

    while (true) {
        cout << "=====================================" << endl;
        cout << "=+= Welcome to your Bank Account! =+=" << endl;
        cout << "=====================================" << endl;
        cout << "   Hello, " << user_name << "." << endl;
        cout << "   Your current balance is $" << account.getBalance() << endl;
        cout << "   What would you like to do?" << endl;
        cout << "     * 1) Make a Deposit\n     * 2) Make a Withdrawal\n     * 3) Deposit History\n     * 4) Withdrawal History\n     * 5) Deposit and Withdrawal History\n     * 6) View Balance\n     * 7) Exit" << endl;
        cout << "\n Enter option number:";
        cin >> menu;

        switch (menu) {
            case 1:
                cout << "Enter your desired deposit amount: ";
                cin >> depositAmount;
                account.deposit(depositAmount);
                break;
            case 2:
                cout << "Enter your desired withdrawal amount: ";
                cin >> withdrawAmount;
                account.withdrawal(withdrawAmount);
                break;
            case 3:
                cout << "\n* Deposit History:\n";
                account.readDepositHistory();
                cout << endl;
                break;
            case 4:
                cout << "\n* Withdrawal History:\n";
                account.readWithdrawalHistory();
                cout << endl;
                break;
            case 5:
                cout << "\n* Deposit and Withdrawal History:\n";
                account.readTransactionHistory();
                cout << endl;
                break;
            case 6:
                cout << "\n* Your current balance is $" << account.getBalance() << ".\n" << endl;
                break;
            case 7:
                cout << "* Your starting balance was $" << startingBalance << "." << endl;
                cout << "* Your final balance is $" << account.getBalance() << "." << endl;
                return 0;
            default:
                cout << "\n* Invalid Value.\n" << endl;
        }
    }

    return 0;
}
