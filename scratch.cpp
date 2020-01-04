#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> wordcount_map;

	std::vector<std::string> word_list = {"alice", "test", "market", "alice", "bambo", "gorgc", "gorgc"};

	for (auto word_var: word_list) {
		wordcount_map[word_var]++;
	}

	for (auto map_var: wordcount_map) {
		std::cout<< map_var.first << " occurs " << map_var.second << ((map_var.second>1)?" times" : " time") << '\n';
	}

	return 0;
}
