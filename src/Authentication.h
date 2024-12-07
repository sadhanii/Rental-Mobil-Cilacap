#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "Admin.h"
#include "Customer.h"

class Authentication {
private:
    static Admin admin;

public:
    static bool registerCustomer(const std::string& name, const std::string& email,
                               const std::string& phone, const std::string& password);
    static Customer* loginCustomer(const std::string& name, const std::string& password);
    static Admin* loginAdmin(const std::string& name, const std::string& password);
};

#endif