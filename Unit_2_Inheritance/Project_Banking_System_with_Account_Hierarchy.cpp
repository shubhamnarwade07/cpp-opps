#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Base Account class
class Account {
protected:
    string accountNumber;
    string holderName;
    double balance;

public:
    Account(string accNum, string name, double initialBalance)
        : accountNumber(accNum), holderName(name), balance(initialBalance) {}

    virtual ~Account() = default;

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited Rs. " << amount << " into account " << accountNumber << ". New balance: Rs. " << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew Rs. " << amount << " from account " << accountNumber << ". New balance: Rs. " << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds in account " << accountNumber << "." << endl;
        }
    }

    virtual void calculateInterest() const = 0; // Pure virtual function

    virtual void displayAccountInfo() const {
        cout << "Account: " << accountNumber << " | Holder: " << holderName << " | Balance: Rs. " << balance << endl;
    }
};

// Derived SavingsAccount class
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string name, double initialBalance, double rate = 4.0)
        : Account(accNum, name, initialBalance), interestRate(rate) {}

    void calculateInterest() const override {
        double interest = balance * (interestRate / 100.0);
        cout << "Annual interest for Savings Account " << accountNumber << " at " << interestRate << "%: Rs. " << interest << endl;
    }

    void displayAccountInfo() const override {
        cout << "[Savings] ";
        Account::displayAccountInfo();
    }
};

// Derived CurrentAccount class
class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(string accNum, string name, double initialBalance, double limit = 10000.0)
        : Account(accNum, name, initialBalance), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            cout << "Withdrew Rs. " << amount << " from Current Account " << accountNumber << ". New balance: Rs. " << balance << endl;
        } else {
            cout << "Withdrawal exceeds overdraft limit or is invalid for account " << accountNumber << "." << endl;
        }
    }

    void calculateInterest() const override {
        cout << "Current Accounts do not earn interest." << endl;
    }

    void displayAccountInfo() const override {
        cout << "[Current] ";
        Account::displayAccountInfo();
        cout << "Overdraft limit: Rs. " << overdraftLimit << endl;
    }
};

// Derived FixedDepositAccount class
class FixedDepositAccount : public Account {
private:
    double interestRate;
    int tenureMonths;

public:
    FixedDepositAccount(string accNum, string name, double initialBalance, double rate, int tenure)
        : Account(accNum, name, initialBalance), interestRate(rate), tenureMonths(tenure) {}

    void withdraw(double amount) override {
        cout << "Premature withdrawal from Fixed Deposit Account " << accountNumber << " incurs a penalty." << endl;
        Account::withdraw(amount); // Call base class withdraw
    }

    void calculateInterest() const override {
        double interest = balance * (interestRate / 100.0) * (tenureMonths / 12.0);
        cout << "Total interest for Fixed Deposit " << accountNumber << " over " << tenureMonths << " months at " << interestRate << "%: Rs. " << interest << endl;
    }

    void displayAccountInfo() const override {
        cout << "[Fixed Deposit] ";
        Account::displayAccountInfo();
        cout << "Tenure: " << tenureMonths << " months" << endl;
    }
};

int main() {
    vector<unique_ptr<Account>> bankAccounts;

    bankAccounts.push_back(make_unique<SavingsAccount>("SA1001", "Alice", 50000.0, 4.5));
    bankAccounts.push_back(make_unique<CurrentAccount>("CA2001", "Bob's Business", 20000.0, 50000.0));
    bankAccounts.push_back(make_unique<FixedDepositAccount>("FD3001", "Charlie", 100000.0, 7.0, 24));

    cout << "=== Bank Account Management System ===" << endl;

    for (const auto& account : bankAccounts) {
        account->displayAccountInfo();
        account->calculateInterest();
        cout << endl;
    }

    cout << "=== Transactions ===" << endl;
    bankAccounts[0]->deposit(5000.0);
    bankAccounts[0]->withdraw(10000.0);
    
    bankAccounts[1]->withdraw(40000.0); // Should succeed due to overdraft
    bankAccounts[1]->withdraw(50000.0); // Should fail

    bankAccounts[2]->withdraw(10000.0); // Shows premature withdrawal message

    return 0;
}
