#include "MenuItem.h"
#include <iostream>
#include <utility>

/** @brief Конструктор за замовчуванням. */
MenuItem::MenuItem() : id(0), name("Unknown"), price(0.0), weight(0.0) {}

/** @brief Конструктор з параметрами. */
MenuItem::MenuItem(int id, std::string name, double price, double weight)
	: id(id), name(name), price(price), weight(weight) {
}

/** @brief Конструктор копіювання. */
MenuItem::MenuItem(const MenuItem& other)
	: id(other.id), name(other.name), price(other.price), weight(other.weight) {
	std::cout << "[INFO] Викликано конструктор копіювання: " << name << std::endl;
}

/** @brief Конструктор переміщення. */
MenuItem::MenuItem(MenuItem&& other) noexcept
	:id(other.id),
	name(std::move(other.name)),
	price(other.price),
	weight(other.weight) {
	other.id = 0;
	std::cout << "[INFO] Викликано конструктор переміщення" << std::endl;
}

/** @brief Віртуальний деструктор для забезпечення правильного очищення пам'яті. */
MenuItem::~MenuItem() {
	//std::cout << "[DESTRUCTOR] Об'єкт '" << name << "' знищено." << std::endl;
}