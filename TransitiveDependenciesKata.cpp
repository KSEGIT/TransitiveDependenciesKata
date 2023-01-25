/*
"Transitive Dependencies Kata" from:
http://codekata.com/kata/kata18-transitive-dependencies/
author: Daniel Kiska
date: 16.11.2022
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <set>

char* holder;

class DependenciesGraph {
private:
	//map data structure for dependencies
	std::map <std::string, std::vector<std::string>> _dependencyMap;
	//sets which run O(log n) time vs(vector O(n)) which is much more efficient with large numbers of elements and prevents duplicates when iterating
	std::set <std::string> _completelist;
public:
	//adding dependencies for token
	void addDependency(const std::string& token, const std::vector<std::string>& dependencies) {
		_dependencyMap.insert({ token , dependencies });
	}

	//printing map for debug
	void printMap2() const {
		std::cout << "My map contains:\n";
		for (const auto& [key, value] : _dependencyMap) {
			std::cout << key << ": ";
			for (const auto& dep : value) {
				std::cout << dep << " ";
			}
			std::cout << std::endl;
		}
	}

	void recurseCheck(const std::string& key, const std::string& token) {
			_completelist.insert(key);
			for (const std::string& it : _dependencyMap[key]) {
				if (it != token) {
					recurseCheck(it, token);
				}
				else {
					std::cout << "Circular dependency found! Provide correct dependencies. \n";
				}
			}
	}

	// getting direct dependencies and running iteration on transitive dependencies (returns full dependency list)
	std::string tokenDependency(const std::string& token) {
		//Iterating direct dependencies
		_completelist.clear();
		for (const std::string& it : _dependencyMap[token]) {
			if (it != token) {
				recurseCheck(it, token);
			}
			else {
				return "Circular dependency found! Provide correct dependencies.";
			}
		}
		//creating dependencies string
		std::string finalString;
		for (const std::string& it : _completelist)
			finalString += it + " ";
		return token + ": " + finalString;
	}
};

int main()
{
	std::cout << "Transitive Dependencies Kata\n\n";

	std::cout << "\n =============== Part 1 =============== \n";
	static DependenciesGraph dataTree;
	dataTree.addDependency("A", { "B", "C" });
	dataTree.addDependency("B", { "C", "E" });
	dataTree.addDependency("C", { "G" });
	dataTree.addDependency("D", { "A", "F" });
	dataTree.addDependency("E", { "F" });
	dataTree.addDependency("F", { "H" });
	//dataTree.printMap2();
	std::cout << dataTree.tokenDependency("A") << " \n";
	std::cout << dataTree.tokenDependency("B") << " \n";
	std::cout << dataTree.tokenDependency("C") << " \n";
	std::cout << dataTree.tokenDependency("D") << " \n";
	std::cout << dataTree.tokenDependency("E") << " \n";
	std::cout << dataTree.tokenDependency("F") << " \n";

	std::cout << "\n =============== Part 2 =============== \n";
	static DependenciesGraph dataTree2;
	dataTree2.addDependency("A", { "B" });
	dataTree2.addDependency("B", { "C" });
	dataTree2.addDependency("C", { "A" });
	//dataTree2.printMap2();
	std::cout << dataTree2.tokenDependency("A") << " \n";
	std::cout << dataTree2.tokenDependency("B") << " \n";
	std::cout << dataTree2.tokenDependency("C") << " \n";

	std::cout << "\n =============== Part 3 =============== \n";
	dataTree.addDependency("I", { "J" });
	dataTree.addDependency("J", { "A" });
	std::cout << dataTree.tokenDependency("I") << " \n";

	std::cin >> holder;
	return 0;
}
