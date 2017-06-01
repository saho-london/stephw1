#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>


struct CompareByPoint {
	int lut[26] = {1, 1, 2, 1, 1, 2, 1, 2, 1, 3, 3, 2, 2, 1, 1, 2, 3, 1, 1, 1, 1, 2, 2, 3, 2, 3};

	int culculate_point(const std::string &str) const {
		int point = 0;
		for(int i = 0; i < str.size(); i++) {
			point += lut[(int)str[i] - 'a'];
		}
		return point;
	}

	bool operator()(const std::string &l, const std::string &r) const {
		return culculate_point(l) < culculate_point(r);
	}
};

std::vector<std::string> dictionary;

bool is_makeable(int given[], int target[]) {
	for(int i = 0; i < 26; i++) {
		if(given[i] < target[i]) {return false;}
	}
	return true;
}

void init() {
	std::ifstream ifs("dictionary.words");
	std::string word;
	while(ifs >> word) {
		for(int i = 0; i < word.size(); i++) {
			//Support only ASCII
			if (word[i] >= 'A' && word[i] <= 'Z') {
				word[i] += 'a' - 'A';
			}
			if (word[i] == 'q') {
				word.erase(word.begin() + i + 1);	
			}
		}
		dictionary.push_back(word);
	}
}

void string_to_array(std::string str, int array[]) {
	for(int i = 0; i < 26; i++) {
		array[i] = 0;
	}
	for(int i = 0; i < str.length(); i++) {
		array[str[i] - 'a']++;
	}
}

std::priority_queue<std::string, std::vector<std::string>, CompareByPoint> search_makeable(std::string problem) {
	int key[26];
	std::priority_queue<std::string, std::vector<std::string>, CompareByPoint> result;

	string_to_array(problem, key);
	for(auto word:dictionary) {
		int target[26];
		string_to_array(word, target);
		if(is_makeable(key, target)) {result.push(word);}
	}
	return result;
}


int main(){
	init();

	std::string problem;

	std::cin >> problem;

	std::priority_queue<std::string, std::vector<std::string>, CompareByPoint> result = search_makeable(problem);

	if(result.empty()) {
		std::cout << "nothing found" << std::endl;
	} else {
		std::cout << result.top() << std::endl;
		result.pop();
	}

	return 0;
}
