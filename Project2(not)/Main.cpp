#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <sqlite3.h>
#include <fstream>

using namespace std;

void display_abonent(sqlite3* DB);
void rewrite_the_lines(sqlite3* DB);
void TASK3();
void TASK4();


int main() {
	sqlite3* DB;
	sqlite3_stmt* stmt;

	//Create a folder in the document folder with any name. Copy the path. Paste it instead of 
	//C:\\Documents\\ (there is another path below, give the same path instead of C:Documents\\). That's all
	const char* path = C:\\Documents\\abonents.db";
	int exit = sqlite3_open(path, &DB);

	if (exit != SQLITE_OK) {
		cerr << "\nFailed to open database" << sqlite3_errmsg(DB) << endl;
		return -1;
	}

	const char* sql = "CREATE TABLE IF NOT EXISTS ABONENTS("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NAME TEXT NOT NULL,"
		"NUMBER TEXT NOT NULL);";

	exit = sqlite3_exec(DB, sql, NULL, 0, 0);
	if (exit != SQLITE_OK) {
		cerr << "\nRequest error" << sqlite3_errmsg(DB) << endl;
		sqlite3_close(DB);
		return -1;
	}
	while (true) {
		char quest;
		cout << "\nTo display DB[1]\
\nInsert file[2]\
\nTask 3[3]\
\nTask 4[4]\
\nexit[0]";
		cin >> quest;
		switch (quest) {
		case '1':	display_abonent(DB); break;
		case '2':	rewrite_the_lines(DB); break;
		case '3':	TASK3(); break;
		case '4':	TASK4(); break;
		case '0':
			sqlite3_close(DB);
			return 0;
		}
	}






	return 0;
}

//It seems to work
#pragma region Task 4
void TASK4() {
	string reading_path;
	int counter = 0;

	cout << "\nEnter the path to the input .txt file:\n";
	cin.ignore();

	getline(cin, reading_path);

	ifstream file(reading_path + ".txt");

	if (!file) {
		cerr << "File doesn't not exists";
		return;
	}


	string buffer_result;

	while (!file.eof()) {
		counter++;
		string buffer;

		getline(file, buffer);

		buffer_result += buffer + '\n';
	}
	file.close();

	string result;
	bool was = false;



	int index = 0;
	for (int i = 0; i < counter; i++) {

		string buffer;
		char sym = ' ';

		for (int a = index; sym != '\n'; a++) {
			sym = buffer_result[a];
			buffer += buffer_result[a];
			index++;
		}

		result += buffer;

		auto how_to_name = find(buffer.begin(), buffer.end(), ' ');

		if (how_to_name == buffer.end()) {
			was = true;

			for (int a = 0; a < 12; a++) {
				result += "-";
			}

			result += '\n';
		}
	}

	if (!was) {
		result += '\n';

		for (int a = 0; a < 12; a++) {
			result += "-";
		}

		result += '\n';
	}

	string recording_path;

	cout << "\nEnter the path to the output .txt file:\n";

	getline(cin, recording_path);


	ofstream to_f(recording_path + ".txt");

	if (!to_f.is_open()) {
		cerr << "\nFailed to create output file.\n";
		return;
	}

	to_f << result;
	to_f.close();
	return;

}
#pragma endregion


#pragma region Task 3
void TASK3() {
	string reading_path;
	cout << "\nEnter the path to the input .txt file:\n";
	cin.ignore();
	getline(cin, reading_path);

	ifstream from_f(reading_path + ".txt");
	if (!from_f.is_open()) {
		cerr << "\nFailed to open input file.\n";
		return;
	}

	string result;
	string line;
	while (getline(from_f, line)) {
		result += line + "\n";
	}
	from_f.close();

	int length = result.length();
	for (int i = 0; i < length / 2; ++i) {
		swap(result[i], result[length - i - 1]);
	}

	string recording_path;
	cout << "\nEnter the path to the output .txt file:\n";
	getline(cin, recording_path);

	ofstream to_f(recording_path + ".txt");
	if (!to_f.is_open()) {
		cerr << "\nFailed to create output file.\n";
		return;
	}

	to_f << result;
	to_f.close();

	cout << "\nSuccessfully reversed and saved to file.\n";
}

#pragma endregion


