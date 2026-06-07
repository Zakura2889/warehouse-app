// Menu.h
#ifndef MENU_H
#define MENU_H

#include "Warehouse.h"
#include "FileIO.h"
#include <string>

class Menu {
private:
    Warehouse warehouse;
    FileIO fileIO;

public:
    // конструктор
    Menu();
    
    // запуск программы
    void run();
    
private:
    // методы для каждого пункта меню
    void showMainMenu();
    void addProductMenu();
    void editProductMenu();
    void deleteProductMenu();
    void searchMenu();
    void filterMenu();
    void sortMenu();
    void analyticsMenu();
    void saveData();
    
    // вспомогательные методы
    void displayProducts(const std::vector<Product>& products) const;
    int getUserInputInt(const std::string& prompt) const;
    double getUserInputDouble(const std::string& prompt) const;
    std::string getUserInputString(const std::string& prompt) const;
};

#endif