#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
protected:
    std::string name;
    std::string password;

public:
    Account(std::string name = "", std::string password = "");
    virtual ~Account() = default;
    
    std::string getName() const;
    std::string getPassword() const;
    void setPassword(const std::string& newPassword);
    
    virtual void displayMenu() = 0;
};

#endif