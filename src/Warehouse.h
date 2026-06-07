// Warehouse.h
#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include <string>
#include "Product.h"

class Warehouse {
private:
    std::vector<Product> products;
    int nextId;

public:
    // конструктор
    Warehouse();
    
    // основные операции (crud)
    void addProduct(const std::string& name, const std::string& category, 
                    double price, int quantity);
    bool editProduct(int id, const std::string& name, const std::string& category, 
                     double price, int quantity);
    bool deleteProduct(int id);
    
    // поиск и фильтрация
    std::vector<Product> searchByName(const std::string& name) const;
    std::vector<Product> filterByCategory(const std::string& category) const;
    std::vector<Product> filterByPriceRange(double minPrice, double maxPrice) const;
    
    // сортировка
    void sortByPrice(bool ascending = true);
    void sortByQuantity(bool ascending = true);
    void sortByName();
    
    // аналитика
    double getTotalValue() const;
    std::vector<Product> getLowStockProducts(int threshold = 5) const;
    std::vector<Product> getTopExpensive(int count = 3) const;
    
    // доступ к данным
    std::vector<Product>& getProducts();
    const std::vector<Product>& getProducts() const;
    int getNextId() const;
};

#endif