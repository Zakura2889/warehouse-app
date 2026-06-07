// FileIO.h
#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>
#include "Product.h"

class FileIO {
private:
    std::string filePath;

public:
    // конструктор
    FileIO(const std::string& path = "data/products.txt");
    
    // загрузка данных из файла
    std::vector<Product> loadProducts();
    
    // сохранение данных в файл
    bool saveProducts(const std::vector<Product>& products);
};

#endif