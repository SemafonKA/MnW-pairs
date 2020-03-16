#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include <string>
#include <conio.h>
#include "Dlist.h"
using namespace std;

const auto peopleCount = 4;
namespace matrix {
	using matrix = vector<vector<int>>;
	void out(matrix& mas) {
		int i{ 0 };
		for (auto& elem : mas) {
			cout << i << ") ";
			for (auto& values : elem) {
				cout << values << " ";
			}
			cout << endl;
			++i;
		}
		cout << endl;
	}
	void random(matrix& newMatrix, const int size) {
		newMatrix.resize(0);
		newMatrix.resize(size);
		random_device rd;

		Dlist<int> priorityList;
		for (auto& elem : newMatrix) {
			for (int i = 0; i < size; ++i) {
				priorityList.push_back(i);
			}
			static int pos{};
			while (!priorityList.isEmpty()) {
				pos = rd() % priorityList.size();
				elem.push_back(priorityList.remove(pos));
			}
		}
	}
}

const string fManPriority = "priorities\\manPriority.txt";
const string fWomanPriority = "priorities\\womanPriority.txt";
void priorityFileFill(const string& adress, matrix::matrix mas) {
	fstream file(adress, ios_base::out | ios_base::trunc);
	if (!file) throw logic_error("Беда с файлом");

	if (mas.empty()) matrix::random(mas, peopleCount);
	file << peopleCount << endl;
	for (auto& elem : mas) {
		for (auto num : elem) {
			file << num << " ";
		}
		file << endl;
	}

	file.close();
}

int priorityFileGet(const string& adress, matrix::matrix& mas) {
	fstream file(adress, ios_base::in);
	if (!file) throw logic_error("Беда с файлом");

	int size{};
	file >> size;
	mas.resize(0);
	mas.resize(size);
	
	string str;
	getline(file, str);
	stringstream ss;
	for (auto& elem : mas) {
		getline(file, str);
		ss.clear();
		ss << str;
		static int num{};
		while (ss >> num && !ss.eof()) {
			elem.push_back(num);
		}
	}

	file.close();
	return size;
}

int main() {
	system("chcp 65001"); system("cls");

	matrix::matrix man;
	matrix::matrix woman;
	
	for (bool isLooped = true; isLooped; ) {
		cout << "Выберите вариант создания матрицы: " << endl;
		cout << "  1) Получить случайные матрицы (без записи в файл)" << endl <<
			"  2) Получить случайные матрицы (и записать в файл)" << endl <<
			"  3) Загрузить матрицы из файлов" << endl;
		switch (_getch()) {
		case 49:
			matrix::random(man, peopleCount);
			matrix::random(woman, peopleCount);
			isLooped = false;
			break;
		case 50:
			matrix::random(man, peopleCount);
			matrix::random(woman, peopleCount);
			priorityFileFill(fManPriority, man);
			priorityFileFill(fWomanPriority, woman);
			isLooped = false;
			break;
		case 51:
			priorityFileGet(fManPriority, man);
			priorityFileGet(fWomanPriority, woman);
			isLooped = false;
			break;
		}
	}

	matrix::out(man);
	matrix::out(woman);

	cout << "\nДля выхода нажмите ввод";
	std::cin.get();
	return 0;
}