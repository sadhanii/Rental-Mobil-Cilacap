#include "Authentication.h"
#include "DBase.h"
#include "Utility.h"

Admin Authentication::admin("Revandika", "Cilacap");

bool Authentication::registerCustomer(const std::string& name, const std::string& email,
                                   const std::string& phone, const std::string& password) {
    if (!Utility::isValidEmail(email) || !Utility::isValidPhone(phone)) {
        return false;
    }
    
    Customer customer(name, email, phone, password);
    DBase::saveCustomer(customer);
    return true;
}

Customer* Authentication::loginCustomer(const std::string& name, const std::string& password) {
    Customer customer;
    if (DBase::loadCustomer(name, customer) && customer.getPassword() == password) {
        return new Customer(customer);
    }
    return nullptr;
}

Admin* Authentication::loginAdmin(const std::string& name, const std::string& password) {
    if (name == admin.getName() && password == admin.getPassword()) {
        return new Admin(admin);
    }
    return nullptr;
}