#ifndef UTILITY_H
#define UTILITY_H

#include <string>

class Utility {
public:
    static void clearScreen();
    static void pause();
    static std::string getCurrentDate();
    static std::string calculateReturnDate(int days);
    static void displayHeader(const std::string& title);
    static bool isValidEmail(const std::string& email);
    static bool isValidPhone(const std::string& phone);
};
#endif 