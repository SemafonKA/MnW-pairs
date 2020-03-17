#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <sstream>
#include <string>
#include <conio.h>
#include "Dlist.h"
#include "Chrono_Timer.h"
using namespace std;

const auto peopleCount = 5;
namespace matrix {
	using matrix = vector<vector<int>>;
	void out(matrix& mas) {
		cout << "\t";
		for (int i{ static_cast<int>(mas.at(0).size()) }; i > 0; --i) {
			cout << "\t[" << i << "]";
		}
		cout << endl;

		int i{ 0 };
		for (auto& elem : mas) {
			cout << i << ")\t\t";
			for (auto& values : elem) {
				cout << values << "\t";
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
		while (ss >> num) {
			elem.push_back(num);
		}
	}

	file.close();
	return size;
}

void pairMaker(matrix::matrix& man, matrix::matrix woman) {
	vector<bool> iswFree;
	vector<bool> ismFree;
	ismFree.resize(woman.size());
	iswFree.resize(man.size());
	for (int i{ 0 }; i < iswFree.size(); ++i) { iswFree.at(i) = true; }
	for (int i{ 0 }; i < ismFree.size(); ++i) { ismFree.at(i) = true; }

	int wPos{}, summary{};
	for (int i{ 0 }; i < woman.size(); ++i) {
		for (int k{ 0 }; k < woman.size(); ++k) {
			for (int j{ 0 }; j < man.size(); ++j) {
				if (!ismFree.at(j)) continue;
				wPos = man.at(j).at(k);
				if (iswFree.at(wPos) && woman.at(wPos).at(i) == j) {
					ismFree.at(j) = false;
					iswFree.at(wPos) = false;
					cout << "[" << j << "]\t><\t[" << wPos << "]\t Эффектность: (" << woman.size() - k << 
						"+" << man.size() - i << ")" << endl;
					summary += woman.size() - k + man.size() - i;
				}
			}			
		}
	}
	cout << "\t\t\t Суммарно:    (" << summary << ")" << endl;
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
			system("cls");
			cout << "\nМассивы заполняются...\n";
			matrix::random(man, peopleCount);
			matrix::random(woman, peopleCount);
			isLooped = false;
			break;
		case 50:
			system("cls");
			cout << "\nМассивы заполняются...\n";
			matrix::random(man, peopleCount);
			matrix::random(woman, peopleCount);
			priorityFileFill(fManPriority, man);
			priorityFileFill(fWomanPriority, woman);
			isLooped = false;
			break;
		case 51:
			system("cls");
			cout << "\nМассивы заполняются...\n";
			priorityFileGet(fManPriority, man);
			priorityFileGet(fWomanPriority, woman);
			isLooped = false;
			break;
		}

	}

	system("cls");
	cout << "\n[Стартовый массив мужчин]\n";
	if (man.size() < 50)	matrix::out(man);
	cout << "\n[Стартовый массив женщин]\n";
	if (woman.size() < 50)	matrix::out(woman);

	Timer tm;
	cout << "Предполагаемые пары\n М\t><\t Ж" << endl;
	pairMaker(man, woman);
	cout << "Выполнено за " << tm.elapsed() << " секунд(-ы)"<< endl;

	cout << "\nДля выхода нажмите ввод";
	cin.get();
	return 0;
}