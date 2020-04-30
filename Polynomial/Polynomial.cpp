// Polynomial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "Polynomial.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
Polynomial::Polynomial(const std::string& str)
{
	std::istringstream iss(str);
	iss >> std::noskipws;
	char a;
	double coeff = 0;
	double degree = 0;
	double prevDegree = 0;
	int i = 0;
	while (iss >> a)
	{
		if (!a)
		{
			throw std::invalid_argument("empty string");
		}
		if (a == '+')
		{
			iss >> a;
		}
		if (a != 'x' && (a < '1' && a > '9'))
		{
			throw std::invalid_argument("expected 'x' or number");
		}
		if (a == 'x')
		{
			coeff = 1;
		}
		if (a >= '1' && a <= '9')
		{
			coeff = a - '0';
			while (iss >> a)
			{
				if (a == 'x')
				{
					break;
				}
				coeff *= 10;
				coeff += (a - '0');
			}
		}
		iss >> a;
		if (a == '^')
		{
			if (!(iss >> degree))
				throw std::invalid_argument("after '^' must be number");
		}
		while (prevDegree - degree > 1)
		{
			coeffs_.push_back(0);
			--prevDegree;
		}
		coeffs_.push_back(coeff);
		prevDegree = degree;
	}
	while (degree > 1)
	{
		coeffs_.push_back(0);
		--degree;
	}
}

std::string Polynomial::to_string() const
{
	std::ostringstream oss;
	Polynomial::coeff_type coeff;
	int size = coeffs_.size();
	int i = 0;
	char x = 'x';
	char plus = '+';
	char degree = '^';
	if (size == 0)
		throw std::invalid_argument("empty polynomial");
	while (size)
	{
		if (size == 1)
		{
			if (coeffs_[i] != 0)
				oss << coeffs_[i];
			return oss.str();
		}
		if (coeffs_[i] == 0)
		{
			--size;
			++i;
			continue;
		}
		if (coeffs_[i] != 1)
		{
			oss << coeffs_[i];
		}
		oss << x;
		if (size > 2)
		{
			oss << degree << size - 1;
		}
		if (std::find_if(coeffs_.begin() + i + 1, coeffs_.end(), [](const coeff_type coeff) {return coeff != 0; }) != coeffs_.end())
		{
			oss << plus;
		}
		--size;
		++i;
	}
	return oss.str();
}
Polynomial::coeff_type Polynomial::integral(coeff_type start, coeff_type end) const
{
	coeff_type sum = 0;
	int size = coeffs_.size();
	for (int i = 0; i < coeffs_.size() + 1; ++i)
	{
		sum += (coeffs_[i] * (1 / size)*(std::pow(end, size) - std::pow(start, size)));
		--size;
	}
	return sum;
}

Polynomial Polynomial::derivative() const
{
	int size = coeffs_.size();
	std::vector<coeff_type> v(size - 1);
	for (int i = 0; i < v.size(); ++i)
	{
		v[i] = coeffs_[i] * (size - i - 1);
	}
	return Polynomial(v.begin(), v.end());
}

Polynomial::const_iterator Polynomial::begin() const
{
	return coeffs_.cbegin();
}
Polynomial::const_iterator Polynomial::end() const
{
	return coeffs_.cend();
}
Polynomial& Polynomial::operator += (const Polynomial& p2)
{
	int thisSize = coeffs_.size();
	int size = p2.coeffs_.size();
	const int maxSize = (size > thisSize) ? size : thisSize;
	const int minSize = (size > thisSize) ? thisSize : size;
	Polynomial p;
	for (int i = 0; i < maxSize - minSize; ++i)
	{
		if (size < thisSize)
			p.coeffs_.push_back(coeffs_[i]);
		else if (size >= thisSize)
			p.coeffs_.push_back(p2.coeffs_[i]);
	}
	int j = 0;
	for (int i = minSize; i < maxSize; ++i)
	{
		if (size < thisSize)
			p.coeffs_.push_back(coeffs_[i] + p2.coeffs_[j]);
		else if (thisSize < size)
			p.coeffs_.push_back(coeffs_[j] + p2.coeffs_[i]);
		++j;
	}
	*this = p;
	return *this;
}

Polynomial& Polynomial::operator -= (const Polynomial& p2)
{
	int thisSize = coeffs_.size();
	int size = p2.coeffs_.size();
	const int maxSize = (size > thisSize) ? size : thisSize;
	const int minSize = (size > thisSize) ? thisSize : size;
	Polynomial p;
	for (int i = 0; i < maxSize - minSize; ++i)
	{
		if (size < thisSize)
			p.coeffs_.push_back(coeffs_[i]);
		else if (size >= thisSize)
			p.coeffs_.push_back(-p2.coeffs_[i]);
	}
	int j = 0;
	for (int i = minSize - 1; i < maxSize; ++i)
	{
		if (size < thisSize)
			p.coeffs_.push_back(coeffs_[i] - p2.coeffs_[j]);
		else if (thisSize < size)
			p.coeffs_.push_back(coeffs_[j] - p2.coeffs_[i]);
		++j;
	}
	*this = p;
	return *this;
}

Polynomial& Polynomial::operator *= (const Polynomial& p2)
{
	int thisSize = coeffs_.size();
	const int thisSize1 = thisSize;
	int size = p2.coeffs_.size();
	Polynomial p;
	//Polynomial p2({ 1,4 });
	//Polynomial p3({ 2,3 });
	p.coeffs_.resize((thisSize - 1)*(size - 1) + 1);
	std::cout << p.coeffs_.size() << "\n";
	int finalSize = coeffs_.size();
	for (int i = 0; i < thisSize1; ++i)
	{
		for (int j = i; j < p2.coeffs_.size(); ++j)
		{
			p.coeffs_[finalSize - (thisSize - 1)*(size - 1) - 1] = coeffs_[i] * p2.coeffs_[j];
			--size;
		}
		--thisSize;
	}
	*this = p;
	return *this;

}
/*
Polynomial& Polynomial::operator /= (const Polynomial& p2)
{
	Polynomial result;
}
Polynomial& Polynomial::operator %= (const Polynomial& p2)
{

}
Polynomial& Polynomial::operator ++ ()
{

}
Polynomial& Polynomial::operator -- ()
{

}
Polynomial Polynomial::operator ++ (int)
{

}
Polynomial Polynomial::operator -- (int)
{

}

Polynomial operator + () const
{

}
Polynomial operator - () const
{

}*/
std::ostream& operator <<(std::ostream& out, const Polynomial& p)
{
	out << p.to_string();
	return out;
}

int main()
{
	Polynomial p({ 2,1,0,5,4,0 });
	Polynomial p1({ 2,1,5 });
	Polynomial p2({ 1,4 });
	Polynomial p3({ 2,3 });
	Polynomial poly("225x^5+x^4+5x^2+4x");
	std::cout << p << "\n";       //2x^5+x^4+5x^2+4x
	std::cout << poly << "\n";    //225x^5+x^4+5x^2+4x
	std::cout << p.derivative() << "\n";//10x^4+4x^3+10x+4
	for (auto coef : p)
		std::cout << coef;
	std::cout << "\n";
	std::cout << (p += p1) << "\n"; //2x^5+x^4+7x^2+5x+5
	std::cout << (p1 -= p2) << "\n";//2x^2+1
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
