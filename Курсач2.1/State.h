#pragma once
#include <string>

class State
{
public:
	virtual std::string  exec() = 0;

	void setFrom(const std::string & temp)
	{
		from = temp;
	}



protected:
	std::string from;
};
