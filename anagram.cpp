#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

std::map<std::string, std::vector<std::string> > words;

void init() {
	std::ifstream ifs("dictionary.words");
	std::string word;
	while(ifs >> word) {
		for(int i = 0; i < word.size(); i++) {
			//Support only ASCII
			if (word[i] >= 'A' && word[i] <= 'Z') {
				word[i] += 'a' - 'A';
			}
		}
		std::string sorted = word;
		std::sort(sorted.begin(), sorted.end());
		words[sorted].push_back(word);
	}
}

int main(){
	init();
	std::string problem;
	std::cin >> problem;
	std::sort(problem.begin(), problem.end());
	auto iter = words.find(problem);
	if (iter != words.end()) {
		for(auto element: iter->second) {
			std::cout << element << ",";
		}
		std::cout << std::endl;
	}
	//for(auto &word : words) {
	//	std::cout << word.first << std::endl;
	//	for(int i = 0; i < word.second.size(); i++) {
	//		std::cout << word.second[i] << ",";
	//	}
	//	std::cout << std::endl;
	//}
	return 0;
}
