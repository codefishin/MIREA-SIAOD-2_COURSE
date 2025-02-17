#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
using namespace std;


class AVLTree {
private:
    struct Node {
        string city;
        Node* left;
        Node* right;
        int height;

        Node(const string& city) : city(city), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    
    int height(Node* node) { return node ? node->height : 0; }
    int balanceFactor(Node* node) { return node ? height(node->left) - height(node->right) : 0; }

    void updateHeight(Node* node) {
        if (node) { node->height = max(height(node->left), height(node->right)) + 1; }
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        if (balanceFactor(node) > 1) {
            if (balanceFactor(node->left) < 0)
            {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }
        if (balanceFactor(node) < -1) {
            if (balanceFactor(node->right) > 0)
            {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }
        return node;
    }

    Node* insert(Node* node, const string& city) {
        if (!node) return new Node(city);
        if (city < node->city) node->left = insert(node->left, city);
        else if (city > node->city) node->right = insert(node->right, city);
        else return node;

        updateHeight(node);
        return balance(node);
    }
    void inorder(Node * node) {
        if (node) {
            inorder(node->left);
            cout << node->city << " ";
            inorder(node->right);
        }
    }
    void reverseInorder(Node* node) {
        if (node) {
            reverseInorder(node->right);
            cout << node->city << " ";
            reverseInorder(node->left);
        }
    }

    int findHeight(Node* node) {
        return node ? node->height : 0;
    }
    int findPathLength(Node* node, const string& city, int length = 0) {
        if (!node) return -1;
        if (node->city == city) return length;
        if (city < node->city) return findPathLength(node->left, city, length + 1);
        else return findPathLength(node->right, city, length + 1);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const string& city) { root = insert(root, city); }
    void inorder() {
        cout << "Симметричный обход: ";
        inorder(root);
        cout << endl;
    }
    void reverseInorder() {
        cout << "Обратный обход: ";
        reverseInorder(root);
        cout << endl;
    }
    int findHeight() {
        return findHeight(root);
    }
    int findPathLength(const string& city) {
        return findPathLength(root, city);
    }

    void displayMenu()
    {
        cout << "\nМеню:\n";
        cout << "1. Вставить элемент\n";
        cout << "2. Балансировать дерево (вставка уже балансирует)\n";
        cout << "3. Симметричный объод\n";
        cout << "4. Обратный обход\n";
        cout << "5. Найти длину пути от корня до значения\n";
        cout << "6. Найти высоту дерева\n";
        cout << "7. Выход\n";
    }
    void run()
    {
        while (true)
        {
            displayMenu();
            int choice;
            cout << "Выберите операцию: ";
            cin >> choice;
            system("cls");
            if (choice == 1) {
                string city;
                cout << "Введите название города для вставки: ";
                cin >> city;
                insert(city);
            }
            else if (choice == 2) {
                cout << "Дерево сбалансировано после каждой вставки.\n";
            }
            else if (choice == 3) inorder();
            else if (choice == 4) reverseInorder();
            else if (choice == 5)
            {
                string city;
                cout << "Введите город для поиска пути от корня: ";
                cin >> city;
                int pathLength = findPathLength(city);
                if (pathLength != -1) {
                    cout << "Длина пути от корня до города '" << city << "': " << pathLength << endl;
                }
                else {
                    cout << "Город не найден.\n";
                }
            }
            else if (choice == 6)
            {
                cout << "Высота дерева: " << findHeight() << endl;
            }
            else if (choice == 7) break;
            else {
                cout << "Неверный выбор, попробуйте снова.\n";
            }
        }
    }
};



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    AVLTree tree;
    tree.run();
    return 0;
}
