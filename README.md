# BigNumber

This project aims to be a library to make calculations with a big number (integer or float).
The project can be divided in three parts:

- The **BigInt** class, which represents integers numbers.
- The **BigFloat** class, which represents floats numbers.
- The **big math** sub-library, which contains some math functions.

## Summary

- [Usage](#usage)
- [Features](#features)

## Usage

1. Download the project from [GitHub](https://github.com/ocineh/BigNumber)

```bash
git clone https://github.com/ocineh/BigNumber.git
```

2. Compile the library:

```bash
cmake -S . -B build
cmake --build build
```

3. Include it in your project:

```bash
g++ -std=c++17 -o my_program.exe my_program.cpp build/libBigNumber.a
```

## Features

- BigInt
  - [x] Comparison operators
    - [x] Equalities
    - [x] Inequalities
    - [x] Greater than
    - [x] Less than
    - [x] Greater or equal
    - [x] Less or equal
  - [x] Arithmetic operators
    - [x] Addition
    - [x] Subtraction
    - [x] Multiplication
    - [x] Division
    - [x] Modulo
    - [x] Negation
    - [x] Increment (prefix and postfix)
    - [x] Decrement (prefix and postfix)
    - [x] Bitwise left shift
    - [x] Bitwise right shift
  - [x] Arithmetic-assignment operators
    - [x] Addition assignment
    - [x] Subtraction assignment
    - [x] Multiplication assignment
    - [x] Division assignment
    - [x] Modulo assignment
    - [x] Bitwise left shift assignment
    - [x] Bitwise right shift assignment
  - [x] Assignment operators
    - [x] Simple assignment with a BigInt
    - [x] Simple assignment with a string
    - [x] Simple assignment with a `long long`
  - [x] I/O steam operators
    - [x] Input stream
    - [x] Output stream
  - [x] Methods
    - [x] Absolut value
    - [x] The length of the number
    - [x] If the number is even or odd
    - [x] If the number is not a number
- BigFloat
  - [x] Comparison operators
    - [x] Equalities
    - [x] Inequalities
    - [x] Greater than
    - [x] Less than
    - [x] Greater or equal
    - [x] Less or equal
  - [ ] Arithmetic operators
    - [ ] Addition
    - [ ] Subtraction
    - [ ] Negation
    - [ ] Increment (prefix and postfix)
    - [ ] Decrement (prefix and postfix)
    - [x] Bitwise left shift
    - [x] Bitwise right shift
  - [ ] Arithmetic-assignment operators
    - [ ] Addition assignment
    - [ ] Subtraction assignment
    - [x] Bitwise left shift assignment
    - [x] Bitwise right shift assignment
  - [x] Assignment operators
    - [x] Simple assignment with a BigFloat
    - [x] Simple assignment with a string
    - [x] Simple assignment with a `long double`
  - [ ] I/O steam operators
    - [ ] Input stream
    - [x] Output stream
  - [ ] Methods
    - [x] Absolut value
    - [ ] The length of the number
    - [ ] If the number is not a number
    - [ ] If the number is zero
    - [ ] Ceil
    - [ ] Floor
- big math
  - [x] Power (Exponentiation)
  - [x] Greatest common divisor
  - [x] Least common multiple
  - [x] Factorial
  - [x] Binomial coefficient
  - [ ] Square root
  - [ ] Logarithm
  - [ ] Sine
  - [ ] Cosine
  - [ ] Tangent
