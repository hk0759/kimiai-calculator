# kimiai-calculator

Simple C++ expression calculator using a recursive descent parser.

## Features
- Supports `+`, `-`, `*`, `/` and parentheses
- Unary `+` / `-`
- Decimal numbers
- Division-by-zero and syntax error handling

## Build
```sh
g++ -std=c++17 -o calculator calculator.cpp
```

## Run
```sh
./calculator
> (1+2)*3/4
= 2.25
```
