#include <iostream>
#include <iomanip>
#include <Windows.h>

#include <algorithm>

#include <string>
#include <fstream>
#include <sstream>

#include <list>

#include "Dishes.h"
#include "Loader.h"
using namespace std;

//Абстрактний клас
class FoodBase {
public:
	virtual void printInfo() const = 0;
	virtual string toFileFormat() const = 0;
	virtual ~FoodBase() {}
};

//class Dishes: public FoodBase {};

//Інтерфейс
class ISearchable {
public:
	virtual bool matches(const string& key) const = 0;
};

//Меню адміна
void adminMenu(Loader& loader) {
	while (true) {
		cout << "\n----- АДМІН МЕНЮ -----\n";
		cout << "\n1. Додати страву";
		cout << "\n2. Показати страви";
		cout << "\n3. Фільтр запису";
		cout << "\n4. Копіювати страви";
		cout << "\n5. Сортування страви";
		cout << "\n6. Пошук страви";
		cout << "\n7. Видалити страву";
		cout << "\n8. Редагування страви";
		cout << "\n9. Зберегти файл";
		cout << "\n10. Вихід";
		cout << "\nВаріант:";

		string choice;
		getline(cin, choice);

		if (choice == "Додати") {
			string m_Category;//категорія
			string m_Name;//назва
			double m_Price;//ціна
			double m_Weight;// вага
			int m_AvailabilityCount;//кількість у наявносі
			int m_CookingTime;// час приготуваня


			//Введення данних
			cout << "Введіть категорію"; getline(cin, m_Category);
			cout << "Введіть назву"; getline(cin, m_Name);
			cout << "Введіть ціну";  cin >> m_Price;
			cout << "Введіть вагу"; 	 cin >> m_Weight;
			cout << "Введіть кількість у наявності"; 	cin >> m_AvailabilityCount;
			cout << "Введіть час приготуваня"; 	 cin >> m_CookingTime;
			

			Dishes d(m_Category, m_Name, m_Price, m_Weight,
				m_AvailabilityCount, m_CookingTime);
			loader.addDishes(d);
			cout << "Страва додана";

		}
		else if (choice == "Показати") {
			loader.showDishes();
		}
		else if (choice == "Фільтр") {
			string type;
			cout << "фільтрувати за (Категорія / Ціна / Назва): ";
			getline(cin, type);
			if (type == "Категорія") {
				string cat;
				cout << "Введіть категорію: ";
				getline(cin, cat);
				loader.filterCategory(cat);
			}
			else if (type == "Ціна") {
				double p;
				cout << "Максимальна ціна: ";
				cin >> p;
				cin.ignore();
				loader.filterPriceLess(p);

			}
			else if (type == "Назва") {
				string n;
				cout << "Введіть частину назви: ";
				/*cin >> n;*/
				getline(cin, n);
				loader.filterName(n);

			}
		}
		else if (choice == "Сортування") {
			string num;
			getline(cin, num);
			loader.sortByType(num);
		}
		else if (choice == "Пошук") {
			SearchCriteria c;

			cout << "Введіть назву (або залиште порожнім): ";
			getline(cin, c.name);

			cout << "Категорія (або порожнім): ";
			getline(cin, c.category);

			cout << "Максимальна ціна (-1 = пропустити): ";
			cin >> c.maxPrice; cin.ignore();

			cout << "Мінімальна ціна (-1 = пропустити):  ";
			cin >> c.minPrice; cin.ignore();

			cout << "Макс час приготування (-1 = пропустити): ";
			cin >> c.maxTime; cin.ignore();

			cout << "Мінімальна вага (-1 = пропустити):  ";
			cin >> c.minWeight; cin.ignore();

			loader.search(c);
		}
		else if (choice == "Видалити") {
			string name;
			cout << "Введіть назву страви для видалення: ";
			getline(cin, name);
			loader.removeByName(name);
		}
		else if (choice == "Редаг") {
			string numDish, numValue, newValue;
			getline(cin, numDish);
			getline(cin, numValue);
			getline(cin, newValue);
			loader.editDish(stoi(numDish), stoi(numValue), newValue);
		}
		else if (choice == "Копіювати") {
			if (loader.getDishes().empty()) {
				cout << "Немає страв для копіювання!\n";
				continue;
			}
			const Dishes& first = *loader.getDishes().begin();

			Dishes copy = first;
			loader.addDishes(copy);

			cout << "Страву скопійовано! ";
		}
		else if (choice == "Зберегти") {
			ofstream out("dishes.txt");
			if (!out) {

				cerr << "Помилка файлу!" << endl;
				continue;
			}
			for (const auto& d : loader.getDishes()) {
				out << d.toFileFormat() << endl;
			}
			cout << "Страва збереженна. \n";
		}
		else if (choice == "Вихід")
			break;
		else
			cout << "Немає такого варіанту\n";
	}
}
//Обирання обліку
int loginMenu() {
	string input;
	cout << "Увійти як:\n1. Адмін\n2. Юзер\n3. Вихід\nОбрано: ";
	getline(cin, input);
	if (input == "Адмін") {
		string password;
		cout << "Введіть пароль: ";
		getline(cin, password);
		return password == "admin123" ? 1 : -1;
	}
	else if (input == "Юзер") {
		return 2;
	}
	else if (input == "Вихід") {
		return 3;
	}
	return 0;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string choice;

	Loader loader("Menu");
    loader.loadDishesFromFile("dishes.txt");
	
	


		int role = loginMenu();

		cout << endl;
		if (role == 1) {
			adminMenu(loader);
			cout << "Вітаю Адмін" << endl << endl;

           
		}
		else if (role == 2) {
			cout << "Вітаю Юзер " << endl << endl;
		}
		else if (role == 3) {
			cout << "До побачення" << endl << endl;
			
		}
		else
			cout << "Помилка входу" << endl << endl;


	return 0;
}