// Product.cpp
#include "Product.h"
#include <iostream>
#include <iomanip>

Product::Product() : id(0), name(""), category(""), price(0.0), quantity(0) {}

Product::Product(int id, const std::string& name, const std::string& category, 
                 double price, int quantity) 
    : id(id), name(name), category(category), price(price), quantity(quantity) {}

int Product::getId() const {
    return id;
}

std::string Product::getName() const {
    return name;
}

std::string Product::getCategory() const {
    return category;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

void Product::setId(int id) {
    this->id = id;
}

void Product::setName(const std::string& name) {
    this->name = name;
}

void Product::setCategory(const std::string& category) {
    this->category = category;
}

void Product::setPrice(double price) {
    if (price >= 0) {
        this->price = price;
    }
}

void Product::setQuantity(int quantity) {
    if (quantity >= 0) {
        this->quantity = quantity;
    }
}

void Product::display() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Название: " << name << std::endl;
    std::cout << "Категория: " << category << std::endl;
    std::cout << "Цена: " << std::fixed << std::setprecision(2) << price << " руб." << std::endl;
    std::cout << "Количество: " << quantity << " шт." << std::endl;
    std::cout << "------------------------" << std::endl;
}