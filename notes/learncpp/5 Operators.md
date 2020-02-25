# 5 - Operators

# 5.1 - Operator precedence and associativity

- **Precedence** is what determines the order in which operators are resolved in a compound expression. To do this, operators are assigned a level of precedence, wherein operators with the highest level of precedence is evaluated first. From the table on the right we notice that * and / is higher in the precedence ranking than + and -, hence * and / are resolved first.
- **What if the precedence is equa**l?

    If this is the case (3 * 4 /  2) the operators associativity tells the compiler whether the operation is to be evaluated from left to right or right to left. The operators in precedence level 5 have an associativity of left to right, so the expression is resolved from left to right: (3 * 4) / 2.

- This being said, **parenthesis** has one of the highest precedence value, helping overcome precedence betwixt classic arithmetic expressions (+, -, *, / ..), like in normal arithmetic.Therefore, in  (4 + 2) * 3, '+' resolved before '*'.
- Always use parenthesis when writing up expressions, to avoid dependency on the table.

![5%20Operators/Untitled.png](5%20Operators/Untitled.png)

# 5.2 - Arithmetic operators

- There are two types of u**nary arithmetic operators**, plus (+) and minus (-).
    - Unary minus returns operand multiplied by -1
    - Unary plus returns operand multiplied by +1
    - Always use an unary operator just before the operand (-x not - x)
- There exists 5 **binary arithmetic operators** :

    ![5%20Operators/Untitled%201.png](5%20Operators/Untitled%201.png)

    +, - and * works just as they do in real life, this however is **not the case** for / and %

- Division has two different modes
    - If either or both operands are floating point values, the division performs a **floating point division** (7.0 / 4 = 1.75, 7 / 4.0 = 1.75, and 7.0 / 4.0 = 1.75).
    - If both operands are integers, division performs an **integer division** dropping off any fractions (4/3 = 1)
