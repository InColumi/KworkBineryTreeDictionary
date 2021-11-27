#include <iostream>
#include <string>
#include <fstream>
#include <cstringt.h>

using namespace std;

/// <summary>
/// Структура для узлов дереа
/// </summary>
struct TreeNode
{
	/// <summary>
	/// Ключ узла
	/// </summary>
	string key;

	/// <summary>
	/// Значение узла
	/// </summary>
	string value;

	/// <summary>
	/// Указатель слева
	/// </summary>
	TreeNode* left;

	/// <summary>
	/// Указатель справа
	/// </summary>
	TreeNode *right;

	/// <summary>
	/// Конструктор с параметрами
	/// </summary>
	/// <param name="k">ключ</param>
	/// <param name="v">значение</param>
	TreeNode(string k, string v)
	{
		key = k;
		value = v;
		left = right = NULL; // указатели справа и слеа равнвы NULL 
	}
};

/// <summary>
/// Класс бинарное дерево
/// </summary>
class BineryTree
{
private:
	/// <summary>
	/// Корень дерева
	/// </summary>
	TreeNode* _root;

public:

	/// <summary>
	/// Консруктор по умолчанию
	/// </summary>
	BineryTree()
	{
		_root = NULL;
	}

	//деструктор
	~BineryTree()
	{
		freemem(_root);
	}

	//Освобождение памяти дерева
	void freemem(TreeNode* tree)
	{
		if(tree != NULL)    // если дерево не пустое
		{
			freemem(tree->left);   // рекурсивно удаляем левую ветку
			freemem(tree->right);  // рекурсивно удаляем правую ветку
			delete tree;           // удаляем корень
		}
	}

	/// <summary>
	/// поиск по ключу
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	string find(string key)
	{
		TreeNode* n = find(_root, key); // вызываем рекурсивный метод
		return (n != NULL ? n->value : "not found"); // взращаем значение, что нашли иначе вернуть "not fond"
	}

	/// <summary>
	/// Вставка нового узла в дерево
	/// </summary>
	/// <param name="key">ключ</param>
	/// <param name="value">значение</param>
	void insert(string key, string value)
	{
		insert(_root, key, value); // вызваем рекурсивный метод
	}

	/// <summary>
	/// Удаление по ключу
	/// </summary>
	/// <param name="key">ключ</param>
	void remove(string key)
	{
		remove(_root, key); // вызваем рекурсивный метод
	}

	/// <summary>
	/// Загрузка в файл
	/// </summary>
	/// <param name="fileName">имя файла</param>
	void loadToFile(string fileName)
	{
		ofstream inFile(fileName); // создаем файл для записи
		addToFile(_root, inFile); // вызваем рекурсивный метод
		inFile.close(); // закрываем файл
	}

	/// <summary>
	/// Добавить слово в файл
	/// </summary>
	/// <param name="fileName">имя файла</param>
	/// <param name="key">ключ</param>
	/// <param name="value">значение</param>
	void AddToFile(string fileName, string key, string value)
	{
		ofstream inFile(fileName, ios::app); // открываем файл если есть, иначе создаем. С ключём добавления в файл.
		inFile << key << '\t' << value << '\n';
		inFile.close(); // закрываем файл
	}

	/// <summary>
	/// Загрузка из файла
	/// </summary>
	/// <param name="fileName">имя файла</param>
	void loadFromFile(string fileName)
	{
		ifstream of(fileName); // открываем файл для считывания
		if(of.is_open() == false) // если файла нет
		{
			cout << "File not found!\n";
			return;
		}
		string key;
		string value;
		while(!of.eof()) // читаем до конца файла
		{
			of >> key;
			of >> value;
			if(key.size() > 0) // если длинна ключа больше нуля
				insert(key, value); // добавляем в дерево
		}
		of.close(); // закрываем файл
	}

	/// <summary>
	/// вывод дерева в консоль
	/// </summary>
	void Show()
	{
		Show(_root);// вызваем рекурсивный метод
	}

private:

	void Show(TreeNode* n)
	{
		if(n == NULL)// если корень равен NULL
			return;
		Show(n->left);// вызваем рекурсивный метод
		cout << n->key << '\t' << n->value << '\n';
		Show(n->right);// вызваем рекурсивный метод
	}

