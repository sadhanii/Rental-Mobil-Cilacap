#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"
#include "Car.h"
#include "DBase.h"
#include <vector>

class Admin : public Account {
public:
    Admin(std::string name = "", std::string password = "");
    void displayMenu() override;
    void addCar();
    void viewCars();
    void verifyCarReturn();
    void deleteCar();
};

#endif