- **How** do we divide two integers and **not lose the fractional part**?

    Using **[static_cast<>](https://www.notion.so/azmed/4-Fundamental-Data-Types-041219584df14d90aab142be6ab1645d#5d5a9d02ae764180ae84531979dfd3d0)** one was able to convert char to its integer form, similarly it can be used to convert an integer to it floating point number, enabling floating point division.

        #include <iostream>
        using namespace std;
        
        int main()
        {
            int x { 2 };
            int y { 3 };
            cout << x / y << endl;                       // 0
            cout << x / static_cast<double>(y) << endl;  // 0.666667
            return 0;
        }

- Trying to divide by 0 (or 0.0) will generally cause your program to crash, as the results are mathematically undefined!
- **Arithmetic assignment operators**

    ![5%20Operators/Untitled%202.png](5%20Operators/Untitled%202.png)

# 5.3 - Modulus and Exponentiation

- The modulus operator (also informally known as the remainder operator) is an operator that returns the remainder after doing an integer division. Example, , 7 % 4 = 3
- Exponent operator in C++ goes by the call pow() and is imported form the cmath library

        #include <cmath>
        double x{ std::pow(3.0, 4.0) }; // 3 to the 4th power

    The return value of pow() float, which often results in rounding errors. So for integer exponentiation, it's advised to create one's own function.

        #include <iostream>
        #include <cstdint> // for std::int_fast64_t
        
        using namespace std;
        
        // note: exp must be positive
        std::int_fast64_t powint(int base, int exp)
        {
            std::int_fast64_t result{1};
            while (exp)
            {
                if (exp & 1)
                    result *= base;
                exp >>= 1;
                base *= base;       
            }
            return result;
        }
        
        int main()
        {
            cout << powint( 7, 12) <<endl;
            return 0;
        }

# 5.5 - Increment/decrement operators, and side effects

Increment/decrement has a prefix and a post-fixed version

![5%20Operators/Untitled%203.png](5%20Operators/Untitled%203.png)

    #include <iostream>
     
    int main()
    {
        int x{ 5 };
        int y{ 5 };
        std::cout << x << " " << y << '\n';     // 5 5
        std::cout << ++x << " " << --y << '\n'; // 6 4
        std::cout << x << " " << y << '\n';     // 6 4
        std::cout << x++ << " " << y-- << '\n'; // 6 4
        std::cout << x << " " << y << '\n';     // 7 3
     
        return 0;
    }

- Side effects can lead to unexpected results, take the example of the code below

        int add(int x, int y)
        {
            return x + y;
        }
         
        int main()
        {
            int x{ 5 };
            int value = add(x, ++x); // is this 5 + 6, or 6 + 6?
            // It depends on what order your compiler evaluates the function arguments in
         
            std::cout << value; // value could be 11 or 12, depending on how the above line evaluates!
            return 0;
        }

    Is add called like this "add(5,6)" or like this "add(6,6). **C++ does not define the order in which function arguments are evaluated.** If the left argument is evaluated first, this becomes a call to add(5, 6), which equals 11. If the right argument is evaluated first, this becomes a call to add(6, 6), which equals 12!

# 5.5 Comma and conditional operators

## Commas

- Comma operator enables evaluation of multiple expressions wherever single expression is allowed. The operator evaluates the left, followed by the right operand and returns the right operand.

        #include <iostream>
         
        int main()
        {
            int x{ 1 };
            int y{ 2 };
         
            std::cout << (++x, ++y); // displays 3
         
            return 0;
        }

    First, the left operand gets evaluated to 2 and the right gets evaluated to 3. This is followed by returning the value of y (to the right of the comma)

- Comma has the lowest precedence, even lower than the assignment operator. Hence the lines below behave differently.

        z = (a, b); // evaluates a,b first to get b and assign that to z
        z = a, b;   // evaluates (z = a), b, and get assigned the value of a, b is discarded.

- Comma can be used as a separator, and using it as such doesn't involve the operator functionality.

## **Conditional operator** :

- Another short alternative to an if statement, the syntax is as follows : (condition) ? expression 1 : expression 2. If true expression 1 else expression 2
- **Parenthesization** of the conditional operator is important because it's easier to read and one can ensure that the precedence is respected. For example, in the code below, case 1 is evaluated as expected -  if x > y, x is returned else y is - however, the same can't be said for case 2 - if x > y 1 is returned else 0 is - as << has greater precedence than ? .

    std::cout << ((x > y) ? x : y); // CASE 1
    std::cout << (x > y) ? x : y; // CASE 2 -> (std::cout << (x > y)) ? x : y;

- To properly compile with C++'s type checking, both expression in a conditional statement must either match, or the second expression must be a convertible to the type of the first expression.

        int main()
        {
        	int x = 5;
        	std::cout << (x != 5 ? x : "x is 5"); // won't compile
         
        	return 0;
        }

- Conditional statements **should not be used** for complex if/else statements, as it quickly becomes both unreadable and error prone.

# 5.6  Relational operators and floating point comparisons

![5%20Operators/Untitled%204.png](5%20Operators/Untitled%204.png)

- Boolean conditional value:
    - if (b1 == true) is better written as if (b1)
    - if (b1== false) is better written as if (!b1)

    Don’t add unnecessary == or != to conditions. It makes them harder to read without offering any additional value.

## Comparison of floating point values

    int main()
    {
        double d1{ 100.0 - 99.99 }; // should equal 0.01
        double d2{ 10.0 - 9.99 }; // should equal 0.01
     
        if (d1 == d2)
            std::cout << "d1 == d2" << '\n';
        else if (d1 > d2)
            std::cout << "d1 > d2" << '\n';
        else if (d1 < d2)
            std::cout << "d1 < d2" << '\n';
        
        return 0;
    }

- Here d1 > d2 despite theoretically their values are deemed to be the same. This anomaly occurs due to rounding errors concerning floating point numbers. d1 = 0.0100000000000005116 and d2 = 0.0099999999999997868
- Under normal circumstances, relational operators on floating point operators produce correct answers and only potentially fail when the operands are almost identical. **However the consequence of getting an answer right with floating point comparisons must always be kept in sight**

## Floating point equality

- Equality operators (== and ≠) are even troublesome as "true" is returned only if two numbers are exactly the same. And even the smallest rounding error will cause two floating point numbers to not be equal, operator== is at high risk for returning false when a true might be expected.
- Comparing floating point number would involving using functions to check if the two number are almost the same. If they are "close enough", they can be deemed to be the same.
- One way of going around this is to write a custom approximative check function

        bool approximatelyEqual(double a, double b, double epsilon) // Knuth's approach
        {                                                           // relative to the magnitude 
                                                                    // of a or b.
            return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * epsilon));
        }

    - **epsilon** here helps defined a percentage up-to which the operands can be off when using relational operators. So if epsilon is 1% = 0.01, the difference between the operands mustn't exceed 0.01

        int main()
        {
        	// a is really close to 1.0, but has rounding errors, so it's slightly smaller than 1.0
        	double a{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };
         
        	// First, let's compare a (almost 1.0) to 1.0.
        	std::cout << approximatelyEqual(a, 1.0, 1e-8) << '\n';    //(1.11022e-16 < 1e-08) = 1
         
        	// Second, let's compare a-1.0 (almost 0.0) to 0.0
        	std::cout << approximatelyEqual(a-1.0, 0.0, 1e-8) << '\n';//(1.11022e-16 < 1.11022e-24) = 0
        }

    - So here the first output is 1 (expected) and the second output is 0 (not expected). And this is because the math simply breaks down close to zero.
    - One way of avoid this is to use Knuth's approach in combination with a an absolute epsilon approach

        bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
        {
        	// Check if the numbers are really close -- needed when comparing numbers near zero.
        	double diff { std::abs(a-b)};
        	if (diff < absEpsilon)
        		return true;
        	// Otherwise fall back to Knuth's algorithm
        	return (diff <= (std::max(std::abs(a), std::abs(b))*relEpsilon));
        }
        
        int main()
        {
            // a is really close to 1.0, but has rounding errors
            double a{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };
         
            std::cout << approximatelyEqual(a, 1.0, 1e-8) << '\n';                 // compare "almost 1.0" to 1.0 = 1
            std::cout << approximatelyEqual(a-1.0, 0.0, 1e-8) << '\n';             // compare "almost 0.0" to 0.0 = 0
            std::cout << approximatelyEqualAbsRel(a-1.0, 0.0, 1e-12, 1e-8) << '\n'; // compare "almost 0.0" to 0.0 = 1
        }

