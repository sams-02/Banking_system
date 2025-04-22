#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Transaction class to store transaction details
class Transaction {
public:
    string type;
    double amount;
    Transaction(const string& t, double a) : type(t), amount(a) {}
};

// Account class to manage balance and transactions
class Account {
    double balance;
    vector<Transaction> transactions;
public:
    Account(double initial = 0) : balance(initial) {}

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        // cout << "Deposited: " << amount << endl; // Commented out
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdraw", amount);
        // cout << "Withdrawn: " << amount << endl; // Commented out
        return true;
    }

    bool transfer(Account& to, double amount) {
        if (withdraw(amount)) {
            to.deposit(amount);
            transactions.emplace_back("Transfer Out", amount);
            to.transactions.emplace_back("Transfer In", amount);
            return true;
        }
        return false;
    }

    double getBalance() const { return balance; }

    void showTransactions() const {
        cout << "Recent Transactions:" << endl;
        if (transactions.empty()) {
            cout << "No transactions yet." << endl;
        } else {
            for (const auto& t : transactions) {
                cout << "  " << t.type << ": " << t.amount << endl;
            }
        }
    }
};

// Customer class to represent a bank customer
class Customer {
    string name;
    Account account;
public:
    Customer(const string& n, double initial) : name(n), account(initial) {}

    string getName() const { return name; }

    void deposit(double amount) { account.deposit(amount); }
    void withdraw(double amount) { account.withdraw(amount); }
    void transfer(Customer& to, double amount) { account.transfer(to.account, amount); }

    void showInfo() const {
        cout << "-----------------------------" << endl;
        cout << "Customer Name: " << name << endl;
        cout << "Current Balance: " << fixed << setprecision(2) << account.getBalance() << endl;
        account.showTransactions();
        cout << "-----------------------------" << endl;
    }
};

int main() {
    vector<Customer> customers;

    // Add default customers
    customers.emplace_back("Ram", 2000);
    customers.emplace_back("Sham", 1500);
    customers.emplace_back("Seeta", 3000);
    customers.emplace_back("Geeta", 2500);
    customers.emplace_back("Rahul", 1800);
    customers.emplace_back("Priya", 2200);
    customers.emplace_back("Amit", 1700);
    customers.emplace_back("Sunita", 2100);
    customers.emplace_back("Vikas", 1600);
    customers.emplace_back("Anjali", 1900);

    int n;
    cout << "How many customers do you want to add? ";
    cin >> n;
    cin.ignore();

    // User input for customer details
    for (int i = 0; i < n; ++i) {
        string name;
        double initial;
        cout << "Enter name for customer " << (i + 1) << ": ";
        getline(cin, name);

        // Check for duplicate names
        bool exists = false;
        for (const auto& customer : customers) {
            if (customer.getName() == name) {
                exists = true;
                break;
            }
        }
        if (exists) {
            cout << "Account with this name already exists. Please enter a different name.\n";
            --i; // repeat this iteration
            continue;
        }

        cout << "Enter initial balance for " << name << ": ";
        cin >> initial;
        cin.ignore();
        customers.emplace_back(name, initial);
    }

    while (true) {
        cout << "\nChoose an option:\n";
        cout << "1. Deposit\n2. Withdraw\n3. Transfer\n4. View Account\n5. View All Accounts\n6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 6) break;

        string name;
        int idx = -1;
        if (choice >= 1 && choice <= 4) {
            cout << "Enter customer name: ";
            getline(cin, name);
            for (int i = 0; i < customers.size(); ++i) {
                if (customers[i].getName() == name) {
                    idx = i;
                    break;
                }
            }
            if (idx == -1) {
                cout << "Customer not found.\n";
                continue;
            }
        }

        if (choice == 1) {
            double amt;
            cout << "Enter amount to deposit: ";
            cin >> amt;
            customers[idx].deposit(amt);
        } else if (choice == 2) {
            double amt;
            cout << "Enter amount to withdraw: ";
            cin >> amt;
            customers[idx].withdraw(amt);
        } else if (choice == 3) {
            string toName;
            double amt;
            cout << "Enter recipient name: ";
            cin.ignore();
            getline(cin, toName);
            int toIdx = -1;
            for (int i = 0; i < customers.size(); ++i) {
                if (customers[i].getName() == toName) {
                    toIdx = i;
                    break;
                }
            }
            if (toIdx == -1) {
                cout << "Recipient not found.\n";
                continue;
            }
            cout << "Enter amount to transfer: ";
            cin >> amt;
            customers[idx].transfer(customers[toIdx], amt);
        } else if (choice == 4) {
            customers[idx].showInfo();
        } else if (choice == 5) {
            for (const auto& customer : customers) {
                customer.showInfo();
            }
        } else {
            cout << "Invalid choice.\n";
        }
    }
    cout << "Thank you for using the bank system!" << endl;
    return 0;
}
