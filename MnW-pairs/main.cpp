#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

constexpr auto countPeople = 4;
const string fManPriority = "\\Priorities\\manPriority.txt";
const string fWomanPriority = "\\priorities\\womanPriority.txt";

void fillPriorityFile(const string adress) {
	fstream file(adress, ios_base::in | ios_base::out | ios_base::trunc);
	if (!file) throw logic_error("Ошибка с файлом");
	file << 1 << 2 << 3 << 4;
	file.close();
}

int main() {
	fillPriorityFile(fManPriority);
	return 0;
}