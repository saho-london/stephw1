#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <queue>
#include <set>

struct CompareByLength {
	bool operator()(const std::string &l, const std::string &r) const {
		return l.size() < r.size();
	}
};

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
			if (word[i] == 'q') {
				word.erase(word.begin() + i + 1);	
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


bool bfs(std::priority_queue<std::string, std::vector<std::string>, CompareByPoint> &que) {
	std::set<std::string> set;
	while(!que.empty()){
		std::vector<std::string> words;
		std::string q = que.top();
		que.pop();
		if(find_words(q, words)) {
			for(auto word: words) {
				std::cout << word << " ";
			}
			std::cout << std::endl;
			return true;
		}
		for(int i = 0; i < q.size(); i++){
			std::string temp = q;
			temp = q.substr(0, i) + q.substr(i + 1);
			auto iter = set.find(temp);
			if(iter != set.end()) {continue;}
			set.insert(temp);
			que.push(temp);
		}
	}
	return false;
}


int main(){
	init();
	std::string problem;
	std::cin >> problem;
	//std::vector<std::string> answers;
	
	std::priority_queue<std::string, std::vector<std::string>, CompareByPoint> que;

	que.push(problem);

	if(!bfs(que)) {
		std::cout << "nothing found" << std::endl;
	}

	//if(find_words(problem, answers)) {
	//	for(auto element: answers){
	//		std::cout << element << ",";
	//	}
	//	std::cout << std::endl;
	//}
	return 0;
}
