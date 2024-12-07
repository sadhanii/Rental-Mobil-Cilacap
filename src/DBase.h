#ifndef DBASE_H
#define DBASE_H

#include <string>
#include <vector>
#include "Car.h"
#include "Customer.h"

class DBase {
public:
    static void saveCustomer(const Customer& customer);
    static bool loadCustomer(const std::string& name, Customer& customer);
    static std::vector<Customer> getAllCustomers();
    static void updateCustomer(const Customer& customer);
    
    static void saveCar(const Car& car);
    static std::vector<Car> loadCars();
    static void updateCar(const Car& car);
    static void deleteCar(const std::string& plateNumber);
    
    static void saveRental(const std::string& customerName, const Car& car, 
                          const std::string& returnDate);
    static std::vector<std::string> loadRentals(const std::string& customerName);
    static bool isCustomerExists(const std::string& name);
    static bool isCarExists(const std::string& plateNumber);
    static bool isCarRented(const std::string& plateNumber);
private:
    static const std::string CUSTOMER_FILE;
    static std::vector<std::string> splitString(const std::string& str, char delimiter);
    static const std::string CAR_FILE;
    static const std::string RENTAL_FILE;
};


#endif