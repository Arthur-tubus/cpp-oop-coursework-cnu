#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

//using namespace std;

/**
 * @class User
 * @brief Клас для представлення облікового запису користувача системи.
 * Зберігає облікові дані та визначає рівень доступу.
 */
class User {
private:
	std::string username;  ///< Логін користувача
	std::string password;  ///< Пароль для автентифікації
	bool isAdminRole; ///< Ознака прав адміністратора

public:
	/**
	 * @brief Конструктор з параметрами.
	 * @param u Логін користувача.
     * @param p Пароль.
     * @param admin Ознака прав адміністратора (за замовчуванням false - звичайний користувач).
	 */
	User(std::string u, std::string p, bool admin = false)
		: username(u), password(p), isAdminRole(admin) {
	}

	/**
	 * @brief Конструктор копіювання
	 * Забезпечує коректне копіювання даних акаунта
	 */
	User(const User& other)
		:username(other.username),
		password(other.password),
		isAdminRole(other.isAdminRole) {
	}

	/**
	 * @brief Деструктор класу.
	 */
	~User() {}

	// --- ГЕТТЕР (Інкапсуляція даних) ---

	/** @brief Повертає логін користувача. */
	std::string GetUsername() const { return username; }

	/** @brief Повертає пароль (виконується при перевірці входу). */
	std::string GetPassword() const { return password; }

	/** @brief Перевіряє, чи має користувач права адміністратора. */
	bool IsAdmin() const { return isAdminRole; }

	/**
	 * @brief Формування рядка для збереження у файл users.txt .
	 * Використовує роздільник ':' для надійності збереження.
	 * @return Рядок формату "login:password:isAdmin"
	 */
	std::string ToFileString() const {
		return username + ":" + password + ":" + (isAdminRole ? "1" : "0");
	}

};

#endif