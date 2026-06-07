// Menu.cpp
#include "Menu.h"
#include <iostream>
#include <limits>

Menu::Menu() : fileIO("data/products.txt") {
    // загружаем данные при старте
    auto products = fileIO.loadProducts();
    for (const auto& product : products) {
        warehouse.getProducts().push_back(product);
    }
}

void Menu::run() {
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
    
    bool running = true;
    while (running) {
        showMainMenu();
        int choice;
        std::cout << "выбор: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                addProductMenu();
                break;
            case 2:
                editProductMenu();
                break;
            case 3:
                deleteProductMenu();
                break;
            case 4:
                searchMenu();
                break;
            case 5:
                filterMenu();
                break;
            case 6:
                sortMenu();
                break;
            case 7:
                analyticsMenu();
                break;
            case 8:
                saveData();
                break;
            case 9:
                running = false;
                std::cout << "до свидания!" << std::endl;
                break;
            default:
                std::cout << "неверный выбор, попробуйте снова" << std::endl;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (running) {
            std::cout << "\nнажмите enter для продолжения...";
            std::cin.get();
        }
    }
}

void Menu::showMainMenu() {
    std::cout << "\n=== складской учет ===" << std::endl;
    std::cout << "1. добавить товар" << std::endl;
    std::cout << "2. редактировать товар" << std::endl;
    std::cout << "3. удалить товар" << std::endl;
    std::cout << "4. поиск по названию" << std::endl;
    std::cout << "5. фильтрация" << std::endl;
    std::cout << "6. сортировка" << std::endl;
    std::cout << "7. аналитика" << std::endl;
    std::cout << "8. сохранить данные" << std::endl;
    std::cout << "9. выход" << std::endl;
}

void Menu::addProductMenu() {
    std::cout << "\n--- добавление товара ---" << std::endl;
    std::string name = getUserInputString("название: ");
    std::string category = getUserInputString("категория: ");
    double price = getUserInputDouble("цена: ");
    int quantity = getUserInputInt("количество: ");
    
    warehouse.addProduct(name, category, price, quantity);
    std::cout << "товар добавлен!" << std::endl;
}

void Menu::editProductMenu() {
    std::cout << "\n--- редактирование товара ---" << std::endl;
    int id = getUserInputInt("id товара: ");
    
    std::string name = getUserInputString("новое название: ");
    std::string category = getUserInputString("новая категория: ");
    double price = getUserInputDouble("новая цена: ");
    int quantity = getUserInputInt("новое количество: ");
    
    if (warehouse.editProduct(id, name, category, price, quantity)) {
        std::cout << "товар обновлен!" << std::endl;
    } else {
        std::cout << "товар с таким id не найден" << std::endl;
    }
}

void Menu::deleteProductMenu() {
    std::cout << "\n--- удаление товара ---" << std::endl;
    int id = getUserInputInt("id товара: ");
    
    if (warehouse.deleteProduct(id)) {
        std::cout << "товар удален!" << std::endl;
    } else {
        std::cout << "товар с таким id не найден" << std::endl;
    }
}

void Menu::searchMenu() {
    std::cout << "\n--- поиск по названию ---" << std::endl;
    std::string name = getUserInputString("введите часть названия: ");
    
    auto results = warehouse.searchByName(name);
    if (results.empty()) {
        std::cout << "ничего не найдено" << std::endl;
    } else {
        displayProducts(results);
    }
}

void Menu::filterMenu() {
    std::cout << "\n--- фильтрация ---" << std::endl;
    std::cout << "1. по категории" << std::endl;
    std::cout << "2. по диапазону цен" << std::endl;
    std::cout << "выбор: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 1) {
        std::string category = getUserInputString("категория: ");
        auto results = warehouse.filterByCategory(category);
        if (results.empty()) {
            std::cout << "ничего не найдено" << std::endl;
        } else {
            displayProducts(results);
        }
    } else if (choice == 2) {
        double minPrice = getUserInputDouble("минимальная цена: ");
        double maxPrice = getUserInputDouble("максимальная цена: ");
        auto results = warehouse.filterByPriceRange(minPrice, maxPrice);
        if (results.empty()) {
            std::cout << "ничего не найдено" << std::endl;
        } else {
            displayProducts(results);
        }
    } else {
        std::cout << "неверный выбор" << std::endl;
    }
}

void Menu::sortMenu() {
    std::cout << "\n--- сортировка ---" << std::endl;
    std::cout << "1. по цене (возрастание)" << std::endl;
    std::cout << "2. по цене (убывание)" << std::endl;
    std::cout << "3. по количеству (возрастание)" << std::endl;
    std::cout << "4. по количеству (убывание)" << std::endl;
    std::cout << "5. по названию" << std::endl;
    std::cout << "выбор: ";
    
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1:
            warehouse.sortByPrice(true);
            break;
        case 2:
            warehouse.sortByPrice(false);
            break;
        case 3:
            warehouse.sortByQuantity(true);
            break;
        case 4:
            warehouse.sortByQuantity(false);
            break;
        case 5:
            warehouse.sortByName();
            break;
        default:
            std::cout << "неверный выбор" << std::endl;
            return;
    }
    
    std::cout << "сортировка выполнена!" << std::endl;
    displayProducts(warehouse.getProducts());
}

void Menu::analyticsMenu() {
    std::cout << "\n--- аналитика ---" << std::endl;
    std::cout << "1. общая стоимость всех товаров" << std::endl;
    std::cout << "2. товары с малым остатком (<=5)" << std::endl;
    std::cout << "3. топ-3 самых дорогих" << std::endl;
    std::cout << "выбор: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 1) {
        double total = warehouse.getTotalValue();
        std::cout << "общая стоимость: " << total << " руб." << std::endl;
    } else if (choice == 2) {
        auto results = warehouse.getLowStockProducts(5);
        if (results.empty()) {
            std::cout << "все товары в достаточном количестве" << std::endl;
        } else {
            displayProducts(results);
        }
    } else if (choice == 3) {
        auto results = warehouse.getTopExpensive(3);
        if (results.empty()) {
            std::cout << "нет товаров" << std::endl;
        } else {
            displayProducts(results);
        }
    } else {
        std::cout << "неверный выбор" << std::endl;
    }
}

void Menu::saveData() {
    std::cout << "\nсохранение данных..." << std::endl;
    if (fileIO.saveProducts(warehouse.getProducts())) {
        std::cout << "данные сохранены успешно!" << std::endl;
    } else {
        std::cout << "ошибка при сохранении" << std::endl;
    }
}

void Menu::displayProducts(const std::vector<Product>& products) const {
    if (products.empty()) {
        std::cout << "список пуст" << std::endl;
        return;
    }
    
    std::cout << "\nнайденные товары:" << std::endl;
    std::cout << "========================" << std::endl;
    for (const auto& product : products) {
        product.display();
    }
}

int Menu::getUserInputInt(const std::string& prompt) const {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        } else {
            std::cout << "ошибка ввода, введите число: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double Menu::getUserInputDouble(const std::string& prompt) const {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        } else {
            std::cout << "ошибка ввода, введите число: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string Menu::getUserInputString(const std::string& prompt) const {
    std::string value;
    std::cout << prompt;
    std::cin.ignore();
    std::getline(std::cin, value);
    return value;
}