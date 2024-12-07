#include "Customer.h"
#include "Utility.h"
#include "DBase.h"
#include <iostream>

Customer::Customer(std::string name, std::string email, 
                  std::string phone, std::string password)
    : Account(name, password), email(email), phone(phone) {}

void Customer::displayMenu() {
    while (true) {
        Utility::clearScreen();
        Utility::displayHeader("Halo, " + name);
        std::cout << "1. Lihat profil\n";
        std::cout << "2. Ubah Password\n";
        std::cout << "3. Lihat Mobil\n";
        std::cout << "4. Riwayat Pemesanan\n";
        std::cout << "5. Sewa Mobil\n";
        std::cout << "6. Logout\n";
        std::cout << "=============\n";
        
        int choice;
        std::cout << "Pilih menu: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: viewProfile(); break;
            case 2: changePassword(); break;
            case 3: viewCars(); break;
            case 4: rentHistory(); break;
            case 5: rentCar(); break;
            case 6: return;
            default: std::cout << "Pilihan tidak valid!\n";
        }
        Utility::pause();
    }
}

void Customer::viewProfile() {
    Utility::clearScreen();
    Utility::displayHeader("Profil Saya");
    
    std::cout << "Nama: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "No. Telepon: " << phone << std::endl;
}

void Customer::changePassword() {
    Utility::clearScreen();
    Utility::displayHeader("Ubah Password");
    
    std::string oldPass, newPass, confirmPass;
    
    std::cout << "Masukkan password lama: ";
    std::cin >> oldPass;
    
    if (oldPass != password) {
        std::cout << "Password lama tidak sesuai!\n";
        return;
    }
    
    std::cout << "Masukkan password baru: ";
    std::cin >> newPass;
    std::cout << "Konfirmasi password baru: ";
    std::cin >> confirmPass;
    
    if (newPass != confirmPass) {
        std::cout << "Konfirmasi password tidak sesuai!\n";
        return;
    }
    
    password = newPass;
    DBase::updateCustomer(*this);
    std::cout << "Password berhasil diubah!\n";
}

void Customer::viewCars() {
    Utility::clearScreen();
    Utility::displayHeader("Daftar Mobil Tersedia");
    
    std::vector<Car> cars = DBase::loadCars();
    bool foundAvailable = false;
    
    std::cout << "Nama\t\tPlat\t\tWarna\t\tKapasitas\tTransmisi\n";
    std::cout << "=================================================================\n";
    
    for (const Car& car : cars) {
        if (car.getIsAvailable()) {
            std::cout << car.getName() << "\t\t"
                      << car.getPlateNumber() << "\t\t"
                      << car.getColor() << "\t\t"
                      << car.getCapacity() << "\t\t"
                      << (car.getIsAutomatic() ? "Auto" : "Manual") << "\n";
            foundAvailable = true;
        }
    }
    
    if (!foundAvailable) {
        std::cout << "Tidak ada mobil yang tersedia untuk disewa.\n";
    }
}

void Customer::rentHistory() {
    Utility::clearScreen();
    Utility::displayHeader("Riwayat Pemesanan");
    
    std::vector<std::string> rentals = DBase::loadRentals(name);
    
    if (rentals.empty()) {
        std::cout << "Belum ada riwayat pemesanan.\n";
        return;
    }
    
    for (const auto& rental : rentals) {
        std::cout << rental << std::endl;
    }
}

void Customer::rentCar() {
    Utility::clearScreen();
    Utility::displayHeader("Sewa Mobil");
    
    std::string plateNumber;
    std::cout << "Masukkan plat nomor mobil yang ingin disewa: ";
    std::cin.ignore();
    std::getline(std::cin, plateNumber);
    
    std::vector<Car> cars = DBase::loadCars();
    bool found = false;
    
    for (Car& car : cars) {
        if (car.getPlateNumber() == plateNumber) {
            if (!car.getIsAvailable()) {
                std::cout << "Mobil ini sedang tidak tersedia.\n";
                return;
            }
            
            std::string returnDate;
            std::cout << "Masukkan tanggal pengembalian (DD/MM/YYYY): ";
            std::getline(std::cin, returnDate);
            
            car.setIsAvailable(false);
            DBase::updateCar(car);
            DBase::saveRental(name, car, returnDate);
            
            std::cout << "Mobil berhasil disewa!\n";
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "Mobil tidak ditemukan.\n";
    }
}

std::string Customer::getEmail() const {
    return email;
}

std::string Customer::getPhone() const {
    return phone;
}