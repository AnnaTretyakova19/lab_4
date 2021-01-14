#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <bitset>
#include <array>

using namespace std;

class normal {

private:

	constexpr static int M = 491;
	constexpr static int P = M * 2 + 1;

	typedef bitset<M> bitset;

	bitset intlong;

	static bool get_cell(int x, int y) {
		return (x + y + P) % P == 1
			|| (x - y + P) % P == 1
			|| (-x + y + P) % P == 1
			|| (-y - x + P) % P == 1;
	}
	static int get_next(int v) {
		return (v * 2) % P;
	}
	static array<normal, M> make_matrix() {
		array<normal, M> result;
		for (int i = 0, x = 1; i < M; ++i, x = get_next(x)) {
			for (int j = 0, y = 1; j < M; ++j, y = get_next(y)) {
				result[i].intlong[M - j - 1] = get_cell(x, y);
			}
		}
		return result;
	}
	static const array<normal, M> matrix;

	normal& shift_left() {
		intlong = (intlong >> (M - 1)) | (intlong << 1);
		return *this;
	}
	normal& shift_right() {
		intlong = (intlong << (M - 1)) | (intlong >> 1);
		return *this;
	}

public:

	normal() = default;
	normal(const bitset& _intlong)
	{
		intlong = _intlong;
	}
	normal(int value) : normal(bitset(value)) {}
	normal(const string& str) : normal(bitset(str)) {}
	normal(const normal&) = default;
	normal& operator = (const normal&) = default;
	~normal() = default;

	bool operator == (const normal& n) const {
		return intlong == n.intlong;
	}

	normal& operator <<= (int n) {
		intlong <<= n;
		return *this;
	}
	normal operator << (int n) const {
		return normal(*this) <<= n;
	}
	normal& operator >>= (int n) {
		intlong >>= n;
		return *this;
	}
	normal operator >> (int n) const {
		return normal(*this) >>= n;
	}
	normal& operator += (const normal& n) {
		intlong ^= n.intlong;
		return *this;
	}
	normal operator + (const normal& n) const {
		return normal(*this) += n;
	}
	normal& operator &= (const normal& n) {
		intlong &= n.intlong;
		return *this;
	}
	normal operator & (const normal& n) const {
		return normal(*this) &= n;
	}
	normal& operator *= (normal n) {
		normal result, temp;
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < M; ++j) {
				temp.intlong[M - j - 1] = (matrix[j] & *this).trace();
			}
			result.intlong[M - i - 1] = (temp & n).trace();
			this->shift_left();
			n.shift_left();
		}
		return *this = result;
	}
	normal operator * (const normal& n) const {
		return normal(*this) *= n;
	}

	bool trace() const {
		return intlong.count() & 1;
	}
	normal sqr() const {
		return normal(*this).shift_right();
	}
	normal inverse() const {
		return pow(*this, bitset(1).flip());
	}
	normal flip() const {
		return bitset(intlong).flip();
	}

	static normal pow(const normal& a, const normal& b) {
		if (b.intlong.none()) {
			return bitset().flip();
		}
		return b.intlong[0] ? pow(a, b >> 1).sqr() * a : pow(a, b >> 1).sqr();
	}

	operator string() const {
		return intlong.to_string();
	}

	friend ostream& operator << (ostream& os, const normal& n) {
		return os << string(n);
	}

};

const array<normal, normal::M> normal::matrix = normal::make_matrix();