# L - Control Flow

# L.5.1 - Control flow introduction

- When a program is run, the CPU begins execution at the top of main(), executes some number of statements and then terminates at the end of main(). The sequence of statements that the CPU executes is called the program's **execution path**.
- Most programs seen so far have been **straight-line programs**, programs that have sequential flow take the same path every time.
- This often is considered undesirable behaviour. Say that a program solicits user input and the user inputs an invalid input, ideally one would want the program to re-solicit the user for a valid input. This wouldn't be possible with **straight-line prog**r**ams**.
- **Control flow statements** allow programmers to change CPUs execution path.

## Halts

- Tells the program to quit running immediately.
- In C++, halt is effectuated through the use of the **exit()** function, defined in the *cstdlib* header.

```cpp
#include <cstdlib>
#include <iostream>
void cleanup()
{}
int main()
{
	std::cout << 1;
	cleanup();
	exit(0);        // terminate and return 0 to operating system
  // The following statements never execute
	std::cout << 2;
	return 0;
}
```

- **exit()** works no-matter what function it's called from.
- Additionally, exit() terminates the program with minimal clean-up, therefore before calling exit one must consider whether any manual clean up is required.

## Jumps

- Causes the CPU to jump to another statement.
- The **goto**, **break** and **continue** keywords all cause different types of jumps.
- Function calls can also cause jump-like behaviour

## Conditional branches

- A statement that causes the program to change the path of execution based on the value of an expression.

- **If** statement is the most basic conditional branch
- The **switch** keyword also provides a good mechanism to effectuate conditional branching.

```cpp
int main()
{
    // do A
    if (expression)
        // do B
    else
        // do C
 
    // do D
}
```

## Loops

- Causes a program to repeatedly execute a series of statements until a given condition is false.
- The program may execute ABC or ABBC or ABBBC or even AC.
- C++ provides 3 types of loops:
    - while loop
    - do while loop
    - for loop
    - for each loop

```cpp
int main()
{
    // do A
    // loop on B, 0 or more times
    // do C
}
```

## Exceptions

- Offers a mechanism towards error handling  during function execution.
- If an error were to occur in a function that the function cannot handle, the exception is triggered. This causes the CPU to jump to the nearest block of code that handles exceptions of that type.

# L.5.2 - If statements

- The most basic type of conditional branch in C++ takes the from as shown on the right.
- The expression is called **conditional expression**.

```cpp
if (expression)
	statement
or 
if (expression)
	statement1
else
	statement2
```

## Implicit blocks

- If a programmer doesn't declare a block in the statement portion of an if/else statement, the compiler will implicitly do so.

    ```cpp
    if (expression)
    	statement1
    else
    	statement2
    ```

```cpp
if (expression)
{
	statement1
}
else
{
	statement2
}
```

- A common beginner error is as shown below, the compiler will throw an error saying that x is undefined.

    ```cpp
    #include <iostream>
    int main()
    {
        if (true)
        {
            int x = 5;
        } // x destroyed here
        else
        {
            int x = 6;
        } // x destroyed here
        std::cout << x; // x isn't defined here
        return 0;
    }
    ```

- If statements can be nested and/or chained
- Use curly braces when constructing nested if-statements to avoid the **dangling else** problem.
- Logical operators like **&&** and **||** can be used within if expressions.
- If statements can be used to perform early returns.
- **Null statements**
    - It's possible to omit the statement part of an if statement. An if statement without a body is called a null statement.
    - Such statements are typically used when the language requires a statement to exist but the programmer doesn't need one.

    ```cpp
    if (x == 0)
        ; // the semicolon acts as a null statement
    x = 1; //
    ```

- **Init statements**
    - If one needs a variable in an if-statement, but not outside, init-statement can be used before the condition

    ```cpp
    #include <iostream>
    #include <string>
     
    int main()
    {
        std::string firstName{};
        std::string lastName{};
     
        std::cout << "First name: ";
        std::cin >> firstName;
     
        std::cout << "Last name: ";
        std::cin >> lastName;
     
        if (std::string fullName{ firstName + ' ' + lastName }; fullName.length() > 20)
        {
            std::cout << '"' << fullName << "\"is too long!\n";
        }
        else
        {
            std::cout << "Your name is " << fullName << '\n';
        }
     
        // code that doesn't need @fullName
     
        return 0;
    }
    ```

# L.5.3 - Switch statements

- Although chaining multiple if-statements together is possible, it decreases readability. **Switch** statements were introduced to improve readability.

