#ifndef DISH_H
#define DISH_H

#include "MenuItem.h"
#include <iostream>
#include <string>

/**
 * @class Dish
 * @brief Клас-нащадок для представлення кулінарних страв у меню.
 * * Реалізує концепцію успадкування, розширюючи базовий клас MenuItem
 * специфічний для їжі  атрибутами: категорією та часом приготування.
 */
class Dish : public MenuItem {
private:
	std::string category; ///< Категорія страви (напр., "Десерти", "Гарячі страви")
	int cookTime;	 ///< Час приготування страви у хвилинах

public:
	/**
	 * @brief Конструктор з параметрами для ініціалізації об'єкта страви.
	 * @param id Унікальний ідентифікатор.
	 * @param name Назва страви.
	 * @param price Вартість.
	 * @param weight Вага в грамах.
	 * @param cat Текстова категорія.
	 * @param time Час приготування (хв).
	 * Викликає конструктор базового класу MenuItem для ініціалізації спільних полів.
	 */
	Dish(int id, std::string name, double price, double weight, std::string cat, int time)
		: MenuItem(id, name, price, weight), category(cat), cookTime(time) {
	}

	/**
	 * @brief Спеціалізоване виведення інформації про страву в консоль.
	 * Перевизначає (override) віртуальний метод базового класу для відображення
	 * розширеного набору даних, включаючи категорію та час очікування.
	 */
	void Display() const override {
		std::cout << "ID: " << GetId() << " | СТРАВА: " << GetName() << " (" << category
			<< ") Вага: " << GetWeight() << "г | Ціна: "
			<< GetPrice() << " грн | Час: " << cookTime << " хв" << std::endl;
	}

	/**
	 * @brief Серіалізація даних об'єкта у формат CSV для збереження у файл.
	 * Формує рядок, де поля розділені комами. Порядок полів критично важливий
	 * для коректного зчитування методом RestaurantManager::LoadFromFile.
	 */
	std::string ToCsv() const override {
		return std::to_string(GetId()) + "," + GetName() + "," + std::to_string(GetPrice()) + ","
			+ std::to_string(GetWeight()) + "," + category + "," + std::to_string(cookTime);
	}

	// --- Гетери та сетери ---

	/**
	 * @brief Повертає назву категорії страви.
	 */
	std::string GetCategory() const { return category; }

	/**
	 * @brief Оновлює категорію страви.
	 */
	void SetCategory(const std::string& cat) { category = cat; }

	/**
	 * @brief Повертає встановлений час приготування страви.
	 */
	int GetCookTime() const { return cookTime; }

	/**
	 * @brief Оновлює час приготування з логічною валідацією.
	 * Запобігає встановленню від'ємного або нульового часу приготування.
	 */
	void SetCookTime(int time) {
		if (time > 0)
			cookTime = time;
	}

	// --- Бізнес-логіка та аналітичні методи ---

	/**
	 * @brief Перевіряє, чи вважається страва "швидкою" (Fast Food).
	 * @return true, якщо приготування займає менше 15 хвилин
	 */
	bool isFastFood() const { return cookTime < 15; }

	/**
	 * @brief Визначає страви, що потребують тривалої підготовки (складні страви).
	 * @return true, якщо приготування займає більше 40  хвилин
	 */
	bool RequiresLongPreparation() const { return cookTime > 40; }

	/**
	 * @brief Формує сервісне повідомлення для офіціанта або клієнта.
	 * @return Рядок з інформацією про орієнтовний час очікування
	 */
	std::string GetPreparationInfo() const {
		return "Час очікування: " + std::to_string(cookTime) + " хв.";
	}
};

#endif 