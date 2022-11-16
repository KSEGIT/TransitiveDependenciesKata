/*
Transitive Dependecies Kata
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
	//map data structure for dependecies
	std::map <std::string, std::vector<std::string>>* _dependencyMap;
	//decided to use sets which run O(log n) time vs (vector O(n)) which is much more efficient with large numbers of elements and preventing duplicates when iterating
	std::set <std::string>* _completelist;

public:
	DependenciesGraph() {
		_dependencyMap = new std::map <std::string, std::vector<std::string>>();
		_completelist = new std::set <std::string>;
	};
	~DependenciesGraph() {
		delete _dependencyMap;
		delete _completelist;
	}
	void addDependency(const std::string& token, std::vector<std::string> dependecies) {
		_dependencyMap->insert({ token , dependecies });
	}

	//printing map for debug
	void printMap() const {
		std::cout << "mymap contains:\n";
		for (std::map<std::string, std::vector<std::string>>::iterator it = _dependencyMap->begin(); it != _dependencyMap->end(); ++it) {
			std::cout << it->first << ": ";
			std::vector <std::string> inVector = it->second;
			for (unsigned j = 0; j < inVector.size(); j++) {
				std::cout << inVector[j] << " ";
			}
			std::cout << std::endl;
		}
	}

	// getting direct dependencies and runing iteration on transitive dependencies (returns full dependency list)
	std::string tokenDependency(std::string const& token) {
		//making sure that set is clear
		_completelist->clear();
		//adding direct dependecies 
		std::copy(_dependencyMap->at(token).begin(), _dependencyMap->at(token).end(), std::inserter(*(_completelist), _completelist->end()));
		//scan for transitive dependencies
		std::set<std::string>::iterator it = _completelist->begin();
		while (it != _completelist->end())
		{
			//guard to block circular dependency
			if (*it != token)
			{
				//There was memory leak when no "key" found inside map. Call map.at() was forbidding compiler to create key with null value
				std::copy((*_dependencyMap)[(*it)].begin(), (*_dependencyMap)[(*it)].end(), std::inserter(*(_completelist), _completelist->end()));
				++it;
			}
			else
			{
				return "circular dependency found!";
			}
		}
		//creating dependencies string
		std::string finalString = "";
		for (std::string i : *(_completelist))
			finalString += i + " ";
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
	//dataTree.printMap();

	std::cout << dataTree.tokenDependency("A") << " \n";
	std::cout << dataTree.tokenDependency("B") << " \n";
	std::cout << dataTree.tokenDependency("C") << " \n";
	std::cout << dataTree.tokenDependency("D") << " \n";
	std::cout << dataTree.tokenDependency("E") << " \n";
	std::cout << dataTree.tokenDependency("F") << " \n";

	std::cout << "\n =============== Part 2 ===============\n";
	static DependenciesGraph dataTree2;
	dataTree2.addDependency("A", { "B" });
	dataTree2.addDependency("B", { "C" });
	dataTree2.addDependency("C", { "A" });
	//dataTree2.printMap();

	std::cout << dataTree2.tokenDependency("A") << " \n";
	std::cout << dataTree2.tokenDependency("B") << " \n";
	std::cout << dataTree2.tokenDependency("C") << " \n";

	std::cin >> holder;
	return 0;
}