```cpp
#include <iostream>
 
enum Colors
{
    COLOR_BLACK,
    COLOR_WHITE,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE
};
 
void printColor(Colors color)
{
    if (color == COLOR_BLACK)
        std::cout << "Black";
    else if (color == COLOR_WHITE)
        std::cout << "White";
    else if (color == COLOR_RED)
        std::cout << "Red";
    else if (color == COLOR_GREEN)
        std::cout << "Green";
    else if (color == COLOR_BLUE)
        std::cout << "Blue";
    else
        std::cout << "Unknown";
}
 
int main()
{
    printColor(COLOR_GREEN);
 
    return 0;
}

```

```cpp
void printColor(Colors color)
{
    switch (color)
    {
        case COLOR_BLACK:
            std::cout << "Black";
            break;
        case COLOR_WHITE:
            std::cout << "White";
            break;
        case COLOR_RED:
            std::cout << "Red";
            break;
        case COLOR_GREEN:
            std::cout << "Green";
            break;
        case COLOR_BLUE:
            std::cout << "Blue";
            break;
        default:
            std::cout << "Unknown";
            break;
    }
}
```

The idea:

- Switch expression is evaluated to produce a value.
- Each case label is tested against this value for equality.
- If a case label matches, the statements after it are executed.
- **Switch** statements can be started using the **switch** keyword, followed by the expression the one would like to evaluate.
- Typically the expression is only a single statement, but can be something more complex too (nX+2 or nX -nY). This being said, the expression must evaluate to an integral type (char, short, int, long, long long, or enum), floating point variables, strings and other non-integral types can't be used here.
- The **case** **label** declared using the **case** keyword is followed by a constant expression. The constant expression is one that evaluates to a constant value.

- All case label expression must evaluate to a unique value.

```cpp
switch (x)
{
    case 4:
    case 4:  // illegal -- already used value 4!
    case COLOR_BLUE: // illegal, COLOR_BLUE evaluates to 4!
}
```

- It is possible to have multiple case labels refer to the same statements.
- In this case  where c is an ASCII digit, the first parameter after the matching statement is executed (which in this case is "return true")
- The **default label** also called the default case and is declared using the **default** keyword.
- The code under this label gets executed if none of the cases match the switch expression.

```cpp
bool isDigit(char c)
{
    switch (c)
    {
        case '0': // if c is 0
        case '1': // or if c is 1
        case '2': // or if c is 2
        case '3': // or if c is 3
        case '4': // or if c is 4
        case '5': // or if c is 5
        case '6': // or if c is 6
        case '7': // or if c is 7
        case '8': // or if c is 8
        case '9': // or if c is 9
            return true; // then return true
        default:
            return false;
    }
}
```

- One of the trickiest things about the switch statement is they way the execution proceeds when case is matched.
- Once a case matches, execution continues until one of the following termination conditions are true:
    - End of the switch block is reached
    - A return statement occurs
    - A goto statement occurs
    - A break statement occurs
    - Something else interrupts the flow of the program.

    **Fall-through** (when execution flow from one case to another case) is probably not wanted

```cpp
switch (2)
{
   case 1: // Does not match
       std::cout << 1 << '\n'; // skipped
   case 2: // Match!
       std::cout << 2 << '\n'; // Execution begins here
   case 3:
       std::cout << 3 << '\n'; // This is also executed
   case 4:
       std::cout << 4 << '\n'; // This is also executed
   default:
       std::cout << 5 << '\n'; // This is also executed
}
```

- **Break statements** tell the compiler that one is done with the switch . After a break statement is encountered, execution continues with the statement after the end of the switch block

