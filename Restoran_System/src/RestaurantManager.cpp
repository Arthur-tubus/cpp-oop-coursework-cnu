#include "RestaurantManager.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <limits>

/**
 * @brief Допоміжний метод для парсингу рядків.
 * Розділяє CSV-рядок на окремі токени для подальшої обробки.
 */
std::vector<std::string> SplitString(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

/**
 * @brief Завантаження бази даних з файлу.
 * Реалізує відновлення об'єктів (десеріалізація)
 * з урахуванням їхнього типу (Dish/Drink).
 */
void RestaurantManager::LoadFromFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open())
		return;

	std::string line;
	while (getline(file, line)) {
		if (line.empty())
			continue;
		auto parts = SplitString(line, ',');
		if (parts.size() < 6)
			continue;

		int id = stoi(parts[0]);
		std::string name = parts[1];
		double price = stod(parts[2]);
		double weight = stod(parts[3]);
		bool isDrink = (parts[5] == "1" || parts[5] == "0") && parts[4].find_first_not_of("0123456789.") == std::string::npos;

		// Логіка розділення об'єктів при читанні
		if (isDrink) {
			// Якщо параметр схожий на дробове число (об'єм), створюємо напій
			AddItem(new Drink(id, name, price, weight, stod(parts[4]), parts[5] == "1"));
		}
		else {
			// В іншому випадку створюємо кулінарну страву
			AddItem(new Dish(id, name, price, weight, parts[4], stoi(parts[5])));
		}

	}

}

/**
 * @brief Видалення елемента за ID.
 * Використовує лямбда-вираз та алгоритм std::remove_if
 * для ефективного очищення контейнера.
 */
void RestaurantManager::RemoveById(int id) {
	auto it = std::remove_if(menu.begin(), menu.end(), [id](MenuItem* m) {
		if (m->GetId() == id) {
			delete m; // звільнення пам'яті перед видаленням вказівника
			return true;
		}
		return false;
		});

	if (it != menu.end()) {
		menu.erase(it, menu.end());
		std::cout << "Об'єкт з ID" << id << " видалено з меню.\n";
	}
	else {
		std::cout << "Об'єкт з ID " << id << " не знайдено.\n";
	}
}

/**
 * @brief Редагування існуючих даних.
 * Оновлює атрибут об'єкта в пам'яті, використовуючи інкапсульовані методи класу.
 */
void RestaurantManager::EditItem(int id) {
	MenuItem* item = FindById(id);
	if (!item) {
		std::cout << "Об'єкт з ID " << id << " не знайдено!\n";
		return;
	}

	std::string input;
	std::cout << "\n--- РЕДАГУВАННЯ ПОЗИЦІЇ ID: " << id << " ---\n";
	std::cout << "(Натисніть Enter, щоб залишити поточне значення)\n";

	// Редагування назви
	std::cout << "Назва [" << item->GetName() << "]: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	getline(std::cin, input);
	if (!input.empty()) {
		item->UpdateName(input);
	}

	// Редагування ціни
	std::cout << "Ціна [" << item->GetPrice() << "] (грн): ";
	std::getline(std::cin, input);
	if (!input.empty()) {
		try {
			item->SetPrice(std::stod(input));
		}
		catch (...) {
			std::cout << "Помилка: введено не число. значення не змінено.\n";
		}
	}

	// Редагування ваги
	std::cout << "Вага [" << item->GetWeight() << "] (г): ";
	std::getline(std::cin, input);
	if (!input.empty()) {
		try {
			item->SetWeight(std::stod(input));
		}
		catch(...){
			std::cout << "Помилка вводу ваги. Значення не змінено.\n";
		}
	}

	// Специфічні поля для Dish
	if (Dish* d = dynamic_cast<Dish*>(item)) {
		std::cout << "Категорія [" << d->GetCategory() << "]: ";
		std::getline(std::cin, input);
		if(!input.empty())
			d->SetCategory(input);
			

		std::cout << "Час приготування [" << d->GetCookTime() << "] (хв): ";
		std::getline(std::cin,input);
		if(!input.empty())
			d->SetCookTime(std::stoi(input));
	}

	// Специфічні поля для Drink
	else if (Drink* dr = dynamic_cast<Drink*>(item)) {
		std::cout << "Об'єм [" << dr->GetVolume() << "] (л): ";
		std::getline(std::cin, input);
		if(!input.empty())
			dr->SetVolume(std::stod(input));

		std::cout << "Алкогольний (1-так, 0-ні) ["<<dr->GetIsAlcoholic()<<"]: ";
		std::getline(std::cin, input);
		if(!input.empty())
			dr->SetAlcoholic(input == "1");
	}
	std::cout << "Дані успішно оновлено.\n";
}

/**
 * @brief Пошук за ідентифікатором.
 * @return Вказівник на об'єкт MenuItem або nullptr.
 */
