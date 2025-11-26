#include <iostream>
#include <iomanip>
#include <Windows.h>

#include <algorithm>

#include <string>
#include <fstream>
#include <sstream>

#include <list>
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
		int m_AvailabilityCount, int m_CookingTime) :

		m_Category(m_Category), m_Name(m_Name),
		m_Price(m_Price), m_Weight(m_Weight),
		m_AvailabilityCount(m_AvailabilityCount), m_CookingTime(m_CookingTime) {
	}

	//конструктор за замовчуванням 
	// додавання нової пустої страви
	Dishes() :
		m_Category("Невідомий"),
		m_Name("Невідомий"),
		m_Price(0),
		m_Weight(0),
		m_AvailabilityCount(0),
		m_CookingTime(0) {
	}



	// гетери
	string get_m_Category() const { return m_Category; }
	string get_m_Name() const { return m_Name; }
	double get_m_Price() const { return m_Price; }
	double get_m_Weight() const { return m_Weight; }
	int get_m_AvailabilityCount() const { return m_AvailabilityCount; }
	int get_m_CookingTime() const { return m_CookingTime; }

	// сетер
	void set_m_Category(const string& category) {
		m_Category = category;
	}
	void set_m_Name(const string name) {
		if (!name.empty())
			m_Name = name;
	}
	void set_m_Price(const int price) {
		if (price >= 0)
			m_Price = price;
	}
	void set_m_Weight(const int weight) {
		if (weight > 0)
			m_Weight = weight;
	}
	void set_m_AvailabilityCount(const int count) {
		if (count >= 0)
			m_AvailabilityCount = count;
	}
	void set_m_CookingTime(const int minetes) {
		if (minetes >= 0)
			m_CookingTime = minetes;
	}
	
	// метод виводу з файлу
	void printInfo() const {
		

		//інфа з таблиці
		cout << setiosflags(ios::right);
		
			cout << setw(11) << m_Category << "|";
			cout << setw(20) << m_Name << "|";
			cout << setw(8) << m_Price << "|";
			cout << setw(8) << m_Weight << "|";
			cout << setw(11) << m_AvailabilityCount << "|";
			cout << setw(16) << m_CookingTime << endl;
		
		cout << setiosflags(ios::left);
	}


	//збереження у файл
	string toFileFormat() const {
		return m_Category + ";" + m_Name + ";" + 
			to_string(m_Price) + ";" + to_string(m_Weight) + 
			";" + to_string(m_AvailabilityCount) + ";" + to_string(m_CookingTime);
	}
	// читання файлу
	static Dishes fromFileFormat(const string& line) {
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
};

//менеджер клас
class Loader {
private:
	list<Dishes> dish;
	string names;
public:
	Loader(string name = "Unnamed Dishes") : names(name) {}
	~Loader() {
		cout << "Dishes destroyed: " << names << endl;
	}
	//додати елемент адміном
	void addDishes(const Dishes& dishes) {
		dish.push_back(dishes);
	}

	// перегляд даних користувачем
	void showDishes() const {
		
		cout << setiosflags(ios::left);

		//перший рядок
		cout << setw(11) << "Категорія" << "|";
		cout << setw(20) << "Назва" << "|";
		cout << setw(8) << "Ціна" << "|";
		cout << setw(8) << "Вага" << "|";
		cout << setw(11) << "Наявність" << "|";
		cout << setw(16) << "Час приготування" << endl;
		for (int i = 0; i < 79; ++i) {


			if (i == 11 || i == 32 || i == 41 || i == 50 || i == 62) {
				cout << "+";
			}
			else
				cout << "-";
			if (i == 78)
				cout << endl;
		}
		for (const Dishes& d : dish) {
			d.printInfo();
		}
	}



	const list<Dishes>& getDishes() const {
		return dish;
	}
	
	// Завантаження з файлу
	void loadDishesFromFile(const string& filename) {
		ifstream in(filename);

		string line;
		while (getline(in, line)) {
			if(!line.empty())
				dish.push_back(Dishes::fromFileFormat(line));
		}
	}



};


//Меню адміна
void adminMenu(Loader& loader) {
	while (true) {
		cout << "\n----- АДМІН МЕНЮ -----\n";
		cout << "\n1. Додати страву";
		cout << "\n2. Показати страви";
		cout << "\n3. Зберегти файл";
		cout << "\n4. Вихід";
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
			cout << "Введіть категорію"; getline(cin, m_Category);// cin.ignore();
			cout << "Введіть назву"; getline(cin, m_Name);
			cout << "Введіть ціну";  cin >> m_Price;
			cout << "Введіть вагу"; 	 cin >> m_Weight;
			cout << "Введіть кількість у наявності"; 	cin >> m_AvailabilityCount;
			cout << "Введіть час приготуваня"; 	 cin >> m_CookingTime;
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');

			Dishes d(m_Category, m_Name, m_Price, m_Weight,
				m_AvailabilityCount, m_CookingTime);
			loader.addDishes(d);
			cout << "Страва додана";

		}
		else if (choice == "Показати") {
			loader.showDishes();
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

	Loader dishes("Menu");
	dishes.loadDishesFromFile("dishes.txt");
	
	do {
		

		int role = loginMenu();
		
		cout << endl;
		if (role == 1) {
			adminMenu(dishes);
			cout << "Вітаю Адмін"<<endl << endl;

		}
		else if (role == 2) {
			cout << "Вітаю Юзер " << endl << endl;
		}
		else if (role == 3) {
			cout << "До побачення" << endl << endl;
			break;
		}
		else
			cout << "Помилка входу" << endl << endl;

	} while (true);
	


	return 0;
}