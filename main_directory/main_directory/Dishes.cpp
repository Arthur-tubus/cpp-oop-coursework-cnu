#include "Dishes.h"

// конструктори
//за параметрами
Dishes::Dishes(string m_Category, string m_Name,
    double m_Price, double m_Weight,
    int m_AvailabilityCount, int m_CookingTime)
    : m_Category(m_Category), m_Name(m_Name),
    m_Price(m_Price), m_Weight(m_Weight),
    m_AvailabilityCount(m_AvailabilityCount), m_CookingTime(m_CookingTime)
{
}
//за замовчуванням
Dishes::Dishes() :
    m_Category("Невідомий"),
    m_Name("Невідомий"),
    m_Price(0),
    m_Weight(0),
    m_AvailabilityCount(0),
    m_CookingTime(0)
{
}
//копіювання та переміщення
Dishes::Dishes(const Dishes& other) = default;
Dishes::Dishes(Dishes&& other) noexcept = default;

// get
string Dishes::get_m_Category() const { return m_Category; }
string Dishes::get_m_Name() const { return m_Name; }
double Dishes::get_m_Price() const { return m_Price; }
double Dishes::get_m_Weight() const { return m_Weight; }
int Dishes::get_m_AvailabilityCount() const { return m_AvailabilityCount; }
int Dishes::get_m_CookingTime() const { return m_CookingTime; }

// set
void Dishes::set_m_Category(const string& category) { m_Category = category; }
void Dishes::set_m_Name(const string name) { if (!name.empty()) m_Name = name; }
void Dishes::set_m_Price(const double price) { if (price >= 0) m_Price = price; }
void Dishes::set_m_Weight(const double weight) { if (weight > 0) m_Weight = weight; }
void Dishes::set_m_AvailabilityCount(const int count) { if (count >= 0) m_AvailabilityCount = count; }
void Dishes::set_m_CookingTime(const int minetes) { if (minetes >= 0) m_CookingTime = minetes; }

// print
void Dishes::printInfo() const {

    cout << setiosflags(ios::right);

    cout << setw(11) << m_Category << "|";
    cout << setw(20) << m_Name << "|";
    cout << setw(8) << m_Price << "|";
    cout << setw(8) << m_Weight << "|";
    cout << setw(11) << m_AvailabilityCount << "|";
    cout << setw(16) << m_CookingTime << " хв" << endl;

    cout << setiosflags(ios::left);
}

// save file
string Dishes::toFileFormat() const {
    return m_Category + ";" + m_Name + ";" +
        to_string(m_Price) + ";" + to_string(m_Weight) +
        ";" + to_string(m_AvailabilityCount) + ";" + to_string(m_CookingTime);
}
//read file
Dishes Dishes::fromFileFormat(const string& line) {
    stringstream ss(line);
    string category, name, priceStr, weightStr, availabilityCountStr, cookingTimeStr;
    getline(ss, category, ';');
    getline(ss, name, ';');

    getline(ss, priceStr, ';');
    getline(ss, weightStr, ';');
    getline(ss, availabilityCountStr, ';');
    getline(ss, cookingTimeStr, ';');

    double price = stod(priceStr);
    double weight = stod(weightStr);
    int availabilityCount = stoi(availabilityCountStr);
    int cookingTime = stoi(cookingTimeStr);

    return Dishes(category, name, price, weight, availabilityCount, cookingTime);
}
//Декструктор
Dishes::~Dishes() {
    //cout << "Страва видалена\n";
}

//Методи
//збільшує ціну на певний відсоток
void Dishes::increasePrice(double percent) {
    if (percent < 0) return;

    m_Price += m_Price * (percent / 100);
}
//перевіряє наявність страви (більше нуля)
bool Dishes::isAvailable() const {
    return m_AvailabilityCount > 0;
}
//перевіряє чи вистачить грошей чи ні
bool Dishes::isExpensive(double maxPrice) {
    return m_Price > maxPrice;
}
//Захист від від'ємного числа
void Dishes::reduceAvailablity(int NumberDish)
{
    if (NumberDish < 0)return;

    if (NumberDish > m_AvailabilityCount)
        m_AvailabilityCount = 0;
    else
        m_AvailabilityCount -= NumberDish;
}
//повертає true, якщо поточний дорожчий 
bool Dishes::compareByPrice(const Dishes& other)const {
    return m_Price > other.m_Price;
};
