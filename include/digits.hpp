#ifndef BIGNUMBER_DIGITS_HPP
#define BIGNUMBER_DIGITS_HPP

#include <list>

class Digits {
public:
	Digits() = default;
	Digits(const Digits &) = default;
	Digits &operator=(const Digits &) = default;
	~Digits() = default;

	void push_back(unsigned char digit);
	void push_front(unsigned char digit);

	[[nodiscard]] unsigned char front() const;
	[[nodiscard]] unsigned char back() const;

	void pop_back();
	void pop_front();

	void clear();
	[[nodiscard]] std::size_t size() const;
	[[nodiscard]] bool empty() const;

	class Iterator {
	public:
		Iterator() = default;
		Iterator(const Iterator &) = default;
		~Iterator() = default;

		Iterator &operator++();
		unsigned char operator*() const;

		[[nodiscard]] bool has_next() const;
	private:
		friend Digits;
		Iterator(
				std::list<unsigned char> const &digits,
				bool front_left,
				bool back_right
		);

		std::list<unsigned char>::const_iterator m_actual, m_it, m_end;
		bool m_back_right = false, m_right = false;
	};

	[[nodiscard]] Iterator get_iterator() const;

	class ReverseIterator {
	public:
		ReverseIterator() = default;
		ReverseIterator(const ReverseIterator &) = default;
		~ReverseIterator() = default;

		ReverseIterator &operator++();
		unsigned char operator*() const;

		[[nodiscard]] bool has_next() const;
	private:
		friend Digits;
		ReverseIterator(
				std::list<unsigned char> const &digits,
				bool front_left,
				bool back_right
		);

		std::list<unsigned char>::const_reverse_iterator m_actual, m_it, m_end;
		bool m_front_left = false, m_left = false;
	};

	[[nodiscard]] ReverseIterator get_reverse_iterator() const;

private:
	std::list<unsigned char> m_digits = { 0 };
	bool m_front_left = false;
	bool m_back_right = false;
};

#endif //BIGNUMBER_DIGITS_HPP
