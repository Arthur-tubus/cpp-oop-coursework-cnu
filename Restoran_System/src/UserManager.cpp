#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

/**
* @brief Конструктор за замовчуванням
* Ініціалізує порожній менеджер без авторизованого користувача.
*/
UserManager::UserManager() :currentUser(nullptr) {}

/**
* @brief Конструктор копіювання.
* Створює глибоку копію (Deep Copy) Списку користувачів, виділяючи нову пам'ять
* для кожного об'єкта, щоб уникнути конфліктів при видаленні.
*/
UserManager::UserManager(const UserManager& other) :currentUser(nullptr) {
	for (auto u : other.users) {
		users.push_back(new User(*u));
	}
}

/**
 * @brief Конструктор переміщення.
 * Ефективно передає ресурси від одного
 * об'єкта до іншого без зайвого копіювання.
 */
UserManager::UserManager(UserManager&& other) noexcept
	:users(std::move(other.users)), currentUser(other.currentUser) {
	other.currentUser = nullptr;
}

/**
 * @brief Деструктор класу.
 * Проходить по вектору вказівників і звільняє пам'ять,
 * виділену під кожного User.
 */
UserManager::~UserManager() {
	for (auto u : users) {
		delete u;
	}
	//std::cout << "[DESTRUCTOR] UserManager знищено, пам'ять очищена." << std::endl;
}

/**
 * @brief Алгоритм авторизації.
 * Перебирає базу користувачів і порівнює логін/пароль.
 * @return true, якщо знайдено збіг, інакше false.
 */
bool UserManager::Login(const std::string& login, const std::string& pass) {
	for (auto u : users) {
		if (u->GetUsername() == login && u->GetPassword() == pass) {
			currentUser = u; // Встановлюємо вказівник на активну сесію
			return true;
		}
	}
	return false;
}

/**
 * @brief Реєстрація нового користувача.
 * Включає валідацію вхідних даних створенням об'єкта.
 */
void UserManager::CreateUser(const std::string& login, const std::string& pass, bool admin) {
	if (login.empty() || pass.empty()) {
		throw std::invalid_argument("Логін або пароль не можуть бути порожніми");
	}
	users.push_back(new User(login, pass, admin));
	std::cout << "Успішно створено новий акаунт!" << std::endl;
}

std::string UserManager::GetLogin() const {
	if (this->currentUser == nullptr)
		return "Гість";
	return this->currentUser->GetUsername();
}

bool UserManager::RegisterUser(const std::string& login, const std::string password, bool isAdmin){
	// Перевірка, чи логін вільний
	for (auto u : users) {
		if (u->GetUsername() == login)
			return false;
	}

	users.push_back(new User(login, password, isAdmin));

	SaveUsersToFile("users.txt");
	return true;
}

/**
 * @brief Видалення користувача за логіном.
 * Використовує ідіому Erase-Remove для безпечного видалення з вектора.
 */
void UserManager::DeleteUser(const std::string& login) {
	// Захист від самовидалення (логічна система безпеки)
	if (currentUser && currentUser->GetUsername() == login) {
		throw std::runtime_error("Ви не можете видаляти власний обліковий запис!");
	}

	// Використання лямбда-виразу для пошуку видалення об'єкта
	auto it = std::remove_if(users.begin(), users.end(), [&](User* u) {
		if (u->GetUsername() == login) {
			delete u; // Звільняємо пам'ять перед видаленням вказівника
			return true;
		}
		return false;
		});

	if (it != users.end()) {
		users.erase(it, users.end()); // Видаляємо "сміття" з кінця вектора  
		std::cout << "Користувача " << login << " успішно видалено.\n";
	}
	else {
		std::cout << "Користувача з таким логіном не знайдено.\n";
	}
}

/**
 * @brief Виведення списку облікових записів.
 * Допомагає адміністратору бачити структуру доступу в системі.
 */
void UserManager::ListUsers()const {
	std::cout << "\n--- Список зареєстрованих користувачів ---" << std::endl;
	for (const auto& u : users) {
		std::cout << "Логін: " << u->GetUsername()
			<< (u->IsAdmin() ? " [Admin]" : " [User]") << std::endl;
	}
}

/**
 * @brief Завантаження  користувачів із текстового файлу.
 * Використовує роздільник ':' для парсингу рядків.
 */
void UserManager::LoadUsersFromFile(const std::string& filename) {
	std::ifstream file(filename);
	try {
		if (!file.is_open()) {
			// Резервний механізм: якщо бази немає, створюємо root-адміна
			CreateUser("admin", "admin123", true);
			return;
		}

		std::string line;
		while (getline(file, line)) {
			std::stringstream ss(line);
			std::string u, p, isAdminStr;
			// Парсинг рядка формату логін:пароль:роль
			if (getline(ss, u, ':') && getline(ss, p, ':') && getline(ss, isAdminStr)) {
				users.push_back(new User(u, p, isAdminStr == "1"));
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Помилка при роботі з файлом користувачів: " << e.what() << std::endl;
	}
	file.close();
}

/**
 * @brief Збереження бази користувачів у файл.
 * Викликає метод ToFileString() для кожного об'єкта.
 */
void UserManager::SaveUsersToFile(const std::string& filename) const {
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Не вдалося відкрити файл для збереження користувачів.");
	}
	for (const auto u : users) {
		file << u->ToFileString() << std::endl;
	}
	file.close();
}