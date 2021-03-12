#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>

#include "account.hpp"

class Card {
private:
    std::string m_cardHolder;
    std::string m_number;
    time_t m_expiration;
    std::string m_securityCode; 
    std::vector<Account*> m_accounts;
public:
    Card(const std::string&, const std::string&, const time_t&, const std::string&, const std::vector<Account*>&);
    Card(const Card&) = delete;
    Card& operator=(const Card&) = delete;
    std::string getCardNumber() const;
    std::vector<Account*> getAccountList() const;
    // getter and setter not defined for simplicity
};

Card::Card(const std::string& cardHolder, const std::string& number, const time_t& expiration, const std::string& securityCode, const std::vector<Account*>& accounts) : 
    m_cardHolder(cardHolder), m_number(number), m_expiration(expiration), m_securityCode(securityCode), m_accounts(accounts) {}

std::string Card::getCardNumber() const {
    return m_number;
}

std::vector<Account*> Card::getAccountList() const {
    return m_accounts;
}
#endif
