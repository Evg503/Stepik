#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>



int mem_distance(const std::string &str1, const std::string &str2);
int get_levenshtein_distance(const std::string &str1, const std::string &str2);

int get_levenshtein_distance(const std::string &str1, const std::string &str2) {
  int insert_distance = mem_distance(str1, str2.substr(1)) + 1;
  int delete_distance = mem_distance(str1.substr(1), str2) + 1;
  int match_distance = mem_distance(str1.substr(1), str2.substr(1)) + (str1[0] != str2[0]);
  return std::min({insert_distance, delete_distance, match_distance});
}

const int max_len = 128;
int D[max_len][max_len];

void init_D()
{
	for(int i = 0; i < max_len; ++i)
		for (int j = 0; j < max_len; ++j)
			D[i][j] = i*j==0?i+j:-1;
}


int mem_distance(const std::string &str1, const std::string &str2)
{
	size_t size1 = str1.size();
	size_t size2 = str2.size();
	if (D[size1][size2] == -1)
		D[size1][size2] = get_levenshtein_distance(str1, str2);
	return D[size1][size2];
}

int main(void) {
  init_D();

  std::string str1;
  std::string str2;

  std::cin >> str1 >> str2;  

  std::cout << get_levenshtein_distance(str1, str2) << std::endl;
}
