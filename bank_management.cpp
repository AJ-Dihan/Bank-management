#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    // Constructor
    BankAccount(string accNumber, string accHolderName, double initialBalance) {
        accountNumber = accNumber;
        accountHolderName = accHolderName;
        balance = initialBalance;
    }

    // Accessors
    string getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    // Member functions
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds." << endl;
        }
    }
};

class Bank {
private:
    vector<BankAccount> accounts;

public:
    // Member functions
    void createAccount() {
        string accNumber, accHolderName;
        double initialBalance;

        cout << "Enter account number: ";
        cin >> accNumber;

        // Check if the account number already exists
        if (findAccount(accNumber) != accounts.end()) {
            cout << "Account with the given number already exists. Please choose a different number.\n";
            return;
        }

        cout << "Enter account holder name: ";
        cin.ignore(); // Ignore any newline character left in the buffer
        getline(cin, accHolderName);

        cout << "Enter initial balance: $";
        cin >> initialBalance;

        // Create a new account and add it to the vector
        BankAccount newAccount(accNumber, accHolderName, initialBalance);
        accounts.push_back(newAccount);

        cout << "Account created successfully.\n";
    }

    void depositToAccount() {
        string accNumber;
        double amount;

        cout << "Enter account number: ";
        cin >> accNumber;

        auto it = findAccount(accNumber);
        if (it != accounts.end()) {
            cout << "Enter deposit amount: $";
            cin >> amount;
            it->deposit(amount);
        } else {
            cout << "Account not found.\n";
        }
    }

    void withdrawFromAccount() {
        string accNumber;
        double amount;

        cout << "Enter account number: ";
        cin >> accNumber;

        auto it = findAccount(accNumber);
        if (it != accounts.end()) {
            cout << "Enter withdrawal amount: $";
            cin >> amount;
            it->withdraw(amount);
        } else {
            cout << "Account not found.\n";
        }
    }

    void displayBalance() {
        string accNumber;

        cout << "Enter account number: ";
        cin >> accNumber;

        auto it = findAccount(accNumber);
        if (it != accounts.end()) {
            cout << "Account Holder: " << it->getAccountHolderName() << endl;
            cout << "Account Balance: $" << it->getBalance() << endl;
        } else {
            cout << "Account not found.\n";
        }
    }

private:
    // Helper function to find an account by account number
    vector<BankAccount>::iterator findAccount(const string& accNumber) {
        return find_if(accounts.begin(), accounts.end(),
                       [accNumber](const BankAccount& acc) { return acc.getAccountNumber() == accNumber; });
    }
};

int main() {
    Bank bank;

    int choice;

    do {
        cout << "\nBank Management System Menu:\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.depositToAccount();
                break;
            case 3:
                bank.withdrawFromAccount();
                break;
            case 4:
                bank.displayBalance();
                break;
            case 0:
                cout << "Exiting the Bank Management System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 0);

    return 0;
}

