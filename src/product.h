// Product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;

public:
    // конструкторы
    Product();
    Product(int id, const std::string& name, const std::string& category, 
            double price, int quantity);
    
    // геттеры
    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    int getQuantity() const;
    
    // сеттеры
    void setId(int id);
    void setName(const std::string& name);
    void setCategory(const std::string& category);
    void setPrice(double price);
    void setQuantity(int quantity);
    
    // метод для вывода информации
    void display() const;
};

#endif