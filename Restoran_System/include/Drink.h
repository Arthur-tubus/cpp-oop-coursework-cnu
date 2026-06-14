#ifndef DRINK_H
#define DRINK_H

#include "MenuItem.h"
#include <iostream>
#include <string>

/**
 * @class Drink
 * @brief Клас-нащадок для представлення напоїв у цифровій системі ресторану.
 * * Наслідується від базового класу MenuItem. Додає специфічні характеристики
 * рідинних товарів, такі як літраж та наявність алкоголю, що критично
 * для логіки продажів та вікових обмежень.
 */
class Drink : public MenuItem {
private:
	double volume;	  ///< Об'єм напою в літрах (напр., 0.33, 0.5, 1.0)
	bool isAlcoholic; ///< Ознака наявності алкоголю (true - алкогольний, false - б/а)

public:
	/**
	 * @brief Конструктор з повною ініціалізацією атрибутів напою.
	 * @param id Унікальний номер у базі.
	 * @param name Назва
	 * @param price Вартість за одиницю.
	 * @param weight Загальна вага продукту.
	 * @param vol Об'єм напою в літрах
	 * @param alc Статус алкоголю
	 * Передає загальні параметри у батьківський конструктор MenuItem через список ініціалізації.
	 */
	Drink(int id, std::string name, double price, double weight, double vol, bool alc)
		: MenuItem(id, name, price, weight), volume(vol), isAlcoholic(alc) {
	}

	/**
	 * @brief Спеціалізована візуалізація даних про напій у консоль.
	 * * Перевизначає віртуальний метод (Поліморфізм). Додає візуальні маркери.
	 * [АЛКО] або [Б/А], що дозволяє персоналу швидко ідентифікувати тип товару
	 */
	void Display() const override {
		std::cout << "ID: " << GetId() 
			<< " | НАПІЙ: " << GetName()
			<< (isAlcoholic ? " [АЛКО]" : " [Б/А]") 
			<< " | Вага: " << GetWeight()
			<< " | Об'єм: " << volume 
			<< "л. | Ціна: " << GetPrice() << " грн." << std::endl;
	}

	/**
	 * @brief Серіалізація об'єкта у CSV-рядка для файлового сховища.
	 * * Гарантує збереження специфічних полів напою в кінці рядка.
	 * Використовується RestaurantManager для синхронізації бази даних з диском.
	 */
	std::string ToCsv() const override {
		return std::to_string(GetId()) + "," + GetName() + "," + std::to_string(GetPrice()) + ","
			+ std::to_string(GetWeight()) + "," + std::to_string(volume) + "," + std::to_string(isAlcoholic);
	}

	// --- Гетери та сетери ---

	/**
	 * @brief Отримання поточного об'єму напою.
	 */
	double GetVolume() const { return volume; }

	/**
	 * @brief Встановлення нового об'єму з перевіркою коректності.
	 * Забезпечує цілісність даних (об'єм не може бути від'ємний)
	 */
	void SetVolume(double v) {
		if (v > 0)
			volume = v;
	}

	/**
	 * @brief Отримання статусу алкогольного вмісту.
	 */
	bool GetIsAlcoholic() const { return isAlcoholic; }

	/**
	 * @brief Зміна статусу алкоголю
	 * Використовується адміністратором при редагуванні бази через RestaurantManager::EditItem.
	 */
	void SetAlcoholic(bool alc) { isAlcoholic = alc; }

	// --- Бізнес-логіка ---

	/**
	 * @brief Перевірка необхідності контролю повноліття клієнта.
	 * @return true, якщо продаж потребує перевірки документів.
	 */
	bool NeedsIdCheck() const { return isAlcoholic; }

	/**
	 * @brief Автоматичне визначення великих порцій (сімейного формату).
	 * @return true, якщо об'єм дорівнює або перевищує 1 літр.
	 */
	bool IsFamilySize() const { return volume >= 1.0; }

	/**
	 * @brief Економічний розрахунок: вартість напою в перерахунку на 1 літр.
	 * Допомагає клієнту оцінити вигоду покупки різних об'ємів одного продукту
	 */
	double CalculateLiterPrice() const {
		return (volume > 0) ?
			GetPrice() / volume : 0;
	}
};

#endif 
