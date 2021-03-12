# simple-atm-controller

## How to Run

- Build [GoogleTest](https://github.com/google/googletest)
- Run the following command
```
g++ -std=c++17 test.cpp libgtest_main.a -o test -lgtest -lpthread

./test
``` 

## API Usage
An ATM exposes the following APIs:
- insertCard
- validatePin
- getAccountList
- selectAccount
- executeTransaction
- ejectCard

A transaction can be one of the following:
- BalanceInquery
- Deposit
- Withdraw

## Notes
- This is not thread-safe.