#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

std::map<std::string, std::vector<std::string> > dictionary;

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
		dictionary[sorted].push_back(word);
	}
}

bool find_words(std::string target, std::vector<std::string> &words) {
	std::sort(target.begin(), target.end());
	auto iter = dictionary.find(target);
	if (iter != dictionary.end()) {
		words = iter->second;
	}
	return iter != dictionary.end();
}

int main(){
	init();
	std::string problem;
	std::cin >> problem;
	std::vector<std::string> answers;
	if(find_words(problem, answers)) {
		for(auto element: answers){
			std::cout << element << ",";
		}
		std::cout << std::endl;
	}

	//for(auto &word : word) {
	//	std::cout << word.first << std::endl;
	//	for(int i = 0; i < word.second.size(); i++) {
	//		std::cout << word.second[i] << ",";
	//	}
	//	std::cout << std::endl;
	//}
	return 0;
}
