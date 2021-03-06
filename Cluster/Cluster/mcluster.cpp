#include "mcluster.h"

vector<int> MCluster::get_categories(int word) const
{
	if (word2categories.find(word) == word2categories.end())
	{
		return vector<int>();
	}

	vector<int> v = word2categories.find(word).operator*().second;
	return v;
}

vector<int> MCluster::get_words(int category) const
{
	if (category2words.find(category) == category2words.end())
	{
		return vector<int>();
	}

	vector<int> v = category2words.find(category).operator*().second;
	return v;
}

bool MCluster::different(int cword1, int cword2) const
{

	vector<int> v1, v2;
	if (cword1 > TEN_MILLION)
		v1 = get_words(cword1);
	else
		v1.push_back(cword1);

	if (cword2 > TEN_MILLION)
		v2 = get_words(cword2);
	else
		v2.push_back(cword2);

	vector<int> vr = vector_and_(v1, v2);
	return vr.size() == 0;
}

void MCluster::add_cluster(map<int, int>& cluster, int prefix)
{
	for (auto item : cluster)
	{
		int voca = item.first;
		int category = prefix + item.second;

		if (word2categories.find(voca) == word2categories.end())
			word2categories[voca] = vector<int>();

		word2categories[voca].push_back(category);


		if (category2words.find(category) == category2words.end())
			category2words[category] = vector<int>();

		category2words[category].push_back(voca);
	}
}

void MCluster::add_clusters(vector<string> paths)
{
	for (auto path : paths)
	{
		map<int, int> cluster1 = loadCluster(data_path + path);
		this->add_cluster(cluster1, m_base_id);
		m_base_id += TEN_MILLION;
	}
}

static function<Word_ID(int)> int2word = [](int item){return Word_ID(item); };


Set2<Word_ID> expand_word(int word, MCluster& cluster)
{
	Set2<Word_ID> word_ids;
	if (word < TEN_MILLION)
		word_ids.insert(word);
	else
	{
		vector<Word_ID> words = mapf(cluster.get_words(word), int2word);
		word_ids.add(words);
	}
	return word_ids;
}

function<string(int)> FunctorIdx2Word(MCluster mcluster, Idx2Word idx2word)
{
	function<string(int) > f = [mcluster, idx2word](int idx){
		if (idx > TEN_MILLION)
		{
			vector<int> idxs = mcluster.get_words(idx);
			size_t sublen = min(idxs.size(), (size_t)10);
			vector<int> subwords(idxs.begin(), idxs.begin() + sublen);
			function<string(int)> mapper = [idx2word](const int idx){
				auto token = idx2word.find(idx);
				if (token != idx2word.end()){
					string word = token.operator*().second;
					return word;
				}
				else
					return string("null");
			};
			vector<string> words = mapf(subwords, mapper);
			string ret = "g[";
			for (auto word : words)
				ret += string(word + ",");
			ret += "]";
			return ret;
		}
		else
		{
			string ret = idx2word.find(idx).operator*().second;
			return ret;
		}
	};
	return f;
}