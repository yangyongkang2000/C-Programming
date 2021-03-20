#include<string>
#include<cstddef>
#include<vector>
#include<cstdio>
#include<iostream>
#include<stdexcept>
#include"simplify_calculator.hpp"
int main()
{
	std::string s;
	while (true) {
		printf( ">>> ");
		char c;
		while ((c = getchar()) != '\n')
			if (c != ' ') s.push_back(c);
		simplify_calculator::trans_in_post_fix<std::vector>(s);
		s.clear();
	}
}


