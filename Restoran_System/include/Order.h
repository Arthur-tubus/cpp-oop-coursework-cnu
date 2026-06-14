#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <iostream>
#include "MenuItem.h"
#include <utility>

/**
 * @class Order
 * @brief Клас для формування замовлення клієнта та розрахунку його вартості.
 * Реалізує механізм агрегації об'єктів MenuItem.
 */
class Order {
private:
	/**
	* @brief Контейнер вказівників на обрані позиції меню.
	* Використовує поліморфізм для зберігання і страв, і напоїв одночасно.
	*/
	std::vector<MenuItem*> items;

public:
	// --- Конструктори та деструктори ---

	Order() = default;

	/**
	* @brief Конструктор копіювання для створення дублікату замовлення.
	*/
	Order(const Order& other) :items(other.items) {
		std::cout << "[ІНФО] Створено копію замовлення." << std::endl;
	}

	/**
	* @brief Конструктор переміщення для оптимізації роботи з тимчасовими об'єктами.
	*/
	Order(Order&& other) noexcept :items(std::move(other.items)) {
		std::cout << "[ІНФО] Замовлення переміщено." << std::endl;
	}

	/**
	* @brief Деструктор класу Order.
	* @note Очищує лише контейнер вказівників. Самі об'єкти MenuItem залишаються в пам'яті,
	* оскільки ними керує RestaurantManager (уникнення помилки подвійного видалення).
	*/
	~Order() {
		//std::cout << "\n[ДЕКСТРУКТОР] Об'єкт замовлення знищено." << std::endl;
	}

	// --- Методи управління замовленням (бізнес-логіка) ---

	/** @brief Додає вказану позицію до поточного замовлення.*/
	void AddItem(MenuItem* item) {
		if (item)
			items.push_back(item);
	}

	/**
	* @brief Розраховує загальну суму замовлення.
	* @return Сума цін усіх доданих об'єктів.
	*/
	double CalculateTotal()const {
		double total = 0;
		for (const auto item : items) {
			total += item->GetPrice();
		}
		return total;
	}

	/** @brief Анулює поточне замовлення (очищення списку).*/
	void ClearOrder() {
		items.clear();
	}

	/** @brief Повертає кількість замовлених позицій.*/
	int GetItemsCount() const {
		return static_cast<int>(items.size());
	}

	/** @brief Перевіряє наявність позицій у кошику.*/
	bool IsEmpty() const {
		return items.empty();
	}

	/**
	* @brief Виводить деталізований  чек у консоль
	* Використовує поліморфний виклик Display() для кожного елемента.
	*/
	void DisplayOrder() const {
		std::cout << "\n--- Поточне замовлення ---" << std::endl;
		for (const auto& item : items) {
			item->Display();
		}
		std::cout << "Разом: " << CalculateTotal() << " грн." << std::endl;
	}
};

#endif // !ORDER_H
