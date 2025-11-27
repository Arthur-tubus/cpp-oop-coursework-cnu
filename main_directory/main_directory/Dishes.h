#ifndef DISHES_H
#define DISHES_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;


//клас нащадок (страви) - для зберігання данних про їжу
class Dishes
{
private:

    string m_Category;//категорія
    string m_Name;//назва
    double m_Price;//ціна
    double m_Weight;// вага
    int m_AvailabilityCount;//кількість у наявносі
    int m_CookingTime;//час приготування

public:
    //конструктор з параметром 
    // додавання нової страви
    Dishes(string m_Category, string m_Name,
        double m_Price, double m_Weight,
        int m_AvailabilityCount, int m_CookingTime);

    //конструктор за замовчуванням 
    // додавання нової пустої страви
    Dishes();

    //копіювання та переміення конструктора
    Dishes(const Dishes& other);
    Dishes(Dishes&& other) noexcept;
    
    // get
    string get_m_Category() const;
    string get_m_Name() const;
    double get_m_Price() const;
    double get_m_Weight() const;
    int get_m_AvailabilityCount() const;
    int get_m_CookingTime() const;

    //set
    void set_m_Category(const string& category);
    void set_m_Name(const string name);
    void set_m_Price(const double price);
    void set_m_Weight(const double weight);
    void set_m_AvailabilityCount(const int count);
    void set_m_CookingTime(const int minetes);

    //ptint
    void printInfo() const;
    
    //save file
    string toFileFormat() const;
    
    //read file
    static Dishes fromFileFormat(const string& line);

    //декструктор
    ~Dishes();

    //методи

    void increasePrice(double percent);

    bool isAvailable() const;

    bool isExpensive(double maxPrice);

    void reduceAvailablity(int NumberDish);

    bool compareByPrice(const Dishes& other)const;
};

#endif
