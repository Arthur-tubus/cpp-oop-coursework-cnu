#ifndef MENUITEM_H
#define MENUITEM_H

#include "IEntity.h"
#include <iostream>
#include <string>

/**
 * @class MenuItem
 * @brief Абстрактний базовий клас для всіх позицій меню.
 * Успадковує інтерфейс IEntity та додає загальні атрибути для страв і напоїв.
 */

class MenuItem : public IEntity {
protected:
	// Protected дозволяє нащадкам (Dish, Drink) мати прямий доступ
	int id; 	  ///< Унікальний ідентифікатор
	std::string name;  ///< Назва позиції
	double price; ///< Вартість
	double weight;///< Вага або об'єм

public:
	// --- Конструктори та деструктори ---

	/** @brief Конструктор за замовчуванням. */
	MenuItem();

	/** @brief Конструктор з параметрами. */
	MenuItem(int id, std::string name, double price, double weight);

	/** @brief Конструктор копіювання. */
	MenuItem(const MenuItem& other);

	/** @brief Конструктор переміщення. */
	MenuItem(MenuItem&& other) noexcept;

	/** @brief Віртуальний деструктор для забезпечення коректного очищення пам'яті. */
	virtual ~MenuItem();

	// --- Геттери та сеттери (Інкапсуляція) ---

	int GetId() const { return id; }
	std::string GetName() const { return name; }
	double GetPrice() const { return price; }
	double GetWeight() const { return weight; }

	/** @brief Встановлює нову ціну. */
	void SetPrice(double priceValue) { price = priceValue; }

	/** @brief Встановлює нову вагу об'єкта з валідацією. */
	void SetWeight(double w) { 
		if(w>0)
			weight = w; 
	}

	// --- Бізнес-логіка класу ---

	/** @brief Перевіряє коректність ціни. */
	bool HasPrice() const { return price > 0; }

	/** @brief Знижує вартість на заданий відсоток. */
	void ApplyDiscount(double percent) {
		if (percent > 0 && percent <= 100)
			price -= price * (percent / 100);
	}

	/** @brief Розраховує питому вартість продукту. */
	double GetPricePerHundredGrams() const {
		return (weight > 0) ? (price / weight) * 100 : 0;
	}

	/** @brief Категоизація порції за вагою. */
	bool IsLargePortion() const {
		return weight > 500;
	}

	/** @brief Валідація та оновлення назви. */
	void UpdateName(const std::string& newName) {
		if (!newName.empty())
			name = newName;
	}
};

#endif 