#pragma region Task 2
void rewrite_the_lines(sqlite3* DB) {
	//The path to the database from which the name value will be taken (it is necessary to specify the number of the column counting from 0).
	const char* path2 = C:Documents\\abonents_input.db";

	//As I said, you need to specify the number of the name column and the number (there is no phone in that table, 
	// instead of the number there is a year. But there should be no mistakes)
	int index_name = 1;
	int index_number = 2;

	sqlite3* DB2;
	sqlite3_stmt* stmt2, * stmt;
	int exit2 = sqlite3_open(path2, &DB2);
	if (exit2 != SQLITE_OK) {
		cerr << "Failed to open the second DB: " << sqlite3_errmsg(DB2);
		return;
	}

	//unless you have a second data table
	string sql = "CREATE TABLE IF NOT EXISTS MUSIC_FOR_TEST("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NAME TEXT NOT NULL,"
		"NUMBER TEXT NOT NULL);";

	int exit = sqlite3_exec(DB2, sql.c_str(), NULL, 0, 0);
	if (exit != SQLITE_OK) {
		cerr << "\nFailed create second table: " << sqlite3_errmsg(DB2) << endl;;
		sqlite3_close(DB2);
		return ;
	}

	//I want to add data to the second table
	sql = "INSERT INTO MUSIC_FOR_TEST (NAME, NUMBER) VALUES (\"Hello World\", \"+380563718\")";
	exit = sqlite3_exec(DB2, sql.c_str(), NULL, 0, 0);
	if (exit != SQLITE_OK) {
		cerr << "\nFailed create second table: " << sqlite3_errmsg(DB2) << endl;
		sqlite3_close(DB2);
		return;
	}
	else{
		cout<<"\nData has been successfully added to the second data plate" << endl; 
	}


	const char* sql2 = "SELECT * FROM MUSIC_FOR_TEST";
	exit2 = sqlite3_prepare_v2(DB2, sql2, -1, &stmt2, 0);
	if (exit2 != SQLITE_OK) {
		cerr << "Failed prepare request: " << sqlite3_errmsg(DB2);
		sqlite3_close(DB2);
		return;
	}


	while ((exit2 = sqlite3_step(stmt2)) == SQLITE_ROW) {
		sql = "INSERT INTO ABONENTS (NAME, NUMBER) VALUES(?, ?);";
		exit2 = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);
		if (exit2 != SQLITE_OK) {
			cerr << "Failed prepare request: " << sqlite3_errmsg(DB);
			return;
		}
		//The sqlite3_column_text function returns const_unsigned_char*. const char* data type is required. Well, I found a way to convert them.
		sqlite3_bind_text(stmt, 1, reinterpret_cast<const char*>(sqlite3_column_text(stmt2, index_name)), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt, 2, reinterpret_cast<const char*>(sqlite3_column_text(stmt2, index_number)), -1, SQLITE_TRANSIENT);
		int exit = sqlite3_step(stmt);
		if (exit != SQLITE_DONE) {
			cerr << "\nRequest error*: " << sqlite3_errmsg(DB) << endl;
			sqlite3_finalize(stmt);
			sqlite3_finalize(stmt2);
			sqlite3_close(DB2);
			return;
		}
	}
	cout << "\nSuccessfully rewrite" << endl;
}
#pragma endregion


#pragma region Task 1
void display_abonent(sqlite3* DB) {
	sqlite3_stmt* stmt;
	const char* sql = "SELECT * FROM ABONENTS";
	int exit = sqlite3_prepare_v2(DB, sql, -1, &stmt, 0);
	if (exit != SQLITE_OK) {
		cerr << "\nRequest preparation error*" << sqlite3_errmsg(DB) << endl;
		return;
	}

	string selected_values;

	cout << "\nto display id[1] name[2] numbers[3]\n\033[31m(Enter the numbers you need IN ONE LINE)\033[0m\n";
	cin.ignore();
	getline(cin, selected_values);

	int id_index = 0;
	int name_index = 1;
	int number_index = 2;

	bool ticket1 = false, ticket2 = false, ticket3 = false;

	for (char i : selected_values) {
		if (i == '1') {
			ticket1 = true;
		}
		if (i == '2') {
			ticket2 = true;
		}
		if (i == '3') {
			ticket3 = true;
		}
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int id_value = sqlite3_column_int(stmt, id_index);
		const unsigned char* name_value = sqlite3_column_text(stmt, name_index);
		const unsigned char* number_value = sqlite3_column_text(stmt, number_index);
		if (ticket1)			cout << "\nID: " << id_value << endl;
		if (ticket2)			cout << "\nName: " << name_value << endl;
		if (ticket3)			cout << "\nNumber: " << number_value << endl;
	}
}
#pragma endregion
