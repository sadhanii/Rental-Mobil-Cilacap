#include <iostream>
#include <limits>
#include "Authentication.h"
#include "Admin.h"
#include "Customer.h"
#include "Utility.h"

int main() {
    while (true) {
        Utility::clearScreen();
        Utility::displayHeader("Rental Mobil CILACAP");
        std::cout << "1. Register\n";
        std::cout << "2. Login sebagai Admin\n";
        std::cout << "3. Login sebagai Customer\n";
        std::cout << "4. Keluar\n";
        std::cout << "-------------------------\n";
        
        int choice;
        std::cout << "Pilih menu: ";
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input tidak valid. Masukkan angka: ";
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: {
                Utility::clearScreen();
                Utility::displayHeader("Register Customer");
    
                std::string name, email, phone, password;
                std::cout << "Nama: ";
                std::getline(std::cin, name);
                std::cout << "Email: ";
                std::getline(std::cin, email);
                std::cout << "No. Telepon: ";
                std::getline(std::cin, phone);
                std::cout << "Password: ";
                std::getline(std::cin, password);
    
    if (Authentication::registerCustomer(name, email, phone, password)) {
        std::cout << "Registrasi berhasil!\n";
    } else {
        std::cout << "Registrasi gagal. Pastikan data valid dan email belum terdaftar.\n";
    }
    Utility::pause();
    break;
            }


            
            case 2: {
                Utility::clearScreen();
                Utility::displayHeader("Login Admin");
                
                std::string name, password;
                std::cout << "Nama: ";
                std::getline(std::cin, name);
                std::cout << "Password: ";
                std::getline(std::cin, password);
                
                Admin* admin = Authentication::loginAdmin(name, password);
                if (admin) {
                    admin->displayMenu();
                } else {
                    std::cout << "Login gagal. Nama atau password salah.\n";
                }
                Utility::pause();
                break;
            }
            case 3: {
                Utility::clearScreen();
                Utility::displayHeader("Login Customer");
                
                std::string name, password;
                std::cout << "Nama: ";
                std::getline(std::cin, name);
                std::cout << "Password: ";
                std::getline(std::cin, password);
                
                Customer* customer = Authentication::loginCustomer(name, password);
                if (customer) {
                    customer->displayMenu();
                } else {
                    std::cout << "Login gagal. Nama atau password salah.\n";
                }
                Utility::pause();
                break;
            }
            case 4:
                std::cout << "Terima kasih telah menggunakan layanan kami.\n";
                return 0;
            default:
                std::cout << "Pilihan tidak valid!\n";
                Utility::pause();
        }
    }
}
