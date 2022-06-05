#include "digits.hpp"

void Digits::push_back(unsigned char digit) {
	if(m_back_right) m_digits.push_back(digit << 4);
	else m_digits.back() |= digit & 0x0F;
	m_back_right = !m_back_right;
}

void Digits::push_front(unsigned char digit) {
	if(m_front_left) m_digits.push_front(digit & 0x0F);
	else m_digits.front() |= digit << 4;
	m_front_left = !m_front_left;
}

void Digits::pop_back() {
	if(m_back_right) m_digits.back() &= 0xF0;
	else m_digits.pop_back();
	m_back_right = !m_back_right;
}

void Digits::pop_front() {
	if(m_front_left) m_digits.front() &= 0x0F;
	else m_digits.pop_front();
	m_front_left = !m_front_left;
}

void Digits::clear() {
	m_digits.clear();
	m_digits.push_back(0);
	m_front_left = false, m_back_right = false;
}

unsigned char Digits::front() const {
	return m_front_left ? (m_digits.front() >> 4) : (m_digits.front() & 0x0F);
}

unsigned char Digits::back() const {
	return m_back_right ? (m_digits.back() & 0x0F) : (m_digits.back() >> 4);
}

std::size_t Digits::size() const {
	return m_digits.size() * 2 - (m_front_left ? 0 : 1) - (m_back_right ? 0 : 1);
}

bool Digits::empty() const {
	return m_digits.size() == 1 && !m_front_left && !m_back_right;
}

// Iterator ==================================================================

Digits::Iterator::Iterator(
		std::list<unsigned char> const &digits,
		bool front_left,
		bool back_right
) : m_actual(digits.begin()), m_it(m_actual), m_end(digits.end()) {
	++m_it;
	m_right = !front_left;
	m_back_right = back_right;
}

Digits::Iterator &Digits::Iterator::operator++() {
	if(m_right) {
		if(m_actual != m_end) ++m_actual;
		if(m_it != m_end) ++m_it;
	}
	m_right = !m_right;
	return *this;
}

unsigned char Digits::Iterator::operator*() const {
	return m_right ? (*m_actual & 0xF) : (*m_actual >> 4);
}

bool Digits::Iterator::has_next() const {
	if(m_it != m_end) return true;
	if(m_actual != m_end) {
		if(!m_right) return true;
		if(m_back_right) return true;
	}
	return false;
}

Digits::Iterator Digits::get_iterator() const {
	return { m_digits, m_front_left, m_back_right };
}

Digits::ReverseIterator::ReverseIterator(
		const std::list<unsigned char> &digits,
		bool front_left,
		bool back_right
) : m_actual(digits.rbegin()), m_it(m_actual), m_end(digits.rend()) {
	++m_it;
	m_left = !back_right;
	m_front_left = front_left;
}

Digits::ReverseIterator &Digits::ReverseIterator::operator++() {
	if(m_left) {
		if(m_actual != m_end) ++m_actual;
		if(m_it != m_end) ++m_it;
	}
	m_left = !m_left;
	return *this;
}

unsigned char Digits::ReverseIterator::operator*() const {
	return m_left ? (*m_actual >> 4) : (*m_actual & 0x0F);
}

bool Digits::ReverseIterator::has_next() const {
	if(m_it != m_end) return true;
	if(m_actual != m_end) {
		if(!m_left) return true;
		if(m_front_left) return true;
	}
	return false;
}

Digits::ReverseIterator Digits::get_reverse_iterator() const {
	return { m_digits, m_front_left, m_back_right };
}
