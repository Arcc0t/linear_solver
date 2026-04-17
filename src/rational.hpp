#ifndef RATIONAL_HPP_GUARD
#define RATIONAL_HPP_GUARD

#include <cstdint>
#include <utility>
#include <cassert>
#ifdef DEBUG_MSG
#include <iostream>
#endif

inline 
uint64_t gcd(uint64_t a, uint64_t b)
{
	while (b){
		a %= b;
		std::swap(a, b);
	}
	return a;
}

inline
uint64_t lcm(uint64_t a, uint64_t b)
{
	return a / gcd(a, b) * b;
}


uint64_t i64abs(int64_t x)
{
	return x < 0? -x: x;	
}

int64_t sign(int64_t x)
{
	return (x > 0) - (x < 0);
}

class rational{
private:
	int64_t num;
	int64_t den;

	void normalize()
	{
		auto sgn_d = sign(den);
		num *= sgn_d;
		den *= sgn_d;
		auto d = gcd(i64abs(num), den);
		num /= d;
		den /= d;
	}
public:

	int64_t numerator() const
	{
		return num;
	}

	int64_t denominator() const
	{
		return den;
	}

	rational opposite() const 
	{
		return rational(-num, den);
	}

	rational add(rational other) const
	{
		auto d = gcd(den, other.den);
		int64_t res_num = other.den / d * num + den / d * other.num;
		int64_t res_den = den / d * other.den;
		return rational(res_num, res_den);
	}

	rational sub(rational other) const
	{
		return add(other.opposite());
	}

	rational multiply(rational other) const
	{
		assert(den > 0);
		assert(other.den > 0);

		int64_t div1 = gcd(i64abs(num), other.den);
		int64_t div2 = gcd(i64abs(other.num), den);

		assert(div1 <= i64abs(num) && div1 <= other.den);
		assert(div2 <= i64abs(other.num) && div2 <= den);	

		int64_t res_num = (num / div1) * (other.num / div2);
		int64_t res_den = (den / div2) * (other.den / div1);
#ifdef DEBUG_MSG
		std::cerr << "DEBUG: div1 = " << div1 << '\n';
		std::cerr << "DEBUG: div2 = " << div2 << '\n';
		std::cerr << "DEBUG: num = " << num << '\n';
		std::cerr << "DEBUG: other.num = " << other.num << '\n';
		std::cerr << "DEBUG: " << res_num << "/" << res_den << '\n';
#endif	
		return rational(res_num, res_den);
	}

	rational divide(rational other) const
	{
		return multiply(other.inversed());
	}
	
	rational inversed() const
	{
		assert(num != 0);
		return rational(den, num);
	}

	void inverse()
	{
		assert(num != 0);
		std::swap(den, num);
		normalize();
	}
	
	rational& operator +=(rational other)
	{
		*this = add(other);
		return *this;
	}

	rational& operator -=(rational other)
	{
		*this = sub(other);
		return *this;
	}

	rational& operator *=(rational other)
	{
		*this = multiply(other);
		return *this;	
	}

	rational& operator /=(rational other)
	{
		*this = divide(other);
		return *this;
	}

	rational(int64_t a = 0, int64_t b = 1) :
		num(a), den(b)
	{
		normalize();
	}
};

inline
rational operator +(rational r1, rational r2)
{
	return r1.add(r1);
}

inline
rational operator -(rational r1, rational r2)
{
	return r1.sub(r2);
}

inline
rational operator *(rational r1, rational r2)
{
	return r1.multiply(r2);
}

inline
rational operator /(rational r1, rational r2)
{
	return r1.divide(r2);
}

inline
rational operator -(rational r)
{
	return r.opposite();
}

inline
rational abs(rational r)
{
	return r.numerator() >= 0? r: -r;
}

inline
bool operator== (const rational& r1, const rational& r2)
{
	return r1.numerator() == r2.numerator() 
		&& r1.denominator() == r2.denominator(); 

}

inline
bool operator!= (const rational& r1, const rational& r2)
{
	return r1.numerator() != r2.numerator() 
		|| r1.denominator() != r2.denominator(); 

}


#endif
