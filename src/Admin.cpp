#include "Admin.h"
#include "Utility.h"
#include <iostream>

Admin::Admin(std::string name, std::string password) 
    : Account(name, password) {}

void Admin::displayMenu() {
    while (true) {
        Utility::clearScreen();
        Utility::displayHeader("Halo, Admin");
        std::cout << "1. Tambahkan Mobil\n";
        std::cout << "2. Lihat Mobil\n";
        std::cout << "3. Verifikasi Mobil\n";
        std::cout << "4. Hapus Mobil\n";
        std::cout << "5. Logout\n";
        std::cout << "================\n";
        
        int choice;
        std::cout << "Pilih menu: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: addCar(); break;
            case 2: viewCars(); break;
            case 3: verifyCarReturn(); break;
            case 4: deleteCar(); break;
            case 5: return;
            default: std::cout << "Pilihan tidak valid!\n";
        }
        Utility::pause();
    }
}

void Admin::addCar() {
    Utility::clearScreen();
    Utility::displayHeader("Tambah Mobil");
    
    std::string name, plateNumber, color;
    int capacity;
    bool isAutomatic;
    
    std::cout << "Masukkan nama mobil: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    std::cout << "Masukkan plat nomor: ";
    std::getline(std::cin, plateNumber);
    
    std::cout << "Masukkan warna: ";
    std::getline(std::cin, color);
    
    std::cout << "Masukkan kapasitas: ";
    std::cin >> capacity;
    
    std::cout << "Apakah automatic? (1/0): ";
    std::cin >> isAutomatic;
    
    Car newCar(name, plateNumber, color, capacity, isAutomatic);
    newCar.setIsAvailable(true);
    
    DBase::saveCar(newCar);
    std::cout << "Mobil berhasil ditambahkan!\n";
}

void Admin::viewCars() {
    Utility::clearScreen();
    Utility::displayHeader("Daftar Mobil");
    
    std::vector<Car> cars = DBase::loadCars();
    // Debug: Print jumlah mobil yang dibaca
    std::cout << "Jumlah mobil yang dibaca: " << cars.size() << std::endl;
    
    if (cars.empty()) {
        std::cout << "Tidak ada mobil yang tersedia.\n";
        return;
    }
    if (cars.empty()) {
        std::cout << "Tidak ada mobil yang tersedia.\n";
        return;
    }
    
    std::cout << "Nama\t\tPlat\t\tWarna\t\tKapasitas\tTransmisi\tStatus\n";
    std::cout << "================================================================================\n";
    
    for (const Car& car : cars) {
        std::cout << car.getName() << "\t\t"
                  << car.getPlateNumber() << "\t\t"
                  << car.getColor() << "\t\t"
                  << car.getCapacity() << "\t\t"
                  << (car.getIsAutomatic() ? "Auto" : "Manual") << "\t\t"
                  << (car.getIsAvailable() ? "Tersedia" : "Disewa") << "\n";
    }
}

void Admin::verifyCarReturn() {
    Utility::clearScreen();
    Utility::displayHeader("Verifikasi Pengembalian Mobil");
    
    std::string plateNumber;
    std::cout << "Masukkan plat nomor mobil yang dikembalikan: ";
    std::cin.ignore();
    std::getline(std::cin, plateNumber);
    
    std::vector<Car> cars = DBase::loadCars();
    bool found = false;
    
    for (Car& car : cars) {
        if (car.getPlateNumber() == plateNumber) {
            if (car.getIsAvailable()) {
                std::cout << "Mobil ini tidak sedang disewa.\n";
                return;
            }
            
            car.setIsAvailable(true);
            DBase::updateCar(car);
            std::cout << "Pengembalian mobil berhasil diverifikasi!\n";
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "Mobil tidak ditemukan.\n";
    }
}

void Admin::deleteCar() {
    Utility::clearScreen();
    Utility::displayHeader("Hapus Mobil");
    
    std::string plateNumber;
    std::cout << "Masukkan plat nomor mobil yang akan dihapus: ";
    std::cin.ignore();
    std::getline(std::cin, plateNumber);
    
    std::vector<Car> cars = DBase::loadCars();
    bool found = false;
    
    for (const Car& car : cars) {
        if (car.getPlateNumber() == plateNumber) {
            char confirm;
            std::cout << "Anda yakin ingin menghapus mobil " << car.getName() 
                      << "? (y/n): ";
            std::cin >> confirm;
            
            if (confirm == 'y' || confirm == 'Y') {
                DBase::deleteCar(plateNumber);
                std::cout << "Mobil berhasil dihapus!\n";
            }
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "Mobil tidak ditemukan.\n";
    }
}