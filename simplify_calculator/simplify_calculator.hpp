#ifndef simplify_calculator_h
#define simplify_calculator_h
namespace simplify_calculator {
	constexpr bool priority[6] = {1,0,0,0,0,1};
	template<typename T>
	struct table {
		bool b=false;
		T x;
		char bin_op;
		table(char _) :bin_op(_) {};
		table(T _) :b(true), x(_) {};
	};
	template<template<typename ...>class V,typename T>
	inline void calc_post_fix(V<table<double>> &rpn) noexcept
	{
		static V<T> num;
		num.clear();
		for (auto& _ : rpn)
		{
			if (_.b)
				num.push_back(_.x);
			else {
				if (num.size() < 2)
				{
					printf("error: the expression is empty\n");
					return;
				}
				double r= num.back();
				num.pop_back();
				double l = num.back();
				num.pop_back();
				switch (_.bin_op)
				{
				case '+':
					num.push_back(l + r);
					break;
				case'-':
					num.push_back(l - r);
					break;
				case'*':
					num.push_back(l * r);
					break;
				case'/':
					if (r == 0)
					{
						printf("error :the denominator cannot be 0 \n");
						return;
					}
					num.push_back(l / r);
					break;
				default:
					printf("error : \"%c\" symbol is illegal \n", _.bin_op);
					break;
				}
			}
		}
		if (num.size() != 1)
		{
			printf("error: the expression is empty\n");
			return;
		};
		std::cout << num.back() << '\n';
	}
	template<template<typename ...> class V>
	inline void trans_in_post_fix( std::string const & s) 
	{
		if (s == "exit()")
			exit(EXIT_SUCCESS);
		static V<char> balance_symbol;
		static V<table<double>> rpn;
		static  V<char> operator_symbol;
		balance_symbol.clear();
		rpn.clear();
		operator_symbol.clear();
		size_t   i = 0;
		while (i < s.size())
		{
			std::size_t t=1;
			switch (s[i])
			{
			case ' ':case'\0':case'\n':
				break;
			case '(':
				balance_symbol.push_back('(');
				operator_symbol.push_back('(');
				break;
			case')':
				if (balance_symbol.empty() || balance_symbol.back() != '(')
				{
					printf("error: \'(\'  \')\' mismatch\n");
					return;
				}
				while (!operator_symbol.empty() && operator_symbol.back() != '(')
				{
					rpn.emplace_back(table<double>{ operator_symbol.back() });
					operator_symbol.pop_back();
				}
				if (!operator_symbol.empty()) operator_symbol.pop_back();
				break;
			case'+':case'-':case '*':case '/':
				while (!operator_symbol.empty() && operator_symbol.back() != '(' && priority[operator_symbol.back()-42] >= priority[s[i]-42])
				{
					rpn.emplace_back(table<double>{operator_symbol.back()});
					operator_symbol.pop_back();
				}
				operator_symbol.push_back(s[i]);
				break;
			case'.':case'0':case'1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':
				try { rpn.emplace_back(table<double>{  std::stod(s.substr(i), &t) }); }
				catch (std::invalid_argument& ia)
				{
					std::cerr << "Invalid argument: " << ia.what() << '\n';
					return;
				}
				catch (std::out_of_range& oor)
				{
					std::cerr << "Out of Range error: " << oor.what() << '\n';
					return;
				}
				break;
			default:
				printf("error : \"%c\" symbol is illegal \n",s[i]);
				return;
				break;
			}
			i += t;
		}
		for(auto it=operator_symbol.rbegin();it!=operator_symbol.rend();it++)
		{
			auto _ = *it;
			if (_ == '(' || _ == ')')
			{
				printf("error : \'(\'  \')\' mismatch\n");
				return;
			}
			rpn.emplace_back(table<double>{_});
		}
		if (rpn.empty())
		{
			printf("error: the expression is empty\n");
			return;
		}
		calc_post_fix<V, double>(rpn);
	}
}
#endif