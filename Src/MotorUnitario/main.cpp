#include <iostream>
#include <fstream>

using namespace std;

int main() {

	ifstream file("Levels\\fichero.txt");
	if (file.is_open()) {
		cout << "estoy abierto\n";
		file.close();
	}
	else cout << "no\n";

	int a;
	cin >> a;

	return 0;
}