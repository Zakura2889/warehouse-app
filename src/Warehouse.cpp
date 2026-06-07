// Warehouse.cpp
#include "Warehouse.h"
#include <algorithm>
#include <cctype>

Warehouse::Warehouse() : nextId(1) {}

void Warehouse::addProduct(const std::string& name, const std::string& category, 
                           double price, int quantity) {
    if (name.empty() || category.empty() || price < 0 || quantity < 0) {
        return;
    }
    
    Product product(nextId, name, category, price, quantity);
    products.push_back(product);
    nextId++;
}

bool Warehouse::editProduct(int id, const std::string& name, const std::string& category, 
                            double price, int quantity) {
    if (name.empty() || category.empty() || price < 0 || quantity < 0) {
        return false;
    }
    
    for (auto& product : products) {
        if (product.getId() == id) {
            product.setName(name);
            product.setCategory(category);
            product.setPrice(price);
            product.setQuantity(quantity);
            return true;
        }
    }
    return false;
}

bool Warehouse::deleteProduct(int id) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getId() == id) {
            products.erase(it);
            return true;
        }
    }
    return false;
}

std::vector<Product> Warehouse::searchByName(const std::string& name) const {
    std::vector<Product> result;
    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    for (const auto& product : products) {
        std::string productName = product.getName();
        std::transform(productName.begin(), productName.end(), productName.begin(), ::tolower);
        
        if (productName.find(lowerName) != std::string::npos) {
            result.push_back(product);
        }
    }
    return result;
}

std::vector<Product> Warehouse::filterByCategory(const std::string& category) const {
    std::vector<Product> result;
    std::string lowerCategory = category;
    std::transform(lowerCategory.begin(), lowerCategory.end(), lowerCategory.begin(), ::tolower);
    
    for (const auto& product : products) {
        std::string productCategory = product.getCategory();
        std::transform(productCategory.begin(), productCategory.end(), productCategory.begin(), ::tolower);
        
        if (productCategory == lowerCategory) {
            result.push_back(product);
        }
    }
    return result;
}

std::vector<Product> Warehouse::filterByPriceRange(double minPrice, double maxPrice) const {
    std::vector<Product> result;
    
    for (const auto& product : products) {
        if (product.getPrice() >= minPrice && product.getPrice() <= maxPrice) {
            result.push_back(product);
        }
    }
    return result;
}

void Warehouse::sortByPrice(bool ascending) {
    if (ascending) {
        std::sort(products.begin(), products.end(), 
                  [](const Product& a, const Product& b) {
                      return a.getPrice() < b.getPrice();
                  });
    } else {
        std::sort(products.begin(), products.end(), 
                  [](const Product& a, const Product& b) {
                      return a.getPrice() > b.getPrice();
                  });
    }
}

void Warehouse::sortByQuantity(bool ascending) {
    if (ascending) {
        std::sort(products.begin(), products.end(), 
                  [](const Product& a, const Product& b) {
                      return a.getQuantity() < b.getQuantity();
                  });
    } else {
        std::sort(products.begin(), products.end(), 
                  [](const Product& a, const Product& b) {
                      return a.getQuantity() > b.getQuantity();
                  });
    }
}

void Warehouse::sortByName() {
    std::sort(products.begin(), products.end(), 
              [](const Product& a, const Product& b) {
                  return a.getName() < b.getName();
              });
}

double Warehouse::getTotalValue() const {
    double total = 0.0;
    for (const auto& product : products) {
        total += product.getPrice() * product.getQuantity();
    }
    return total;
}

std::vector<Product> Warehouse::getLowStockProducts(int threshold) const {
    std::vector<Product> result;
    
    for (const auto& product : products) {
        if (product.getQuantity() <= threshold) {
            result.push_back(product);
        }
    }
    return result;
}

std::vector<Product> Warehouse::getTopExpensive(int count) const {
    std::vector<Product> sorted = products;
    std::sort(sorted.begin(), sorted.end(), 
              [](const Product& a, const Product& b) {
                  return a.getPrice() > b.getPrice();
              });
    
    if (count > sorted.size()) {
        count = sorted.size();
    }
    
    return std::vector<Product>(sorted.begin(), sorted.begin() + count);
}

std::vector<Product>& Warehouse::getProducts() {
    return products;
}

const std::vector<Product>& Warehouse::getProducts() const {
    return products;
}

int Warehouse::getNextId() const {
    return nextId;
}