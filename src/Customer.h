#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Account.h"
#include <string>

class Customer : public Account {
private:
    std::string email;
    std::string phone;

public:
    Customer(std::string name = "", std::string email = "", 
             std::string phone = "", std::string password = "");
    
    void displayMenu() override;
    void viewProfile();
    void changePassword();
    void viewCars();
    void rentHistory();
    void rentCar();
    
    std::string getEmail() const;
    std::string getPhone() const;
};
#endif