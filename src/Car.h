#ifndef CAR_H
#define CAR_H

#include <string>

class Car {
private:
    std::string name;
    std::string plateNumber;
    std::string color;
    int capacity;
    bool isAutomatic;
    bool isAvailable;

public:
    Car(std::string name = "", std::string plateNumber = "", 
        std::string color = "", int capacity = 0, bool isAutomatic = true);
    
    std::string getName() const;
    std::string getPlateNumber() const;
    std::string getColor() const;
    int getCapacity() const;
    bool getIsAutomatic() const;
    bool getIsAvailable() const;
    
    void setIsAvailable(bool available);
    std::string toString() const;
};

#endif