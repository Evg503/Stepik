#include <vector>
#include <string>
#include <iostream>

using namespace std;

string trim(const string& s)
{
	const string delims = " \r\n\t";
	auto b = s.find_first_not_of(delims);
	auto e = s.find_last_not_of(delims);
	return string(s.begin()+b, s.begin()+e+1);
}

int main1()
{
	vector<string> commands;
	while(cin)
	{
		string s;
		getline(cin, s, '|');

		if(cin)
			commands.push_back(move(trim(s)));
	}

	for( const auto& s:commands)
		cout << "Run:[" << s << "]" << endl;
}

int main()
{
	string s;
	getline(cin, s);
	FILE * p = popen(s.c_str(), "r");
	FILE * out = fopen("/home/box/result.out", "w");
	int c;
	while((c=fgetc(p)) != EOF)
	{
		fputc(c, out);
	}
	pclose(p);
	fclose(out);
}

