# Random
Generates one or more random decimal/hex numbers or strings of different widths

To compile:
```
g++ -Wall -Wextra -std=c++11 \
  -o ./rand \
  ./_rand.cc \
  -I${BOOST}/include \
  -L${BOOST}/lib \
  -lboost_program_options;
```

Usage:
```
%> ./rand --help
Allowed options:
  -h [ --help ]            print this help message
  -c [ --count ] arg (=1)  number of random numbers to print
  -d [ --decimal ]         print numbers in decimal format instead of hex
  -w [ --width ] arg (=32) width in bits of each number
```

Examples:
```
%> rand -c 3 -w 8 -d
214
60
78
%> rand --count=3 --width=16
0xe275
0x1d32
0xd0b4
%> rand -c 5 -s -w 20
0>C@42>@4LF`z$m5;8'0
g1BC"m]qYs)|h7,t7tdE
M>DA/*Ah{9H2i\y<!Tt@
Vp1$dRh(FWz{k^2)Upk^
2sQI*7S>WB){XNfYf\*B
```
