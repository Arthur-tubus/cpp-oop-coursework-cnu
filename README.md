# Restaurant Dish Order Management System

This repository contains a C++ Object-Oriented Programming coursework project developed for Chernivtsi National University. The project implements a Restaurant Dish Order Management System, demonstrating core OOP principles such as encapsulation, inheritance, polymorphism, composition, operator overloading, exception handling, and file processing.

---

### 🇺🇦 Мова інтерфейсу / Language
Проєкт та весь його інтерфейс (меню, вивід у консоль, робота з користувачами) реалізовані **виключно українською мовою**.

---

## 🛠️ Як зібрати та запустити проєкт (Building the Project)

Для збірки проєкту вам знадобляться компілятор з підтримкою **C++17** (або новіше) та встановлений **CMake**.

### 1. Компіляція проєкту
1. Відкрийте термінал або командний рядок (cmd) безпосередньо у **кореневій папці** проєкту (там, де знаходяться папки `src`, `include` та файл `CMakeLists.txt`).
2. Послідовно виконайте наступні команди для створення папки збірки та компіляції:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   
### 2. Налаштування ресурсів 
Після успішної збірки виконайте наступні кроки, щоб програма бачила необхідні дані:
1. Перейдіть у папку resources у корені проєкту.
2. Скопіюйте всі файли звідти (menu.csv та accounts.txt).
3. Перейдіть у папку згенерованого виконуваного файлу: build -> Debug (або build -> Release, залежно від конфігурації).
4. Вставте скопійовані файли в цю папку (туди, де лежить ваш .exe файл)
