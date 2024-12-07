#include "Car.h"
#include <sstream>

Car::Car(std::string name, std::string plateNumber, std::string color, 
         int capacity, bool isAutomatic)
    : name(name), plateNumber(plateNumber), color(color), 
      capacity(capacity), isAutomatic(isAutomatic), isAvailable(true) {}

std::string Car::getName() const { return name; }
std::string Car::getPlateNumber() const { return plateNumber; }
std::string Car::getColor() const { return color; }
int Car::getCapacity() const { return capacity; }
bool Car::getIsAutomatic() const { return isAutomatic; }
bool Car::getIsAvailable() const { return isAvailable; }

void Car::setIsAvailable(bool available) { isAvailable = available; }

std::string Car::toString() const {
    std::stringstream ss;
    ss << "Nama: " << name
       << " | Plat: " << plateNumber
       << " | Warna: " << color
       << " | Kapasitas: " << capacity
       << " | Transmisi: " << (isAutomatic ? "Matic" : "Manual")
       << " | Status: " << (isAvailable ? "Tersedia" : "Disewa");
    return ss.str();
}