#include "DBase.h"
#include "Utility.h"
#include <fstream>
#include <sstream>
#include <iostream>

const std::string DBase::CUSTOMER_FILE = "customers.txt";
const std::string DBase::CAR_FILE = "cars.txt";
const std::string DBase::RENTAL_FILE = "rentals.txt";

bool DBase::isCustomerExists(const std::string& name) {
    std::ifstream file(CUSTOMER_FILE);
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedName;
        getline(ss, storedName, ',');
        
        if (storedName == name) {
            return true;
        }
    }
    return false;
}

bool DBase::isCarExists(const std::string& plateNumber) {
    std::vector<Car> cars = loadCars();
    for (const auto& car : cars) {
        if (car.getPlateNumber() == plateNumber) {
            return true;
        }
    }
    return false;
}

bool DBase::isCarRented(const std::string& plateNumber) {
    std::vector<Car> cars = loadCars();
    for (const auto& car : cars) {
        if (car.getPlateNumber() == plateNumber) {
            return !car.getIsAvailable();
        }
    }
    return false;
}

std::vector<std::string> DBase::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void DBase::saveCustomer(const Customer& customer) {
    std::ofstream file("customers.txt", std::ios::app);
    if (file.is_open()) {
        file << customer.getName() << ","
             << customer.getEmail() << ","
             << customer.getPhone() << ","
             << customer.getPassword() << "\n";
        file.close();
    }
}

bool DBase::loadCustomer(const std::string& name, Customer& customer) {
    std::ifstream file("customers.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedName, email, phone, password;
        
        getline(ss, storedName, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, password, ',');
        
        if (storedName == name) {
            customer = Customer(storedName, email, phone, password);
            return true;
        }
    }
    return false;
}

void DBase::updateCustomer(const Customer& customer) {
    std::ifstream inFile("customers.txt");
    std::ofstream tempFile("temp.txt");
    std::string line;
    
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string name;
        getline(ss, name, ',');
        
        if (name != customer.getName()) {
            tempFile << line << "\n";
        }
    }
    
    tempFile << customer.getName() << ","
             << customer.getEmail() << ","
             << customer.getPhone() << ","
             << customer.getPassword() << "\n";
             
    inFile.close();
    tempFile.close();
    
    remove("customers.txt");
    rename("temp.txt", "customers.txt");
}

void DBase::saveCar(const Car& car) {
    std::ofstream file("cars.txt", std::ios::app);
    if (file.is_open()) {
        file << car.getName() << ","
             << car.getPlateNumber() << ","
             << car.getColor() << ","
             << car.getCapacity() << ","
             << car.getIsAutomatic() << ","
             << car.getIsAvailable() << "\n";
        file.close();
    }
}

std::vector<Car> DBase::loadCars() {
    std::vector<Car> cars;
    std::ifstream file("cars.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, plateNumber, color;
        int capacity;
        bool isAutomatic, isAvailable;
        
        getline(ss, name, ',');
        getline(ss, plateNumber, ',');
        getline(ss, color, ',');
        ss >> capacity;
        ss.ignore();
        ss >> isAutomatic;
        ss.ignore();
        ss >> isAvailable;
        
        Car car(name, plateNumber, color, capacity, isAutomatic);
        car.setIsAvailable(isAvailable);
        cars.push_back(car);
    }
    
    return cars;
}

void DBase::updateCar(const Car& car) {
    std::vector<Car> cars = loadCars();
    std::ofstream file("cars.txt");
    
    for (const auto& c : cars) {
        if (c.getPlateNumber() != car.getPlateNumber()) {
            file << c.getName() << ","
                 << c.getPlateNumber() << ","
                 << c.getColor() << ","
                 << c.getCapacity() << ","
                 << c.getIsAutomatic() << ","
                 << c.getIsAvailable() << "\n";
        }
    }
    
    file << car.getName() << ","
         << car.getPlateNumber() << ","
         << car.getColor() << ","
         << car.getCapacity() << ","
         << car.getIsAutomatic() << ","
         << car.getIsAvailable() << "\n";
    
    file.close();
}

void DBase::deleteCar(const std::string& plateNumber) {
    std::vector<Car> cars = loadCars();
    std::ofstream file("cars.txt");
    
    for (const auto& car : cars) {
        if (car.getPlateNumber() != plateNumber) {
            file << car.getName() << ","
                 << car.getPlateNumber() << ","
                 << car.getColor() << ","
                 << car.getCapacity() << ","
                 << car.getIsAutomatic() << ","
                 << car.getIsAvailable() << "\n";
        }
    }
    
    file.close();
}

void DBase::saveRental(const std::string& customerName, const Car& car, const std::string& returnDate) {
    std::ofstream file("rentals.txt", std::ios::app);
    if (file.is_open()) {
        file << customerName << ","
             << car.getPlateNumber() << ","
             << Utility::getCurrentDate() << ","
             << returnDate << "\n";
        file.close();
    }
}

std::vector<std::string> DBase::loadRentals(const std::string& customerName) {
    std::vector<std::string> rentals;
    std::ifstream file("rentals.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, plateNumber, rentDate, returnDate;
        
        getline(ss, name, ',');
        if (name == customerName) {
            getline(ss, plateNumber, ',');
            getline(ss, rentDate, ',');
            getline(ss, returnDate, ',');
            
            rentals.push_back("Mobil: " + plateNumber + 
                            " | Tanggal Sewa: " + rentDate +
                            " | Tanggal Kembali: " + returnDate);
        }
    }
    
    return rentals;
}