	void addToFile(TreeNode* n, ofstream& inFile)
	{
		if(n == NULL) // если корень равен NULL
			return;
		addToFile(n->left, inFile);// вызваем рекурсивный метод
		inFile << n->key << '\t' << n->value << '\n';
		addToFile(n->right, inFile);// вызваем рекурсивный метод
	}

	TreeNode* find(TreeNode* n, string key)
	{
		if(n == NULL || key == n->key) // если ключ равен ключу корневого узла или корень равен NULL
			return n;
		return find((key < n->key ? n->left : n->right), key);// вызваем рекурсивный метод. Если ключ меньше, то идём влево, иначе вправо. 
	}

	void insert(TreeNode*& n, string key, string value)
	{
		if(n == NULL)// если корень равен NULL
			n = new TreeNode(key, value); // создаем первый узел
		else if(key < n->key) // если ключ меньше идем влево
			insert(n->left, key, value); // вызваем рекурсивный метод
		else
			insert(n->right, key, value);// вызваем рекурсивный метод
	}

	/// <summary>
	/// Ищем узел слева
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	TreeNode* successor(TreeNode* n)
	{
		TreeNode* r = n->right;
		while(r->left != NULL)
			r = r->left;
		return r;
	}

	/// <summary>
	/// Удаление 
	/// </summary>
	/// <param name="n"></param>
	/// <param name="key"></param>
	void remove(TreeNode*& n, string key)
	{
		if(n == NULL)// если корень равен NULL
			return;
		if(key == n->key)
		{
			if(n->left == NULL || n->right == NULL)
			{
				TreeNode* child = (n->left != NULL ? n->left : n->right); // Если слева не ничего, то идем влево, иначе вправо
				delete n;  // удаляем
				n = child; // ставим следующий на предыдущий узел
			}
			else
			{
				TreeNode* succ = successor(n); // находим узел слева.
				n->key = succ->key;
				n->value = succ->value;
				remove(n->right, succ->key); // вызваем рекурсивный метод
			}
			return;
		}
		if(key < n->key) // ищем дальше
			remove(n->left, key); // вызваем рекурсивный метод
		else
			remove(n->right, key); // вызваем рекурсивный метод
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	BineryTree tree;
	bool isExit = false;
	int numberCommand;
	string userInput;
	string wordEng;
	string wordRus;
	cout << "Программа словаря на основе бинарного дерева(англо-русского словарь)\n\n";
	while(isExit == false)
	{
		cout << "Главное меню:\n";
		cout << "1 - загрузка словаря из файла\n";
		cout << "2 - запись словаря в файл\n";
		cout << "3 - добавить слово в программу\n";
		cout << "4 - найти слово\n";
		cout << "5 - удалить слово\n";
		cout << "6 - печать словаря\n";
		cout << "7 - добавить слово в файл\n";
		cout << "8 - выход из программы\n";
		cout << "Введите номер команды: ";
		cin >> userInput;
		try
		{
			numberCommand = stoi(userInput);
			switch(numberCommand)
			{
				case 1:
					cout << "Введите название файла с расширением (пример data.txt)\n";
					cin >> userInput;
					tree.loadFromFile(userInput);
					break;
				case 2:
					cout << "Введите название файла с расширением (пример data.txt)\n";
					cin >> userInput;
					tree.loadToFile(userInput);
					break;
				case 3:
					cout << "Введите слово(english): ";
					cin >> wordEng;
					cout << "Введите слово(russian): ";
					cin >> wordRus;
					tree.insert(wordEng, wordRus);
					break;
				case 4:
					cout << "Введите слово: ";
					cin >> userInput;
					cout << tree.find(userInput) << "\n";
					break;
				case 5:
					cout << "Введите слово: ";
					cin >> userInput;
					tree.remove(userInput);
					break;
				case 6:
					tree.Show();
					break;
				case 7:
					cout << "Введите название файла с расширением (пример data.txt)\n";
					cin >> userInput;
					cout << "Введите слово(english): ";
					cin >> wordEng;
					cout << "Введите слово(russian): ";
					cin >> wordRus;
					tree.AddToFile(userInput, wordEng, wordRus);
					break;
				case 8:
					isExit = true;
					break;
				default:
					cout << "Неверная команда!\n";
					break;
			}
			tree.Show();
		}
		catch(const std::exception& err)
		{
			cout << err.what() << endl;
		}
	}
	cout << "Программа закончила свою работу!\n";
	system("pause");
	return 0;
}