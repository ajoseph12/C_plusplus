# 11 - Functions

# 11.1 - Function parameters and arguments

- A **function** **parameter** is a variable declared in the function declaration : `void foo(int x)`
- An argument is the value passed to the function by the caller : `foo(6)`
- When a function is called, the parameters of the function is created as variables, and the value of the arguments are copied into the parameters.
- Function parameters have **local** scope.

# 11.2 - Passing arguments by values

- By default, non-pointer arguments in C++ are passed by value, i.e argument value is **copied** onto function parameters.
- **Advantages** of passing by value
    - Arguments passed by value value can be just about anything : variables (e.g. x), literals (e.g. 6), expressions (e.g. x+1), structs and classes, and enumerators.
    - Arguments are **never changed** by the function being called.
- **Disadvantages** of passing by value
    - Copying structs and classes can incur a significant performance penalty, especially if the function is called multiple times.
- **One can pass** by value, when passing fundamental data type and enumerators, and the function doesn't need to change the argument.
- **One shouldn't pass** by value when passing struct or classes (including std::array, std::vector, and std::string).

# 11.3 - Passing arguments by reference

- Passing a variable by reference entails declaring function parameters as references rather than normal variables.
    
    ```cpp
    void addOne(int &ref) // ref is a reference variable
    {
    	ref += 1
    }
    
    int main()
    {
        int value = 5;
     
        cout << "value = " << value << '\n';
        addOne(value);
        cout << "value = " << value << '\n';
        return 0;
    }
    ```
    
    - Unlike a pointer, once a reference is bound to an object, it can not be "reseated" to another object. The reference itself isn't an object (it has no identity; taking the address of a reference gives you the address of the referent; remember: the reference is its referent).
- Sometimes we'd want to return multiple values, However, since functions can have only one return value, references can come in handy.
    
    ```cpp
    void getSinCos(double degrees, double &sinOut, double &cosOut)
    {
    	static constexpr double pi { 3.14 };
    	double radians = degrees * pi / 180.0;
    	sinOut = std::sin(radians);
    	cosOut = std::cos(radians);
    }
    int main()
    {
    	double sin(0.0);
    	double cos(0.0);
    	getSinCos(30, sin, cos);
    	std::cout << sin << std::endl;
    	std::cout << cos << std::endl;
    	return 0;
    }	
    ```
    
    Doing so comes with a set of caveats:
    
    - Caller must pass arguments to hold updated outputs even if it's never used.
    - It's not obvious that sin and cos are output variables, misinterpretations of the same could cause big problems down the lane.
    
    Using reference to return multiple values is not recommend, however were one to choose to follow through, it's advised to use an "out" prefix to name the object.
    
- Non-const references can only reference non-const l-value, so reference parameter **cannot** accept an argument that is a constant l or r value.
- Using references in function to pass large objects such as structs and array do indeed help with optimizing the process flow.
    - However, were a reference meant to refer an object for read-only purposes, the reference doesn't provide any guarantee on the fact that it'll not be modified.
    - Under such circumstances, it's is advised to pass arguments by **constant reference**.
        
        ```cpp
        void foo(const std::string &x) // x is a const reference
        {
            x = "hello";  // compile error: a const reference cannot have its value changed!
        }
        ```
        
    
    When passing an argument by reference, always use a const reference unless you need to change the value of the argument.
    
- Non-constant references can't bind to r-values.
    
    ```cpp
    #include <string>
     
    void foo(std::string& text) {}
     
    int main()
    {
      std::string text{ "hello" };
      
      foo(text); // ok
      foo(text + " world"); // illegal, non-const references can't bind to r-values.
     
      return 0;
    }
    ```
    
- It's possible to pass a pointer by reference and have the function change the address of the pointer.
    
    ```cpp
    #include <iostream>
    void foo(int *&ptr)
    {
    	ptr = nullptr;
    }
    int main()
    {
    	int x = 5;
    	int *ptr = &x;
    	std::cout << "ptr is : " << (ptr ? "non-null" : "null") << "\n";
    	foo(ptr);
    	std::cout << "ptr is : " << (ptr ? "non-null" : "null") << "\n";
    	return 0;
    }
    ```
    
- A C-style array can be passed by reference too. However in order to edit the array or access the type information the fixed array is carrying, one would have to explicitly define the array size in the parameter.
    
    ```cpp
    #include <iostream>
     
    // Note: You need to specify the array size in the function declaration
    void printElements(int (&arr)[4])
    {
      int length{ sizeof(arr) / sizeof(arr[0]) }; // we can now do this since the array won't decay
      
      for (int i{ 0 }; i < length; ++i)
      {
        std::cout << arr[i] << '\n';
      }
    }
     
    int main()
    {
        int arr[]{ 99, 20, 14, 80 };
        
        printElements(arr);
     
        return 0;
    }
    ```
    
- When to use pass by reference:
    - When passing structs or classes (use `const` if read-only).
    - When you need the function to modify an argument.
    - When you need to access the type of information of a fixed-array.
- Don't use references when using fundamental data-types that need not be modified.

Use pass by (const) reference instead of pass by value for structs and classes and other expensive-to-copy types.

# 11.4 - Passing arguments by address

- It involves passing the address of the argument variable instead of the variable itself. Since the argument is an address, the function parameter must be a pointer. The function can then de-reference the pointer to access or change the value being pointed to.
    
    ```cpp
    void food(int *ptr)
    {
    	*ptr = 6;
    }
    int main()
    {
    	int value{ 5 };
    	std::cout << "value = " << value << '\n';  // 5
      foo(&value);
      std::cout << "value = " << value << '\n';  // 6
      return 0; 
    }
    ```
    
- Built-in-arrays passed to a function uses pointers to indicate its location (and to avoid passing large arrays as arguments to function).
    
    ```cpp
    void printArray(int *array, int len)
    {
    	// if user passed in a null pointer for array, bail out early!
      if (!array)
        return;
    	for(int i{ 0 }; i < len; ++i)
    		std::cout << array[i] << ' ';
    }
    int main()
    {
    	int array[3]{1, 2, 3};
    	printArray(array, 3) // no need for '&' as array evaluates to pointer to its 1st element
    ```
    
    ⚠️Fixed arrays decay into pointers, hence length ought to passed as a separate parameter.
    
    ⚠️Ensure parameters passed by address are not null pointers, as it can cause a program to crash
    
