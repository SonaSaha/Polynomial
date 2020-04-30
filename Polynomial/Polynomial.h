#pragma once
#include <utility>
#include <string>
#include <vector>

class Polynomial
{
public:
	typedef double coeff_type;
	typedef std::vector<coeff_type> container_type;
	typedef container_type::iterator iterator;
	typedef container_type::const_iterator const_iterator;
public:
	Polynomial() {};
	explicit Polynomial(const std::initializer_list<coeff_type>& list) :coeffs_(list) {};
	template<class iter>
	Polynomial(iter first, iter last) :coeffs_(first, last) {};
	explicit Polynomial(const std::string& str);
	std::string to_string() const;
	coeff_type integral(coeff_type start, coeff_type end) const;
	Polynomial derivative() const;
	//Polynomial antiderivative(coeff_type c = 0) const;
	container_type get_coeffs() const { return coeffs_; };
	const_iterator begin() const;
	const_iterator end() const;

public:
	Polynomial& operator += (const Polynomial& p2);
	Polynomial& operator -= (const Polynomial& p2);
	Polynomial& operator *= (const Polynomial& p2);
	Polynomial& operator /= (const Polynomial& p2);
	Polynomial& operator %= (const Polynomial& p2);
	Polynomial& operator ++ ();
	Polynomial& operator -- ();
	Polynomial operator ++ (int);
	Polynomial operator -- (int);

	Polynomial operator + () const;
	Polynomial operator - () const;
private:
	container_type coeffs_;
};

bool operator == (const Polynomial& p1, const Polynomial& p2);
bool operator != (const Polynomial& p1, const Polynomial& p2);
Polynomial operator + (const Polynomial& p1, const Polynomial& p2);
Polynomial operator - (const Polynomial& p1, const Polynomial& p2);
Polynomial operator * (const Polynomial& p1, const Polynomial& p2);
Polynomial operator / (const Polynomial& p1, const Polynomial& p2);
Polynomial operator % (const Polynomial& p1, const Polynomial& p2);

std::ostream& operator <<(std::ostream& out, const Polynomial& p);