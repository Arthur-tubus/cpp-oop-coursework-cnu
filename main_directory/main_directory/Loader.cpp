#include "Loader.h"
#include <fstream>
//конструктор 
// з параметром 
Loader::Loader(string name) : names(name) {}
//за замовчуванням
Loader::Loader() : names("Без назви") {}

//Декструктор
Loader::~Loader() {
    cout << "Страва видалена: " << names << endl;
}
//копіювання
Loader::Loader(const Loader& other) = default;
//переміщення
Loader::Loader(Loader&& other)noexcept = default;

// get
const list<Dishes>& Loader::getDishes() const {
    return dish;
}
// set
void Loader::setNames(const string& newName) {
    names = newName;
}
void Loader::Print() const {
    cout << setiosflags(ios::left);

    cout << setw(11) << "Категорія" << "|";
    cout << setw(20) << "Назва" << "|";
    cout << setw(8) << "Ціна" << "|";
    cout << setw(8) << "Вага" << "|";
    cout << setw(11) << "Наявність" << "|";
    cout << setw(16) << "Час приготування" << endl;

    for (int i = 0; i < 82; ++i) {
        if (i == 11 || i == 32 || i == 41 || i == 50 || i == 62) {
            cout << "+";
        }
        else
            cout << "-";
        if (i == 81)
            cout << endl;
    }
}

//метод
//Виводить інформацію
void Loader::showDishes() const {

    Print();

    for (const Dishes& d : dish) {
        d.printInfo();
    }
}
//Завантажує страви з файлу
void Loader::loadDishesFromFile(const string& filename) {
    ifstream in(filename);

    string line;
    while (getline(in, line)) {
        if (!line.empty())
            dish.push_back(Dishes::fromFileFormat(line));
    }
}

//бере передану страву і додає до списку страв
void Loader::addDishes(const Dishes& dishes) {
    dish.push_back(dishes);
}

// метод сортування
void Loader::sortByType(string num) {
    if (num == "категорія") {
        dish.sort([](const Dishes& a, const Dishes& b) {
            return a.get_m_Category() < b.get_m_Category();
            });
    }
    else if (num == "назві") {
        dish.sort([](const Dishes& a, const Dishes& b) {
            return a.get_m_Name() < b.get_m_Name();
            });
    }
    else if (num == "ціні") {
        dish.sort([](const Dishes& a, const Dishes& b) {
            return a.get_m_Price() < b.get_m_Price();
            });
    }
    else if (num == "вага") {
        dish.sort([](const Dishes& a, const Dishes& b) {
            return a.get_m_Weight() < b.get_m_Weight();
            });
    }
    else if (num == "кількості") {
        dish.sort([](const Dishes& a, const Dishes& b) {
            return a.get_m_AvailabilityCount() < b.get_m_AvailabilityCount();
            });
    }
    else if (num == "часу") {
        dish.sort([](const Dishes& a, const Dishes& b) {
            return a.get_m_CookingTime() < b.get_m_CookingTime();
            });
    }
    else
        cout << "Немає такого варіанту ";
}

//редагування властивостей об'єкта
void Loader::editDish(int index, int field, const string& newValue) {
    if (index < 0 || index >= dish.size()) {
        cout << "Невірний індекс Страви!\n";
        return;
    }

    auto it = dish.begin();
    advance(it, index);

    switch (field) {
    case 1:
        it->set_m_Category(newValue);
        break;

    case 2:
        it->set_m_Name(newValue);
        break;
    case 3:
        it->set_m_Price(stod(newValue));
        break;

    case 4:
        it->set_m_Weight(stod(newValue));
        break;
    case 5:
        it->set_m_AvailabilityCount(stoi(newValue));
        break;
    case 6:
        it->set_m_CookingTime(stoi(newValue));
        break;
    default:
        cout << "Невірне поле редагування!\n";
    }

}

//Видалити об'єкт
void Loader::removeByName(const string& name) {
    for (auto it = dish.begin(); it != dish.end(); ++it) {
        if (it->get_m_Name() == name) {
            dish.erase(it);
            cout << "Страву \"" << name << "\" видаленно.\n";
            return;
        }
    }
    cout<< "Страву \"" << name << "\" не знайдено.\n";
}

//фільтр поушку
//категорія страви
void Loader::filterCategory(const string& category) const {
    bool found = false;
    Print();

    for (const auto& d : dish) {
        if (d.get_m_Category() == category) {
            d.printInfo();
            found = true;
        }
    }
    if (!found)
        cout << "Страва з категорією \"" << category << "\" не знайдено. \n";
}

//ціна страви
void Loader::filterPriceLess(double maxPrice) const {
    bool found = false;
    Print();

    for (const auto& d : dish) {
        if (d.get_m_Price() <= maxPrice) {
            d.printInfo();
            found = true;
        }
    }
    if (!found)
        cout << "Страва дешевше \"" << maxPrice << "\" грн не знайдено. \n";
}
//Назва страви
void Loader::filterName(const string& part) const {
    bool found = false;
    Print();

    for (const auto& d : dish) {
        if (d.get_m_Name().find(part) != string::npos) {
            d.printInfo();
            found = true;
        }
    }

    if (!found)
        cout << "Нічого не знайдено для \"" << part << "\". \n";
}
//
void Loader::search(const SearchCriteria& c) const {
    bool found = false;
    Print();

    for (const auto& d : dish) {

        //назва
        if (!c.name.empty() && d.get_m_Name().find(c.name) == string::npos)
            continue;
        //категорія
        if (!c.category.empty() && d.get_m_Category() != c.category)
            continue;
        //макс ціна
        if (c.maxPrice >= 0 && d.get_m_Price() > c.maxPrice)
            continue;

        // мінімальна ціна
        if (c.minPrice >= 0 && d.get_m_Price() < c.minPrice)
            continue;

        // максимальний час
        if (c.maxTime >= 0 && d.get_m_CookingTime() > c.maxTime)
            continue;
        // мінімальна вага
        if (c.minWeight >= 0 && d.get_m_Weight() < c.minWeight)
            continue;

        d.printInfo();
        found = true;

    }
    if (!found)
        cout << "Нічого не знайденно за заданими критеріями. \n";

}