- **Passing by const address** is advised when the function is not meant to change the content of the content the address is point at. `void printArray(const int *array, int len)`
- Since **addresses are passed by value**, any changes to the pointer [parameter](https://www.notion.so/11-Functions-9056d9573ebd4883b3567619ffe3ef07) effectuated in the function wouldn't be reflected in the original pointer argument
- Food for thought
    - When passing an argument by address, the function parameter receives a copy. So the argument and the parameter will hold similar values.
    - The function parameter can then be dereferenced to modify the value at the address. Were this to be done, the value the argument and the parameter was pointing towards will reflect this change.
    - If the function parameter is assigned a different address, it will not impact the argument. Since the function parameter is a copy, and changing the copy won’t impact the original.
- Nevertheless, were one looking to modify the function parameter, it can be done by passing the address by reference.
    
    ```cpp
    #include <iostream>
     
    // tempPtr is now a reference to a pointer, so any changes made to tempPtr 
    // will change the argument as well!
    void setToNull(int *&tempPtr)
    {
        tempPtr = nullptr; // use 0 instead if not C++11
    }
     
    int main()
    { 
        // First we set ptr to the address of five, which means *ptr = 5
        int five{ 5 };
        int *ptr{ &five };
    	
        // This will print 5
        std::cout << *ptr;
     
        // tempPtr is set as a reference to ptr
        setToNull(ptr);
     
        // ptr has now been changed to nullptr!
     
        if (ptr)
            std::cout << *ptr;
        else
            std::cout << " ptr is null";
     
        return 0;
    }
    ```
    
- To summarize
    - References are typically implemented by the compiler as pointers. Meaning, behind the scenes, pass by reference is essentially just a pass by address (with access to the reference doing an implicit dereference).
    - And as seen from above, pass by address is actually just passing an address by value. Therefore, we can conclude that C++ really passes everything by value! The properties of pass by address (and reference) come solely from the fact that we can dereference the passed address to change the argument, which we can not do with a normal value parameter!
    - **Advantages of passing by address**
        - Allows function to change the value of the argument. Using `const` can ensure this doesn't happen.
        - The argument is not copied, hence it's fast.
        - Multiple values can be returned via out parameter.
    - **Disadvantages of passing by address**
        - Since literals and expressions don't have address, pointer arguments must be normal variables.
        - All values must be checked to see whether they are null.
        - Because dereferencing a pointer is slower than accessing a value directly, accessing arguments passed by address is slower than accessing arguments passed by value.
    
    **⚠️Prefer pass by reference to pass by address whenever applicable.**
    

# 11.5 - Returning values by value, reference and address

## Returning by value

- The simplest and safest type to use.
- A copy of the value is returned to the caller.
- One can return by value literals (e.g. 5), variables (e.g. x), or expressions (e.g. x+1), which makes return by value very flexible.
- Using return by value allows caller to receive values that have interacted with local variables.

```cpp
int doubleValue(int x)
{
	int value{ x * 2 };
	return value;
}
```

- Return by value when returning:
    - variables declared in the function
    - function arguments passed by value.
- Don't return by value when returning:
    - a built-in array or pointer (use return by address)
    - a large struct or class

## Returning by address

- Involves returning address of a variable to the caller.
- Similar to pass by address, return by address can only return address or a variable (not literals and expressions)
- Use return by address when returning:
    - dynamically allocated memory, and one can't use a type to handle allocations.
    - function arguments that were passed by address.
- Don't use return by address when returning :
    - variables declared inside the function or parameters passed by value.
    - large struct or class passed by reference (use reference).

⚠️Returning address of a variable local to the function could result in the program exhibiting undefined behaviour. 

```cpp
int* doubleValue(int x)
{
	int value{ x * 2 };
	return &value
}
```

Often used to return [dynamically allocated](https://www.notion.so/P-Arrays-Strings-Pointers-and-References-b91fb87503e2465aa81bf328e41f97ad) memory to the caller. This works cause dynamic memory doesn't go out of scope at the end of the block in which it it's declared, so memory will still exist when address is returned back to the caller.

```cpp
int* allocateArray(int size)
{
	return new int[size];
}
int main()
{
	int *array{ allocateArray(25) };
```

## Return by reference

- Values returned by reference must be variables (shouldn't return a reference to a literal or an expression that resolves to a temporary value, as those will go out of scope at the end of the function and you'll end up returning a dangling reference).
- Return by reference is often used to return arguments passed by reference to the function back to the caller.
- **Use** return by reference when returning
    - a reference parameter.
    - member of an object passed into function by reference or address.
    - a larger struct or class that will not be destroyed at the end of the function.

```cpp
int& doubleValue(int x)
{
	int value{ x * 2 };
	return value;
}// value destroyed here (caller receives
// garbage value)
```

```cpp
int& getElement(std::array<int, 25> &array, int index)
{
	return array[index]
}
int main()
{
	std::array<int, 25> array;
	getElement(array, 10) = 5;
	std::cout << std::array[index] ; // prints 5
	return 0;
} 
```

- **Don't** use return by reference when returning:
    - variables declared inside a function or parameters passed by value.
    - built-in array or pointer value (use return by address).

## Mixing return references and values

Given the code snippet,

- in **case A** a reference return value is assigned to a non-reference variable. Since **giana** isn't a reference, the return value is copied into **giana** as if `returnByReference` had return by value.
- In **case** **B** reference **ref** is being initialized with a copy of the value returned by `returnByValue`. However, since the value being returned doesn't have an address (since it's an r-value) a compiler error is thrown.
- **Case C** works just fine as const references can bind to r-values. In theory , the scope of the literal is local and is bound to terminate at the end of the function. However, when bound to const-reference, the lifetime of the r-value is extended to match the lifetime of the reference.

```cpp
int returnByValue()
{
	return 5;
}
int& returnByReference()
{
	static int x{ 5 }; // ensure x isn't destroyed at the end of the function.
	return x;
}
int main()
{
	int giana{ returnByReference() }; // case A -- ok, treated as return by value
  int& ref{ returnByValue() }; // case B -- compile error since the value is an r-value, and an r-value can't bind to a non-const reference
  const int& cref{ returnByValue() }; // case C -- ok, the lifetime of the return value is extended to the lifetime of cref
	return 0;
}
```

## Returning multiple values

Unfortunately C++ hasn't put in-place any direct means for passing multiple values back to the caller. Fortunately, there exists a few indirect method.

- Passing out parameters as discussed [here](https://www.notion.so/11-Functions-9056d9573ebd4883b3567619ffe3ef07) is one way, however it's not advised.
- Another method involves using a data-only struct
    
    ```cpp
    struct S
    {
    	int m_x;
    	double m_y;
    }
    S returnStruct()
    {
    	S s;
    	s.m_x = 5;
    	s.m_y = 1.2;
    	return s;
    }
    int main()
    {
    	S s{ returnStruct() };
    	std::cout << s.m_x << ' ' << s.m_y << '\n';
    	return 0;
    }
    ```
    
- Another way is to use `std::tuple`. A tuple is a sequence of elements that may be of different types, where the type of each element must be explicitly specified.
    
    ```cpp
    #include <tuple>
    #include <iostream>
    
    std::tuple<int, double> returnTuple() // return a tuple that contains an int and a double
    {
    	return {5, 6.7}
    }
    int main()
    {
    	std::tuple s{ returnTuple() }; // get our tuple
    	std::cout << std::get<0>(s) << ' ' << std::get<1>(s) << '\n'; // std::get<n> gets nth value of tuple
    	return 0;
    }
    ```
    
- One can also use `std::tie` to unpack the tuple into pre-defined variables
    
    ```cpp
    #include <tuple>
    #include <iostream>
    
    std::tuple<int, double> returnTuple() // return a tuple that contains an int and a double
    {
    	return {5, 6.7}
    }
    int main()
    {
    	int a;
    	double b;
    	std::tie(a, b) = returnTuple(); // put elements of tuple in variables a and b
    	std::cout << a << " " << b << '\n';
    	return 0;
    }
    /*
    C++17
    auto [a, b]{ returnTuple() };
    std::cout << a << ' ' << b << '\n';
    */
    ```
    

Using a `struct` is a better option that a tuple, especially if it's being used in multiple places. However, for cases where you’re just packaging up these values to return and there would be no reuse from defining a new struct, a tuple is a bit cleaner

## Quiz

1. A function named sumTo() that takes an integer parameter and returns the sum of all the numbers between 1 and the input number.
    
    ```cpp
    int sumTo(const int num)
    {
    	int sum{ 0 };
    	for(int i{ 0 }; i <= num; i++)
    		sum += i
    	return sum
    }
    ```
    
2. A function named printEmployeeName() that takes an Employee struct as input.
    
    ```cpp
    void printEmployeeName(const Employee &emp_struct){
     
    ```
    
3. A function named minmax() that takes two integers as input and returns back to the caller the smaller and larger number in a std::pair. A std::pair works identical to a std::tuple but stores exactly two elements.
    
    ```cpp
    std::pair<int, int> minmax(const int a, const int b)
    ```
    
4. A function named getIndexOfLargestValue() that takes an integer array (as a std::vector), and returns the index of the largest element in the array.
    
    ```cpp
    int getIndexOfLargestValue(const std::vector<int>& vector)
    ```
    
5. A function named getElement() that takes an array of std::string (as a std::vector) and an index and returns the array element at that index (not a copy). Assume the index is valid, and the return value is const.
    
    ```cpp
    const std::string& getElement(const std::vector<std::string>& array, const int index)
    ```
    

# 11.6 - Inline functions

- Some of the benefits of using functions are:
    - Code inside the function can be reused.
    - It's much easier to change or update code in a function.
    - It makes the code easier to read and understand.
    - They provide type checking to ensure function call arguments match the function parameters.
    - They allow for easier debugging.
- This being said, a major downside of functions is that every time a function is called,
    - A certain amount of performance overhead is implicit.
    - As the CPU ought to store the address of the current instructions it's executing (so it knows where to return to later) along with other registers, all the function parameters must be created and assigned values, and the program has to branch to a new location.
- For functions that are large and perform complex tasks, the overhead is usually insignificant compared to the amount of time the function takes to run.
- For small, commonly-used functions, the **time needed to make the function call is longer** than the time needed to execute it, resulting in substantial performance penalty. **Inline functions to the rescue**.
- Consider the code snippet below
    
    ```cpp
    int min(int x, int y)
    {
        return x > y ? y : x;
    }
     
    int main()
    {
        std::cout << min(5, 6) << '\n';
        std::cout << min(3, 2) << '\n';
        return 0;
    }
    ```
    
    `min()` is called twice, incurring function call overhead penalty twice. Since it's short, it make for a perfect candidate for inlining. 
    
    ```cpp
    inline int min(int x, int y)
    {
    	return x > y ? y : x
    }
    ```
    
    When the program now runs with with the inline function, it will do in the following fashion 
    
    ```cpp
    int main()
    {
        std::cout << (5 > 6 ? 6 : 5) << '\n';
        std::cout << (3 > 2 ? 2 : 3) << '\n';
        return 0;
    }
    ```
    
    This will execute quite a bit faster, at the cost of the compiled code being slightly larger.
    
- `inline` keyword is only a recommendation to the compiler. It can ignore the keyword were it to find the function lengthy or complex.
- Modern compilers are quite good at inlining functions automatically. Even if a function is not declared explicitly with the `inline` keyword, modern compliers will inline the function if it deems doing so would bring about an improvement in performance.
- Previously we have seen that implementing functions (with external linkage) in header files and then including them into multiple .cpp files raises an error, as the same function would be defined more than once.
    - Inline function are exempt from this rule because they do not actually result in a real function being compiled - therefore, there’s no conflict when the linker goes to link multiple files together.

# 11.7 - Function overloading

It's a feature in C++ that allows one to create multiple functions with the same name, as long as they have different parameters.

## Why function overloading?

To understand the need for function overloading, let's take the example below:

- `addInteger` adds two integers where as `addDouble` adds two double
    
    ```cpp
    int addInteger(int x, int y)
    {
        return x + y;
    }
     
    double addDouble(double x, double y)
    {
        return x + y;
    }
    ```
    
    While there's nothing wrong the above code snippet, one must keep in mind the names of the functions in order to call the right one when the time comes.
    
- On the contrary, `add` can be defined with different parameters to accommodate addition of integers and double.
    
    ```cpp
    int add(int x, int y)
    {
        return x + y;
    }	
    double add(double x, double y)
    {
        return x + y;
    }
    ```
    
    Declaring two function with the same name is called **overloading**, but in this case an error is not thrown since the parameter types of the functions are different. Therefore, the compiler will be able to select the appropriate function based on the arguments passed.
    

## Matching function calls

- Making a call to an overloaded function results in one of three possible outcomes:
    - **A match is found** : The call is resolved to a particular overloaded function.
    - **No match is found** : The arguments cannot be matched to any overloaded function.
    - **An ambiguous match is found** : The arguments matched more than one overloaded function.
- When an overloaded function is called, C++ goes through the following process to determine which version of the function was called:
    - First, C++ tries to find an exact match - the case where passed arguments matches perfectly with the parameters of one of the functions.
        
        ```cpp
        void print(char *value);
        void print(int value);
         
        print(0); // exact match with print(int)
        ```
        
        Although could technically match (char *) as a null pointer, it exactly matches int. Matching (char *) would require implicit conversion.
        
    - If not exact match is found, C++ tries to find a match through promotion ([link](https://www.notion.so/6-Object-Scope-and-Conversions-c1d2b4cb978545aa82c53437dbdd2f2c)).
        - Char, unsigned char, and short is **promoted** to int.
        - Unsigned short can be **promoted** to int or unsigned int, depending on the size of an int.
        - Float is **promoted** to double
        - Enum is **promoted** to int
        
        ```cpp
        void print(char *value);
        void print(int value);
         
        print('a'); // promoted to match print(int)
        ```
        
        In this case, because there isn't `print(char)` it's promote to int.
        
    - If no promotion is possible, C++ tries to find a match through standard conversion, which includes
        - Any numeric type will match with any other numeric type, including unsigned (e.g. int to float)
        - Enum will match the format type of a numeric type (e.g. enum to float)
        - Zero will match a pointer type and numeric type (e.g. 0 to char*, or 0 to float)
        - A pointer will match a void pointer.
        
        ```cpp
        struct Employee; // defined somewhere else
        void print(float value);
        void print(Employee value);
         
        print('a'); // 'a' converted to match print(float)
        ```
        
        Here, neither is `print(char)` nor is `print(int)` present (promotion match). the 'a' is then converted to a float and matched with `print(float)`.
        
        ⚠️ All standard conversion are considered equal. No standard conversion is considered better than another.
        
    - Finally, C++ tries to find a match through user-defined conversion. Classes can define conversions to other types that can be implicitly applied to objects of that class (one could define `class X` and as user-defined conversion to `int`.
        
        ```cpp
        class X; // with user-defined conversion to int
         
        void print(float value);
        void print(int value);
         
        X value; // declare a variable named value of type class X
        print(value); // value will be converted to an int and matched to print(int)
        ```
        
        Although `value` is of type class X, because this particular class has a user-defined conversion to int, the function call `print(value)` will resolve to `Print(int)` version of the function.
        
    
    ## Ambiguous matches
    
    - Since standard conversions are considered equal, it's possible that a function call could result in more than one match.
        
        ```cpp
        void print(unsigned int value);
        void print(float value);
        print('a');
        print(0);
        print(3.14159);
        ```
        
        - In case `print('a')` doesn't find an exact match, it's promoted to `int`, but `print(int)` is absent too. Using standard conversion, it can convert 'a' to both an unsigned int and a floating point value. And since all standard conversions are equal this is an ambiguous match.
        - `print(0)` is similar. 0 is int, and there isn't `print(int)`, it matches both calls via standard conversion.
        - `print(3.14159)` is a double (`f` suffix ought to be used for it to be considered `float`). There is no `print(double)`, consequently, it matches both calls via standard conversion.
        
        To match with multiple arguments C++ applies the matching rules to each argument in turn.
        
    
    # 11.8 - Default arguments
    
    - Value provided by the function parameter in case the user doesn't if a user doesn't supply an explicit argument.
        
        ```cpp
        void printValues(int x, int y=10) // 10 is the default argument, y is now an optional parameter
        {
            std::cout << "x: " << x << '\n';
            std::cout << "y: " << y << '\n';
        }
         
        int main()
        {
            printValues(1); // y will use default argument 10
            printValues(3, 4); // y will use user-supplied argument 4
        ```
        
    - Default arguments are an excellent option when the function needs a value that the user may or many not want to override. For example :
        
        ```cpp
        void openLogFile(std::string filename="default.log");
        int rollDie(int sides=6);
        void printStringInColor(std::string str, Color color=COLOR_BLACK); // Color is an enum
        ```
        
    - A function can have multiple default arguments.
        
        ```cpp
        void printValues(int x=10, int y=20, int z=30)
        {
            std::cout << "Values: " << x << " " << y << " " << z << '\n';
        }
        ```
        
    
    ⚠️  In the code above It's impossible to supply an argument for parameter z without also
          supplying arguments for parameters x and y. This is because C++ doesn't support a
          function call syntax such as `printValues( , , 3)`. This has two major repercussions:
    
    - All default arguments must be for the right most parameters. The following is not allowed: `void printValue(int x=10, int y);`
    - If more than one default argument exists, the leftmost argument must be the one most likely to be explicitly set by the user.
    - Once declared, default arguments can't be re-declared.
        
        ```cpp
        void printValues(int x, int y=10);
        void printValues(int x, int y=10) // error: redefinition of default argument
        {
            std::cout << "x: " << x << '\n';
            std::cout << "y: " << y << '\n';
        }
        ```
        
        Best practice is to declare the default argument in the forward declaration and not in the function definition, as the forward declaration is more likely to be seen by other files (especially if it's in the header).
        
    - Function with default arguments may be overloaded. This following is allowed :
        
        ```cpp
        void print(std::string string);
        void print(char ch=' ');
        ```
        
        If `print()` is called, it would resolve to `print(' ')` , which would print space.
        
    
    ❗ Optional parameters do NOT count towards the parameters that make the function unique. 
         Hence the following isn't allowed:
    
    ```cpp
    void printValues(int x);
    void printValues(int x, int y=20);
    ```
    
    Were `printValues(10)` to be called, the complier wouldn't be able to diambiguate between the two `printValues` functions.
    

# 11.9 - Function Pointers

- Variables that point to functions.
- Following is the syntax towards creating a non-const function pointer : `int (*fcnPtr)()`.
    - The pointer in the example points towards a function that has no parameters and returns an integer.
    - The parenthesis around `*fcnPtr` is essential for precedence reasons, else `*fcnPtr()` would be interpreted as forward declaration for a function named fcnPtr that takes no parameters and returns a pointer to an integer.
    - To create a contant function pointer, the const goes after asterisk : `int (*const fcnPtr)()`

## Assigning a function to a pointer and calling it using the pointer

- Function pointers can be initialized with a function (and non-const function pointers can be assigned a function).
- Like with pointers to variables, one can add `&` before the function to obtain its address.
    
    ```cpp
    int foo()
    {
    	return 5;
    }
    int goo()
    {
    	return 6;
    }
    int main()
    {
    	int (*fcnPtr)(){ &foo }; // fcnPtr points to foo
    	fcnPtr = &goo;           // fcnPtr points to goo
    	return 0;
    }
    ```
    
- A common mistake is `fcnPtr = goo()`, which would assign the return value of the function to the function pointer.
- The type (parameter return type) of the function pointer must match the type of the function.
    
    ```cpp
    // function prototypes
    int foo();
    double goo();
    int hoo(int x);
     
    // function pointer assignments
    int (*fcnPtr1)(){ &foo }; // okay
    int (*fcnPtr2)(){ &goo }; // wrong -- return types don't match!
    double (*fcnPtr4)(){ &goo }; // okay
    fcnPtr1 = &hoo; // wrong -- fcnPtr1 has no parameters, but hoo() does
    int (*fcnPtr3)(int){ &hoo }; // okay
    ```
    
- There are two ways of calling a function using the pointer:
    - Via explicit reference
        
        ```cpp
        int foo(int x)
        {
        	return x;
        }
        int main()
        {
        	int (*fcnPtr)(int){ &foo };
        	(*fcnPtr)(5);
        	return 0;
        }
        ```
        
    - Via implicit reference
        
        ```cpp
        int foo(int x)
        {
        	return x;
        }
        int main()
        {
        	int (*fcnPtr)(int){ &foo };
        	fcnPtr(5);
        	return 0;
        }
        ```
        
    - One can notice that implicit dereference method looks just like a normal function call -which is what you’d expect, since **normal function names are pointers to functions anyway**!
    
    ℹ️   Default paramètres won't work for functions called through function pointers.  Default parameters are resolved at compile time - if argument is not supplied for a default parameter, the compiler substitutes one during compilation. However, function pointers resolved at run-time, hence default parameters can't be resolved when making a function call with a function pointer - values ought to be explicitly passed.
    
    ## Passing functions as arguments to other functions
    
    - Function used as arguments to another function are sometimes called **callback function**.
    - An example of such a use case would be, say a function is being written to sort an array, and say one would want the user to define how the particular sorting task ought to be performed.
    - Example
        - Below is the selection sort algorithm
            
            ```cpp
            void SeclectionSort(int *array, int size)
            {
            	// Step through each element in the array
            	for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
            	{
            		// smallestIndex is the index of the smallest element we've encountered so far
            		int smallestIndex{ startIndex };
            		
            		// Look for the smallest element in the remaining array from startIndex + 1 onwards
            		for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
            	
            		// If the current element is smaller than the previous smallest element
            		if (array[smallestIndex] > array[currentIndex])
            		{
            			smallestIndex = currentIndex
            		}
            		// Swap start element with smallest element
            		std::swap(array[startIndex], array[smallestIndex]);
            	}
            }
            ```
            
        - Let's replace the comparison with a function like this
            
            ```cpp
            bool ascending(int x, int y)
            {
            	return x > y; // swap if 1st element is greater than 2nd
            }
            
            void SeclectionSort(int *array, int size)
            .
            .
            if (ascending(array[smallestIndex], array[currentIndex])) // COMPARISON DONE HERE
            .
            .
            ```
            
        - Now to let the caller decide how the sorting will be done, instead of using our hard-coded comparison function, we can allow the caller to pass a custom function.
            
            ```cpp
            void SeclectionSort(int *array, int size, bool (*funPtr)(int, int))
            {
            ...
            }
            
            // Here is a comparison function that sorts in ascending order
            bool ascending(int x, int y)
            {
                return x > y; // swap if the first element is greater than the second
            }
             
            // Here is a comparison function that sorts in descending order
            bool descending(int x, int y)
            {
                return x < y; // swap if the second element is greater than the first
            }
            
            int main()
            {
                int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };
             
                // Sort the array in descending order using the descending() function
                selectionSort(array, 9, descending);
             
                // Sort the array in ascending order using the ascending() function
                selectionSort(array, 9, ascending);
             
                return 0;
            }
            ```
            
        - One can even provide default functions to the function pointers.
            
            ```cpp
            void selectionSort(int *array, int size, bool (*comparisonFcn)(int, int) = ascending);
            ```
            
    
    ## Making function pointers prettier
    
    - The syntax for pointer to function is quite verbose. To this end, using type aliases could come in handy.
        
        ```cpp
        using ValidateFunction = bool(*)(int, int);
        
        // Now, instead of doing this
        bool validate(int x, int y, bool (*fcnPtr)(int, int));
        
        // One can do this
        bool validate(int x, int y, ValidateFunction pfcn)
        ```
        
    - One can even use **std::function**
        
        ```cpp
        bool validate(int x, int y, std::function<bool(int, int)> fcn);
        // std::function method that returns a bool and takes two int params
        ```
        
    - Much like the **auto** keyword can be used to infer the type of normal variables, the **auto** keyword can also infer the type of function pointer.
        
        ```cpp
        # include <iostream>
        
        int foo(int x)
        {
        	return x;
        }
        int main()
        {
        	auto fcnPtr{ &foo };
        	std::cout << fcnPtr(5) << '\n';
        	return 0;
        }
        ```
        

# 11.10 - The stack and the heap

Memory that a program uses is divided into segments:

- **Code** / **Text** **segment**, where the compiled program sits in the memory (typically read-only).
- **Bss** **segment** (also called uninitialized data segment), where zero-initialized global and static variables are stored.
- **Data segment** (also called initialized data segment), where initialized global and static variables are stored.
- **Heap**, where dynamically allocated variables are allocated from.
- **Call Stack**, where function parameters, local variables, and other function-related information are stored.

## The heap segment

- Also known as the free store, keeps track of memory used for dynamic memory allocation.
- When the **new** operator is used to allocate memory, memory is allocated in the application's heap segment.
    
    ```cpp
    int *ptr = new int; // ptr is assigned 4 bytes in the heap
    int *array = new int[10]; // array is assigned 40 bytes in the heap
    ```
    
    - Address of the memory is passed back by the operator **new** and is stored in the pointer.
    
    ℹ️. Sequential memory requests may not result in sequential memory address being
           allocated.
    
- Heap has the following advantages and disadvantages:
    - Allocating memory in the heap is comparatively slow.
    - Allocated memory stays allocated until explicitly deallocated or the applications ends.
    - Dynamically allocated memory must be accessed through a pointer. Dereferencing a pointer is slower than directly accessing it from variables.
    - Since **heap** is a big pool of memory, large arrays, structures, or classes can be allocated here.

## The call stack

- Keeps track of all active function (those that have been called but not yet terminated) from the start of the program to the current point of execution.
- Handles allocation of all function parameters and local variables.

### The stack data structure

- A data structure is a programming mechanism for organizing data so that it can be used efficiently.
- Arrays and structs are examples of data structures that provide a mechanism for storing and accessing data in an efficient way.
- **Stack** is one such data structure. It's a container data structure that holds multiple variables.
- While a **stack** could bear resemblance to an **array**, accessing it's elements can't be done in any order as opposed to arrays equipped with **random access**.
- The following operations can be performed on a stack :
    - Look at the top item on the stack (usually done via a function called top(), but sometimes called peek())
    - Take the top item off of the stack (done via a function called pop())
    - Put a new item on top of the stack (done via a function called push())
- A stack is a last-in, first-out (LIFO) structure - the last element pushed in would be the 1st element to be popped off.
- The **mailbox** analogy
    - Consider a bunch of mailboxes stacked one above the other.
    - Each mailbox can hold only one item and all mailboxes start out empty.
    - Each mailbox is nailed to the mailbox below, so the number of mailboxes can't be changed.
    - A marker (say a post-it) is used to keep track of where the bottom-most empty mailbox is - the lowest mailbox at the beginning.
    - When a item is pushed onto the mailbox stack, it is pushed into the mailbox that is marked (the first empty mailbox), and the marker is moved up one mailbox.
    - When an item is popped off the stack, the marker is moved one mailbox down while removing the item from that mailbox.
    - Anything below the marker is considered "on the stack", and everything else not.

## The call stack segment

- It holds the memory for the call stack. When the application starts, the main() function is pushed on the call stack by the operating system. The the program begins executing.
- When a function call is encountered, the function is pushed ont the call stack. When the current function ends, it's popped out of the stack. Thus one can simply refer to the call stack to observe the application flow.

### The call stack in action

- Following are the steps that follow when a function is called
    - The program encounters a function call.
    - A **stack frame** is constructed and pushed onto the stack. A stack frame consists of:
        - The address of the instruction beyond the function call (called the **return address**).
        - All function arguments.
        - Memory for any local variables.
        - Saved copies of any registers modified by the function that need to be restored when the function returns.
    - The CPU jumps to the function start point.
    - The instructions inside the function begins executing.
- When the function terminates, the following happens:
    - Registers are restored from the call stack.
    - The stack frame is popped off the stack. This frees the memory for all local variables and arguments.
    - The return value is handled.
    - The CPU resumes execution at the return address.

```cpp
int foo(int x)
{
	// b
	return x;
}
int main()
{
	// a
	foo(5); // foo is pushed on the call stack
  // c
	return 0;
} 
```

This is what the call stack resembles:

@a

`main()`

@b

`foo() (including parameter x)
main()`

@c

`main()`

## Stack overflow

- The stack is of a limited size and as a consequence can hold only a limited amount of information.
    - 1MB in windows
    - 8MB on some unix machines
- If the program/application tries to put too much information on the stack, this results in a **stack overflow**.
- Stack overflow is generally the result of allocating too many variables on the stack, and/or making too many nested function calls. Below are a few examples:

```cpp
#include <iostream>
 
int main()
{
    int stack[10000000];
    std::cout << "hi";
    return 0;
}
```

The program tries to allocate a huge array on the stack (about 40MB). Since the stack is not large enough to handle this array, it overflow into portions of the memory the program isn't allowed to use.

```cpp
void foo()
{
    foo();
}
int main()
{
    foo();
    return 0;
}
```

The above program results in infinitely calling `foo()`. This too will cause the stack to overflow.

## Advantages and disadvantages of stack

- Allocating memory on the stack is comparatively fast.
- Memory allocated on the stack stays in scope as long as it is in the stack - it's destroyed once it's popped off.
- All memory allocated on the stack is know at compile time. Consequently memory can be accessed directly through a variable.
- Because the stack is relatively small, it is generally not a good idea to do anything that eats up lots of stack space. This includes passing by value or creating local variables of large arrays or other memory-intensive structures.

# 11.11 - `std::vector` capacity and stack behaviour

This chapter expounds on a few other interesting attributes of `std::vector` with respect to stack behaviour.

## Length vs capacity

- Take the following example into considerations:
    
    `int *array{new int[10] { 1, 2, 3, 4, 5 } };`
    
    Here the array even though the array has been assigned a length of 10, only 5 elements are being used.
    
- Say if one wanted to track array length and capacity separately, doing it with `std::array` wouldn't be possible, since it only keeps track of array length. This however isn't the case with `std::vector`.
- `std:vector` contains two separate attributes: length and capacity. Where **length** is how many elements are being used in the array, and **capacity** is how many elements were allocated in the memory.
    
    ```cpp
    #include <vector>
    #include <iostream>
     
    int main()
    {
      std::vector<int> array{};
      array = { 0, 1, 2, 3, 4 }; // okay, array length = 5
      std::cout << "length: " << array.size() << "  capacity: " << array.capacity() << '\n';
     
      array = { 9, 8, 7 }; // okay, array length is now 3!
      std::cout << "length: " << array.size() << "  capacity: " << array.capacity() << '\n';
     
      return 0;
    }
    
    // length: 5  capacity: 5
    // length: 3  capacity: 5
    ```
    
- The range of the subscript operator ([]) and at() function is based on the **vector's** **length** **not** **capacity**. Consider the array in the above example, were one to try and access the array element with index 4, it would fail since 4 is greater than the length of the array.
- The **capacity** of a vector is either equal to or greater than its **length**.

## Stack behaviour with `std::vector`

- Although `std::vector` can be used as a dynamic array, it can also be used as a stack. The following three functions help to facilitate the same:
    - `push_back()` pushes an element on the stack.
    - `back()` returns the value of the top element on the stack.
    - `pop_back()` pops an element off the stack.
    - Example
        
        ```cpp
        #include <iostream>
        #include <vector>
        
        void printStack(const std::vector<int> &stack)
        {
        	for (auto element : stack)
        		std::cout << element << ' ';
        	std::cout << "(cap" << stack.capacity() << " length " << stack.size() << ")\n";
        }
        
        int main()
        {
        	std::vector<int> stack{};
        	printStack(stack);
        	
        	stack.push_back(5); // push_back() pushes an element on the stack
        	printStack(stack);
         
        	stack.push_back(3);
        	printStack(stack);
         
        	stack.push_back(2);
        	printStack(stack);
         
        	std::cout << "top: " << stack.back() << '\n'; // back() returns the last element
         
        	stack.pop_back(); // pop_back() pops an element off the stack
        	printStack(stack);
         
        	stack.pop_back();
        	printStack(stack);
         
        	stack.pop_back();
        	printStack(stack);
         
        	return 0;
        }
        
        // (cap 0 length 0)
        // 5 (cap 1 length 1)
        // 5 3 (cap 2 length 2)
        // 5 3 2 (cap 3 length 3)
        // top: 2
        // 5 3 (cap 3 length 2)
        // 5 (cap 3 length 1)
        // (cap 3 length 0)
        ```
        
- In the above [example](https://www.notion.so/11-Functions-9056d9573ebd4883b3567619ffe3ef07), the vector `stack` gets resized 3 times and since resizing a vector is an expensive operation, it's preferable to allocate a certain amount of capacity up front using the `reserve()` function.
    - Example
        
        ```cpp
        #include <vector>
        #include <iostream>
         
        void printStack(const std::vector<int> &stack)
        {
        	for (auto element : stack)
        		std::cout << element << ' ';
        	std::cout << "(cap " << stack.capacity() << " length " << stack.size() << ")\n";
        }
         
        int main()
        {
        	std::vector<int> stack{};
         
        	stack.reserve(5); // Set the capacity to (at least) 5
         
        	printStack(stack);
         
        	stack.push_back(5);
        	printStack(stack);
         
        	stack.push_back(3);
        	printStack(stack);
         
        	stack.push_back(2);
        	printStack(stack);
         
        	std::cout << "top: " << stack.back() << '\n';
         
        	stack.pop_back();
        	printStack(stack);
         
        	stack.pop_back();
        	printStack(stack);
         
        	stack.pop_back();
        	printStack(stack);
         
        	return 0;
        }
        // (cap 5 length 0)
        // 5 (cap 5 length 1)
        // 5 3 (cap 5 length 2)
        // 5 3 2 (cap 5 length 3)
        // top: 2
        // 5 3 (cap 5 length 2)
        // 5 (cap 5 length 1)
        // (cap 5 length 0)
        ```
        
- When a vector is resized, the vector may allocate more capacity than is needed. This is done to provide some leeway for potential additional elements to come.
    
    ```cpp
    #include <vector>
    #include <iostream>
     
    int main()
    {
    	std::vector<int> v{ 0, 1, 2, 3, 4 };
    	std::cout << "size: " << v.size() << "  cap: " << v.capacity() << '\n';
    	
    	v.push_back(5); // add another element
    	std::cout << "size: " << v.size() << "  cap: " << v.capacity() << '\n';
     
    	return 0;
    }
    // size: 5  cap: 5
    // size: 6  cap: 7
    ```
    

# 11.12 - Recursion

A function that calls itself.

```cpp
#include <iostream>

void countDown(int count)
{
	std::cout << "push" << count << std::endl;
	countDown(count - 1);
}
int main()
{
	countDown(5);
	return 0;
}
```

- The above function would run forever (assuming infinite memory), hence it's necessary to have a **recursive termination**. It's condition that when the recursive function encounters it would put a stop to the recursive calls.
    
    ```cpp
    std::cout << "push " << count << '\n';
    	if (count > 1) // termination condition
    	    countDown(count-1);
    std::cout << "pop " << count << '\n';
    ```
    
- Below is another example of a recursive function

![11%20-%20Funct%20399c7/Untitled.png](11%20-%20Funct%20399c7/Untitled.png)

```cpp
int sumTo(int sumto)
{
	if (sumto <= 0)
		return 0; // base case (termination condition) when user passed in an unexpected parameter (0 or negative)
	else if (sumto == 1)
		return 1; // normal base case (termination condition)
	else
		return sumTo(sumto - 1) + sumto // recursive function call
}
```

![11%20-%20Funct%20399c7/Untitled%201.png](11%20-%20Funct%20399c7/Untitled%201.png)

Since such functions are hard to understand by a simple glance, it's important to comment well these functions.

- Recursive functions typically solve a problem by first finding the solution to a subset of the problem (recursively) and then modifying that sub-solution to get a solution.
- For a large majority of recursive functions, some inputs produced trivial outputs 0, 1, "", " or nul. Inputs for which an algorithm trivially produces an output is called a **base case**. It acts as termination condition for the algorithm.

## Fibonnaci and memoization

- Calculating the nth Fibonnaci

```cpp
int fibonacci(int count)
{
	if count == 0:
		return 0;   // base case
	else if count == 1:
		return 1;
	else:
		return fibonacci(count-1) + fibonacci(count-2);

int main()
{
	int nth {13};
	for (int count=0; count < nth; ++count)
		std::cout << fibonacci(count) << " ";
}
```

![11%20-%20Funct%20399c7/Untitled%202.png](11%20-%20Funct%20399c7/Untitled%202.png)

`0 1 1 2 3 5 8 13 21 34 55 89 144`

- The above example as one must have noticed isn't the most efficient means of calculating the nth fibonnaci using recursion. In fact the above function is called 1205 times. Memoization is a technique used to cache the results of expensive function calls so the result can be returned when the same input occurs again.
    
    ```cpp
    #include <iostrea>
    #include <vector>
    
    int fibonacci(int count)
    {
    	// Static std::vector is used to cache calculated results
    	static std::vector<int> results{ 0, 1 };
    
    	// If fibonnacci for this count has already been calculated return it from the cached reslts
      if (count < static_cast<int>(std::size(results)))
    		return results[count];
    	else
    	{
    		results.push_back(fibonacci(count - 1) + fibonnacci(count - 2));
    		return resutls[count];
    	}
    }
    
    int main()
    {
    	int nth {13};
    	for (int count=0; count < nth; ++count)
    		std::cout << fibonacci(count) << " ";
    }
    ```
    
    This version makes 35 function calls.
    
    - The above problem using dynamic arrays
        
        ```python
        #include <iostream>
        #include <array>
        #include <random>
        #include <algorithm>
        
        using namespace std;
        
        int calcFib(int array[], int count)
        {
            if (count < 0)
                return array[0];
            if (count == 1)
                return array[1];
            else
            {
                array[count] = calcFib(array, count - 1) + calcFib(array, count - 2);
                return array[count];
            }
        }
        
        int main()
        {
            cout << "Till which number you want the fib series? : ";
            int fibSeqLimit{ 0 };
            cin >> fibSeqLimit;
            cin.ignore(32727, '\n');
        
            int *array{ new int[fibSeqLimit]{} };
            array[0] = 0;
            array[1] = 1;
        
            for (int i{ 0 }; i < fibSeqLimit; i++)
                cout << calcFib(array, i) << " ";
            
            delete[] array;
        }
        ```
        

## Recursive vs Iterative

- Sometimes one does ponder why not simply use a loop of sort instead of recursion, simply because, its easier. Try coding the above function using loops, you'll understand.
- Iterative function are almost always more efficient that their recursive counterparts, since every time a function is called some overhead is incurred during pushing and popping functions off the stack. Iterative functions avoid this overhead.
- However, there exists some use-cases wherein **recursion** is a cleaner solution while incurring little overhead, particularly if the algorithm needn't recurse as much.
- Recursion is a good choice when:
    - recursion code is simpler to implement.
    - recursion depth is limited.
    - the iterative version of the algorithm requires managing a stack of data.
    - this isn't a performance-critical section of code.

# 11.15 - Introduction to lambdas (anonymous functions)

- Taking the example below into account:
    - `std::find_if` requires a function pointer to be passed to it.
    - This forces our hand to define a function, that's only going to be used once.
    - Long story short, we need lambda functions!
    - Example
        
        ```cpp
        #include <algorithm>
        #include <array>
        #include <iostream>
        #include <string>
        #include <string_view>
        
        static bool containsWord(std::string_view str)
        {
            return (str.find("nuts") != std::string_view::npos);
        }
        
        int main()
        {
            const std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };
            const auto found{ std::find_if(arr.begin(), arr.end(), containsWord) };
            
            if (found == arr.end())
            {
                std::cout << "No nuts\n";
            }
            else
            {
                std::cout << "Found " << *found << "\n";
            }
            return 0;
        }
        ```
        

## Lambdas to the rescue

- Lambda expression (also called a lambda or closure) allows us to define an anonymous function inside another function. Below is the syntax:
    
    ```cpp
    [ capturClause ] ( parameters ) -> returnType
    {
    	statements;
    }
    // captureClause and parameters can be empty if not needed
    // return type is optional, if omitted `auto` will be assumed
    
    int main()
    {
    	[]() {};
    	return 0;
    }
    ```
    

- The nesting is important as it helps to :
    - avoid namespace naming pollution
    - define the function as close to where it is used as possible.

- Re-coding the above function using **lambda:**
    
    ```cpp
    // Replace `const auto found` with 
    const auto found { std::find_if(arr.begin(), 
                                    arr.end(),
                                    [](std::string_view str)
                                          {
                                              return (str.find("nuts") != std::string_view::npos);
                                          })};
    ```
    
    - Lambda has no capture clause.
    - The trailing return type has been omitted, since `operator!=` returns bool, lambda returns bool too.

## Type of a lambda

- In the above example, lambda was defined where it was needed. This use of lambda is sometimes called **function literal**.
- **Function literal** can make lambda's harder to read. Named lambda along with a good function name can make things easier on the eyes.
    
    ```cpp
    // Bad: We have to read the lambda to understand what's happening
    return std::all_of(array.begin(), array.end(), [](int i){ return ((i % 2) == 0); })
    
    // Good: Lambda stored in a named variable and then passed to the function
    auto isEven{
    	[](int i)
    	{
    		return ((i % 2) == 0);
    	};
    }
    ```
    
- What type are lambdas assigned?
    - They don't have a type that one can use explicitly use. When lambda's are written, the compiler generates a unique type just for lambdas (that remain in-exposed to us)
    - Lambdas aren't functions, they're a special kind of object called **functor**. Functors are objects that contain an overloaded `operator()` that make them callable like a function.
- Ways of declaring lambdas
    
    ```cpp
    int main()
    {
    	// A regular function pointer. Only works with an empty capture clause
    	double (*addNumbers1)(double double){
    		[](double a, double b){
    			return (a + b)
    	}
    };
    
    // Using std::function. The lambda could have a non-empyty capture clause
    std::function addNumbers2{ // pre C++17, std::function<doube(double, double)> is used instead
    	[](double a, double b){
    		return (a + b);
    	}
    }
    
    // Using auto. Stores the lambda with its real type.
    auto addNumbers3{
    	[](double a, double b){
    		return (a + b);
    	}
    }
    ```
    
    - `auto` is the only way of using lambda's actual type. Additionally, `auto` has the benefit of having no overhead compared to `std::function`.
    - Unfortunately, we can't always use `auto`. In cases where the actual lambda is unknown, we can't use `auto`. In such cases, `std::function` ought to be used.
        - Example
            
            ```cpp
            #include <functional>
            #include <iostream>
            
            // We don't know what fn will be. std::function works with regular functions and Lambdas
            void repeat(int repetitions, const std::function<void(int)>& fn)
            {
            	for( int i{ 0 }; i < repetitions; i++)
            	{
            		fn(i)
            	}
            }
            int main()
            {
            	repeat(3, [](int i) {
            		std::cout << i << '\n';
            	});
            	return 0;
            ```
            
        
        ℹ️ Use `auto` when initializing variables with lambdas, and `std::function` if one can't initialize variable with lambda.
        

## Generic Lambdas

- For the most part, lambda parameters work by the same rules as regular function parameters.
- When lambda has one or more `auto` parameter, the compiler will infer what parameter types are needed from the calls to the lambda.
- Since lambdas with one or more `auto` parameter can potentially work with a wide variety of types, they're called **generic lambdas**. When used in the context of a lambda, auto is just a shorthand for a template parameter.
- Example
    
    ```cpp
    #include <algorithm>
    #include <array>
    #include <iostream>
    #include <string_view>
    
    int main()
    {
        const std::array months{ // pre-C++17 use std::array<const char*, 12>
            "January",
            "February",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December"
            };
    
        // Search for two consecutive months that start with the same letter
        const auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
                                                  [](const auto&a, auto&b){
                                                      return (a[0] == b[0]);
                                                  })};
        if (sameLetter != months.end())
        {
            // std::next returns the next iterator after sameLetter
            std::cout << *sameLetter << " and " << *std::next(sameLetter)
            << " start with the same letter\n";
        }
        return 0;
    }
    ```
    
    - In the example above, `auto` parameters to capture strings by `const` reference.
    - All string types - `std::string`, C-style etc - allow access to individual characters via `operator []`
    - Lambda here accepts any string types, therefore, were lambda types to be changed later, we wouldn't need to re-write it.
- Counter Example
    
    ```jsx
    #include <algorithm>
    #include <array>
    #include <iostream>
    #include <string_view>
     
    int main()
    {
      constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
      };
     
      // Count how many months consist of 5 letters
      const auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
                                           [](std::string_view str) {
                                             return (str.length() == 5);
                                           }) };
     
      std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";
     
      return 0;
    }
    ```
    
    - This being said `auto` isn't always the best choice.
    - In this example, `auto` would infer a type of `const char*`. C-style strings aren't easy to work with (apart from using `operator []`).
    - Here, one would prefer to explicitly define the parameter as a `std::string_view` allowing us to work with underlying data much easily.

## Generic lambdas and static variables

- A unique lambda will be generated for each different type `auto` resolves to.
- Example
    
    ```cpp
    #include <algorithm>
    #include <array>
    #include <iostream>
    #include <string_view>
     
    int main()
    {
    	auto print{
    		[](auto value){
    			static int callCount{ 0 };
    			std::cout << callCount++ << ": " << value << "\n";
    		}
    	};
    	print("hello"); // 0: hello
      print("world"); // 1: world
     
      print(1); // 0: 1
      print(2); // 1: 2
     
      print("ding dong"); // 2: ding dong
    	return 0;
    }
    ```
    
- In the example, lambda is defined and called with two different parameters (a string literal parameter, and an integer parameter). This generates two different versions of lambda.
- Most of the time this is inconsequential, however it's important to note that, if the generic lambda uses static duration variables, those variables are not shared between the generated lambdas.

## Return type deduction and trailing return types

- Were return type deduction used, a lambda's return type is deduced from the statements inside lambda.
- If return type inference is used, all return statements in the lambda must return the same type.
- Example 1
    
    ```cpp
    #include <iostream>
    
    int main()
    {
    	auto divide{ [](int x, int y, bool bInteger) { // no specified return type
    		if (bInterger)
    			return x / y;
    		else
    			return static_cast<double>(x) / y; // Error: return type doesn't match previous return type
    	}};
    	std::cout << divide(3, 2, true) << '\n';
    	std::cout << divide(3, 2, false) << '\n';
    	return 0;
    }
    ```
    
    - Here a compiler error is produced, since the return type of the 1st statement (int) doesn't match with the return type of the 2nd statement (double).
    - Given the error, we are left with two choices:
        - Do explicit casts to make all the return types match, or
        - explicitly specify a return type for the lambda, and let the compiler do implicit conversions.
- Example 2 (better choice)
    
    ```cpp
    #include <iostream>
     
    int main()
    {
      // note: explicitly specifying this returns a double
      auto divide{ [](int x, int y, bool bInteger) -> double {
        if (bInteger)
          return x / y; // will do an implicit conversion to double
        else
          return static_cast<double>(x) / y;
      } };
     
      std::cout << divide(3, 2, true) << '\n';
      std::cout << divide(3, 2, false) << '\n';
     
      return 0;
    }
    ```
    
    - This way, were one to decide to change the return type, one only need to change the lambda's return type, leaving its body untouched.

ℹ️ For common operations (e.g. addition, negation, or comparison) one needn't write one's own lambda, since the standard library comes with many basic callable objects that can be used instead.

- Example
    
    ```cpp
    #include <algorithm>
    #include <array>
    #include <iostream>
    #include <functional> // for std::greater
    
    bool greater(int a, int b)
    {
      // Order @a before @b if @a is greater than @b.
      return (a > b);
    }
    int main()
    {
      std::array arr{ 13, 90, 99, 5, 40, 80 };
      // Pass greater to std::sort
      std::sort(arr.begin(), arr.end(), greater);
      for (int i : arr)
      {
        std::cout << i << ' ';
      }
      std::cout << '\n';
      return 0;
    
    // STD LIBRARY FUNCTION OBJECTS
    int main()
    {
      std::array arr{ 13, 90, 99, 5, 40, 80 };
      // Pass std::greater to std::sort
      std::sort(arr.begin(), arr.end(), std::greater{}); // note: need curly braces to instantiate object
      for (int i : arr)
      {
        std::cout << i << ' ';
      }
      std::cout << '\n';
     
      return 0;
    }
    ```
    

ℹ️ Lambdas are great, but they don’t replace regular functions for all cases. Prefer regular functions for non-trivial and reusable cases.

# 11.16 - Lambda captures

- Say we modify [this](https://www.notion.so/11-Functions-9056d9573ebd4883b3567619ffe3ef07) example to the following
    
    ```cpp
    .
    std::string search{};
    std::cin >> search
    auto found{ std::find_if(arr.begin(), arr.end(), [](std::string_view str) {
        // Search for @search rather than "nut".
        return (str.find(search) != std::string_view::npos); // Error: search not accessible in this scope
      }) };
    .
    .
    ```
    
    - The code will not compile
    - Unlike nested blocks, where any identifier defined in an outer block is accessible in the scope of the nested block, lambdas only access specific kind of identifiers:
        - global identifiers
        - entities know at compile time
        - entities with static storage duration
        
        `search` fulfills none of the above requirements, so lambda can't see it. Hence the need for capture clause.
        

## The capture clause

- Used to (indirectly) give a lambda access to variables available in the surrounding scope that it wouldn't normally have access to.
- One simply ought to list the entities one would want to access from within the lambda as part of the capture clause.
- Therefore we can re-write the [above](https://www.notion.so/11-Functions-9056d9573ebd4883b3567619ffe3ef07) example as:
    
    ```cpp
    .
    std::string search{};
      std::cin >> search;
     
      // Capture @search                                vvvvvv
      auto found{ std::find_if(arr.begin(), arr.end(), [search](std::string_view str) {
        return (str.find(search) != std::string_view::npos);
      }) };
    .
    .
    ```
    

### Its working

- When lambda definition is executed, for each variable the lambda captures, a clone of that variable is made (with identical name) inside the lambda.
- These cloned variables are initialized from the outer scope variables to the same name at this point.
- While the cloned variables have the same name, they don't necessarily have the same type as original variables.

## The different captures

### Constant captures

- By default, variables are captured by `const value`. So when lambdas are created, it captures a constant copy of the outer scope variable.
    - Example
        
        ```cpp
        #include <iostream>
         
        int main()
        {
          int ammo{ 10 };
         
          auto shoot{
            // We don't need mutable anymore
            [&ammo]() { // &ammo means ammo is captured by reference
              // Changes to ammo will affect main's ammo
              --ammo;
         
              std::cout << "Pew! " << ammo << " shot(s) left.\n";
            }
          };
         
          shoot();
          std::cout << ammo << " shot(s) left\n";
         
          return 0;
        }
        ```
        

The **mutable** keyword in this context removes the `const` qualification from all variables captured by value.

```cpp
[ammo]() mutable {
    // We're allowed to modify ammo now
    --ammo;

    std::cout << "Pew! " << ammo << " shot(s) left.\n";}};
}};
```

⚠️ The original value of `ammo` is preserved as changes are only effectuated on the clone.

### Capture by reference and multiple values

- Just as function can change the value of arguments passed by reference, lambda captures by reference allows modification of the passed argument.
    
    ```cpp
    auto shoot{
        // We don't need mutable anymore
        [&ammo]() { // &ammo means ammo is captured by reference
          // Changes to ammo will affect main's ammo
          --ammo;
     
          std::cout << "Pew! " << ammo << " shot(s) left.\n";
        }
      };
    // Pew! 9 shot(s) left.
    // 9 shot(s) left
    ```
    
- Multiple variables can be captured by separating them with a comma.
    
    ```cpp
    int health{ 33 };
    int armour{ 100 };
    std::vector<CEnemy> enemies {};
    // Capture health and mrmour by value and enemies by reference
    [health, armour, &enemies](){};
    ```
    

### Default captures (or capture-default)

- Having to explicitly list the variables that one would want to capture is burdensome, especially if one were to modify a lambda, one could very well forget to add or remove captured variables.
- A **default capture** captures all variables mentioned in the lambda. Variables not mentioned in the lambda are not captured if a default capture is used.
    - To capture all used variables by value, use a capture value of =.
    - To capture all used variables by reference, use a capture value of &.
    - Example
        
        ```cpp
        #include <array>
        #include <iostream>
         
        int main()
        {
          std::array areas{ 100, 25, 121, 40, 56 };
         
          int width{};
          int height{};
         
          std::cout << "Enter width and height: ";
          std::cin >> width >> height;
         
          auto found{ std::find_if(areas.begin(), areas.end(),
                                   [=](int knownArea) { // will default capture width and height by value
                                     return (width * height == knownArea); // because they're mentioned here
                                   }) };
         
          if (found == areas.end())
          {
            std::cout << "I don't know this area :(\n";
          }
          else
          {
            std::cout << "Area found :)\n";
          }
         
          return 0;
        }
        ```
        
- Default captures can be mixed with normal captures. Some variables can be captured by value and others by reference, but each variable can only be captured once.
    - Examples
        
        ```cpp
        int health{ 33 };
        int armor{ 100 };
        std::vector<CEnemy> enemies{};
         
        // Capture health and armor by value, and enemies by reference.
        [health, armor, &enemies](){};
         
        // Capture enemies by reference and everything else by value.
        [=, &enemies](){};
         
        // Capture armor by value and everything else by reference.
        [&, armor](){};
         
        // Illegal, we already said we want to capture everything by reference.
        [&, &armor](){};
         
        // Illegal, we already said we want to capture everything by value.
        [=, armor](){};
         
        // Illegal, armor appears twice.
        [armor, &health, &armor](){};
         
        // Illegal, the default capture has to be the first element in the capture group.
        [armor, &](){};
        ```
        

## Lambda-capture variables

### Defining new variables

- Sometimes one would like to capture a variable with a slight modification or declare a new variable that's only visible in the scope of the lambda. This can be done by defining a variable in a lambda-capture without mentioning its type.
    
    ```cpp
    // We store areas, but the user entered width and height.
    // We need to calculate the area before we can search for it.
    auto found{ std::find_if(areas.begin(), areas.end(),
    												// Declare a new variable that's visible only to the lambda.
                            // The type of userArea is automatically deduced to int.
    												[userArea{ width * height }](int knownArea) {
    													return (userArea == KnownArea);
    												}) };
    ```
    
- `userArea` will only be calculated once when the lambda is defined.
- The calculated area is stored in the lambda object and is the same for every call.
- If the lambda is mutable and modifies a variable that was defined in the capture, the original value will be overridden.

ℹ️ Only initialize variables in the capture if their value is short and their type is obvious. Otherwise it’s best to define the variable outside of the lambda and capture it.

### Dangling capture variables

- Variables are captured at the point of lambda definition. If a variable captured by reference dies before the lambda, the lambda will be left holding a dangling reference.
    - Example
        
        ```cpp
        #include <iostream>
        #include <string>
         
        // returns a lambda
        auto makeWalrus(const std::string& name)
        {
          // Capture name by reference and return the lambda.
          return [&]() {
            std::cout << "I am a walrus, my name is " << name << '\n'; // Undefined behavior
          };
        }
         
        int main()
        {
          // Create a new walrus whose name is Roofus.
          // sayName is the lambda returned by makeWalrus.
          auto sayName{ makeWalrus("Roofus") };
         
          // Call the lambda function that makeWalrus returned.
          sayName();
         
          return 0;
        }
        ```
        
        - Call to `makeWalrus` creates a temporary `std::string` from the literal "Roofus".
        - The lambda in `makeWalrus` captures the temporary string by reference.
        - The temporary string dies when `makeWalrus` returns, but lambda still references it.
        - `sayName` is then called, the dangling reference is accessed causing undefined behaviour.
        
        ℹ️ Were one to require for `name` to be captured, one needs to capture it by value.
        

❗Be extra careful when you capture variables by reference, especially with a default reference capture. The captured variables must outlive the lambda.

## Unintended copies of multiple lambdas

- Since lambdas are objects that can be copied, it can cause issues in some cases, as shown by the example below
    - Example
        
        ```cpp
        #include <iostream>
        
        int main()
        {
        	int i{ 0 };
        	// Create lambda
        	auto count{
        		[i]() mutable {
        			std::cout << ++i << "\n";	
        		}
        	};
        	count(); // invoke count ones
        	auto otherCount{ count }; // create a copy of count
        
        	// invoke both count and copy
        	count();
        	otherCount();
        	return 0;
        }
        // 1
        // 2
        // 2
        ```
        
        - Rather than printing 1, 2, 3; 2 is printed twice.
        - When we created otherCount as a copy of count, we created a copy of count in its current state. count‘s i was 1, so otherCount‘s i is 1 as well. Since otherCount is a copy of count, they each have their own i
    - Less obvious example
        
        ```cpp
        #include <iostream>
        #include <functional>
         
        void invoke(const std::function<void(void)>& fn)
        {
            fn();
        }
         
        int main()
        {
            int i{ 0 };
         
            // Increments and prints its local copy of @i.
            auto count{ [i]() mutable {
              std::cout << ++i << '\n';
            } };
         
            invoke(count);
            invoke(count);
            invoke(count);
         
            return 0;
        }
        // 1
        // 1
        // 1
        ```
        
        - When std::function is created with a lambda, the std::function internally makes a copy of the lambda object. Thus, our call to fn() is actually being executed on the copy of our lambda, not the actual lambda.
- There are two ways of avoiding the possibility of inadvertent lambda copies for mutable lambdas:
    - Use a non-capturing lambda: one could remove the capture and track our state using static local variables. ⚠️ This however could  be quite cumbersome.
    - Prevent copies of lambda: as a part of the <functional> header, C++ provides `std::reference_wrapper` that allows one to pass a normal type as if it were a reference. `std::reference_wrapper` can be created using the `std::ref()` function. By wrapping our lambda in a `std::reference_wrapper`, whenever anybody tries to make a copy of our lambda, they’ll make a copy of the reference instead, which will copy the reference rather than the actual object.
    - Less obvious update example
        
        ```cpp
        #include <iostream>
        #include <functional>
         
        void invoke(const std::function<void(void)> &fn)
        {
            fn();
        }
         
        int main()
        {
            int i{ 0 };
         
            // Increments and prints its local copy of @i.
            auto count{ [i]() mutable {
              std::cout << ++i << '\n';
            } };
         
            // std::ref(count) ensures count is treated like a reference
            // thus, anything that tries to copy count will actually copy the reference
            // ensuring that only one count exists
            invoke(std::ref(count));
            invoke(std::ref(count));
            invoke(std::ref(count));
         
            return 0;
        }
        ```
        

# Comprehensive Quiz

- Function arguments can be passed by value, reference or address.
    - Pass by value should be used for fundamental data types.
    - Pass by reference should be used for structs, classes or when one needs to modify an argument.
    - Pass by address is used for passing pointers or built-in arrays.
    
    ℹ️  Make pass by reference and address parameters const whenever possible.
    
- Values can be returned by value, reference or address.
    - Return by value suffices for most use cases.
    - Return by address can be useful when working with dynamically allocated data, structs or classes.
    
    ℹ️. If one chooses to return by address or reference make sure that the returned object doesn’t go out of scope.
    
- Inline functions allows one to request the compiler to replace ones function call with the function code.
- Function pointers allows us to pass a function to another function - a useful technique were the user looking to modify the behaviour of a funciton.
- Dynamic memory is allocated on the heap.
- The call stack keeps track of all active functions that have been called from the start of the program to the current point of execution.
    - Local variables are allocated on the stack
    - The stack has a limited size.
    - `std::vector` can be used to implement stack like behaviour.
- A recursive function is one that calls itself repeatedly until the termination condition is encountered.
- Command line arguments allow users or other programs to pass data to the program at startup. Command line arguments are C-style strings and ought to be converted to numbers if numeric values are desired.
- Ellipsis allows one to pass a variable number of arguments to a function.
    - However, ellipsis arguments suspend type checking and don’t know how many arguments were passed. The program is tasked with keeping track of this.
- Lambda functions can be nested within other function. They need not be named and are very useful in combination with the algorithm’s library.