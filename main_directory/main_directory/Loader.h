#ifndef LOADER_H
#define LOADER_H

#include <list>
#include <string>
#include <iostream>
#include <iomanip>

 
#include "Dishes.h"
using namespace std;

//критерії
struct SearchCriteria {
    string name;
    string category;
    double maxPrice = -1;
    double minPrice = -1;
    int maxTime = -1;
    double minWeight = -1;
};

//Менеджер класу
class Loader {
private:
    list<Dishes> dish;//файл для збереження
    string names;//
public:
    //конструктори
    // з параметром 
    Loader(string name );
    //за замовчуванням
    Loader();
    //декструктор 
    ~Loader();
    //копіювання
    Loader(const Loader& other);
    //переміщення
    Loader(Loader&& other) noexcept;

    //get
    const list<Dishes>& getDishes() const;
    //set
    void setNames(const string& newName);

    //метод
    void Print() const;
    //Виводить інформацію
    void showDishes() const;
    //Завантажує страви з файлу
    void loadDishesFromFile(const string& filename);
    //бере передану страву і додає до списку страв
    void addDishes(const Dishes& dishes);
    //Сортування
    void sortByType(string num);
    //редагування властивостей об'єкта 
    void editDish(int index, int field, const string& newValue);
    //Видалити об'єкт
    void removeByName(const string& name);
    
    //фільтр поушку
    //категорія страви
    void filterCategory(const string& category) const;
    //ціна страви
    void filterPriceLess(double maxPrice) const;
    //назва страви
    void filterName(const string& part) const;

    //Пошук за критеріями
    void search(const SearchCriteria& criteria) const;
};

#endif
