# Polynomial
A small console program that calculate statements of polynomial.

# Combine
To combine and run this program:
```
g++ -o polynomial main.cpp
./polynomial
```

# User Manual
1. Correct form of polynomials:  
You can type a correct Polynomial if you follow this syntax: The variable of polynomial is alphabet character in lowercase. And you must write this character into the brackets `[` and `]`. The degree of the polynomial is before `^` character and it can not be smaller than 0. Example:  
```
[x]2x^2-3x+1 
[y]2*y^2-3*y+1.     
```
Noted: If you want to type a number, you must follow the rule of polynomial, i.e the polynomial with zero degree, because all objects are also polynomials (Example: `[x]42` is number fourty two).   
  
2. Operators of polynomials:  
There are 5 operators: you can use `+` character to plus 2 polynomials, and use `-` to minus, `*` to multiplicate. If you want to divide 2 polynomials, use `/`. Or you can use `%` for modulo division. Note: The division of polynomial also comply with the rule of real numbers, such as it can't divide to 0,...  

3. Functions of polynomials:
- `gcd(polynomial a,polynomial b)`: find the greatest common division of a and b.  
- `eap(polynomial a,polynomial b)`: display steps of Euclide's algorithm for polynomial to find the greatest common division of a and b.  
- `tep(polynomial a,value x)`: find the Taylor expansion polynomial of a at x value.  
- `htp(polynomial a,value x)`: display the Horner table to find the Taylor expansion polynomial of a at x value.  

4. Command to program:  
- Type `clear` to clear all the screen.  
- Type `delete` to delete all polynomial objects in memory.  
- Type `about` to read more informations about the developer.   
- Type `exit` to leave the program.  