- One can have multiple statements inside belonging to a case label within a switch block.
- One can declare but not initialize variables inside the switch (both before and after the case labels.
- Variables declared within one case can be used within another. Thus a variable defined in one case can be used by another case even though the former is never executed.
- When you define a local variable like “int y;”, the variable isn’t created at that point -- it’s actually created at the start of the block it’s declared in. However, it is not visible (in scope) until the point of declaration. The declaration statement doesn’t need to execute -- it just tells the compiler that the variable can be used past that point

```cpp
switch (1)
{
		int a; // okay, declaration is allowed before the case labels
    int b = 5; // illegal, initialization is not allowed before the case labels
    case 1:
        std::cout << 1;
        foo();
        std::cout << 2;
        break;
		case 2:
        int y; // okay, declaration is allowed within a case
        y = 4; // okay, this is an assignment
        break;
		case 3:
        int z = 4; // illegal, initialization is not allowed within a case
        break;
    default:
        std::cout << "default case\n";
        break;
}
```

# L.5.4 - Goto statements

- Control flow statement that cause the CPU to jump to another spot in the code.
- The spot is identified through use of a **statement label**.

    ```cpp
    #include <iostream>
    #include <cmath>

    int main()
    {
    	double x;
    tryAgain: // statement label
    	std::cout << "Enter a non-negative number";
    	std::cin >> x;

    	if (x < 0.0)
    		goto tryAgain; // the 'goto' statement
    	
    	std::cout << "The sqrt of " << x << " is " << sqrt(x) << std::endl;
    }	
    ```

    If the program gets an invalid user input, it begins from the point where the statement label is inserted.

- Goto statements use **function scope**. The goto statement and its corresponding statement label must appear in the same function.
- Goto statement is almost never used in C++. Results in spaghetti code

# L.5.5 - While statements

- Declared using the while keyword,
- When the while statement is executed, the expression is evaluated and the program advances only if the expression evaluates to true.

    ```cpp
    while (expression)
    	statement;
    ```

- Watch out for infinite loops.

    ```cpp
    while (1)
    {
    	std::cout << "Infinity";
    }
    ```

- **Loop variables**, often called **counters** are integer variables declared to count the number of times the loop has been executed (++i, —count.. etc).
- What might be the issue with the code below?

    ```cpp
    int main()
    {
        unsigned int count = 10;
     
        // count from 10 down to 0
        while (count >= 0)
        {
            if (count == 0)
                std::cout << "blastoff!";
            else
                std::cout << count << " ";
            --count;
        }
    }
    ```

    It starts out by printing 10 9 8 7 6 5 4 3 2 1 blastoff!" as desired, but then goes off the rails, and starts counting down from 4294967295. Due to the use of unsigned integers, when count is 0 and the value is decreased by 1, count overflows back to 4294967295. 

    Moral of the story : Never use unsigned integers (unless absolutely necessary). 

- Each time a loop executes, it's called an **iteration**. Since loop body is a block, and with every iteration the block is entered, variables declared inside the loop body are created and then destroyed with each iteration.

    ```cpp
    #include <iostream>
     
    int main()
    {
        int count = 1;
        int sum = 0; // sum is declared up here because we need it later (beyond the loop)
     
        while (count <= 5) // iterate 5 times
        {
            int x; // x is created here with each iteration
     
            std::cout << "Enter integer #" << count << ':';
            std::cin >> x;
     
            sum += x;
     
            // increment the loop counter
            ++count;
        } // x is destroyed here with each iteration
     
        std::cout << "The sum of all numbers entered is: " << sum;
     
        return 0;
    }
    ```

    - In the program above x is created and destroyed 5 times
    - With **fundamental variables** it's fine, but for **non-fundamental variables** (like structs and classes) it could cause performance issues. Hence it's wise to use non-fundamental variables before the loop.
    - If we want something done every 'n' iterations, use the modulus operator.

        ```cpp
        // if the loop variable is divisible by 10, print a newline
        if (count % 10 == 0)
            std::cout << "\n";
        ```

- It's even possible to have **nested loops** with while loop. .

    ```cpp
    #include <iostream>
     
    // Loop between 1 and 5
    int main()
    {
        int outer = 1;
        while (outer <= 5)
        {
            // loop between 1 and outer
            int inner = 1;
            while (inner <= outer)
                std::cout << inner++ << " ";
     
            // print a newline at the end of each row
            std::cout << "\n";
            ++outer;
        }
     
        return 0;
    }
    ```

# L.5.6 - Do while statements

- With a **while** loop, if the initial condition is initially false, the while loop will never execute. This being said, one would sometimes want the loop to execute at least once. Hence the **do while** statement.

    ```cpp
    do 
    	statement
    while (condition);
    ```

- Statements in a do while loop is executed at least once. Once the statement has been executed, the do-while loop checks condition. If **true**, the path of execution jumps back to the do while loop and executes it again.

```cpp
#include <iostream>
 
int main()
{
    // selection must be declared outside do/while loop
    int selection;
 
    do
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }
    while (selection != 1 && selection != 2 &&
        selection != 3 && selection != 4);
 
    // do something with selection here
    // such as a switch statement
 
    std::cout << "You selected option #" << selection << "\n";
 
    return 0;
}
```

# L.5.7 - For statements

Ideal to use a **for** statement when one is aware of the number of times one needs to iterate.

```cpp
for (init-statement; condition-expression; end-expression)
	statement

// Converting for to a while loop
{ // note the block here
    init-statement;
    while (condition-expression)
    {
        statement;
        end-expression;
    }
} // variables defined inside the loop go out of scope here
```

- Variables defined in a loop, have **loop scope**. They only accessible within a loop and not outside.
- Evaluation:
    - The init-statement is evaluated. It's performed only once when the loop is executed.
    - The condition-expression is evaluated. If it evaluates to false, the loop terminates else it continues.
    - After the statement is executed the end-expression is evaluated.

    ```cpp
    for (int count { 0 }; count< 10; ++count)
    	std::cout << count << ' ';
    ```

## Some particularities

- **Off-by-one errors**

    Off-by-one errors occur when the loop iterates one too many or one too few times. This generally happens because the wrong relational operator is used in the conditional-expression (eg. > instead of >=).

- **Omitted expression**

    It is possible to write for loops that omit any or all expressions. It comes in handy when a variable has already been initialised or end-expression need not be run. 

    ```cpp
    int count=0;
    for ( ; count < 10; )
    {
        std::cout << count << ' ';
        ++count;
    }

    OR (infinite loop)
    for(;;)
    	statement;
    ```

- **Multiple declarations**

    Although in a majority of the cases for loops iterate over only a single variable, sometimes one would need to work with multiple variables. 

    ```cpp
    for (int i {0}, int j {9}; i < 0; ++i, --j)
    	std::cout << i << ' ' << j << '\n';
    ```

- **For loops in old code**

    In older versions of C++, variables defined as part of the init-statement did not get destroyed at the end of the loop. 

    ```cpp
    for (int count{ 0 }; count < 10; ++count) // count defined here
        std::cout << count << ' ';
     
    // count is not destroyed in older compilers adn will carry the value 10
    ```

- Nested for loops are possible, like with while loops.

# L.5.8 - Break and continue

Break statements causes a do, for, switch or while statement to terminate. 

- In the context of a loop, a break statement can be used to cause the loop to terminate early.
- A break statement terminates the loop (within which it's called) and continues the execution of the program beyond the switch or loop.

Continue statement way to jump to the end of the loop body for the current iteration. 

```cpp
int count {0};
do 
{
	if (count == 5)
		continue // jump to end of the loop
	std::cout << ' ';
	// The continue statement jumps to here
} while (++count < 10);
```

Judicious use of break and continue can help make loops more readable keeping the number of nested blocks down and reducing the need for complicated looping logic.

# L.5.9 - Random number generation

A **pseudo-random number generator (PRNG)** is a program that takes a number (called **seed**), and performs mathematical operations on it to transform it into some number that appears to be unrelated to the seed. The generated number is taken and performs the same mathematical operation on it to transform it into a new number that appears to be unrelated to the number it was generated from. By continually applying the algorithm to the last generated number, it can generate a series of new numbers that will appear to be random if the algorithm is complex enough. 

*Only seed a random number generator once. Seeding them multiple times will cause the results to be less random or non-random*

```cpp
unsigned int PRNG()
{
	static unsigned int seed {1230};
	// Take the current seed and generate a new value from it
  // Due to our use of large constants and overflow, it would be
  // hard for someone to casually predict what the next number is
  // going to be from the previous one.
	seed = 982039482 * seed + 405837;
	return seed % 4420;
}
int main()
{
	// Print 100 random-numbers
	for (int count {1}; count <= 100; ++count)
	{
		std::cout << PRNG() << '\t';
		if (count%5 == 0)
			std::cout << '\n';
	}
	return 0;
}
```

## Generating random numbers in C++

- C comes with a built-in pseudo-random number generator. It's implemented as two separate functions that live in the cstdlib header:
    - **std::srand()** : sets the initial seed value to a value that's passed in by the caller srand() should only be called once at the beginning of the program.
    - **std::rand()** : generates the next random number in sequence. That number will be a pseudo-random integer between 0 and RAND_MAX, a constant typically set to 32767.

    ```cpp
    #include <iostream>
    #include <cstdlib> // for std::rand() and std::srand()
     
    int main()
    {
        std::srand(5323); // set initial seed value to 5323
     
        // Print 100 random numbers
        for (int count{ 1 }; count <= 100; ++count)
        {
            std::cout << std::rand() << '\t';
     
            // If we've printed 5 numbers, start a new row
            if (count % 5 == 0)
                std::cout << '\n';
    	}
        return 0;
    }
    ```

## PRNG sequence and seeding

- Running **std::rand()** multiple times will print the same sequence every time. So, even if each number in the sequence is seemingly random with regard to the pervious one, the entire sequence is not random at all. This results in predictable sequences, which could sometimes be desirable to reproduce results of a scientific simulation, but in most cases, it isn't desirable. **How to fix this?**
- PRNG sequence is generated from the previous number in a deterministic way. Thus given any seed number to begin with, PRNG will generate the same sequence of numbers from that seed.
- To randomize the entire sequence, one would need to pick a random value for the seed. The system clock is a commonly accepted method to do just this. Using the time value as the seed, PRNG generates a different sequence of random value every time the program is run.
- C comes with a function called std::time(), that returns the number of seconds since midnight on Jan 1, 1970.

    ```cpp
    #include <iostream>
    #include <cstdlib> // for std::rand() and std::srand()
    #include <ctime> // for std::time()
     
    int main()
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
     
        for (int count{ 1 }; count <= 100; ++count)
        {
            std::cout << std::rand() << '\t';
     
            // If we've printed 5 numbers, start a new row
            if (count % 5 == 0)
                std::cout << '\n';
    	}
     
        return 0;
    }
    ```

- Say if one want to generate random values between a **custom** min and max value, rather than 0 and RAND_MAX (to simulate rolling of a die for example).

    ```cpp
    int getRandomNumber(int min, int max)
    {
        static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };  // static used for efficiency, so we only calculate this value once
        // evenly distribute the random number across our range
        return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
    }
    ```

- **std::rand() is a mediocre PRNG**
    - Most implementations of rand() uses a method called **linear congruential generator (LCG)**, the [first example](https://www.notion.so/azmed/L-Control-Flow-2546ee4eec6a498fa7d707dd2fcac8d5#a5e8499ab5644b2b8418d8982e6aaa13) above is one.
    - One of the main short comings for rand() is that RAND_MAX is set to 32767 (15-bits). So the method is not suitable for generating numbers over a larger range. Neither is rand() good if one wants to generate random floating point numbers. This being said, rand() is perfectly suitable for learning how to program, and for programs in which a high-quality PRNG is not a necessity.

## Mersenne Twister

- Setting random seed to a constant value help with debugging and reproducibility.
- For applications where a high-quality PRNG is useful, **Mersenne Twister** is recommended.
- Generating random numbers using Mersenne twister

    ```cpp
    #include <iostream>
    #include <random> // for std::mt19937
    #include <ctime> // for std::time
     
    int main()
    {
    	// Initialize our mersenne twister with a random seed based on the clock
    	std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
     
    	// Create a reusable random number generator that generates uniform numbers between 1 and 6
    	std::uniform_int_distribution<> die{ 1, 6 };
     
    	// Print a bunch of random numbers
    	for (int count{ 1 }; count <= 48; ++count)
    	{
    		std::cout << die(mersenne) << '\t'; // generate a roll of the die here
     
    		// If we've printed 6 numbers, start a new row
    		if (count % 6 == 0)
    			std::cout << '\n';
    	}
     
    	return 0;
    }
    ```

    Mersenne Twister generates random 32-bit unsigned integers (not 15-bit integers like std::rand()), giving a lot more range. There’s also a version (std::mt19937_64) for generating 64-bit unsigned integers.

- In the above example, random generator is used within a single function. How about using it on multiple functions?
    - One can create a static local std::mt19937 variable in each function that needs it (*static* so seed gets called only once), but it's overkill to have every function that needs a random number generator seed and maintain its own local generator.
    - Creating a global random number generator (inside a namespace) is a better option. This would entail declaring it as a non-constant global variable (an exception).

    ```cpp
    #include <iostream>

    namesapce MyRandom
    {
    	std::mt19937 mersenne { static_cast<std::mt19937::result_type>(std::time(nullptr))};
    }
    int getRandomNumber(int min, int max)
    {
    	std::uniform_int_distribution<> die {min, max};
    	return die(MyRandom::mersenne);
    }
    int main()
    {
    	std::cout << getRandomNumber(1, 6) << '\n';
    	std::cout << getRandomNumber(1, 10) << '\n';
    	std::cout << getRandomNumber(1, 20) << '\n';
     
    	return 0;
    }
    ```

- A perhaps better solution is to use a 3rd party library that handles all of this stuff for you, such as the header-only Effolkronium’s random library

    ```cpp
    #include <iostream>
    #include "random.hpp"
     
    // get base random alias which is auto seeded and has static API and internal state
    using Random = effolkronium::random_static;
     
    int main()
    {
    	std::cout << Random::get(1, 6) << '\n';
    	std::cout << Random::get(1, 10) << '\n';
    	std::cout << Random::get(1, 20) << '\n';
     
    	return 0;
    }
    ```

# L.5.10 - std::cin, extraction, and dealing with invalid text input

This chapter is about the ways in which users can enter invalid text input via std::cin and how to handle them

## std::cin, buffers and extraction

- The **>>** operator (in context of cin >>)
    - The operator extracts user input into a variable.
    - When user enters input in response to the **extraction** operation, the data is placed in a buffer.
    - A **buffer** is simply a piece of memory set aside for temporary storage of data. It holds user input while it's waiting to be extracted to variables.

- Usage of the extraction operator entails the following steps:
    - If data is already present in the buffer, it is used for extraction.
    - If the input buffer contains no data, the user is asked to input data for extraction. When the user hits enter, a '\n' character will be placed in the input buffer.
    - **>>** extracts as much as data from the input buffer as it can into the variable (ignoring whitespaces).
    - Un-extracted data is left in the buffer for the next extraction.

```python
int main()
{
    int a;
    cin >> a;
    
    char b;
    cin >> b;
    
    cout <<a<<b;
    return 0;
}
```

If 9e is input, 9 will be assigned to variable a and e will be assigned automatically to variable b without taking into consideration the user input  for b.

- The process of checking whether user input conforms to what the program is expecting is called **validation**. The three ways to perform input validation are:
    - Inline (as the user types) : Prevents user from typing invalid input in the 1st place
    - Post-entry (after the user types) :
        - Let the user enter whatever they want into a string, then validate whether the string is correct, and if so, convert the string to the final variable format.
        - Let the user enter whatever they want, let std::cin and operator>> try to extract it, and handle the error cases
    - Take the below example into consideration:

    ```cpp
    #include <iostream>
     
    double getDouble()
    {
        std::cout << "Enter a double value: ";
        double x;
        std::cin >> x;
        return x;
    }
     
    char getOperator()
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char op;
        std::cin >> op;
        return op;
    }
     
    void printResult(double x, char op, double y)
    {
        if (op == '+')
            std::cout << x << " + " << y << " is " << x + y << '\n';
        else if (op == '-')
            std::cout << x << " - " << y << " is " << x - y << '\n';
        else if (op == '*')
            std::cout << x << " * " << y << " is " << x * y << '\n';
        else if (op == '/')
            std::cout << x << " / " << y << " is " << x / y << '\n';
    }
     
    int main()
    {
        double x = getDouble();
        char op = getOperator();
        double y = getDouble();
     
        printResult(x, op, y);
     
        return 0;
    }
    ```

    - Were correct inputs fed to the program, the output would be as expected. But what if:
        - the user enters a character instead of entering a number? The extraction fails here.
        - the user enters a symbol apart from the ones specified? The input will be extracted, but what happens afterwards is not handled.
        - the user inputs "*q hello" for a symbol input requested? The '*' character will be extracted, but there'll be additional input left in the buffer that could cause problems later.

    ## Types of invalid inputs

    - **Error case 1 : Extraction succeeds but input is meaningless**

        ```cpp
        Enter a double value: 5
        Enter one of the following: +, -, *, or /: k
        Enter a double value: 7
        ```

        - Here instead of the picking symbols from the mentioned list, the user inputs 'k'. Given 'k' is a valid character, it gets returned to main(). However the program wasn't expecting this to happen and hence can't deal with it properly.
        - The **solution** is simple

            ```cpp
            char getOperator()
            {
            	while (true)
            	{
            		std::cout << "Enter one of the following: +, -, *, or /: ";
            		char op;
            		std::cin >> op;
            		
            		// Check whether the user entered meaningful input
            		if (op == '+' || op == '-' || op == '*' || op == '/')
            			return op;
            		else // tell the user that input is valid and try again
            			std::cout << "Oops, that input is invalid.  Please try again.\n";
            	} // and try again
            }
            ```

    - **Error case 2 : Extraction succeeds but with extraneous input**

        ```cpp
        Enter a double value: 5*7
        Enter one of the following: +, -, *, or /: Enter a double value: 5 * 7 is 35
        ```

        The program prints the right value, but the formatting is all messed up. 

        - When the user enters “5*7” as input, that input goes into the buffer. Then operator>> extracts the 5 to variable x, leaving “*7\n” in the buffer.
        - - Next, the program prints “Enter one of the following: +, -, *, or /:”. However, when the extraction operator was called, it sees “*7\n” waiting in the buffer to be extracted, so it uses that instead of asking the user for more input. Consequently, it extracts the ‘*’ character, leaving “7\n” in the buffer.
        - The same story repeats for 7.

        It would be perfect if the program can ignore any extraneous characters. 

        - **std::cin.ignore(32767, '\n')** does just this. It clears (up to 32767) characters out of the buffer until '\n' is encountered.

            ```cpp
            double getDouble()
            {
                std::cout << "Enter a double value: ";
                double x;
                std::cin >> x;
                std::cin.ignore(32767, '\n'); // clear (up to 32767) characters out of the buffer until a '\n' character is removed
                return x;
            }
            ```

    - **Error case 3 : Extraction fails**

        ```cpp
        Enter a double value: a
        Enter one of the following: +, -, *, or /: Enter a double value:
        ```

        The program simply ends when character 'a' is input. But, how so?

        - When user enters 'a', the character is placed in the buffer.
        - The **>>** then tries to extract 'a' to variable x, of type double.
        - Since 'a' can't be converted to double, >> can't extract.
        - 'a' is then left in the buffer and std::cin goes into failure mode.

        Guess what! Fortunately, this can be detected too! 

        ```cpp
        double getDouble()
        {
        	while (true) // loop until user enters valid input
        	{
        		std::cout << "Enter a double value : ";
        		double x;
        		std::cin >> x;
        		
        		if (std::cin.fail()) // has a previous extraction faild?
        		{
        			// handle failure 
        			std::cin.clear(); // put us back in 'normal' operation mode
        			std::cin.ignore(32767, '\n'); // and remove bad input
        		}
        		else // if succeeded
        		{
        			std::cin.ignore(32767, '\n');
        			return x;
        		}
        }
        ```

    - **Error case 4 : Extraction succeeds but the user overflows a numeric value**

        ```cpp
        #include <cstdint>
        #include <iostream>
         
        int main()
        {
            std::int16_t x { 0 }; // x is 16 bits, holds from -32768 to 32767
            std::cout << "Enter a number between -32768 and 32767: ";
            std::cin >> x;
         
            std::int16_t y { 0 }; // y is 16 bits, holds from -32768 to 32767
            std::cout << "Enter another number between -32768 and 32767: ";
            std::cin >> y;
         
            std::cout << "The sum is: " << x + y << '\n';
            return 0;
        }

        Enter a number between -32768 and 32767: 40000
        Enter another number between -32768 and 32767: The sum is: 32767
        ```

        What happens if the user enters a number that is too large?

        - std::cin goes immediately into **failure mode**, but also assigns the closest in-range value to the variable. Consequently x is assigned 32767.
        - Additional inputs are skipped, leaving y with the initialized value of 0. This error can be handled in the same way as a failed extraction.

        Putting it all together: 

        ```cpp
        #include <iostream>

        using namespace std;

        double getDouble()
        {
            while (true) // check user value and continue loop if invalid
            {
                double x;
                cout << "Enter a double value : ";
                cin >> x;
                
                
                if (cin.fail())
                {
                    cin.clear(); // return back to normal state
                    cin.ignore(32767, '\n'); // remove any extraneous inputs
                    cout << "Invalid double input entered, please try again .. \n";
                }
                else
                {
                    cin.ignore(327767, '\n');
                    return x;
                }
            }
        }

        char getOperator()
        {
            while (true)
            {
                char op;
                cout << "Enter one of the following: +, -, *, or /: ";
                cin  >> op;
                
                cin.ignore(32767, '\n');
                
                if (op == '+' || op == '-' || op == '*' || op == '/')
                    return op;
                else
                    cout << "Invalid operator input entered, please try again ... \n";
            } // try again
        }

        void printResult(double x, char op, double y)
        {
            if (op == '+')
                std::cout << x << " + " << y << " is " << x + y << '\n';
            else if (op == '-')
                std::cout << x << " - " << y << " is " << x - y << '\n';
            else if (op == '*')
                std::cout << x << " * " << y << " is " << x * y << '\n';
            else if (op == '/')
                std::cout << x << " / " << y << " is " << x / y << '\n';
            else // Being robust means handling unexpected parameters as well, even though getOperator() guarantees op is valid in this particular program
                std::cout << "Something went wrong: printResult() got an invalid operator.";
        }

        int main()
        {
            double x    = getDouble();
            char  op    = getOperator();
            double y    = getDouble();
            
            printResult(x, op, y);
            
            return 0;
        }
        ```

As you write your programs, consider how users will misuse your program, especially around text input. For each point of text input, consider:

- Could the extraction fail?
- Could the user enter more inputs than expected?
- Could the user enter meaningless input?
- Could the user overflow an input?

# L.5.11 - Introduction to testing code

- **Testing challenge** : comprehensive testing of even a simple block of code would require a myriad number of iterations passing all possible inputs are arguments.

## Testing tips

- **Tip 1** : Write your program in small and well defined units (functions), compile often along the way.
- **Code coverage** : how much of the source code is executed while testing
- **Tip 2** : Aim fro 100% statement coverage
    - **Statement coverage** : percentage of statements in the code that have been exercised by ones testing routines.

        ```cpp
        int foo(int x, int y)                // EXAMPLE 1
        {
            bool z = y;
            if (x > y)
            {
                z = x;
            }
            return z;
        }
        // foo(1,0) gives complete statement coverage for this 
        // function, as every statement in the function is executed

        bool isLowerVowel(char c)           // EXAMPLE 2
        {
            switch (c) // statement 1
            {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true; // statement 2
            default:
                return false; // statement 3
            }
        }
        // Two test calls will be require two calls to test all
        // the statements, as statements 2 and 3 can't be tested
        // in the same function call.
        ```

- **Tip 3** : Aim for 100% branch coverage
    - **Branch coverage** : refers to the percentage of branches that have been executed, with the affirmative case and negative case counting separately.
    - In *code example 1* foo(1,0) gave us 100% statement coverage and exercised the positive use case, but only gives 50% branch coverage. foo(1,0) ought to called once more to test the use case where the if statement doesn't execute.

    *Test each branch such that they are true at least once and false at least once*

- **Tip 4** : Aim for 100% loop coverage (0, 1, 2 test)
    - The idea is, if one has a loop in their code, one should ensure it works properly 0 times, 1 time and 2 times. If it works correctly for the 2 iteration case, it should work correctly for all iterations greater than 2.
- **Tip 5** : Ensure one is testing different categories of input
    - Category is a set of inputs that have similar characteristics.
    - Guidelines for category testing:
        - **For integers**, one should ensure that the function handles negative values, zero and positive values. *For user input, overflow must be checked for, if relevant.*
        - **For floating point number**, scrutinise how the function handles values that have precision issues (values slightly smaller or larger than expected). 0.1 to -0.1  to test numbers that are slightly larger than expected, and 0.6 to -0.6 to test numbers that are slightly smaller than expected.
        - **For strings**, examine how ones function handles an empty string (just a null terminator), normal valid string, strings that have whitespaces and strings that are white spaces. If ones function takes a pointer to a char array, don't forget to test nullptr as well.

## Other pointers

- Although writing tests and erasing them is good enough for quick and temporary testing. For code that one expects to be reused or modified in the future, it makes more sense to preserve ones tests.
- **Automating testing** :

    ```cpp
    #include <iostream>
     
    bool isLowerVowel(char c)
    {
        switch (c)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
        }
    }
     
    // returns the number of the test that failed, or 0 if all tests passed
    int test()
    {
        if (isLowerVowel('a') != true) return 1;
        if (isLowerVowel('q') != false) return 2;
     
        return 0;
    }
     
    int main()
    {
        return 0;
    }
    ```

    Now, one can call test() at any time to re-prove that one hasn't broken anything, and the test routine will do all the work.

# L.5.x - Chapter 5 comprehensive quiz

- **If statements** allow to execute a statement based on whether some condition is **true**. **Else statements** execute if the associated if statement is **false**.
- **Switch** statement provides a cleaner and faster method for selecting between a number of discrete items. *Switch statements pair great with enumerations*.
- **Goto** statements allow the program to jump to somewhere else in the code. **Don't use them.**
- **While** loops allow the program to loop as long as the given condition is true.
- **Do while** loops are similar to while loop, but the condition is evaluated after the loop execution. *They are great for things that ought to be executed at least once*.
- **For** loops are used when a loop is wished to be effectuated a specific number of times.
- **Break** statements allow us to break out of a switch, while, do while, for loop or range based for loop.
- **Continue** statements allow us to move immediately to the next loop iteration.