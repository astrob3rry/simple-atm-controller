#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "account.hpp"

class Transaction {
private:
    std::string m_transactionId;
public:
    Transaction(const std::string&);
    Transaction(const Transaction&) = delete;
    Transaction& operator=(const Transaction&) = delete;
    virtual int execute(Account*) = 0;
};

Transaction::Transaction(const std::string& transactionId) : m_transactionId(transactionId) {}

class BalanceInquery : public Transaction {
public:
    BalanceInquery(const std::string&);
    int execute(Account*) override;
};

BalanceInquery::BalanceInquery(const std::string& transactionId) : Transaction(transactionId) {}

int BalanceInquery::execute(Account* account) {
    if (!account) {
        throw std::invalid_argument("account cannot be null");
    }

    return account->getBalance();
}

class Deposit : public Transaction {
private:
    int m_amount;
public:
    Deposit(const std::string&, int);
    int execute(Account*) override;
};

Deposit::Deposit(const std::string& transactionId, int amount) : m_amount(amount), Transaction(transactionId) {
    if (amount <= 0) {
        throw std::invalid_argument("amount should be positive");
    }
}

int Deposit::execute(Account* account) {
    if (!account) {
        throw std::invalid_argument("account cannot be null");
    }

    account->deposit(m_amount);
    return m_amount;
}

class Withdraw : public Transaction {
private:
    int m_amount;
public:
    Withdraw(const std::string&, int);
    int execute(Account*) override;
};

Withdraw::Withdraw(const std::string& transactionId, int amount) : m_amount(amount), Transaction(transactionId) {
    if (amount <= 0) {
        throw std::invalid_argument("amount should be positive");
    }
}

int Withdraw::execute(Account* account) {
    if (!account) {
        throw std::invalid_argument("account cannot be null");
    }

    try {
        account->withdraw(m_amount);
    } catch (const std::invalid_argument& e) {
        throw e;
    }

    return m_amount;
}

#endif