#include "Utility.h"
#include <iostream>
#include <string>
#include <regex>
#include <ctime>

void Utility::clearScreen() {
    for(int i = 0; i < 50; i++) {
        std::cout << "\n";
    }
}

void Utility::pause() {
    std::cout << "\nTekan Enter untuk melanjutkan...";
    std::cin.get();
}

std::string Utility::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    char buffer[80];
    strftime(buffer, 80, "%d/%m/%Y", ltm);
    return std::string(buffer);
}

std::string Utility::calculateReturnDate(int days) {
    time_t now = time(0);
    now += days * 24 * 60 * 60;
    tm* ltm = localtime(&now);
    
    char buffer[80];
    strftime(buffer, 80, "%d/%m/%Y", ltm);
    return std::string(buffer);
}

void Utility::displayHeader(const std::string& title) {
    std::cout << "==== " << title << " ====\n";
}

bool Utility::isValidEmail(const std::string& email) {
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, pattern);
}

bool Utility::isValidPhone(const std::string& phone) {
    const std::regex pattern("\\+?\\d{10,13}");
    return std::regex_match(phone, pattern);
}