# 5.7 Logical operators

Provides us with the capability to test multiple conditions. C++ has 3 logical operators.

![5%20Operators/Untitled%205.png](5%20Operators/Untitled%205.png)

## Logical NOT

- Logical NOT has a very high level of precedence, and one must be wary of its usage

        int main()
        {
            int x { 5 };
            int y { 7 };
         
            if (! x > y)                                        // correct way : if (!(x>y))
                std::cout << "x is not greater than y\n";
            else
                std::cout << "x is equal to or greater than y\n"; //outputs this as if(!(s) > y)
        																												// evaluates to if (0 > y) which 
        																												// is false. Hence else is called 
            return 0;
        }

- Logical NOT is intended to operate on the result of other operators, the other operators and operands ought to be enclosed in brackets.

![5%20Operators/Untitled%206.png](5%20Operators/Untitled%206.png)

## Logical OR

- Used to test if either of the condictions are true.
- One can string together many logical OR statements

    if (value == 0 || value == 1 || value == 2 || value == 3)
         std::cout << "You picked 0, 1, 2, or 3\n";

![5%20Operators/Untitled%207.png](5%20Operators/Untitled%207.png)

- Logical OR operator (||) and the bitwise OR operator (|) have separate funcitions.

## Logical AND

- Checks if both operands are true.

![5%20Operators/Untitled%208.png](5%20Operators/Untitled%208.png)

## Short circuit evaluation

In order for AND operator to return True, both operands must evaluate to True, If the first operand evaluated to false, regardless of the value of the second operand, a False is returned. This is called short ciruit evaluation. Similar logic applies for OR

## Mixing AND and ORs

- Quite the risky task
- AND has higher precedence than OR, i.e value1 || value2 && value3 is evaluated as value1 || (value2 && value3)
- GOLDEN RULE : Always use parentheisis!!!

## De Morgan's Law

- Many programmers think that !(x && y) is not the same as !x && !y, unfortunately it's false
- De Morgan's law tells us how logical NOT should be distributed
    - !(x && y) is equivalent to !x || !y
    - !(x || y) is equivalent to !x && !y

## Logical exclusive (XOR)

    if (a != b) ... // a XOR b, assuming a and b are Booleans
    if (a != b != c != d) ... // a XOR b XOR c XOR d, assuming a, b, c, and d are Booleans
    

The above doesn't work on integers. If one needs a form of logical XOR that works on non-boolean operands, **static_cast** can be used 

![5%20Operators/Untitled%209.png](5%20Operators/Untitled%209.png)

    if (static_cast<bool>(a) != static_cast<bool>(b) != static_cast<bool>(c) != static_cast<bool>(d)) 
    ... // a XOR b XOR c XOR d, for any type that can be converted to bool