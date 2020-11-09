#include <iostream>


#include <string>
#include <map>
#include <regex>

using Int = long long;

std::string derivative(std::string p) {

    std::map<Int, Int> pp, in;
    std::regex r("(([+-]?\\d*)\\*?)?(x?)(\\^(\\d+))?");
    for(auto it = std::sregex_iterator(p.begin(), p.end(), r); it != std::sregex_iterator(); ++it)
    {
      if(it->str(0) == "") continue;
      Int k = 0;
      if (it->str(2) == "") k = 1;
      else if (it->str(2) == "+") k = 1;
      else if (it->str(2) == "-") k = -1;
      else k = atoi(it->str(2).c_str());
      Int power = 0;

      if (it->str(3) == "") power = 0;
      else if (it->str(5) == "") power = 1;
      else power = atoi(it->str(5).c_str());

      pp[power] += k;

    }
    for (auto& it:pp)
    {
      Int power = it.first;
      Int k = it.second;
      if (power > 0 && k != 0)
        in[power-1] = k*power;
    }
    std::string delim, result;

    for (auto& it:in)
    {
      Int power = it.first;
      Int k = it.second;
      std::ostringstream b;
      if (power == 0)
      {
        b<<k;
      }
      else
      {
        if (k != 1)
          b<<k<<"*";

        b<<"x";

        if(power != 1)
          b<<"^"<<power;

      }
      std::string nom = b.str();
      if(!result.empty() && result[0] == '-')
        delim = "";
       result = nom + delim + result;
       delim = "+";
    }
    return result;
}

bool check(std::string in, std::string expected)
{
   std::string result = derivative(in);
   if(result == expected)
   {
	std::cout<<".";
	return true;
   }
   else
   {
      std::cout << "\n expected:[" << expected << "]\n but return:[" << result << "]\n";
   }
}


int main()
{
	check("-x^2+x", "-2*x+1");
	check("2*x^100+100*x^2", "200*x^99+200*x");

	check("x^10000+x+1", "10000*x^9999+1");
	check("-x^2-x^3", "-3*x^2-2*x");
	check("x+x+x+x+x+x+x+x+x+x", "10");
	check("x+x+x+x+1-1+1+x+x+x", "7");
}
