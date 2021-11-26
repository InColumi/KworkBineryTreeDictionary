#include <iostream>
#include <iostream>
#include <fstream>
#include <cstringt.h>

using namespace std;

struct TreeNode
{
	string key;
	string value;
	TreeNode* left, * right;
	TreeNode(string k, string v)
	{
		key = k;
		value = v;
		left = right = NULL;
	}
};

class BineryTree
{
private:
	TreeNode* _root;

public:

	BineryTree()
	{
		_root = NULL;
	}

	string find(string key)
	{
		TreeNode* n = find(_root, key);
		return (n != NULL ? n->value : "not found");
	}

	void insert(string key, string value)
	{
		insert(_root, key, value);
	}

	void remove(string key)
	{
		remove(_root, key);
	}

	/*void loadToFile(string fileName)
	{
		traverse(n->left);
		printf("%d", n->value);
		traverse(n->right);

		ofstream inFile(fileName, ios::app);
		inFile << engWord << '\n';
		inFile << rusWord << '\n';
		inFile.close();
	}*/

	void Show()
	{
		Show(_root);
	}

private:

	void Show(TreeNode* n)
	{
		if(n == NULL)
			return;
		Show(n->left);
		cout << n->key << '\t' <<  n->value << '\n';
		Show(n->right);
	}

	TreeNode* find(TreeNode* n, string key)
	{
		if(n == NULL || key == n->key)
			return n;
		return find((key < n->key ? n->left : n->right), key);
	}

	void insert(TreeNode*& n, string key, string value)
	{
		if(n == NULL)
			n = new TreeNode(key, value);
		else if(key < n->key)
			insert(n->left, key, value);
		else
			insert(n->right, key, value);
	}

	TreeNode* successor(TreeNode* n)
	{
		TreeNode* r = n->right;
		while(r->left != NULL)
			r = r->left;
		return r;
	}

	void remove(TreeNode*& n, string key)
	{
		if(n == NULL)
			return;
		if(key == n->key)
		{
			if(n->left == NULL || n->right == NULL)
			{
				TreeNode* child = (n->left != NULL ? n->left : n->right);
				delete n;
				n = child;
			}
			else
			{
				TreeNode* succ = successor(n);
				n->key = succ->key;
				n->value = succ->value;
				remove(n->right, succ->key);
			}
			return;
		}
		if(key < n->key)
			remove(n->left, key);
		else
			remove(n->right, key);
	}
};

//struct TreeNode
//{
//	char rusWord[30];
//	char engWord[30];
//	TreeNode* Left, * Right;
//};
//
//TreeNode* tree = NULL;
//
//
//void addToFile(char rusWord[], char engWord[])
//{
//	ofstream of("data.txt", ios::app);
//	of << engWord << endl;
//	of << rusWord << endl;
//	of.close();
//}
//
//
//void push(char rusWord[], char engWord[], TreeNode** t)
//{
//	if((*t) == NULL) // создаем узел 
//	{
//		(*t) = new TreeNode;
//		copy(engWord, engWord + strlen(engWord), (*t)->engWord);
//		copy(rusWord, rusWord + strlen(rusWord), (*t)->rusWord);
//		(*t)->Left = (*t)->Right = NULL;
//		return;
//	}
//
//	if(strcmp((*t)->engWord, engWord) > 0)
//		push(rusWord, engWord, &(*t)->Right); // для ввода английского слова
//	else
//		push(rusWord, engWord, &(*t)->Left);// для ввода русского слова слова
//}
//
//bool success;
//void find(TreeNode* t, bool type, char findWord[])
//{
//	if(t == NULL) return;
//	else
//	{
//		if(!success)
//			find(t->Left, type, findWord);
//		else
//			return;
//		if(type)
//		{
//			if(strcmp(t->engWord, findWord) == 0)
//			{
//				cout << t->rusWord << endl;
//				success = true;
//				return;
//			}
//		}
//		else
//			if(strcmp(t->rusWord, findWord) == 0)
//			{
//				cout << t->engWord << endl;
//				success = true;
//				return;
//			}
//	}
//	if(!success)
//		find(t->Right, type, findWord);
//	else
//		return;
//}
//void Load(TreeNode** t)
//{
//	char buffer[30];
//	char buffer2[30];
//	ifstream of("data.txt");
//	if(of.is_open() == false)
//	{
//		cout << "File not found!\n";
//	}
//	while(!of.eof())
//	{
//		of >> buffer;
//		of >> buffer2;
//		if(strlen(buffer) > 0)
//			push(buffer2, buffer, t);
//	}
//	of.close();
//}

int main()
{
	setlocale(LC_ALL, "rus");
	/*bool type = true;
	int menu;
	char buffer[30], buffer2[30];
	Load(&tree);

	while(true)
	{
		if(type)
			cout << "Режим: Англо-русский словарь (поиск осуществляется по английскому слову)" << endl;
		else
			cout << "Режим: Русско-английский словарь(поиск по русскому слову)" << endl;
		cout << "Выберите действие" << endl;
		cout << "1. Добавить слово" << endl;
		cout << "2. Переключить режим работы" << endl;
		cout << "3. Поиск перевода слова" << endl;
		cout << "0. Выход" << endl;
		cin >> menu;
		switch(menu)
		{
			case 1:
				if(type)
				{
					cout << "Введите слово (по-русски)" << endl;
					cin >> buffer2;
					cout << "Введите перевод (по-английски)" << endl;
					cin >> buffer;
				}
				else
				{
					cout << "Введите слово (по-английски)" << endl;
					cin >> buffer;
					cout << "Введите перевод (по-русски)" << endl;
					cin >> buffer2;
				}
				push(buffer2, buffer, &tree);
				addToFile(buffer2, buffer);
				break;
			case 2:
				type = !type;
				break;
			case 3:
				cout << "Введите слово " << endl;
				cin >> buffer;
				success = false;
				find(tree, type, buffer);
				if(!success)
					cout << "Перевод не найден" << endl;
				break;
			case 0:
				break;
			default:
				cout << "Ошибка выбора" << endl;
				break;
		}
		if(menu == 0)
			break;
	}*/

	BineryTree a;
	a.insert("home", "дом");
	a.insert("hi", "привет");
	a.Show();
	return 0;
}