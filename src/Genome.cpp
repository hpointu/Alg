#include "Genome.hpp"
#include <cstdlib>
#include <map>
#include <iostream>
Genome::Genome()
{
	singleSymbols[0] = 'F';
	singleSymbols[1] = '+';
	singleSymbols[2] = '-';
	singleSymbols[3] = 'A';
	singleSymbols[4] = 'B';
	singleSymbols[5] = 'C';

	schemes[0] = "B";
	schemes[1] = "[-CF-CF-CF-CF]CF[+CF+CF+CF+CF]";
	schemes[2] = "BF";
}

LSys Genome::getLSys() const
{
	std::map<std::string, std::string> rules;
	rules["A"] = schemes[0];
	rules["B"] = schemes[1];
	rules["C"] = schemes[2];

	return LSys(rules);
}

void Genome::mutateRandomScheme()
{
	int scheme = rand()%2 +1;
	int mutype = rand()%15;
//	mutype = 3;

	std::cout << "Mutation type: " << mutype << std::endl;
	std::cout << "Scheme: " << scheme << std::endl;
	std::cout << "-> " << schemes[scheme] << std::endl;

	switch(mutype)
	{
	case 0:
	case 1:
	case 2:
		transformOneChar(scheme);
		break;
	case 3:
	case 4:
	case 5:
		addBrackets(scheme);
		break;
	case 6:
	case 7:
	case 8:
		removeBrackets(scheme);
		break;
	case 9:
	case 10:
	case 11:
		addOneChar(scheme);
		break;
	case 12:
	case 13:
	case 14:
		removeOneChar(scheme);
		break;
	default:
		break;
	}
	std::cout << "-> " << schemes[scheme] << std::endl;
}

void Genome::transformOneChar(int scheme)
{
	std::string str = schemes[scheme];
	if(str.size() > 0)
	{
		unsigned int pos = rand()%str.size();
		while(str[pos] == '[' || str[pos] == ']')
		{
			pos++;
		}
		if(pos < str.size())
		{
			char newChar = singleSymbols[rand()%6];
			std::string s = std::string(1, newChar);

			str.replace(pos, 1, s);
			schemes[scheme] = str;
		}
	}
}

void Genome::addOneChar(int scheme)
{
	std::string str = schemes[scheme];
	int pos = str.size()>0 ? rand()%str.size() : 0;
	char newChar = singleSymbols[rand()%6];
	str.insert(pos, 1, newChar);
	schemes[scheme] = str;
}

void Genome::removeOneChar(int scheme)
{
	std::string str = schemes[scheme];
	if(str.size() > 0)
	{
		unsigned int pos = rand()%str.size();
		while(str[pos] == '[' || str[pos] == ']')
		{
			pos++;
		}
		if(pos < str.size())
		{
			str.erase(pos, 1);
			schemes[scheme] = str;
		}
	}
}

bool Genome::hasBrackets(int scheme)
{
	std::string str = schemes[scheme];
	return str.find('[') != str.npos;
}

void Genome::addBrackets(int scheme)
{
	if(!hasBrackets(scheme))
//	if(true)
	{
		std::string str = schemes[scheme];
		int pos1 = str.size()>0 ? rand()%str.size() : 0;
		int pos2 = str.size()>0 ? rand()%str.size() : 0;

		if(pos1 == pos2) pos2++;

		int o = pos2>pos1 ? pos1 : pos2;
		int c = pos2>pos1 ? pos2 : pos1;

		str.insert(o, 1, '[');
		str.insert(c, 1, ']');

		schemes[scheme] = str;
	}
}

void Genome::removeBrackets(int scheme)
{
//	if(hasBrackets(scheme))
	if(false)
	{
		std::string str = schemes[scheme];
		size_t o = str.find('[');
		if(o != str.npos)
		{
			str.erase(o,1);
			size_t c = str.find(']');
			if(c != str.npos)
				str.erase(c,1);
			schemes[scheme] = str;
		}
	}
}
