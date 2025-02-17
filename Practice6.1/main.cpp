#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct UniversityRecord {
    string universityName;  // Название университета
    string codeSpecialty;   // Код специальности
    int yearOfEstablishment; // Год основания университета;
};

class HashTable {
private:
    vector<UniversityRecord*> table;  // Массив для хранения записей
    int currentSize;                  // Текущий размер таблицы
    int capacity;                     // Вместимость таблицы

    // Хеш-функция, которая будет рассчитывать индекс по коду специальности
    int hashFunction(const string& codeSpecialty) {
        int hash = 0;
        for (char ch : codeSpecialty) {
            hash = (hash * 31 + ch) % capacity; // Простой метод вычисления хеша
        }
        return hash;
    }

    // Функция расширения таблицы (рехеширование)
    void rehash() {
        int newCapacity = capacity * 2;
        vector<UniversityRecord*> newTable(newCapacity, nullptr);

        // Перехеширование всех записей
        for (auto& record : table) {
            if (record != nullptr) {
                int index = hashFunction(record->codeSpecialty) % newCapacity;
                while (newTable[index] != nullptr) {
                    index = (index + 1) % newCapacity; // Линейное пробирование
                }
                newTable[index] = record;
            }
        }

        // Обновляем таблицу и вместимость
        table = newTable;
        capacity = newCapacity;
    }

public:
    HashTable(int initialCapacity = 10) : capacity(initialCapacity), currentSize(0) {
        table.resize(capacity, nullptr);
    }

    // Вставка нового элемента
    void insert(const UniversityRecord& record) {
        if (currentSize >= capacity / 2) {
            rehash();
        }

        int index = hashFunction(record.codeSpecialty) % capacity;
        while (table[index] != nullptr) {
            index = (index + 1) % capacity;  // Линейное пробирование
        }

        table[index] = new UniversityRecord(record);
        currentSize++;
    }

    // Поиск по ключу (коду специальности)
    UniversityRecord* search(const string& codeSpecialty) {
        int index = hashFunction(codeSpecialty) % capacity;
        int initialIndex = index;

        while (table[index] != nullptr) {
            if (table[index]->codeSpecialty == codeSpecialty) {
                return table[index];
            }
            index = (index + 1) % capacity;
            if (index == initialIndex) break;  // Вернулись к начальной позиции
        }
        return nullptr;  // Элемент не найден
    }

    // Удаление записи по ключу (коду специальности)
    void remove(const string& codeSpecialty) {
        int index = hashFunction(codeSpecialty) % capacity;
        int initialIndex = index;

        while (table[index] != nullptr) {
            if (table[index]->codeSpecialty == codeSpecialty) {
                delete table[index];
                table[index] = nullptr;
                currentSize--;
                return;
            }
            index = (index + 1) % capacity;
            if (index == initialIndex) break;
        }
    }

    // Вывод всех записей в таблице
    void printTable() {
        cout << "Current records in the hash table:" << endl;
        for (int i = 0; i < capacity; ++i) {
            if (table[i] != nullptr) {
                cout << "Index " << i << ": " << table[i]->universityName
                    << ", " << table[i]->codeSpecialty
                    << ", Year of Establishment: " << table[i]->yearOfEstablishment << endl;
            }
        }
    }
};
void showMenu() {
    cout << "\nChoose an operation:" << endl;
    cout << "1. Insert a university record" << endl;
    cout << "2. Search for a university by specialty code" << endl;
    cout << "3. Remove a university record" << endl;
    cout << "4. Print all university records" << endl;
    cout << "5. Exit" << endl;
}

int main() {
    HashTable hashTable;

    while (true) {
        showMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            UniversityRecord record;
            cout << "Enter university name: ";
            cin.ignore();  // Для игнорирования оставшегося символа новой строки после ввода числа
            getline(cin, record.universityName);

            cout << "Enter specialty code (e.g., '09.03.01'): ";
            cin >> record.codeSpecialty;

            cout << "Enter year of establishment: ";
            cin >> record.yearOfEstablishment;

            hashTable.insert(record);
        }
        else if (choice == 2) {
            string codeSpecialty;
            cout << "Enter specialty code to search: ";
            cin >> codeSpecialty;

            UniversityRecord* record = hashTable.search(codeSpecialty);
            if (record != nullptr) {
                cout << "Found record: " << record->universityName
                    << ", " << record->codeSpecialty
                    << ", Year of Establishment: " << record->yearOfEstablishment << endl;
            }
            else {
                cout << "Record not found." << endl;
            }
        }
        else if (choice == 3) {
            string codeSpecialty;
            cout << "Enter specialty code to remove: ";
            cin >> codeSpecialty;

            hashTable.remove(codeSpecialty);
        }
        else if (choice == 4) {
            hashTable.printTable();
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
