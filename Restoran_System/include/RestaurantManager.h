#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

#include "MenuItem.h"
#include "Dish.h"
#include "Drink.h"

//using namespace std;

/**
 * @class RestaurantManager
 * @brief Менеджер-клас для управління колекціями об'єктів меню
 * * Реалізує бізнес-логіку системи: CRUD-операції, пошук, сортування та фільтрацію.
 * Відповідає за життєвий цикл об'єктів MenuItem (Dish та Drink).
 */
class RestaurantManager {
private:
	/**
	 * @brief Поліморфна колекція вказівників на MenuItem.
	 * Дозволяє зберігати об'єкти різних класів-нащадків в одному контейнері.
	 */
	std::vector<MenuItem*> menu; ///< Поліморфна колекція вказівників
public:
	/**
	 * @brief Деструктор класу.
	 * Забезпечує коректне звільнення динамічнох пам'яті для всіх об'єктів меню.
	 */
	~RestaurantManager() {
		for (auto item : menu)
			delete item;
		menu.clear();
	}

	// --- CRUD операції ---

	/** @brief Додає новий об'єкт до меню. */
	void AddItem(MenuItem* item) {
		if (item)
			menu.push_back(item);
	}

	/** @brief Видаляє об'єкт за ідентифікатором. */
	void RemoveById(int id);

	/** @brief Пошук об'єкта за його унікальним ID. */
	MenuItem* FindById(int id) const;

	/** @brief Редагування існуючих полів об'єкта. */
	void EditItem(int id);

	/** @brief Генерація наступного унікального ID на основі максимального існуючого. */
	int GenerateNextId() const;

	// --- Пошук, сортування, фільтрація ---

	/** @brief Сортує дані за зростанням ціни. */
	void SortByPrice();

	/** @brief Фільтрує записи, виводячи тільки ті, що дешевші за maxPrice. */
	void FilterByPrice(double maxPrice) const;

	/** @brief Пошук об'єкта за точною відповідністю назви. */
	MenuItem* FindByName(const std::string& name) const;

	/** * @brief Виводить тільки об'єкти типу Dish.
	 * Використовує dynamic_cast для фільтрації типу.
	 */
	void DisplayDishes()const;

	/** * @brief Виводить тільки об'єкти типу Drink.
	 * Використовує dynamic_cast для фільтрації типу.
	 */
	void DisplayDrinks()const;

	/** * @brief Пошук без урахування регістру.
	 * Шукає входження підрядка в назву страви.
	 */
	void SearchItems(const std::string& query) const;

	// --- Робота з файлами ---

	/** @brief Серіалізація даних та збереження у файл CSV. */
	void SaveToFile(const std::string& filename) const;

	/** @brief Десеріалізація даних з файлу та відновлення об'єктів у пам'яті. */
	void LoadFromFile(const std::string& filename);
};

#endif 
