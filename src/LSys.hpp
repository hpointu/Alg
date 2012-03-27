#ifndef LSYS_HPP
#define LSYS_HPP

#include <map>
#include <string>

using namespace std;
class LSys
{
public:
	LSys();
	LSys(const map<string, string> &rules);

	void iter(int steps = 1);

	inline string str() const { return currentExpr; }

private:
	void applyRules();

	string currentExpr;
	int currentIter;
	map<string,string> rules;
};

#endif // LSYS_HPP