MenuItem* RestaurantManager::FindById(int id)const {
	for (auto item : menu) {
		if (item->GetId() == id)
			return item;
	}
	return nullptr;
}

/**
 * @brief Генерація нового унікального ID.
 * Гарантує цілісність бази даних при додаванні нових записів.
 */
int RestaurantManager::GenerateNextId() const {
	int maxId = 0;
	for (const auto& item : menu) {
		if (item->GetId() > maxId)
			maxId = item->GetId();
	}
	return maxId + 1;
}

/**
 * @brief Сортування за ціною.
 * Використовує стандартний алгоритм std::sort
 * з кастомним компаратором
 */
void RestaurantManager::SortByPrice() {
	std::sort(menu.begin(), menu.end(), [](MenuItem* a, MenuItem* b) {
		return a->GetPrice() < b->GetPrice();
		});
}

/**
 * @brief Фільтрація за ціновим порогом.
 */
void RestaurantManager::FilterByPrice(double maxPrice) const {
	std::cout << "Результати фільтрації (до " << maxPrice << " грн):" << std::endl;
	for (auto item : menu) {
		if (item->GetPrice() <= maxPrice)
			item->Display();
	}
}

/**
 * @brief Пошук без урахування регістру.
 * Реалізує трансформацію рядків для зручного пошуку користувачем.
 */
void RestaurantManager::SearchItems(const std::string& query) const {

	if (query.empty()) {
		std::cout << "Запит порожній!\n";
		return;
	}

	bool globalFound = false;

	// Приведення запиту до нижнього регістру для зручності
	auto toLowerUA = [](std::string data) {
		for (int i = 0; i < data.length(); i++) {
			unsigned char c = (unsigned char)data[i];
			if (c >= 'A' && c <= 'Z')
				data[i] = c + 32;
			else if (c >= 192 && c <= 223)
				data[i] = c + 32;
			else if (c == 178)
				data[i] = 179;
			}
		return data;
		};

	std::string lowerQuery = toLowerUA(query);

	std::cout << "\n--- РЕЗУЛЬТАТИ ПОШУКУ: \"" << query << "\" ---\n";

	for (auto item : menu) {
		bool isMatch = false;

		
		// 2 Пошук за назвою (працює на всіх об'єктів MenuItem)
		std::string lowerName = toLowerUA(item->GetName());
		if (lowerName.find(lowerQuery) != std::string::npos) {
			isMatch = true;
		}

		// 3 Пошук за категорією (тільки для страв)
		if (!isMatch) {
			if (Dish* d = dynamic_cast<Dish*>(item)) {
				std::string lowerCat = toLowerUA(d->GetCategory());
				if (lowerCat.find(lowerQuery) != std::string::npos)
					isMatch = true;
				}
		}

		// 4 Специфічний пошук для напоїв
		// Якщо користувач ввів "алко", або "alc" - показуємо алкогольні напої
		if (!isMatch) {
			if (Drink* dr = dynamic_cast<Drink*>(item)) {
				if ((lowerQuery == "алко") && dr->GetIsAlcoholic())
					isMatch = true;
				else
					if ((lowerQuery == "б/а") && dr->GetIsAlcoholic() != 1)
						isMatch = true;
			}
		}

		// Вивід: тільки якщо знайшли б один збіг
		if (isMatch) {
			item->Display();
			globalFound = true;
		}


	}
	if (!globalFound)
		std::cout << "За вашим запитом \"" << query << "\" нічого не знайдено.\n";
}

MenuItem* RestaurantManager::FindByName(const std::string& name) const {
	for (auto item : menu) {
		if (item->GetName() == name)
			return item;
	}
	return nullptr;
}

/**
 * @brief Збереження у файл (Серіалізація).
 */
void RestaurantManager::SaveToFile(const std::string& filename) const {
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Критична помилка: файл " + filename + " не знайдено!");
	}
	for (const auto& item : menu) {
		file << item->ToCsv() << "\n";
	}
	file.close();
}

/**
 * @brief Виведення страв за допомогою dynamic_cast.
 * Демонструє використання RTTI для фільтрації об'єктів за типом
 */
void RestaurantManager::DisplayDishes()const {
	std::cout << "\n--- СПИСОК СТРАВ ---\n";
	bool found = false;
	for (auto item : menu) {
		if (dynamic_cast<Dish*>(item)) {
			item->Display();
			found = true;
		}
	}
	if (!found)
		std::cout << "Страви ще не додані.\n";
}

/**
 * @brief Виведення напоїв за допомогою dynamic_cast.
 */
void RestaurantManager::DisplayDrinks() const {
	std::cout << "\n--- СПИСОК НАПОЇВ ---\n";
	bool found = false;
	for (auto item : menu) {
		if (dynamic_cast<Drink*>(item)) {
			item->Display();
			found = true;
		}
	}
	if (!found)
		std::cout << "Напої ще не додані.\n";
}