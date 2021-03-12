#include <iostream>
#include <vector>

#include "atm.hpp"
#include "gtest/gtest.h"

// Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw

TEST(ATMTest, insertCard) {
    ATM atm("a001");
    EXPECT_ANY_THROW(atm.insertCard(nullptr)); // no card

    std::vector<Account*> accounts;
    Account saving("123", 100);
    Account checking("456", 0);
    accounts.push_back(&saving);
    accounts.push_back(&checking);
    Card nonExistCard("Amelia", "c009", 1641013200, "000", accounts);
    EXPECT_ANY_THROW(atm.insertCard(&nonExistCard)); // card does not exist

    Card existCard("Amelia", "c001", 1641013200, "000", accounts);
    EXPECT_NO_THROW(atm.insertCard(&existCard));
}

TEST(ATMTest, enterPin) {
    ATM atm("a001");
    EXPECT_ANY_THROW(atm.validatePin("aaa")); // no card

    std::vector<Account*> accounts;
    Account saving("123", 100);
    Account checking("456", 0);
    accounts.push_back(&saving);
    accounts.push_back(&checking);
    Card card("Amelia", "c001", 1641013200, "000", accounts);

    EXPECT_NO_THROW(atm.insertCard(&card));
    EXPECT_ANY_THROW(atm.validatePin("aaa")); // invalid characters
    EXPECT_FALSE(atm.validatePin("000000")); // wrong pin
    EXPECT_TRUE(atm.validatePin("123456")); // correct pin
}

TEST(ATMTest, selectAccount) {
    ATM atm("a001");
    std::vector<Account*> accounts;
    Account saving("123", 100);
    Account checking("456", 0);
    accounts.push_back(&saving);
    accounts.push_back(&checking);
    Card card("Amelia", "c001", 1641013200, "000", accounts);

    EXPECT_ANY_THROW(atm.selectAccount(nullptr)); // no card
    EXPECT_NO_THROW(atm.insertCard(&card));
    EXPECT_ANY_THROW(atm.selectAccount(nullptr)); // no account

    Account wrongAccount("666", 0);
    EXPECT_ANY_THROW(atm.selectAccount(&wrongAccount)); // account does not belong to the card
    
    EXPECT_NO_THROW(atm.selectAccount(&saving));
    EXPECT_NO_THROW(atm.selectAccount(&checking));
}

TEST(ATMTest, seeBalance) {
    ATM atm("a001");
    std::vector<Account*> accounts;
    Account saving("123", 100);
    Account checking("456", 0);
    accounts.push_back(&saving);
    accounts.push_back(&checking);
    Card card("Amelia", "c001", 1641013200, "000", accounts);
    EXPECT_NO_THROW(atm.insertCard(&card));
    
    BalanceInquery savingBalance("t001");
    EXPECT_ANY_THROW(atm.executeTransaction(&savingBalance)); // no account
    EXPECT_NO_THROW(atm.selectAccount(&saving));
    EXPECT_EQ(atm.executeTransaction(&savingBalance), 100);

    EXPECT_NO_THROW(atm.selectAccount(&checking));
    BalanceInquery checkingBalance("t002");
    EXPECT_EQ(atm.executeTransaction(&checkingBalance), 0);
}

TEST(ATMTest, deposit) {
    ATM atm("a001");
    std::vector<Account*> accounts;
    Account saving("123", 100);
    Account checking("456", 0);
    accounts.push_back(&saving);
    accounts.push_back(&checking);
    Card card("Amelia", "c001", 1641013200, "000", accounts);
    EXPECT_NO_THROW(atm.insertCard(&card));

    EXPECT_ANY_THROW(Deposit invalidDeposit("t003", -100)); // amount should be positive
    EXPECT_NO_THROW(Deposit validDeposit("t004", 100));
    Deposit validDeposit("t004", 100);
    EXPECT_ANY_THROW(atm.executeTransaction(&validDeposit)); // no account
    EXPECT_NO_THROW(atm.selectAccount(&saving));
    EXPECT_EQ(atm.executeTransaction(&validDeposit), 100);
    EXPECT_NO_THROW(atm.selectAccount(&checking));
    EXPECT_EQ(atm.executeTransaction(&validDeposit), 100);
}

TEST(ATMTest, withdraw) {
    ATM atm("a001");
    std::vector<Account*> accounts;
    Account saving("123", 100);
    Account checking("456", 0);
    accounts.push_back(&saving);
    accounts.push_back(&checking);
    Card card("Amelia", "c001", 1641013200, "000", accounts);
    EXPECT_NO_THROW(atm.insertCard(&card));

    EXPECT_ANY_THROW(Withdraw invalidWithdraw("t005", 0)); // amount should be positive
    EXPECT_NO_THROW(Withdraw validWithdraw("t006", 100));
    Withdraw validWithdraw("t006", 100);
    EXPECT_ANY_THROW(atm.executeTransaction(&validWithdraw)); // no account
    EXPECT_NO_THROW(atm.selectAccount(&saving));
    EXPECT_EQ(atm.executeTransaction(&validWithdraw), 100);
    EXPECT_NO_THROW(atm.selectAccount(&checking));
    EXPECT_ANY_THROW(atm.executeTransaction(&validWithdraw)); // withdraw amount larger than balance
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}