/**
 * @file main.cpp
 * @brief Головний файл програмної системи "Restaurant Management System".
 * * Цей файл містить точку входу в програму (функцію main), реалізацію
 * головного циклу подій, обробку консольного інтерфейсу, а також логіку
 * взаємодії між користувачем (клієнтом/адміністратором) та менеджерами системи.
 */

#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <Windows.h>

#include "UserManager.h"
#include "RestaurantManager.h"
#include "Order.h"

 /**
  * @brief Допоміжна функція для очищення буфера введення.
  * * Використовується для скидання прапорців помилок потоку std::cin та
  * очищення залишкових символів у буфері. Запобігає нескінченному
  * зацикленню програми при введенні текстових символів замість числових значень.
  */
void static СlearInput() {
	std::cin.clear();
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

/**
 * @brief Відображення головного меню адміністратора.
 * * Виводить у консоль перелік доступних дій для облікового запису з правами адміністратора.
 * Реалізує принцип розмежування прав доступу в системі.
 */
void static ShowAdminMenu() {
	std::cout
		<< "\n=== ПАНЕЛЬ АДМІНІСТРАТОРА ===\n"
		<< "1. Вивести список страв та напоїв\n"
		<< "2. Управління меню\n"
		<< "3. Управління акаунтам користувачів\n"
		<< "0. Вихід та збереження\n"
		<< "Ваш вибір: ";
}

/**
 * @brief Відображення підменю для CRUD-операцій з об'єктами меню.
 * * Виводить опції для додавання нових позицій (страв або напоїв),
 * їх редагування та видалення з бази даних (MenuItem).
 */
void static ShowMenuManagement() {
	std::cout
		<< "\n--- УПРАВЛІННЯ МЕНЮ ---\n"
		<< "1. Додати нову страву\n"
		<< "2. Додати новий напій\n"
		<< "3. Редагування існуючу позицію\n"
		<< "4. Видалити позицію за ID\n"
		<< "0. Повернутися назад\n"
		<< "Ваш вибір: ";
}

/**
 * @brief Виведення довідкової інформації.
 * * Короткий посібник (інструкція) для користувача системи щодо
 * правил навігації, збереження даних та призначення ролей.
 */
void static ShowHelp() {
	std::cout << "\n======= ДОПОМОГА (ІНСТРУКЦІЯ) =======\n"
		<< "\n1. Для входу введіть логін та пароль.\n"
		<< "\n2. Пункти меню обираються введеням відповідної цифри.\n"
		<< "\n3. Адміністратор має право на редагування даних.\n"
		<< "\n4. При виході (клавіша 0) дані зберігаються автоматично.\n"
		<< "\n=====================================\n";
}

/**
 * @brief Відображення меню для клієнта (Користувача).
 * * Виводить перелік дій, доступних для звичайного клієнта без адміністративних привілеїв:
 * перегляд меню, пошук, сортування та робота з кошиком замовлень.
 */
void static ShowUserMenu() {
	std::cout
		<< "\n--- МЕНЮ КЛІЄНТА ---\n"
		<< "1. Переглянути меню страв та напоїв\n"
		<< "2. Пошук страв та напоїв\n"
		<< "3. Сортування меню за ціною\n"
		<< "4. Додати страву до замовлення\n"
		<< "5. Розрахувати вартість (Чек)\n"
		<< "6. Допомога\n"
		<< "0. Вихід\n"
		<< "Ваш вибір: ";
}


/**
 * @brief Головна функція програми.
 * * Відповідає за ініціалізацію кодування консолі, створення об'єктів менеджерів,
 * завантаження початкових даних з файлів та управління нескінченним циклом подій
 * (автентифікація та обробка запитів користувачів).
 * * @return int Код завершення програми (0 - успішне виконання).
 */
int main() {
	// Встановлення кодування Windows-1251 для коректної підтримки кирилиці в консолі
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	// Ініціалізація керуючих класів (Менеджерів)
	UserManager userMgr;
	RestaurantManager restMgr;
	Order currentOrder;

	// Спроба завантаження бази даних при запуску
	try {
		userMgr.LoadUsersFromFile("users.txt");
		restMgr.LoadFromFile("menu.csv");
	}
	catch (const std::exception& e) {
		std::cerr << "Помилка ініціалізації: " << e.what() << std::endl;
	}

	while (true) {
		int authChoice = -1;

		// --- БЛОК АВТОРИЗАЦІЇ ---
		while (userMgr.GetCurrentUser() == nullptr) {

			std::cout << "\n========== ГОЛОВНЕ МЕНЮ ==========\n";
			std::cout << "1. Увійти\n";
			std::cout << "2. Створити нового користувача (Реєстрація)\n";
			std::cout << "3. Допомога (Інструкція)\n";
			std::cout << "0. Вихід\n";
			std::cout << "----------------------------------\n";
			std::cout << "Ваш вибір:";

			std::string input;
			std::getline(std::cin, input);

			// Перевірка на порожній рядок (просто натиснули Enter)
			if (input.empty()) {
				std::cout << "\nУВАГА: Ви нічого не ввели. Спробуйте ще раз!" << std::endl;
				continue;
			}
			// Перевірка на коректність числа
			if (input != "0" && input != "1" && input != "2" && input != "3") {
				std::cout << "\nПомилка: Невірний вибір! Введіть 0, 1, 2 або 3."<<std::endl;
				continue;
			}
			// Спроба перетворити рядок на число
			try {
				authChoice = std::stoi(input);
			}
			catch (const std::invalid_argument&) {
				// Відпрацює, якщо ввели літери або символи
				std::cout << "\nУВАГА: Введіть число!" << std::endl;
				continue;
			}			

			if (authChoice == 0)
				return 0; // Повний вихід з програми
			if (authChoice == 1) {
				// Авторизація користувача
				std::string  login, pass; 
				
				std::cout << "\nЛогін: "; getline(std::cin, login);
				std::cout << "Пароль: "; getline(std::cin, pass);

				if (!userMgr.Login(login, pass)) {
					std::cout << "Неправильний логін або пароль!\n";
				}
			}
			else if (authChoice == 2) {
				// Реєстрація користувача
				std::string  login, pass;

				std::cout << "\nВведіть новий логін: "; getline(std::cin, login);
				std::cout << "Введіть новий пароль: "; getline(std::cin, pass);

				if (userMgr.RegisterUser(login, pass, false)) {
					std::cout << "Реєстрація успішна! Тепер ви можете увійти.\n";
				}
				else {
					std::cout << "Користувач з таким логіном вже існує!\n";
				}
			}
			else if (authChoice == 3) {
				ShowHelp();
			}
		}

		int choice = -1;
		bool isLogout = false;

		std::cout << "\nВхід успішний!\n" << std::endl;

		// --- ГОЛОВНИЙ ЦИКЛ ОБРОБКИ ПОДІЙ (після входу) ---
		while (!isLogout) {
			try {
				User* user = userMgr.GetCurrentUser();

				// Перевірка ролі та виведення відповідного інтерфейсу
				if (user->IsAdmin()) {
					ShowAdminMenu();
				}
				else {
					ShowUserMenu();
				}

				if (!(std::cin >> choice))
					throw std::invalid_argument("Введіть число!");
				std::cin.ignore();

				if (choice == 0) { // Завершення сесії користувача
					userMgr.Logout();
					isLogout = true;
					std::cout << "Вихід з системи успішний.\n";
					break;
				}

				// --- БЛОК ФУНКЦІОНАЛУ АДМІНІСТРАТОРА ---
				if (user->IsAdmin()) {
					switch (choice) {
					case 1: { // Розділений вивід категорій з поліморфним перетворенням
						restMgr.DisplayDishes();
						restMgr.DisplayDrinks();
						break;
					}
					case 2: { // Підменю управління базою MenuItem (CRUD операції)
						int subChoice = -1;
						while (subChoice != 0) {
							ShowMenuManagement();
							std::cin >> subChoice;

							// Збереження змін та вихід з підменю
							if (subChoice == 0) {
								restMgr.SaveToFile("menu.csv");
								userMgr.SaveUsersToFile("users.txt");
								break;
							}

							// Створення об'єкта Dish
							if (subChoice == 1) {
								int id = restMgr.GenerateNextId();
								std::string name, cat; double p, w; int t;

								std::cout << "\n-------------------------------------"
									<< "\n   ДОДАВАННЯ НОВОЇ СТРАВИ (ID: " << restMgr.GenerateNextId() << ")"
									<< "\n-------------------------------------\n";


								std::cout << "Назва страва: ";
								std::cin.ignore(); getline(std::cin, name);

								std::cout << "Категорія: ";
								getline(std::cin, cat);

								std::cout << "Ціна: ";
								if (!(std::cin >> p))
									throw std::invalid_argument("Некоректна ціна!");

								std::cout << "Вага: ";
								if (!(std::cin >> w))
									throw std::invalid_argument("Некоректна вага!");

								std::cout << "Час приготування: ";
								if (!(std::cin >> t))
									throw std::invalid_argument("Некоректна час!");

								restMgr.AddItem(new Dish(id, name, p, w, cat, t));
								std::cout << "Страву успішно додано!\n";
							}
							// Створення об'єкта Drink
							else if (subChoice == 2) {
								int id = restMgr.GenerateNextId();
								std::string name; double p, v, w; bool alc;

								std::cout << "\n-------------------------------------"
									<< "\n   ДОДАВАННЯ НОВОГО НАПОЮ (ID: " << restMgr.GenerateNextId() << ")"
									<< "\n-------------------------------------\n";

								std::cout << "Назва напою: ";
								std::cin.ignore(); getline(std::cin, name);

								std::cout << "Ціна: ";
								if (!(std::cin >> p))
									throw std::invalid_argument("Некоректна ціна!");

								std::cout << "Вага (загальна маса подачі): ";
								if (!(std::cin >> w))
									throw std::invalid_argument("Некоректна вага!");

								std::cout << "Об'єм (рідина): ";
								if (!(std::cin >> v))
									throw std::invalid_argument("Некоректний об'єм!");

								std::cout << "Алкогольний (1/0): ";
								if (!(std::cin >> alc))
									throw std::invalid_argument("Введіть 1 або 0!");

								restMgr.AddItem(new Drink(id, name, p, v, v, alc));
								std::cout << "Напій успішно додано!\n";
							}
							/// Редагування існуючих записів за ID
							else if (subChoice == 3) {
								int id;
								std::cout << "\nID для редагування: ";
								
								if (!(std::cin >> id))
									throw std::invalid_argument("Некоректно введено ID!");
								restMgr.EditItem(id);
							}
							// Видалення об'єкта з бази за ID
							else if (subChoice == 4) {
								int id;
								std::cout << "\nID для видалення: ";
								if (!(std::cin >> id))
									throw std::invalid_argument("Некоректно введено ID!");
								restMgr.RemoveById(id);
							}
						}
						choice = -1; // Повернення до головного адмін-меню
						break;
					}
					case 3: { // Підменю управління обліковими записами
						int userChoice = -1;
						while (userChoice != 0) {
							std::cout
								<< "\n--- УПРАВЛІННЯ АКАУНТАМИ ---"
								<< "\n1. Список"
								<< "\n2. Створити"
								<< "\n3. Видалити"
								<< "\n0. Назад"
								<< "\nВаш вибір: ";
							if (!(std::cin >> userChoice))
								throw std::invalid_argument("Некоректно введено ID!");
							
							// Виведення списку всіx зареєстрованих користувачів
							if (userChoice == 1) {
								userMgr.ListUsers();
							}
							// Адміністративне створення нового користувача з визначенням ролі
							else if (userChoice == 2) {
								std::string n, p;
								int r;
								std::cout << "\nЛогін: "; std::cin >> n;
								std::cout << "Пароль: "; std::cin >> p;

								std::cout << "Роль(1-адмін/0-клієнт): ";
								
								if(!(std::cin >> r))
									throw std::invalid_argument("Некоректна обрання ролі!");

								userMgr.CreateUser(n, p, r == 1);
							}
							// Видалення користувача за логіном (із перевіркою самовидалення)
							else if (userChoice == 3) {
								std::string l;
								std::cout << "\nЛогін: "; std::cin >> l;
								userMgr.DeleteUser(l);
							}

						}
						choice = -1;
						break;
					}
					case 0: { // Збереження всіх даних у файли та завершення програми
						restMgr.SaveToFile("menu.csv");
						userMgr.SaveUsersToFile("users.txt");
						return 0;
					}
					}
				}
				// --- БЛОК ФУНКЦІОНАЛУ КОРИСТУВАЧА ---
				else {
					switch (choice) {
					case 1: { // Виведення повного електронного меню
						restMgr.DisplayDishes();
						restMgr.DisplayDrinks();
						break;
					}
					case 2: { // Універсальний пошук (регістронезалежний)
						std::string query;
						std::cout << "\n================ ПОШУК У МЕНЮ ================\n"
							<< " Ви можете шукати за:\n"
							<< " - Назвою (напр. 'борщ' або 'сік')\n"
							<< " - Категорією страв (напр. 'десерти')\n"
							<< " - Вмістом алкоголю для напоїв ('алко' або 'б/а')\n"
							<< "----------------------------------------------\n"
							<< "Введіть запит: ";

						std::cin.ignore(); getline(std::cin, query);
						restMgr.SearchItems(query);
						break;
					}
					case 3: { // Поліморфне сортування колекції за ціною
						restMgr.SortByPrice();
						std::cout << "Меню відсортовано за ціною." << std::endl;
						restMgr.DisplayDishes();
						restMgr.DisplayDrinks();
						break;
					}
					case 4: { // Формування замовлення (додавання об'єкта до кошика)
						int id;
						std::cout << "Введіть ID позиції для замовлення: ";
						std::cin >> id;

						MenuItem* item = restMgr.FindById(id);
						if (item) {
							// RTTI: Якщо знайдений об'єкт є напоєм (Drink)
							if (Drink* dr = dynamic_cast<Drink*>(item)) {

								if (dr->NeedsIdCheck())
									std::cout << "\n[УВАГА]: Напій алкогольний! Перевірте документи!\n";

								std::cout << "[Інфо] Ціна за 1 літр: " << dr->CalculateLiterPrice() << " грн.\n";
								if (dr->IsFamilySize()) {
									std::cout << "[Порада] Це велика порція (Family Size), запропонуйте додаткові склянки.\n";
								}
							}

							// RTTI: Якщо знайдений об'єкт є стравою (Dish)
							if (Dish* ds = dynamic_cast<Dish*>(item)) {
								std::cout << "[Кухня] " << ds->GetPreparationInfo() << std::endl;

								if (ds->isFastFood())
									std::cout << "[Інфо] Ця страва готується швидко.\n";

								if (ds->RequiresLongPreparation()) {
									std::cout << "[Інфо] Увага: приготування займе тривалий час.\n";
								}
							}

							currentOrder.AddItem(item);
							std::cout << "Додано: " << item->GetName() << ". Товарів у кошику: " << currentOrder.GetItemsCount() << " шт." << std::endl;

						}
						else
							std::cout << "Помилка: ID не знайдено.\n";
						break;
					}
					case 5: { // Розрахунок вартості (Чек) та оплата
						if (currentOrder.IsEmpty()) {
							std::cout << "Кошик порожній!" << std::endl;
						}
						else {
							currentOrder.DisplayOrder();

							std::cout << "\n1 - Підтвердити та оплатити замовлення";
							std::cout << "\n2 - Очистити кошик";
							std::cout << "\n0 - Назад";
							std::cout << "\nВибір: ";

							int subChoice;
							std::cin >> subChoice;
							if (subChoice == 1) {
								Order archivedOrder = currentOrder;
								std::cout << "\nЧек оплачено на суму: " << currentOrder.CalculateTotal() << " грн." << std::endl;
								currentOrder.ClearOrder();
							}
							else if (subChoice == 2) {
								currentOrder.ClearOrder();
								std::cout << "Кошик очищеною\n";
							}
						}
						break;
					}
						  
					case 6: { // Довідник для користувача
						ShowHelp();
						break;
					}
					case 0: { // Безпечне завершення 
						return 0;
					}
					}
				}
			}
			catch (const std::exception& e) {
				// Централізована обробка виключних ситуацій циклу
				std::cout << "\nУВАГА: " << e.what() << std::endl;
				СlearInput();
			}
		}
	}

	return 0;
}