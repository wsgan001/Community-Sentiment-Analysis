#include "word2idx.h"


map<int, string> load_idx2word(string path)
{
	map<int, string> idx2word;
	ifstream infile(path);
	string line;
	while (std::getline(infile, line))
	{
        line = trim(line);
		std::istringstream iss(line);
		int idx;
		iss >> idx;
        int loc = line.find('\t');
		string word = line.substr(loc+1);
		idx2word[idx] = word;
	}
	return idx2word;
}

map<string, int > reverse_idx2word(const Idx2Word& idx2word)
{
	map<string, int> rev;

	for (auto item : idx2word)
	{
		int index = item.first;
		string word = item.second;
		rev[word] = index;
	}
	return rev;
}
