#include "LSys.hpp"
#include <boost/algorithm/string.hpp>
#include <iostream>

LSys::LSys()
{
	rules["A"] = "BAF";
	rules["B"] = "F[-B][+B]CB";
	rules["C"] = "CA-";

	currentExpr = "A";
	currentIter = 0;
}

LSys::LSys(const map<string, string> &rules) :
	rules(rules)
{
	currentExpr = "A";
	currentIter = 0;
}


void LSys::iter(int steps)
{
//	cout << "from: " << currentExpr << endl;
	while(steps > 0)
	{
		applyRules();
//		cout << currentExpr << endl;
		currentIter++;
		steps--;
	}
}

void LSys::applyRules()
{
	string str = currentExpr;
	unsigned int i=0, size=str.size();
	string c;
	while(i<size)
	{
		c = string(1, str[i]);
		if( rules.count(c)>0 )
		{
			// do replacement
			str.replace(i, 1, rules[c]);
			i += (rules[c].size()-1);
			size = str.size();
		}
		i++;
	}


	currentExpr = str;
}
