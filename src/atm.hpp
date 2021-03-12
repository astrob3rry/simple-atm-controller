#ifndef ATM_H
#define ATM_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

#include "card.hpp"
#include "account.hpp"
#include "transaction.hpp"

class ATM {
private:
    std::string m_atmID;
    Card* m_card;
    Account* m_account;
    static std::unordered_map<std::string, std::string> cardNumToPin; // simulate bank API
public:
    ATM(const std::string&);
    ATM(const ATM&) = delete;
    ATM& operator=(const ATM&) = delete;
    void insertCard(Card*);
    bool validatePin(const std::string&) const;
    std::vector<Account*> getAccountList() const; 
    void selectAccount(Account*);
    int executeTransaction(Transaction*);
    void ejectCard();
};

std::unordered_map<std::string, std::string> ATM::cardNumToPin = {{"c001", "123456"},
                                                                  {"c002", "000000"},
                                                                  {"c003", "888888"}};

ATM::ATM(const std::string& atmID) : m_atmID(atmID), m_card(nullptr), m_account(nullptr) {}

void ATM::insertCard(Card* card) {
    if (!card) {
        throw std::logic_error("card not found");
    }

    if (!cardNumToPin.count(card->getCardNumber())) {
        throw std::invalid_argument("card not activated");
    }
    m_card = card;
}

// only supports numeric inputs
bool ATM::validatePin(const std::string& pin) const {
    if (!m_card) {
        throw std::logic_error("card not found");
    }

    if (pin.find_first_not_of("0123456789") != std::string::npos) {
        throw std::invalid_argument("illegal characters found");
    }

    return pin == cardNumToPin[m_card->getCardNumber()];
}

std::vector<Account*> ATM::getAccountList() const {
    if (!m_card) {
        throw std::logic_error("card not found");
    }

    return m_card->getAccountList();
}

void ATM::selectAccount(Account* account) {
    if (!m_card) {
        throw std::logic_error("card not found");
    }

    if (!account) {
        throw std::logic_error("account not found");
    }

    std::vector<Account*> accounts = getAccountList();
    if (find(accounts.begin(), accounts.end(), account) == accounts.end()) {
        throw std::invalid_argument("invalid account");
    }

    m_account = account;
}

int ATM::executeTransaction(Transaction* transaction) {
    if (!m_card) {
        throw std::logic_error("card not found");
    }

    if (!m_account) {
        throw std::logic_error("account not found");
    }

    if (!transaction) {
        throw std::invalid_argument("transaction cannot be null");
    }

    try {
        return transaction->execute(m_account);
    } catch (const std::logic_error& e) {
        throw e;
    }
}

void ATM::ejectCard() {
    if (!m_card) {
        throw std::logic_error("card not found");
    }

    m_account = nullptr;
    m_card = nullptr;
}


#endif