#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "User.h"

/**
 * @class UserManager
 * @brief Клас-контролер для управління обліковими записами користувачів.
 * Відповідає за аутентифікацію (Login), авторизацію (Rights) та збереження даних акаунтів.
 */
class UserManager {
private:
	std::vector<User*> users; ///< Поліморфна колекція зареєстрованих користувачів.
	User* currentUser; ///< Вказівник на активну сесію (nullptr, якщо не авторизовано)

public:
	// --- КОНСТРУКТОРИ ТА ДЕСТРУКТОРИ ---

	/**
	 * @brief Конструктори за замовчуванням
	 */
	UserManager();

	/**
	 * @brief Конструктор копіювання для створення дубліката бази користувачів.
	 */
	UserManager(const UserManager& other);

	/**
	 * @brief Конструктор переміщення для оптимізації передачі даних.
	 */
	UserManager(UserManager&& other) noexcept;

	/**
	 * @brief Деструктор.
	 * Гарантує очищення динамічної пам'яті для всіх об'єктів User
	 */
	~UserManager();

	// --- СИСТЕМА АВТОРИЗАЦІЇ ---

	std::string GetLogin() const;

	bool RegisterUser(const std::string& login, const std::string password, bool isAdmin);
	/**
	 * @brief Виконує вхід користувача в систему.
	 * @return true - якщо пара логін/пароль вірна, false - в іншому випадку
	 */
	bool Login(const std::string& login, const std::string& pass);

	/** @brief Скидає вказівник поточного користувача (вихід із системи). */
	void Logout() { currentUser = nullptr; }

	/** @brief Повертає вказівник на поточного авторизованого користувача. */
	User* GetCurrentUser() const { return currentUser; }

	// --- ФУНКЦІЇ АДМІНІСТРАТОРА ---

	/** @brief Реєстрація нового користувача в системі. */
	void CreateUser(const std::string& login, const std::string& pass, bool admin = false);

	/** @brief Видаляє акаунт за логіном (з перевіркою на самовидалення). */
	void DeleteUser(const std::string& login);

	/** @brief Виводить список користувачів (доступно лише адміністратору). */
	void ListUsers() const;

	// --- РОБОТА З ФАЙЛАМИ ---

	/** @brief Завантаження бази користувачів із текстового файлу. */
	void LoadUsersFromFile(const std::string& filename);

	/** @brief Синхронізація поточної колекції користувачів із файлом. */
	void SaveUsersToFile(const std::string& filename) const;

};

#endif 
