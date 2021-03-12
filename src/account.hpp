#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <exception>

class Account {
private:
    std::string m_number;
    int m_balance;
public:
    Account(const std::string&, int);
    Account(const Account&) = delete;
    Account& operator=(const Account&) = delete;
    int getBalance() const;
    void deposit(int);
    void withdraw(int);
};

Account::Account(const std::string& number, int balance) : m_number(number), m_balance(balance) {}

int Account::getBalance() const {
    return m_balance;
}

void Account::deposit(int amount) {
    m_balance += amount;
}

void Account::withdraw(int amount) {
    if (amount > m_balance) {
        throw std::invalid_argument("insufficient balance");
    }

    m_balance -= amount;
}

#endif