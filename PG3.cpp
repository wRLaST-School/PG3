#include <iostream>
#include <random>
#include <time.h>
#include <Windows.h>
#include <string>
#include <functional>
using namespace std;

void TimedFunc(std::function<void(void)> func, int waitSeconds) {
	Sleep(waitSeconds * 1000);
	func();
}

int main() {
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<> rand100(1, 100);

	string input;

	cout << "奇数か偶数か、予想を入力してください" << endl;

	cin >> input;

	while (input != "奇数" && input != "偶数") {
		cout << "\"奇数\"か\"偶数\"で入力してください。" << endl;
		cin >> input;
	}

	int theNum = rand100(mt);		
	int over = input == "奇数" ?
		1 :
		0;

	//コールバック処理
	std::function<void(void)> showResult = (theNum % 2 == over) ?
		std::function<void(void)>([&]() { cout << "結果は・・・ " << theNum << "! " << "正解！" << endl; }):
		std::function<void(void)>([&]() { cout << "結果は・・・ " << theNum << "! " << "残念！" << endl; });

	TimedFunc(showResult, 3);

	getchar();
	getchar();

	return 0;
}