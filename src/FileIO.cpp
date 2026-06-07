// FileIO.cpp
#include "FileIO.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileIO::FileIO(const std::string& path) : filePath(path) {}

std::vector<Product> FileIO::loadProducts() {
    std::vector<Product> products;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cout << "файл не найден, создаем новый список товаров" << std::endl;
        return products;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string idStr, name, category, priceStr, quantityStr;
        
        if (std::getline(iss, idStr, ',') &&
            std::getline(iss, name, ',') &&
            std::getline(iss, category, ',') &&
            std::getline(iss, priceStr, ',') &&
            std::getline(iss, quantityStr, ',')) {
            
            try {
                int id = std::stoi(idStr);
                double price = std::stod(priceStr);
                int quantity = std::stoi(quantityStr);
                
                Product product(id, name, category, price, quantity);
                products.push_back(product);
            } catch (const std::exception& e) {
                std::cout << "ошибка при чтении строки: " << line << std::endl;
            }
        }
    }
    
    file.close();
    return products;
}

bool FileIO::saveProducts(const std::vector<Product>& products) {
    std::ofstream file(filePath);
    
    if (!file.is_open()) {
        std::cout << "ошибка: не удалось открыть файл для записи" << std::endl;
        return false;
    }
    
    for (const auto& product : products) {
        file << product.getId() << ","
             << product.getName() << ","
             << product.getCategory() << ","
             << product.getPrice() << ","
             << product.getQuantity() << "\n";
    }
    
    file.close();
    return true;
}