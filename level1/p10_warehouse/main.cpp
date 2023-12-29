#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <string>

struct Database {
	::std::filesystem::path file;
	::std::map<::std::string, int> items;
	
	Database(::std::filesystem::path file):
		file{::std::move(file)},
		items{}
	{
		::std::ifstream in(this->file);
		::std::string name;
		int count;
		while (in >> name >> count) {
			this->items[name] = count;
		}
	}

	~Database() {
		::std::ofstream out(this->file);
		for (auto&& [name, count] : this->items) {
			out << name << ' ' << count << '\n';
		}
	}
};

int main() {
	using namespace ::std;
	namespace fs = ::std::filesystem;

	string name;
	cout << "Enter database file name: ";
	cin >> name;
	Database db(fs::current_path() / "db" / (name + ".txt"));

	while (true) {
		cout << "Type \"display\" to display all items\n";
		cout << "Type \"add\" to add an item\n";
		cout << "Type \"remove\" to remove an item\n";
		cout << "Type \"exit\" to exit\n";

		string command;
		cout << "Enter command: ";
		cin >> command;

		if (command == "display") {
			if (db.items.empty()) {
				cout << "No items\n";
			}
			else {
				for (auto&& [name, count] : db.items) {
					cout << name << ' ' << count << '\n';
				}
			}
		}
		else if (command == "add") [&]{
			cout << "Enter the name of the item: ";
			string name;
			cin >> name;
			cout << "Enter the number to add: ";
			int count;
			cin >> count;
			if (count <= 0) {
				cout << "Invalid number\n";
				return;
			}
			db.items[name] += count;
		}();
		else if (command == "remove") [&]{
			cout << "Enter the name of the item: ";
			string name;
			cin >> name;
			auto it = db.items.find(name);
			if (it == db.items.end()) {
				cout << "Item not found\n";
				return;
			}
			cout << "The number of item is " << it->second << '\n';
			cout << "Enter the number to remove: ";
			int count;
			cin >> count;
			if (count <= 0 || count > it->second) {
				cout << "Invalid number\n";
				return;
			}
			it->second -= count;
			if (it->second == 0) {
				db.items.erase(it);
			}
		}();
		else if (command == "exit") {
			break;
		}
		else {
			cout << "Unknown command: " << command << '\n';
		}

		cout << endl;
	}
	
	return 0;
}
