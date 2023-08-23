#pragma once

#include <string>

class App {
public:
	void mainMenu();

	template <typename T>
	bool convertValue(const std::string& input, T& value);

	template <typename T>
	void workWithBinTree();

	template <typename T>
	void workWithLinSearch();
};

