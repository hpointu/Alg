#ifndef GENOME_HPP
#define GENOME_HPP

#include "LSys.hpp"
#include <string>

class Genome
{
public:
	Genome();

	void mutateRandomScheme();

	LSys getLSys() const;

private:
	void transformOneChar(int scheme);
	void addOneChar(int scheme);
	void removeOneChar(int scheme);
	void addBrackets(int scheme);
	void removeBrackets(int scheme);

	bool hasBrackets(int scheme);

	std::string schemes[3];
	char singleSymbols[6];
};

#endif // GENOME_HPP
