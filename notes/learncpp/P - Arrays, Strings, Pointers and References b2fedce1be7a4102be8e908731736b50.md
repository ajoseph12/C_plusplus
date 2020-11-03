# P - Arrays, Strings, Pointers and References

# P.6.1 - Arrays (Part 1)

An **array** is an aggregate data type that lets us access many variables of the same type through a single identifier. Say one would want to record test scores for 30 students in a class, there are two ways of going about this: 

```cpp
// allocate 30 integer variables (each with a different name)
int testScoreStudent1;
int testScoreStudent2;
.
.
int testScoreStudent30;

// allocate 30 integer variales in a fixed array
int testScore[30]
```

- In an array variable declaration, one should use square brackets ([]) to tell the compiler that:
    - this is an array variable
    - is an array where length is know at compile time (**array length**)
- Each variable in an array is called an **element**. They don't have a unique name. Instead, to access individual elements of an array, on should use the array name, along with this **subscript operator** ([]) and a parameter called a **subscript** (or **index**) that tells the compiler the element one wants. This process is called **subscripting** or **indexing** the array..
- For an array of length N, the array elements are numbered 0 through N.

## Array data types and subscripts

- Arrays can be made of any datatypes

    ```cpp
    int main()
    {
    	double array[3];
    	array[0] = 2.0;
    	array[1] = 3.0;
    	array[2] = 4.3;
    	std::cout << " The sum is " << array[0] + array[1] + array[2] << "\n";
    	
    	return 0;
    }		
    ```

- Arrays can also be made from structs.

    ```cpp
    struct Rectangle
    {
    	int length;
    	int width;
    }
    Rectangle rect[5]; // declare an array of 5 rectangle

    // Accessing the struct member of an array element
    rect[0].length = 20
    ```

- Array **subscripts** in C++ must always be an integral type, which includes, char, short, int, long, and bool..
- An array subscript can be a literal value, a variable (constant or non-constant), or an expression that evaluates to an integral type.

    ```cpp
    int array[5]; // declare an array of length 5

    array[1] = 7; // using a literal index	

    enum Animals
    {
    	ANIMAL_CAT = 2;
    };
    array[ANIMAL_CAT] = 4;

    short index = 3;
    array[index] = 7;

    array[1+2] = 7
    ```

## Fixed array declarations and dynamic arrays

- When declaring a fixed array, the length of the array must be a compile-time constant. This is because the length of the array must be known at compile time. Below are a few ways to declare a fixed array.

    ```cpp
    // Using a literal contant
    int array[5];

    // Using a macro symbol constant
    #define ARRAY_LENGTH 5
    int array[ARRAY_LENGTH]; // Syntactically okay, but don't do this

    // Using a symbolic constant
    const int arrayLength = 5;
    int array[arrayLength];

    // Using an enumerator
    enum ArrayElements
    {
    	MAX_ARRAY_LENGTH = 5;
    }
    int array[MAX_ARRAY_LENGTH];
    ```

- Non constant variables and runtime variables can't be used.

    ```cpp
    // using a non-const variable
    int length;
    std::cin >> length;
    int array[length]; // Not ok -- length is not a compile-time constant!
     
    // using a runtime const variable
    int temp = 5;
    const int length = temp; // the value of length isn't known until runtime, so this is a runtime constant, not a compile-time constant!
    int array[length]; // Not ok
    ```

- Since fixed arrays have memory allocated at compile time, it brings about the following two limitations:
    - Fixed arrays cannot have length based on either user input or values calculated during run time.
    - Fixed arrays have fixed length that cannot be changed.

    Fortunately, C++ supports a second kind of array known as a **dynamic array**. The length of a dynamic array can be set at runtime, and their length can be changed. However, dynamic arrays are a little more complicated to instantiate

# P.6.2 - Arrays (Part 2)

## Initializing fixed arrays and omitted length

- An array can be initialized via the use of an initializer list.

    ```cpp
    int prime[5] = {2, 3, 5, 7, 11};
    int array[5] = {};    // Initialize all elements to 0
    double array[5] = {}; // Initialize all elements to 0.0
    // As of C++11, the uniform initialization syntax should be used instead:
    int prime[5] = {2, 3, 5, 7, 11};
    ```

    - An **error** is generated if there are more initializers in the list than the array can hold.
    - There however isn't any issues if there are less initializers than the array can hold. The remaining elements are initialized to 0 (called **zero initialization**).
- If one were to declare a fixed length array with an initializer list, the array length needn't be explicitly mentioned, as the compiler can figure this out.

    ```cpp
    int array[] = { 0, 1, 2, 3, 4 }; // let initializer list set length of the array
    ```

## Arrays and enums / enum classes

- One of the issues with arrays is that integer indices don't provide any information to the programmer about the meaning of the index.

    ```cpp
    const int numOfStudents(5);
    int testScores[numOfStudents];
    testScores[2] = 76; // It's not clear who's represented by testScores[2]
    ```

- **Enums** can help solve this.

    ```cpp
    enum StudentNames
    {
        KENNY, // 0
        KYLE, // 1
        STAN, // 2
        BUTTERS, // 3
        CARTMAN, // 4
        MAX_STUDENTS // 5
    };
    int main()
    {
        int testScores[MAX_STUDENTS]; // allocate 5 integers
        testScores[STAN] = 76;
        return 0;
    }
    ```

- **Enum classes** don't have an implicit conversion to integer, so the following code will result in a compiler error.

    ```cpp
    enum class StudentNames
    {
        KENNY, // 0
        KYLE, // 1
        STAN, // 2
        BUTTERS, // 3
        CARTMAN, // 4
        WENDY, // 5
        MAX_STUDENTS // 6
    };
     
    int main()
    {
        int testScores[StudentNames::MAX_STUDENTS]; // allocate 6 integers
        testScores[StudentNames::STAN] = 76;
     
        return 0;
    }	

    // A conversion to int must be effectuated to dodge this error
    int main()
    {
        int testScores[static_cast<int>(StudentNames::MAX_STUDENTS)]; // allocate 6 integers
        testScores[static_cast<int>(StudentNames::STAN)] = 76;
     
        return 0;
    }
    ```

- Since the solution above is somewhat cumbersome, it's best to define an enum inside a namespace.

    ```cpp
    namespace StudentNames
    {
        enum StudentNames
        {
            KENNY, // 0
            KYLE, // 1
            STAN, // 2
            BUTTERS, // 3
            CARTMAN, // 4
            WENDY, // 5
            MAX_STUDENTS // 6
        };
    }
     
    int main()
    {
        int testScores[StudentNames::MAX_STUDENTS]; // allocate 6 integers
        testScores[StudentNames::STAN] = 76;
     
        return 0;
    ```

## Passing arrays to functions

- When a normal variable is passed by values, C++ copies value of the argument to the function parameter. And since the parameter is a copy, changing the value of the parameter doesn't result in a change in the value of the original argument.
- Since copying large arrays can be expensive, C++ doesn't copy an array passed to a function. Instead, the actual array is passed.

    ```cpp
    #include <iostream>
     
    void passValue(int value) // value is a copy of the argument
    {
        value = 99; // so changing it here won't change the value of the argument
    }
     
    void passArray(int prime[5]) // prime is the actual array
    {
        prime[0] = 11; // so changing it here will change the original argument!
        prime[1] = 7;
        prime[2] = 5;
        prime[3] = 3;
        prime[4] = 2;
    }
     
    int main()
    {
        int value = 1;
        std::cout << "before passValue: " << value << "\n";
        passValue(value);
        std::cout << "after passValue: " << value << "\n";
     
        int prime[5] = { 2, 3, 5, 7, 11 };
        std::cout << "before passArray: " << prime[0] << " " << prime[1] << " " << prime[2] << " " << prime[3] << " " << prime[4] << "\n";
        passArray(prime);
        std::cout << "after passArray: " << prime[0] << " " << prime[1] << " " << prime[2] << " " << prime[3] << " " << prime[4] << "\n";
     
        return 0;
    }
    // before passValue: 1
    // after passValue: 1
    // before passArray: 2 3 5 7 11
    // after passArray: 11 7 5 3 2
    ```

- To ensure that the value of the array is not changed, simply pass it as a constant

    ```cpp
    oid passArray(const int prime[5])
    {
        // so each of these lines will cause a compile error!
        prime[0] = 11;
        prime[1] = 7;
        prime[2] = 5;
        prime[3] = 3;
        prime[4] = 2;
    }
    ```

## Size of arrays and determining length of fixed array

- The **sizeof** operator used on arrays will return the total size of the array. However, given the way C++ passes arrays to function the operator **malfunctions** on arrays passed to functions.

    ```cpp
    void printSize(int array[])
    {
        std::cout << sizeof(array) << '\n'; // prints the size of a pointer, not the size of the array!
    }
     
    int main()
    {
        int array[] = { 1, 1, 2, 3, 5, 8, 13, 21 };
        std::cout << sizeof(array) << '\n'; // will print the size of the array
        printSize(array);
     
        return 0;
    }
    // 32
    // 4
    ```

- Length of array (prior to C++17)

    ```cpp
    #include <iostream> // for std::cout
    int main()
    {
        int array[] = { 1, 1, 2, 3, 5, 8, 13, 21 };
        std::cout << "The array has: " << sizeof(array) / sizeof(array[0]) << " elements\n"; 
        return 0;
    }
    // The array has 8 elements
    ```

- Length of array (in C++17/C++20)

    ```cpp
    #include <iostream> // for std::cout
    int main()
    {
        int array[] = { 1, 1, 2, 3, 5, 8, 13, 21 };
        std::cout << "The array has: " << std::size(array) << " elements\n"; 
        return 0;
    }
    // The array has 8 elements
    ```

- When space isn’t a constraint, doubles should be preferred over floats.

# P.6.3 - Arrays  and loops

- Doing this quite cumbersome

    ```cpp
    int numStudents{ 5 };
    int score0{ 84 };
    int score1{ 92 };
    int score2{ 76 };
    int score3{ 81 };
    int score4{ 56 };
     
    int totalScore{ score0 + score1 + score2 + score3 + score4 };
    auto averageScore{ static_cast<double>(totalScore) / numStudents };
    ```

- So we use arrays and loops

    ```cpp
    #include <iostream> 
    int main()
    {
        int scores[]{ 84, 92, 76, 81, 56 };
        int numStudents{ sizeof(scores)/sizeof(scores[0])};
        int totalScore { 0 };
    		int maxScore { 0 };
        
        for (int i {0}; i < numStudents; ++i)
        {
            if ( scores[i] > maxScore )
    						maxScore = scores[i];
    				totalScore+=scores[i];
        }

        auto averageScore{ static_cast<double>(totalScore) / numStudents };
        std::cout << averageScore <<std::endl;
    		std::cout << "The best score was " << maxScore << '\n';
        return 0;

    }
    ```

- Loops are used in combination with arrays to do the following:
    - Calculate a value
    - Search for a value
    - Reorganize the array

# P.6.4 - Sorting an array using selection sort

- Sorting (based on time, size, etc) can make search easier
- Sorting a list isn't worth performing if only a one-time search is to be effectuated
- Sorting is generally performed by comparing pairs of elements and swapping them if they meet some pre-defined criteria.

    ```cpp
    int x{ 2 };
    int y{ 4 };
    std::cout << "Before swap: x = " << x << ", y = " << y << '\n';
    std::swap(x, y); // swap the values of x and y
    std::cout << "After swap:  x = " << x << ", y = " << y << '\n';
    ```

## Selection sort

One of the easier and slower kinds of sorting.

Selection sort performs the following steps to sort any array from smallest to largest:

- Starting at index 0, search the entire array to find the the smallest value.
- Swap the smallest value found in the array with the value at index 0.
- Repeat steps 1 and 2

Because sorting arrays is so common, C++ standard library includes a sorting function named std::sort.

## Bubble sort

Bubble sort works by comparing adjacent pairs of elements, and swapping them if the criteria is met, so that elements “bubble” to the end of the array

Unoptimized bubble sort performs the following steps:

- Compare array element 0 with array element 1. and swap postitions if condition met.
- Now do the same for elements 1 and 2, and every subsequent pair of elements until the end of the array. At this point, the last element in the array will be sorted.
- Repeat the first two steps until the array is sorted.

To optimize the sort, one can:

- Avoid iterating until the end of the array at every loop, since the last elements in theory are supposed to be sorted.
- During an iteration, if no elements are swapped, break the loop and terminate the sort. Since, no swap would mean that elements are in desired order.

# 6.P.5 - Multidimensional Arrays

Elements of an array can be of any datatype, including an array. An array of array is called **multidimensional array**. 

```cpp
int array[3][5]; // a 3 element array of 5 elements 
```

In a 2-D array the left subscript indicates the number of rows while the right subscript indicates the number of columns, Such arrays are called **row-major order** arrays. The above array can be laid our like this: 

```cpp
[0][0]  [0][1]  [0][2]  [0][3]  [0][4] // row 0
[1][0]  [1][1]  [1][2]  [1][3]  [1][4] // row 1
[2][0]  [2][1]  [2][2]  [2][3]  [2][4] // row 2
```

## Initializing and accessing 2-D array elements

- To initialize a 2-D array, it's easiest to use nested braces, with each set of numbers representing a row:

    ```cpp
    int array[3][5]
    {
      { 1, 2, 3, 4, 5 }, // row 0
      { 6, 7, 8, 9, 10 }, // row 1
      { 11, 12, 13, 14, 15 } // row 2
    };
    ```

- While some compilers allow 2-D array initialization without inner braces, it's recommend to use inner braces for readability and because of the way C++ replaces missing initializers with 0.

    ```cpp
    int array[3][5]
    {
      { 1, 2 }, // row 0 = 1, 2, 0, 0, 0
      { 6, 7, 8 }, // row 1 = 6, 7, 8, 0, 0
      { 11, 12, 13, 14 } // row 2 = 11, 12, 13, 14, 0
    };	
    ```

- 2-D arrays with initializer list can only omit the row specification.

    ```cpp
    int array[][5]
    {
      { 1, 2, 3, 4, 5 },
      { 6, 7, 8, 9, 10 },
      { 11, 12, 13, 14, 15 }
    };

    // NOT ALLOWED!!!
    int array[][] 
    {
      { 1, 2, 3, 4 },
      { 5, 6, 7, 8 }
    };
    ```

- Like normal array multi-dimensional arrays can be initialized to 0 : **int array[3][4] {};**
- Accessing all elements in a 2-D array requires 2 loops: one for row and another for column.

    ```cpp
    for (int row{ 0 }; row < numRows; ++row) // step through the rows in the array
        for (int col{ 0 }; col < numCols; ++col) // step through each element in the row
            std::cout << array[row][col];
    ```

# P.6.6 - C-style strings

In C++ std::string is often used to work with strings, and it's a part of the standard library. However modern C++ supports **std::string** and **C-style** strings (natively inherited from the C language). And as it may turn out, std::string is implemented using C-style

A **C-style string** is a simple array of characters that uses a null terminator. A **null terminator** is a special character ('\0', ascii code 0) used to indicated the end of the string. Put it differently, C-string is a null-terminated string. 

- To define a C-style string, one needs to simply declare a char array and initialize it with string literal : **char myString[]{"string"};**

    Though the above string's length is 6, since a null terminator is added at the end, it actual length becomes 7.

    ```cpp
    # include <iostream>

    int main()
    {
    	char myString[]{"string"};
    	const int length { sizeof(myString) / sizeof(myString[0]) };
    	std::cout << myString <<" has " << length << " characters. \n";
    	
    	for (int index { 0 }; index < length; ++index)
    		std::cout << static_cast<int>(myString[index]) << " ";

    	std::cout << std::endl;
    	return 0;
    }

    // string has 7 characters.
    // 115 116 114 105 110 103 0
    ```

- While declaring strings in this manner, it's a good idea to use **[]** letting the compiler calculate the length of the array. So if the string is changed later, the string length wouldn't have to be manually adjusted.
- C-strings follow all the same rules as arrays:
    - A string can be initialized on creation but values can't be assigned to it.

        ```cpp
        char myString[]{ "string" }; // ok
        myString = "rope"; // not ok!
        ```

    - Since C-style strings are arrays, **[]** can be used to change individual characters in the string.

        ```cpp
        #include <iostream>
         
        int main()
        {
            char myString[]{ "string" };
            myString[1] = 'p';
            std::cout << myString << '\n';
         
            return 0;
        }
        // spring
        ```

    - When printing C-style string **std::cout** prints characters until it encounters the null terminator. If this is accidentally overwritten, std::cout  will print all characters in the string, followed by printing everything in adjacent memory slots until null is encountered.

## C-style strings and std::cin

Often is the case when we don't know the length of the string in advance (eg: getting a user name). In such scenarios, one can declare a large enough array. 

```cpp
#include <iostream>
 
int main()
{
    char name[255]; // declare array large enough to hold 255 characters
    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "You entered: " << name << '\n';
 
    return 0;
}
```

While the above program works just fine, nothing is stoping the user from either unintentionally, or maliciously entering more than 255 characters. So a better way to accept user input would be: 

```cpp
std::cin.getline(name, (sizeof(name)/sizeof(name[0]));
```

The call to cin.getline() will read up to 254 characters (leaving room for null terminator), and excess character is discarded.

## Manipulating C-style strings

C++ provides many functions to manipulate C-style strings as part of the <string> library. Here are a few:

- **strcpy()** : allows one to copy contents of one string into another string.

    ```cpp
    # include <iostream>
    # include <cstring>
    int main()
    {
    	char source[]{ " Copy me "};
    	char dest[50];
    	std::strcpy(dest, source);
    	std::cout << dest << "\n";
    	return 0;
    }
    ```

    - This, however, could cause array overflow were a string of length greater than 50 assigned to "dest".
    - To counter this **strncpy()** is often used instead, as it allow the user to specify the size of the buffer, ensuring overflow doesn't occur. However strncpy doesn't check if the string is null terminated, leaving plenty of room for array overflow.
    - In C++11, **strcpy_s()** is preferred, which adds a new parameter to define the size of the destination : **strcpy_s(dest, 5, source);** . However not all compilers support this.
    - **strlcpy()** is another alternative, but then again it's not included in all compilers.

    **Long story short, there isn't a universally recommended solution here if you need to copy C-style string**

- **strlen()** : returns the length of the C-style string without the null terminator

    ```cpp
    #include <iostream>
    #include <cstring>
    #include <iterator> // for std::size
     
    int main()
    {
        char name[20]{ "Alex" }; // only use 5 characters (4 letters + null terminator)
        std::cout << "My name is: " << name << '\n';
        std::cout << name << " has " << std::strlen(name) << " letters.\n";
        std::cout << name << " has " << sizeof(name) / sizeof(name[0]) << " characters in the array.\n"; // use sizeof(name) / sizeof(name[0]) if not C++17 capable
     
        return 0;
    }
    // My name is: Alex
    // Alex has 4 letters.
    // Alex has 20 characters in the array.
    ```

- **strcat()** : appends one string to another (dangerous, as doesn't check for null pointer on the final string)
- **strncat()** : appends one string to another (with buffer length check)
- **strcmp()** : compares two strings (returns 0 if equal)
- **strncmp()** : compares two strings up to a specific number of characters (returns 0 if equal)

Long story short : **DON'T USE C-STYLE STRINGS**

# P.6.6a - An introduction to std::string_view

- As with some of the downsides of using C-string, std::string also has downsides, particularly when it comes to **const** strings.

    ```cpp
    #include <iostream>
    #include <string>

    int main()
    {
    	char text[]{"hello"};
    	std::string str{ text };
    	std::string more{ str };
    	std::cout << text << " " << str << " " << more << "\n";
    	return 0;
    }
    // hello hello hello
    ```

    Internally main copies "hello" 3 times, resulting in 4 copies.

    - The string literal "hello" known at compile time and stored in the binary.
    - One copy is created when **char []** is created.
    - Two **`std::string`** objects create one copy of the string each. Since **`std::string`** is designed to be modifiable , each **`std::string`** must contain its own copy of the string, so that a give **`std::string`** can be modified without affecting other **`std::string`** object.
- Taking the examples of a car seen through a window, one can see the car but can't touch it or move it. The window just provides a view and is a completely separate object. This analogy can be applied to **`std::string_view`**.
- Unlike `std::string`, which keeps its own copy of the string, `std::string_view` provides a view of a string that's defined elsewhere.

    ```cpp
    #include <iostream>
    #include <string_view>
     
    int main()
    {
      std::string_view text{ "hello" }; // view the text "hello", which is stored in the binary
      std::string_view str{ text }; // view of the same "hello"
      std::string_view more{ str }; // view of the same "hello"
     
      std::cout << text << ' ' << str << ' ' << more << '\n';
     
      return 0;
    }
    // hello hello hello
    ```

    The output is similar to the program above . When one copies a  `std::string_view` , the new `std::string_view` observes the same string as the copied from `std::string_view` is observing. `std::string_view` is fast and has many functionalities of `std::string`.

    ```cpp
    #include <iostream>
    #include <string_view>

    int main()
    {
    	std::string_view str{ "Trains are fast" };
    	
    	std::cout << str.length() << "\n";
    	std::cout << str.substr(0, str.find(' ') << "\n";
    	std::cout << (str == "Trains are fast") << "\n";

    	// SInce C++20
    	std::cout << str.starts_with("Boots") << "\n";
    	std::cout << str.ends_with("fast") << "\n";

    	std::cout < str << "\n";

    	return 0;
    }
    ```

    Since `std::string_view` doesn't make a copy of the string, if viewed string is changed, this change would be reflected in the `std::string_view`.

- Use `std::string_view` instead of C-style strings.
- Prefer `std::string_view` over `std::string` for read-only strings, unless one already has used a `std::string`.

## View modification functions

Taking the window analogy again, but this time with curtains. Curtains reduce the visibility of what can be observed through the window. Curtains however don't change what's outside, it just reduces the visibility.

Some function that allows for reduced visibility are: `remove_prefix` and `remove_suffix`. 

```cpp
#include <iostream>
#include <string_view>
 
int main()
{
  std::string_view str{ "Peach" };
  std::cout << str << '\n';
 
  // Ignore the first characters.
  str.remove_prefix(1);
  std::cout << str << '\n';
 
  // Ignore the last 2 characters.
  str.remove_suffix(2);
  std::cout << str << '\n';
 
  return 0;
}
// Peach
// each
// ea
```

Unfortunately, unlike real curtain, a `std::string_view` can't be opened back up.

Unlike C-style strings and `std::string`, `std::string_view` doesn't use null terminators to mark the end of the string. It keeps track of string length and hence knows where the string ends. 

## Ownership issues and std::string_view to a std::string/C-style string conversion

- Being only a view, a `std::string_view`'s lifetime is independent of that of the string it's viewing. So were the string being viewed goes out of scope, `std::string_view` has nothing to observe and causes undefined behaviour.

    ```cpp
    #include <iostream>
    #include <string>
    #include <string_view>
     
    std::string_view askForName()
    {
      std::cout << "What's your name?\n";
     
      // Use a std::string, because std::cin needs to modify it.
      std::string str{};
      std::cin >> str;
     
      // Switching to std::string_view for demonstrative purposes only.
      std::string_view view{ str };
     
      std::cout << "Hello " << view << '\n';
     
      return view;
    } // str dies, and so does the string that str created.
     
    int main()
    {
      std::string_view view{ askForName() };
     
      // view is observing a string that already died.
      std::cout << "Your name is " << view << '\n'; // Undefined behavior
     
      return 0;
    }
    // What's your name?
    // c++
    // Hello c++
    // Your name is �P@�P@
    ```

- The same can happen were one to create a `std::string_view` from a `std::string` and modify the `std::string`. Modifying the `std::string` can cause internal string to die and be replaced with a new one in a different place. The `std::string_view` will still look at the address where the old sting was present resulting in un-defined behaviour.
- A `std::string_view` will not implicitly be converted to `std::string`, but can be explicitly converted.

    ```cpp
    #include <iostream>
    #include <string>
    #include <string_view>
     
    void print(std::string s)
    {
      std::cout << s << '\n';
    }
     
    int main()
    {
      std::string_view sv{ "balloon" };
      sv.remove_suffix(3);
     
      // print(sv); // compile error: won't implicitly convert
      std::string str{ sv }; // explicit conversion
     
      print(str); // okay
      print(static_cast<std::string>(sv)); // okay
    	   
      return 0;
    }
    // ball
    // ball
    ```

- Some old functions (old `strlen`) still expects C-style strings. To convert a `std::string_view` to a C-style string, we can do so by first converting to a `std::string`.

    ```cpp
    #include <cstring>
    #include <iostream>
    #include <string>
    #include <string_view>
     
    int main()
    {
      std::string_view sv{ "balloon" };
     
      sv.remove_suffix(3);
     
      // Create a std::string from the std::string_view
      std::string str{ sv };
     
      // Get the null-terminated C-style string.
      auto szNullTerminated{ str.c_str() };
     
      // Pass the null-terminated string to the function that we want to use.
      std::cout << str << " has " << std::strlen(szNullTerminated) << " letter(s)\n";
     
      return 0;
    }
    // ball has 4 letter(s)
    ```

## Opening the window via the data() function

- The string being viewed via `std::string_view` can be accessed by using the `data()` function, which returns a C-style . This provides fast access to a string being viewed  (as C-string). But it should only be used if `std::string_view` hasn't been modified and the string being viewed is null-terminated.

    ```cpp
    #include <cstring> // For std::strlen
    #include <iostream>
    #include <string_view>
     
    int main()
    {
      std::string_view str{ "balloon" };
     
      std::cout << str << '\n';
     
      // We use std::strlen because it's simple, this could be any other function
      // that needs a null-terminated string.
      // It's okay to use data() because we haven't modified the view, and the
      // string is null-terminated.
      std::cout << std::strlen(str.data()) << '\n';
     
      return 0;
    }
    // baloon 
    // 7
    ```

- When `std::string_view` is modified, `data()` doesn't always do what we'd like it to.

    ```cpp
    #include <cstring>
    #include <iostream>
    #include <string_view>
     
    int main()
    {
      std::string_view str{ "balloon" };
     
      // Remove the "b"
      str.remove_prefix(1);
      // remove the "oon"
      str.remove_suffix(3);
      // Remember that the above doesn't modify the string, it only changes
      // the region that str is observing.
     
      std::cout << str << " has " << std::strlen(str.data()) << " letter(s)\n";
      std::cout << "str.data() is " << str.data() << '\n';
      std::cout << "str is " << str << '\n';
     
      return 0;
    }

    // all has 6 letter(s)
    // str.data() is alloon
    // str is all
    ```

    - Length information is lost when `data()` is accessed.
    - `std::strlen` and `std::cout` keep reading characters from the underlying string until null-terminator is encountered (i.e end of ballon).

# P.6.7 - Introduction to pointers

- In the previous lessons we saw how when a variable is defined, it's assigned to a free address in the memory and the identifier can be used to access this variable.
- The **address-of-operator (&)** allows us to see what memory address has been assigned to the variable.
- The **dereference operator (*)** allows us to access the value at a particular address

```cpp
#include <iostream>
 
int main()
{
    int x{ 5 };
    std::cout << x << '\n'; // print the value of variable x
    std::cout << &x << '\n'; // print the memory address of variable x
    std::cout << *(&x) << '\n'; /// print the value at the memory address of variable x (parenthesis not required, but make it easier to read)
 
    return 0;
}
5
0x7ffeefbff568
5
```

## Pointers

- A pointer is a variable that holds a memory address as its value.
- Pointers are declared with an '*' between the data type and the variable name. This asterisk isn't a **dereference**. It's part of the pointer declaration syntax.

    ```cpp
    int *iPtr{}; // a pointer to an integer value (Best practice)
    double *dPtr{}; // a pointer to a double value (Best practice)
     
    int* iPtr2{}; // also valid syntax (acceptable, but not favored)
    int * iPtr3{}; // also valid syntax (but don't do this, it looks like multiplication)
     
    int *iPtr4{}, *iPtr5{}; // declare two pointers to integer variables (not recommended)
    ```

- When returning a pointer, it's clearer to put the asterisk next to the return type. This makes it clear that the function is returning of type int* and not int.

    ```cpp
    int* doSomething();	
    ```

## Assigning a value to a pointer

- Since pointers only hold addresses, one assigns addresses to a pointer.

    ```cpp
    int v{ 5 };
    int *ptr{ &v }; // initialize ptr with address of variable v
    ```

![P%20-%20Arrays,%20Strings,%20Pointers%20and%20References%20b2fedce1be7a4102be8e908731736b50/Untitled.png](P%20-%20Arrays,%20Strings,%20Pointers%20and%20References%20b2fedce1be7a4102be8e908731736b50/Untitled.png)

- Type of the pointer has to match the type of the variable being assigned to:

    ```cpp
    int iValue{ 5 };
    double dValue{ 7.0 };
     
    int *iPtr{ &iValue }; // ok
    double *dPtr{ &dValue }; // ok
    iPtr = &dValue; // wrong -- int pointer cannot point to the address of a double variable
    dPtr = &iValue; // wrong -- double pointer cannot point to the address of an int variable
    ```

- The following is illegal too:
    - `int *ptr{ 5 }` cause pointers can only hold addresses.
    - `double *dPtr{ 0x0012FF7C }` cause C++ doesn't allow one to convert literal memory address to pointer.
- **Address-of Operator (&)** : doesn't return address of its operand as a literal. Instead it returns a pointer containing the address of the operand, whose type is defined from an argument. In essence, taking the address of int will return the address in an int pointer (int *).

## Dereferencing pointers

- Once one has a pointer variable pointing to something, what follows usually is dereferencing the pointer, to get the value of what's being pointed at. A dereferencing pointer evaluated the contents of the address it's pointing to.

    ```cpp
    int value { 5 };
    std::cout << &value;  // 0012FF7C
    std::cout << value    //  5

    int *ptr{ &value };
    std::cout << ptr;     // 0012FF7C
    std::cout << *ptr;    // 5
    ```

    It is essential that pointers have a type, else it wouldn't know how to interpret contents it's pointing to when dereferenced. Additionally, the type of the pointer and the variable address it is being assigned to must match else it would misinterpret the bits during dereferencing. 

- Once assigned a pointer value can be reassigned to another value.
- When the address of the variable value is assigned to ptr, the following are true:
    - ptr is the same as &value
    - *ptr is treated the same as value

    ```cpp
    int value{ 5 };
    int *ptr{ &value }; // ptr points to value
     
    *ptr = 7; // *ptr is the same as value, which is assigned 7
    std::cout << value << '\n'; // prints 7
    ```

- **Size-of-Pointers :** it is dependent on the architecture the executable is compiled for - a 32-bit executable uses a 32-bit memory address, while a 64-bit executable uses a 64-bit memory address.

## Uses of pointers

- Arrays are implemented using pointers, and pointers can be used to iterate through an array.
- They are the only way one can dynamically allocate memory in C++.
- They can be used to pass a large amount of data to a function without the need of copying it.
- They can be used to pass a function as a parameter to another function.
- They can be used to achieve polymorphism when dealing with inheritance.
- They can be used to have one struct/class point at another struct/class, to form a chain. Useful with linked list and trees.

# P.6.7a - Null pointers

## Null values and null pointers

- Like with variables, pointers are initialized when instantiated. Unless a value is assigned to a pointer, it will point to some **garbage value.**
- Besides memory addresses, pointers can hold a null value too. A null value is a special value that means the pointer is not pointing towards anything.
- To assign a pointer null value, one can simply initialize it to 0. `double *ptr { 0 };` pointers convert to boolean false if null.

## Dereferencing null pointers and NULL macro

- Dereferencing a null pointer results in undefined behaviour. Causing the application to crash in some cases. This makes sense conceptually, as dereferencing means, go to the address the pointer is pointing at, null pointers don't have an address.
- In C++, a special preprocessor macro called NULL  is used to indicate a null pointer.

    ```cpp
    #include <cstddef> // for NULL
    double *ptr { NULL }; // ptr is a null pointer
    ```

## Perils of using 0 (or NULL) and nullptr

- Value 0 isn't a pointer type, so assigning 0 to a pointer to denote that the pointer is a null pointer is inconsistent.
- This can even cause problems because the compiler can't tell apart a null pointer from

    ```cpp
    #include <iostream>
    #include <cstddef> // for NULL
     
    void print(int x)
    {
    	std::cout << "print(int): " << x << '\n';
    }
     
    void print(int *x)
    {
    	if (!x)
    		std::cout << "print(int*): null\n";
    	else
    		std::cout << "print(int*): " << *x << '\n';
    }
     
    int main()
    {
    	int *x { NULL };
    	print(x); // calls print(int*) because x has type int*
    	print(0); // calls print(int) because 0 is an integer literal
    	print(NULL); // likely calls print(int), although we probably wanted print(int*)
     
    	return 0;
    }
    ```

- **Function overloading :** A function with a different parameter list is a new function, even if a function with the same name exists
- To address the above issues, C+11 introduces **nullptr**. `int *ptr { nullptr };`
- C++ will implicitly convert nullptr to any pointer type. So were **nullptr** used instead of **NULL** in the above example, it will be converted integer pointer.
- C++11 introduces `std::nullptr_t` . It can hold only a single value and comes into use when one needs to write a function that accepts only a nullptr argument.

    ```cpp
    #include <iostream>
    #include <cstddef> // for std::nullptr_t
     
    void doSomething(std::nullptr_t ptr)
    {
        std::cout << "in doSomething()\n";
    }
     
    int main()
    {
        doSomething(nullptr); // call doSomething with an argument of type std::nullptr_t
     
        return 0;
    }
    ```

# P.6.8 - Pointers and arrays

In all but two cases, when a fixed array is used in an expression, the fixed array will **decay** to  (implicitly converted) a pointer that points to the first element in the array. 

```cpp
# include <iostream>

int main()
{
	int array[5]{ 1,2,3,4,5 };
	std::cout <<"Element 0 has address: " << &array[0] << "\n";
	std::cout << "The array decays to a pointer holder address: " << array << "\n";
	return 0;
}
// Element 0 has address: 0042FD5C
// The array decays to a pointer holding address: 0042FD5C
```

- In the above case, array is of type "int[5]" and its value is the array elements themselves. A pointer to the array would be of type "int *", and its value would be the address of the first element of the array.
- All array elements can still be accessed through the pointer, but information derived from array type (eg : length of array) can't be accessed by the pointer.
- Like with integers arrays can be de-referenced and assigned to pointers too.

    ```cpp
    char name[]{ "Jason" }; // C-style string (also an array)
    std::cout << *name << '\n'; // will print 'J'
    int array[5]{ 9, 7, 5, 3, 1 };
    std::cout << *array << '\n'; // will print 9
    int *ptr{ array };
    std::cout << *ptr << '\n'; // will print 9
    ```

Differences between fixed array and pointers

- Applying `sizeof()` on pointers and arrays yield different results. While on arrays it would print the *number of elements * size of each element*, with pointers it would only print the size of the memory address in bytes.
- Using **address-of-operator (&)** on a pointer yields the memory address of the pointer variable, while using it on an array returns a pointer to the entire array. While the pointer in the first case is of type int *, the pointer in the second case is of type int(*)[5].*

## Passing fixed arrays to functions

- The earlier sections made it clear that in C++ doesn't send a copy of an array when it's passed as an argument to the function, because were the arrays large, doing so would be expensive. Instead, when passing an array as an argument to a function, a fixed array decays into a pointer, which is passed to the function.

    ```cpp
    #include <iostream>
    //if "void printSize(int array[])" is used
    // C++ will implicitly convert parameter array[] to *array

    void printSize(int *array)
    {
        // array is treated as a pointer here
        std::cout << sizeof(array) << '\n'; // prints the size of a pointer, not the size of the array!
    }
     
    int main()
    {
        int array[]{ 1, 1, 2, 3, 5, 8, 13, 21 };
        std::cout << sizeof(array) << '\n'; // will print sizeof(int) * array length
     
        printSize(array); // the array argument decays into a pointer here
     
         return 0;
    }
    ```

- In the above example using `void printSize(int array[]);` and using `void printSize(int *array);` equates to the same. Programmers prefer [] syntax because it makes it clear that the function is expecting an array, and not just a pointer to a value.
- In most cases, since pointers aren't aware of the array size, one will have to pass the array size as a separate parameter.
- It is however recommended to use `*array` so the behaviour of the pointer/array being passed to the function doesn't come as a surprise.

Arrays that are part of structs or classes don't decay when the whole struct or class is passed to a function. **Hence a useful way to prevent decay if desired.** 

# P.6.8a - Pointer arithmetic and array indexing

- In C++ one can perform integer addition or subtraction operations on pointers. If `ptr` points to an integer, `ptr + 1` is the address of the next integer in memory, and `ptr - 1` is the integer that comes before.
- `ptr + 1` doesn't return the memory address after `ptr`, but memory address of the next object type that `ptr` points towards.
    - If `ptr` points to an integer, `ptr + 3` means 3 integers (12 bytes) after `ptr`.
    - if `ptr` points to a character, `ptr + 3` means 3 chars (3 bytes) after `ptr`.

    ```cpp
    #include <iostream>
     
    int main()
    {
        int value{ 7 };
        int *ptr{ &value };
     
        std::cout << ptr << '\n';    // 0x7ffeefbff568
        std::cout << ptr+1 << '\n';  // 0x7ffeefbff56c
        std::cout << ptr+2 << '\n';  // 0x7ffeefbff570
        std::cout << ptr+3 << '\n';  // 0x7ffeefbff574
        // Each of these addresses differ by a value of 4
        return 0;
    }
    ```

- Let's try this on arrays

    ```cpp
    include <iostream>
     
    int main()
    {
        int array[]{ 9, 7, 5, 3, 1 };
     
        std::cout << "Element 0 is at address: " << &array[0] << '\n'; // 0x7ffeefbff550
        std::cout << "Element 1 is at address: " << &array[1] << '\n'; // 0x7ffeefbff554
        std::cout << "Element 2 is at address: " << &array[2] << '\n'; // 0x7ffeefbff558
        std::cout << "Element 3 is at address: " << &array[3] << '\n'; // 0x7ffeefbff55c
    		// Again, each of these memory addresses is 4 bytes apart. 
        return 0;
    }
    ```

- So it now is clear that:
    - memory is laid out sequentially
    - fixed array can decay int a pointer to the first element of the array.
    - adding 1 to a pointer returns the memory address of the next object of that type of memory.

    With this one can conclude that adding 1 to an array should point to the second element of the array. `array[n]` is the same as `*(array + n)` where n is an integer. 

## Using a pointer to iterate through an array

- One can use a pointer and pointer arithmetic to loop through an array. Subscripts are generally used as it's easier to read and less error prone.

    ```cpp
    #include <iostream>

    bool isVowel(char ch)
    {
    	switch (ch)
    	{
    		case 'A':
    		case 'a':
    		.
    		.
    		case 'u':
    			return true;
    		default:
    			return false;
    	}
    }
    int main()
    {
    	char name[]{ "Allwyn" };
    	int arrayLength{ sizeof(name) / sizeof(name[0]) };
    	int numVowels{ 0 };

    	for (char* ptr{ name }; ptr < (name + arrayLength); ++ptr)
    	{
    		if (isVowel(*ptr)
    		{
    			++numVowels;
    		}
    	}
    	std::cout << name << " has " << numVowels << " vowels.\n";
    	return 0;
    }
    ```

- Since counting elements s common, the algorithms library offers `std::count_if` which count elements that fullfil a condition.

    ```cpp
    int main()
    {
    	char name[]{ "hello" };
    	auto numVowels { std::count_if(std::begin(name), std::end(name), isVowel);
    	std::cout << name << "has" << numVowels << "vowels. \n";
    	return 0;
    }
    ```

    - `std::begin` returns an iterator (pointer) to the first element
    - `std::end` returns an iterator to the element that would be one after the last. The iterator returned by the same is only used as a marker, accessing it causes undefined behaviour cause it doesn't point to a real element.

# P.6.8b - C-style string symbolic constants

- C++ supports a way to create C-style string symbolic constants using pointers:

    ```cpp
    #include <iostream>
     
    int main()
    {
        // char myName[]{ "Alex" }; // fixed array
        // std::cout << myName << '\n';

    		const char *myName{ "Alex" }; // pointer to symbolic constant
        std::cout << myName << '\n';
     
        return 0;
    }
    ```

    The commented lines (program 1) and the non-commented (program 2) lines result in the same output.

    - In the fixed array case, the program allocates memory for a fixed array of length 5, and initializes that memory with the string “Alex\0”. Because memory has been specifically allocated for the array, you’re free to alter the contents of the array. The array itself is treated as a normal local variable, so when the array goes out of scope, the memory used by the array is freed up for other uses.
    - In the symbolic constant case, the compiler places the string "Alex\0" into read-only memory and then set a pointer to it. And as the memory is only read-only, the best practice is to make sure the string is constant.
- For optimization purposes, multiple string literals may be consolidated into a single value.

    ```cpp
    const char *name1{ "Alex" };
    const char *name2{ "Alex" };
    ```

    The compiler may opt to combine these into a single shared string literal, with both name1 and name2 pointed at the same address. Thus, if name1 was not const, making a change to name1 could also impact name2.

- Hence string literals are stored in a fixed location in memory, and they have static duration (dies at the end of the program) rather than automatic duration (dies at the end of the block defined within)
- In the code below, getName() will return a pointer to C-style string "Alex".

    ```cpp
    const char* getName()
    {
        return "Alex";
    }
    ```

    - Were this function to return any other kind of literal by address, the literal would be destroyed at the end of `getName()` and a dangling pointer would be returned.
    - Here, since the literal has static duration, "Alex" will not be destroyed when `getName()` terminates.
- `std::cout` **and char pointers**

    ```cpp
    #include <iostream>
     
    int main()
    {
        int nArray[5]{ 9, 7, 5, 3, 1 };
        char cArray[]{ "Hello!" };
        const char *name{ "Alex" };
     
        std::cout << nArray << '\n'; // nArray will decay to type int*
        std::cout << cArray << '\n'; // cArray will decay to type char*
        std::cout << name << '\n'; // name is already type char*
     
        return 0;
    }
    // 003AF738
    // Hello!
    // Alex
    ```

    The reason `cout` prints values and not address is cause, `std::cout` makes some assumptions about ones intent. If a non-char pointer is passed, it'll simply print the contents of that pointer. However, if an object of type `char*` or `const char*` is passed, it'll assume one is intending to print a string. Consequently, instead of printing the pointer’s value, it will print the string being pointed to instead.

# P.6.9 - Dynamic memory allocation with new and delete

C++ supports three basic types of memory allocation, of which two have already been covered:

- **Static memory allocation** happens for static and global variables. Memory for these types of variables is allocated once the program is run and persists throughout the life of the program.
- **Automatic memory allocation** happens for function parameters and local variables. Memory for these kinds of variables is allocated when the relevant block is entered and freed when the block is exited.
- **Dynamic memory allocation**

The common points between static and automatic allocation are the follows:

- The size of variable must be known at compile time.
- Memory allocation and deallocation happens automatically.

Most of the time these constraints workout just fine. However, one can come across situations where one or both these constraints cause problems, usually when dealing with external input.

[Why using static/automatic memory allocation might be a poor solution for dynamic input (get user name)?](https://www.learncpp.com/cpp-tutorial/69-dynamic-memory-allocation-with-new-and-delete/) 

- Leads to wastage of memory if variables aren't used.
- Hard to say which bits of the memory is actually used.
- Most normal variables (including arrays) are allocated in a portion of memory called stack. The amount of stack memory for a program is generally quite low.
- Can lead to artificial limitations and/or array overflows.

All of these problems can be addressed using dynamic memory allocation.

## Dynamically allocating single variables and working

- Scale (non-array) form of the new operator is used to allocated a single variable dynamically,

    ```cpp
    new int; // dynamically allocate an integer (and discard the result)
    ```

    Here, we're requesting an integer's worth of memory from the operating system. The **new** operator creates the object using that memory, and returns a pointer containing the address of the memory that has been allocated. 

- Its common practice to assign return value of one's pointer variable so one can access the allocated memory later.

    ```cpp
    int *ptr{ new int }; // dynamically allocate an integer and assign the address to ptr so we can access it later
    ```

- The pointer can then be dereferenced to access the memory

    ```cpp
    *ptr = 7; // assign value of 7 to allocated memory
    ```

- So how does dynamic memory work?
    - One's computer has memory (ideally, lots of it), for applications to use.
    - When an application is run, the OS loads the application into some of that memory.
    - This memory used by the application is divided into different areas, each serving a different purpose. A part of the area is used to store code, a part used for normal operations (keeping track of which functions were called, creating and destroying global and local variables, etc…).
    - However, much of the memory available just sits there, waiting to be handed out to programs that request it.
    - When memory is dynamically allocated, one is asking the system to reserve some of that memory for one's program use.
    - If this request can be fulfilled, the OS will return the address of that memory to the application.
    - From here on the application can use the memory as it wishes, and when the application is done with the memory it returns it back to the OS.
    - Unlike static or automatic memory, the program itself is responsible for requesting and disposing of dynamically allocated memory.

## Initializing and deleting memory

- One can dynamically allocate a variable via direct/uniform initialization

    ```cpp
    int *ptr1{ new int (5) }; // use direct initialization 
    int *ptr2{ new int { 6 } }; // use uniform inintialization
    ```

- When one is done with dynamically allocated variable, one needs to explicitly tell C++ to free the memory for reuse. For single variables, this done through a scalar form of the delete operator.

    ```cpp
    // assume ptr has previously been allocated with operator new
    delete ptr; // return the memory pointed to by ptr to the operating system
    ptr = 0; // set ptr to be a null pointer (use nullptr instead of 0 in C++11)
    ```

- The **delete** operator in reality doesn't delete anything. It simply returns the memory being pointed back to the OS. The OS is then free to reassign that memory to another application. Although it might seem like this deletes a variable, this's not the case. The pointer still has the same scope as before and can be assigned a new value just like any other variable.

    Deleting a pointer that's not pointing to dynamically allocated memory may cause bad shit.

## Dangling pointers

- C++ doesn't make any guarantee about what will happen to the contents of deallocated memory, or to the value of the pointer being deleted. In most cases, the memory returned to the OS will contain the same values it had before it was returned, and the pointer will be left pointing to the new deallocated memory.
- A pointer pointing to deallocated memory is called dangling pointer. Dereferencing, or deleting a dangling pointer will lead to undefined behaviour.

    ```cpp
    #include <iostream>
     
    int main()
    {
        int *ptr{ new int }; // dynamically allocate an integer
        *ptr = 7; // put a value in that memory location
     
        delete ptr; // return the memory to the operating system.  ptr is now a dangling pointer.
     
        std::cout << *ptr; // Dereferencing a dangling pointer will cause undefined behavior
        delete ptr; // trying to deallocate the memory again will also lead to undefined behavior.
     
        return 0;
    }

    // 7 (most likely)
    // learncpp(15703,0x100398380) malloc: *** error for object 0x100606820: pointer 
    // being freed was not allocated
    ```

- Deallocating memory may create multiple dangling pointers

    ```cpp
    #include <iostream>
     
    int main()
    {
        int *ptr{ new int{} }; // dynamically allocate an integer
        int *otherPtr{ ptr }; // otherPtr is now pointed at that same memory location
     
        delete ptr; // return the memory to the operating system.  ptr and otherPtr are now dangling pointers.
        ptr = nullptr; // ptr is now a nullptr
     
        // however, otherPtr is still a dangling pointer!
     
        return 0;
    }
    ```

- **Best practices**
    - Try and avoid having multiple pointers point at the same piece of dynamic memory. If this is not possible be clear about which pointer "owns" the memory and which is simply accessing it.
    - When one deletes a pointer, if the pointer is not immediately going out of scope afterward, set the pointer to 0 (`ptr = nullptr`).

## New, null pointers and memory leaks

**New**

- When requesting memory form the OS, under rare circumstances, the OS may not have any memory to grant the request with.
- By default an exception is throw and the program crashes, unless the exception is handled of course.
- In many cases, having **new** throw an exception is undesirable, so there's an alternate **new** that can be used instead to tell new to return a null pointer if memory can't be allocated. This is done by adding the constant `std::nothrow` between the new keyword and allocation type.

    ```cpp
    int *ptr = new (std::nothrow) int; // value will be set to a null pointer if the integer allocation fails
    ```

- If one then attempts to dereference this memory (say null pointer is assigned), undefined behaviour will result, crashing the program. Therefore it's best to check all memory request to ensure they actually succeeded before using the allocated memory.

    ```cpp
    int *value{ new (std::nothrow) int{} };
    if (!value)
    {
    	std::cout << "Could not allocate memory";
    }
    ```

**Null pointer and Dynamic memory allocation**

- Null pointers are useful when dealing with dynamic memory allocation. In essence it implies "no memory has been allocated to this pointer”. This allows one to conditionally allocate memory.

    ```cpp
    // If ptr isn't already allocated, allocate it
    if (!ptr)
    	ptr = new int;
    ```

    If ptr is non-null, the dynamically allocated variable will be deleted. If it is null, nothing will happen. 

**Memory leaks**

- Dynamically allocated memory stays allocated until it's explicitly deallocated or until the program ends. However, the pointers used to hold dynamically allocated memory addresses follow the normal scoping rules for local variable. **This mismatch can create interesting problems.**
- Consider the following function

    ```cpp
    void doSomething()
    {
     int *ptr{ new int{} };
    }		
    ```

    - This function allocates an integer dynamically, but never frees it using delete. Since pointer variables are just normal variables, it goes out of scope at the end of the function. When the pointer is destroyed, the reference towards the dynamically allocated memory no longer exists. Hence, the address towards this bit of the memory is lost and the program can no longer delete the **int** value at that memory location. This is called **memory leak.**
    - **Memory leak** happens when one's program losses the address of some bit of dynamically allocated memory before giving it to the OS. So not only can one not delete his contents at the address, but the OS can't reassign the address.
    - Memory leaks eat up free memory while the program is running, making less memory available not only to this program, but to other programs as well. Programs with severe memory leak problems can eat all the available memory, causing the entire machine to run slowly or even crash. Only after your program terminates is the operating system able to clean up and “reclaim” all leaked memory.
- Other examples of **memory leaks** are as follows:

    ```cpp
    int value = 5;
    int *ptr{ new int{} }; // allocate memory
    ptr = &value; // old address lost, memory leak results

    int *ptr{ new int{} };
    ptr = new int{}; // old address lost, memory leak results
    //fix by 
    delete ptr; // return memory back to operating system

    ```

# P.6.9a - Dynamically allocating arrays

- To allocate an array dynamically, we use the array form of **new** and **delete** (often called new[], delete[]).

    ```cpp
    # include <iostream>
    int main()
    {
    	std::cout << "Enter a positive integer";
    	int length{};
    	std::cin >> length;

    	int *array{ new int[length]{} }; // use array new. Note that length need not be constant

    	std::cout << "Array of integers of length : " << length << "\n";

    	array[0] = 5;

    	delete[] array; // use array delete to deallocate array

    	// we don't need to set array to nullptr/0 here because it's going to go out of 
    	// scope immediately after this anyway
    	return 0;
    }
    ```

    - Since one is allocating an array, C++ knows that it should use the array version of new instead of the scalar version of new. Essentially, the new[] operator is called, even though the [] isn't placed next to the **new** keyword.
    - Since the memory is allocated from a different place than the memory used for fixed arrays, the size of the array can be quite large.
- Using delete[] version lets the CPU know that it needs to clean up multiple variables instead of only a single. Usage of scaler version of delete on arrays will result in undefined behaviour.
- Since new[] keeps track of how much memory was allocated to a variable, so that array delete[] can delete the right amount of memory.
- Initializing dynamically allocated array to 0 `int *array{ new int[length]{} } ;`
- Initializing arrays with values:

    ```cpp
    int fixedArray[5] = { 9, 7, 5, 3, 1 }; // initialize a fixed array in C++03
    int *array{ new int[5]{ 9, 7, 5, 3, 1 } }; // initialize a dynamic array in C++11
    // No operator between array length and initialzer list
    ```

- **Resizing an array :** Dynamically allocating an array allows one to get the array length at the time of allocation. However, C++ **doesn't** provide a built-in way to **resize** an array that has already been allocated. A **work around** is by dynamically allocating a new array. copying the elements over and deleting the old array. However, this can be error prone especially when the element type is a class.

# P.6.10 - Pointers and const

- One can't assign a non-constant pointer to a constant variable

    ```cpp
    const int value = 5; // value is const
    int *ptr = &value; // compile error : cannot convert const int* to int*xc
    ```

    Were one able to assign a non-const pointer to a constant value then in theory one should be able to change the value of the constant variable, which defeats the purpose of **const.**

- A pointer to a const value is a (non-const) pointer that points to a constant value.

    ```cpp
    const int value = 5;
    const int *ptr = &value; // this is okay, ptr is a non-const pointer that is pointing to a "const int"
    *ptr = 6; // not allowed, we can't change a const value
    ```

- Assigning a int* to const int* is fine too.

    ```cpp
    int value = 5;
    const int *ptr = &value; // ptr points to a "const int"
    value = 6; // the value is non-const when accessed through a non-const identifier
    // NOT THIS HOWEVER
    *ptr = 6; // ptr treats its value as const, so changing the value through ptr is not legal
    ```

- Since a pointer to a const value is not const itself (it just points to a const value), the pointer can be redirected to point at other values.

## Const pointers

- It's possible to make a pointer a const itself.

    ```cpp
    int value1 = 5;
    int *const ptr = &value1;

    int value2 = 6;
    ptr = &value2; // not okay, once initialized, a const pointer can not be changed.
    ```

    - Now change the pointer value wouldn't be possible
    - However since the value it's pointing is non-const it can be **changed** via **dereferencing**.
- It's possible to declare a const pointer to a const value.

    ```cpp
    int value = 5;
    const int *const ptr = &value;
    ```

    A pointer to a const value treats the value as const (even if it is not), and thus can not change the value it is pointing to.

# P.6.11 - Reference variables

- Until now two variable types have been discussed, namely normal variables and pointers, references are the third kind. It's a third kind of C++ variable that acts as an alias to another object or value.
- C++ supports three kinds of reference:
    - References to non-const values - called **references** or **non-const references**.
    - Reference to const values - called **const references**.
    - r-value references

## Reference to non-const values and as aliases

A reference (to a non-const value) is declared by using ampersand (&) between the reference type and the variable name. Here the ampersand doesn't mean address of, it means **reference to**.

Similar to the position of * with pointers, it doesn't matter as to where the ampersand symbol is placed.

```cpp
int value{ 5 };    // normal integer
int &ref{ value }; // reference to variable value
```

```cpp
int& ref1{ value };
int &ref2{ value };
```

- References generally act identically to the values they're referencing. In this sense, a reference acts as an alias for the object being referenced . Here setting or getting a value of x, y or z will do the same thing.
- In the example to the right,*value* and *ref* is treated synonymously.

    ```cpp
    cout << &value; // prints 0012FF7C
    cout << &ref; // prints 0012FF7
    ```

```cpp
int x{ 5 };  // normal integer
int &y{ x }; // y is a reference to x
int &x{ y }; // z is a reference to x
```

```cpp
int main()
{
    int value{ 5 };    // normal integer
    int &ref{ value }; // reference to variable value
 
    value = 6;         // value is now 6
    ref = 7;           // value is now 7
 
    std::cout << value << '\n'; // prints 7
    ++ref;
    std::cout << value << '\n'; // prints 8
 
    return 0;
}
```

## l-values and r-values

- In C++, variables are a type of l-value. An **l-value** is a value that has a address, and since all variables have address, all variables are l-values.
- The name l-values comes from the fact that, l-values are the only values that can be on the left side of an assignment statement.
- When an assignment is performed, the left side of the assignment operator must be an l-value. Consequently, a statement like `5 = 6;` will cause a compile error as 5 is not a l-value. The value of 5 has no memory and nothing can be assigned to it.
- The opposite of l-values are r-values. An **r-value**, is a expression that is not an l-value. Examples of r-value are literals (such as 5) and non-l-value expressions (such as 2 + x ).
- The key take-away is that, to the left side of the assignment one must have something that represents a memory address (such as a variable). Everything to the right side of the assignment will be evaluated to produce a value.
- Const variables are **non-modifiable l-values**.

## Reference must be initialized and can't be reassigned

- Reference must be initialized when created.
- Unlike pointers, which can hold a null value, there's no such thing as a null reference.
- Reference to non-const values can only be initialized with non-const l-values.
- One can't initialize a non-const reference with a const object. Else one would be able to change the value of the const object through the reference

```cpp
int x{5 };
int &ref{ x } ; // valid reference, initialized to variable value
int &invalidRef ; // invalid, needs to reference something

int &ref1{ x }; // okay
const int y{ 7 };
int &ref2{ y }; // not okay
int &ref3{ 6 }; // not okay, 6 is an r-value
```

- Once initialized, a reference can't be changed to another reference variable.
- The 4 statement, instead of changing ref to reference variable value 2, it simply assigns value of value 2 to value1.

```cpp
int value1{ 5 };
int value2{ 6 };
 
int &ref{ value1 }; // okay
ref = value2; // assigns 6 (the value of value2) to value1 -- does NOT change the reference!
```

## Reference as function parameters

- References are most often used as function parameters. In this context, the reference parameter acts as an alias for the argument and no copy of the argument is made into the parameter. This can lead to better performance if the argument is large or expensive to copy.
- Reference parameter acts as an alias for the argument, a function that uses reference parameter is able to modify the argument passed in.

```cpp
#include <iostream>
 
// ref is a reference to the argument passed in, not a copy
void changeN(int &ref)
{
	ref = 6;
}
 
int main()
{
	int n{ 5 };
 
	std::cout << n << '\n';
 
	changeN(n); // note that this argument does not need to be a reference
 
	std::cout << n << '\n';
	return 0;
}
```

- When **n** is passed to the function, the function parameter ref is set as a reference to argument n. Allowing the function to change the value of **n** through ref.
- **Best practice** : Pass arguments by non-const reference when the argument needs to be modified by the function.
- **Downside :** While using non-const references as function parameters, one must ensure that the argument must be a non-const l-value.

## Using reference to pass C-style arrays to functions and reference as shortcuts

- An issue with C-style arrays is that in most cases they decay to pointers when evaluated. However, if a C-style array is passed by reference, this decaying doesn't happen.

    ```cpp
    #include <iostream>
    #include <iterator> 
     
    // Note: You need to specify the array size in the function declaration
    void printElements(int (&arr)[4])
    {
      int length{ static_cast<int>(std::size(arr)) }; // we can now do this since the array won't decay
      
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

- A secondary use of reference is to provide easier access to nested data.
- Say one would need to work with value1 field of the *Something* struct of *Other*. To access value1, one would need to do something like this `other.something.value1`. Reference could help make this less verbose.

```cpp
struct Something
{
    int value1;
    float value2;
};
 
struct Other
{
    Something something;
    int otherValue;
};
 
Other other;

int &ref{ other.something.value1 };
other.something.value1 = 5;
ref = 5;
```

## References vs pointers

References acts like a pointer that's implicitly dereferenced when accessed. They are usually implemented internally by the compiler using pointers. *ptr and ref evaluates identically, As a result, the following two components produce the same effect. 

```cpp
int value{ 5 };
int *const ptr{ &value };   // *ptr = 5
int &ref{ value };          // ref = 5
```

Since references must be initialized to valid objects (can't be null) and can't be changed once set, references are generally much safer to use than pointers (there's a risk of de-referencing a null pointer).

If a task can be solved with references or pointers, preference must be given to references.

# P.6.11a - Reference and const

Like pointers, references can be declared to a constant value too. This is done by declaring a reference using a const keyword. Such references are called **const reference**.

```cpp
const int value{ 5 };
const int &ref { value }; // ref is a reference to some value
```

## Initializing references to const values

Unlike references to non-const values, which can only be initialized with non-const l-values,references to const values can be initialized with non-const l-value, const l-value, and r-values.  

```cpp
int x{ 5 };
const int& ref1{ x }; // Okay, x is a non-const l-value

const int y{ 7 };
const int& ref2{ y }; // Okay, x is const l-value

const int& ref3{ 5 }; // Okay, 6 is an r-value
```

Much like a pointer to a const value, a reference to a const value can reference non-const variable. 

```cpp
int value{ 5 };
const int& ref{ value }; // create const reference to variable value
 
value = 6; // okay, value is non-const
ref = 7; // illegal -- ref is const
```

## References to r-values extend the lifetime of the referenced value

Normally r-values have **expression scope**, meaning the values are destroyed at the end of the expression in which they are created. 

```cpp
std::cout << 2 + 3 << '\n'; // 2 + 3 evaluates to r-value 5, which is destroyed at the end of this statement
```

However, when a reference to a const value is initialized with an r-value, the lifetime of the r-value is extended to match the lifetimes of the references. 

```cpp
int somefcn()
{
    const int& ref{ 2 + 3 }; // normally the result of 2+3 has expression scope and is destroyed at the end of this statement
    // but because the result is now bound to a reference to a const value...
    std::cout << ref << '\n'; // we can use it here
} // and the lifetime of the r-value is extended to here, when the const reference dies
```

## Const references as function parameters

References used a function parameters can also be const. This allows us to access the argument without making a copy of it, while guaranteeing that the function will not change the value being referenced. 

```cpp
void changeN(const int& ref):
{
	ref = 6; // not allowed, ref is const
}
```

Referencing const values are particularly useful as function parameters because of their versatility. A const reference parameter allows one to pass in a non-const l-value argument, a const l-value argument, a literal or the result of an expression.

```cpp
#include <iostream>
 
void printIt(const int& x)
{
    std::cout << x;
}
 
int main()
{
    int a{ 1 };
    printIt(a); // non-const l-value
 
    const int b{ 2 };
    printIt(b); // const l-value
 
    printIt(3); // literal r-value
 
    printIt(2+b); // expression r-value
 
    return 0;
}
// 1234
```

**To avoid making unnecessary potentially expensive copies, variables that are not pointers or fundamental data-types (int, double etc) should generally be passed by (const) reference. Fundamental data types should be passed by value, unless the function needs to change them. There are a few exceptions to this rule, namely types that are so small that it’s faster for the CPU to copy them than having to perform an extra indirection for a reference.**

**Pass non-pointer, non-fundamental data type variables (such as structs) by (const) reference, unless you know that passing it by value is faster.**

# P.6.12 - Member selection with pointers and references

```cpp
struct Person
{
	int age;
	double weight;
};
Person person;
person.age = 5;
```

```cpp
struct Person
{
	int age;
	double weight;
};
Person person;
Person &ref = person
ref_age = 5
```

A similar syntax as with references

```cpp
struct Person
{
	int age;
	double weight;
};
Person person;
Person *ptr = &person
(*ptr).age = 5
```

With pointers, need to dereference it first

For pointers, dereference must be enclosed in paranthesis, because the memeber section operator has hihger precedence than dereference operator. 

Since syntax for access to structs and class memebers through a pointer is awkward, C++ offers a second member operator (→) for doing member selection from pointers The following lines are equivalent.

```cpp
(*ptr).age = 5;
ptr->age = 5;
```

When using a pointer to access the value of a member, use operator-> instead of '.' operator. 

# P.6.12a - For-each loops

The previous lessons showed one way of iterating through arrarys was using a loop (for loop in particular) to iterate through the elements of an array. While for loops provide a convenient way to loop through array, they are easy to mess up and prone to **off-by-one errors**.

The **for-each** loop or **range-based** for loop is an easier and safer way to iterate through the elements in an array.

## For-each loops and auto keyword

- When this syntax is encountered, the loop will iterate through each element in the array, assigning the value of the current array element to the varaible declared in element_declaration. To **avoid** **type conversion** , element_declaration should have the same type as the array elements.

    ```cpp
    // Syntax
    for (element_declaration : array)
    	statement;
    	
    int main()
    {
    	constexpr int fibonacci[]{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    	for (int number : fibonacci) // iterate over fibonacci array
    	{
    		// access array element throught the variable 'number'
    		std::cout << number << ' '; 
    	}
    	std::cout << "\n";
    	return 0;
    }
    ```

    The loop iterates through all elements of the array (while executing elements within the scope of the loop) until it arrives at the final value.

- Since, for best results, `element_declaration` should have the same type as the array elements, this is an ideal case in which the `auto` keyword comes in handy.

    ```cpp
    // The above example with the 'auto' keyword
    int main()
    {
    	constexpr int fibonacci[]{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    	for (auto number : fibonacci) // type is auto, so number has 
    																// its type deduced from the fibonacci array
    	{
    		std::cout << number << ' ';
    	}
    	std::cout << "\n";
    	return 0;
    }
    ```

## For each loops and references and non-array objects

Within for-each loops, the values of an array will be copied onto a variable (number in the above example). This being said, copying array elements can be expensive, and most of the time only need to refer to the original element. Fortunately, we have **references**:

```cpp
std::string array[]{"peter", "likes", "frozen", "yogurt" };
for (auto &element : array) // The ampersand makes element a reference to the
														// actual array element, preventing a copy from being made
{
 std::cout << element << ' ';
}
```

- Any changes to element will be reflected in the array - which is not the case if normal variables were to be used.
- Additionally, it's a good idea to make your reference `const` if one intends to use it in a read-only fashion. `const auto &element : array`
- In for-each loops element declarations, if your elements are non-fundamental types, use references or const references for performance reasons.
- Max scores example using a for-each loop

    ```cpp
    #include <iostream>
     
    int main()
    {
        constexpr int scores[]{ 84, 92, 76, 81, 56 };
        int maxScore{ 0 }; // keep track of our largest score
     
        for (auto score : scores) // iterate over array scores, assigning each value in turn to variable score
        {
            if (score > maxScore)
            {
                maxScore = score;
            }
        }
     
        std::cout << "The best score was " << maxScore << '\n';
     
        return 0;
    }
    ```

    - One should note from this example that, array subscription is history (arr[i]).
    - Array element can be directly accessed through the varaible score.
    - Tha array has ot have size information.
    - An array decayed to a **pointer can't** be used in a for-each loop
- Apart from arrays, for-each loops work with many kinds of list-like structures such as vectors, linked lists, trees, and maps.

    ```cpp
    #include <iostream>
    #include <vector>
     
    int main()
    {
        std::vector fibonacci{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 }; /
        // Before C++17
        // std::vector<int> fibonacci{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
     
        for (auto number : fibonacci)
        {
            std::cout << number << ' ';
        }
     
        std::cout << '\n';
     
        return 0;
    }
    ```

## For-each with pointers to an array and indexing

- In order ot iterate through the array, for-each needs ot know how big the array is, which means knowing the array size. Because arrays that have decayed into **pointers don't know their size, for-each loops will not work with them.**

    ```cpp
    //int sumArray(const int (&array)[5]) // array is a reference
    //{
    //    int sum{ 0 };
    //    
    //    for (auto number : array)
    //    {
    //        sum += number;
    //    }
    //    
    //    return sum;
    //}

    int sumArray(int array[]) // array is a pointer
    {
        int sum{ 0 };
     
        for (auto number : array) // compile error, the size of array isn't known
        {
            sum += number;
        }
     
        return sum;   
    }
     
    int main()
    {
         constexpr int array[]{ 9, 7, 5, 3, 1 };
     
         std::cout << sumArray(array) << '\n'; // array decays into a pointer here
     
         return 0;
    }
    ```

    For the same reason dynamic arrays won't work for for-each loops.

- For-each loops don't provide a direct way to get the array index of current element. This is essentially because, many of the structures that for-each loop can be used with aren't directly indexable.
    - Since C++20, range-based for loops can be used with an **init-statement**. Using the same, a manual counter can be created without polluting the function in which the for-loop is placed.

        ```cpp
        for (init-statement; element_declaration : array)
        	statement;
        ```

    - In the example below two arrays are correlated by index. For example, the student with the name at names[3] has a score of scores[3]. Whenever a student with a new high score is found, their name and difference in points to the previous high score is printed.

        ```cpp
        # include <iostream>

        int main()
        {
        	std::string names[]{ "Alex", "Betty", "Caroline", "Dave", "Emily" };
        	constexpr int scores[]{ 84, 92, 76, 81, 56 };
        	int maxScore{ 0 };

        	for (int i{ 0 }; auto score : scores)
        	{
        		if (score > maxScore)
        		{
        			std::cout << names[i] << " beat the previous best score of " << maxScore << " by " << (score - maxScore) << " points!\n";
        			maxScore = score;
        		}
        		++i;
        	}
        	std::cout << "The best score was " << maxScore << '\n';
          return 0;
        }
        ```

        - The `int i{ 0 };` is the init-statement which gets executed only once at the start of the loop.

**For-each loops provide a superior syntax for iterating through an array when we need to access all of the array elements in forwards sequential order. It should be preferred over the standard for loop in the cases where it can be used. To prevent making copies of each element, the element declaration should ideally be a reference**.

# P.6.13 - Void pointers

Void pointers are also know as **generic pointer**, is a special type of pointer that can be pointed at objects of any data type. It is can be declared like a normal pointer using the `void` key word as the pointer type.

```cpp
int nValue;
float fValue;

struct Something
{
	int n;
	float f;
};
Something sValue;
void *ptr;
ptr = &nValue;
ptr = &fValue;
ptr = &sValue;
```

**However,** since the void pointer doesn't know what type of object it is pointing to, it can't be dereferenced directly. It should be cast to another pointer type before it's dereferenced. 

```cpp
int value{ 5 };
void *voidPtr( &value };
std::cout << *voidPtr << '\n'; // illegal: cannot dereference a void pointer
int *intPtr{ static_cast<int*>(voidPtr) }; // if one casts their void pointer to an int pointer...
std::cout << *intPtr << '\n'; // then one can dereference it like normal
```

So if a void pointer doesn't know what it's pointing to, how will one know what to cast it to you. **Unfo**r**tunately**, this will require one to keep track of the same. 

```cpp
# include <iostream>

enum class Type
{
	INT,
	FLOAT,
	CSTRING
};

void printValue(void *ptr, Type type)
{
	switch(type)
	{
		case Type::INT:
			std::cout << *static_cast<int*>(ptr) << '\n'; // cast to int pointer and dereference
			break;
		case Type::FLOAT:
			std::cout << *static_cast<float*>(ptr) << '\n'; // float to int pointer and dereference
			break;
		case Type::CSTRING:
            std::cout << static_cast<char*>(ptr) << '\n'; // cast to char pointer (no dereference)
			break;
```

Void pointers can be set to a null value: 

```cpp
void *ptr{ nullptr };
```

Although some compilers allow deleting a void pointer that points dynamically allocated memory, doing so must be avoided, as it can result in **undefined behaviour**.

So the **difference between a void and null pointer** is that, a void pointer doesn't know the type of object it's pointing to. Additionally, the pointer must be explicitly cast into another type of pointer, in order to eventually dereference the value it's pointing towards. A null pointer on the other hand doesn't point to any address, a void pointer can be a null pointer.

# P.14 - Pointer to pointers and dynamic multi-dimensional arrays

## Pointers to pointers

A pointer to pointer works just as a normal pointer - can be dereference to retrieve the value pointed to. Since the value itself is a pointer it can once again be dereferenced to get the underlying value. 

```cpp
int main()
{
	int value = 5;

	int *ptr = &value;
	std::cout << *ptr;  // 5

	int **ptrptr = &ptr;
	std::cout << **ptrptr; // 5

	std::cout << &value <<"\n";  // 0x7ffeefbff568
	std::cout << *ptr <<"\n";    // 5
  std::cout << &ptr <<"\n";    // 0x7ffeefbff560
  std::cout << ptr <<"\n";     // 0x7ffeefbff568
}
```

- One can't set a pointer to a pointer directly to a value. This is because the address of operator (operator&) required an lvalue, but &value is an rvalue.

    ```cpp
    int value = 5;
    int **ptrptr = &&value; // not valid
    ```

- However, a pointer to a pointer can be set to null.

    ```cpp
    int *ptrptr = nullptr;
    ```

## Arrays of pointers

- Pointers to pointers have a few uses, The most common use is to dynamically allocate any array of pointers. The works just like standard dynamically allocated array, except array elements are of type "pointer to integer" instead of integer.

    ```cpp
    int **array = new int*[10]; // allocatean an array of 10 int pointers
    ```

- Pointers to pointers are also used with dynamically allocated multidimensional arrays. The two ways in which this can be done are:
    - If rightmost array dimension is a compile-time constant `int (*array)[5] = new int[10][5];` . The parenthesis is required to ensure proper precedence.
    - Using the **auto** keyword `auto array = new int[10][5];` . Unfortunately, this solution doesn't work if any non-leftmost array dimension isn't a compile time constant. If this i1s the case, the declaration gets slightly complicated.
        - First, an array of pointers is allocated
        - Then array of pointers is iterated through, **allocating a dynamic array** for each element. The dynamic two-dimensional array is a dynamic one-dimensional array of dynamic one-dimensional arrays!

            ```cpp
            int **array = new int*[10];
            for (int count = 0; count < 10; ++count)
            	array[count] = new int-[5];

            array[9][4] = 3; // The array can then be accessed as usual
            ```

        - With this method, it's possible to create dynamically allocated 2-D arrays that are not rectangular.

            ```cpp
            int **array = new int*[10];
            for (int count = 0; count < 10; ++count)
            	array[count] = new int-[count + 1];
            ```

        - Deallocating a dynamically allocated 2D array using this method would require a loop as well.

            ```cpp
            for (int count = 0; count < 10; ++count)
            	delete[] array[count];
            delete array; // to be done last
            ```

        - Since allocating and deallocating a 2D array is messy, it's often advised to flatten the 2D array into a 1D array

            ```cpp
            // Instead of this:
            int **array = new int*[10]; // allocate an array of 10 int pointers — these are our rows
            for (int count = 0; count < 10; ++count)
                array[count] = new int[5]; // these are our columns
             
            // Do this
            int *array = new int[50]; // a 10x5 array flattened into a single array
            ```

        - To allocate values to a flattened matrix, a simple function can be used :

            ```cpp
            int getSingleIndex(int row, int col, int numberOfColumnsInArray)
            {
                 return (row * numberOfColumnsInArray) + col;
            }
             
            // set array[9,4] to 3 using our flattened array
            array[getSingleIndex(9, 4, 5)] = 3;
            ```

## Pointer to pointer to pointer

- Much like we use pointer parameters to change the actual value of the underlying argument passed in, we can pass a pointer to a pointer to a function and use that pointer to change the value of the pointer it points to. However, were one to require a function to be able to modify what a pointer argument points to, it's better to use **reference**.
- It is also possible to declare a pointer to a pointer to a pointer : `int ***ptrx3;` These can be used to dynamically allocate 3D arrays. However, it's implementation can get complicated.

**Pointer to pointers are only recommended if not other option is available as they are complicated and potentially dangerous.** 

# P.6.15 - An introduction to std::array

In the previous chapters **fixed** and **dynamic** arrays were introduced, both of them with their own sets of positives and negatives.

- Fixed arrays decay into pointers (when passed to a funciton), losing the array length information.
- Dynamic arrays have messy deallocation issues and are challenging to resize without error.

Introduced in C++11, `std::array` provides fixed array functionality that won't decay when passed to a function. 

```cpp
#include <array>
std::array<int, 3> myArray // declare an integer array with length 3
```

- Length of array must be known at compile time
- Unfortunately, unlike with built-in fixed arrays std::array you can not omit the array length when providing an initializer

    ```cpp
    std::array<int, > myArray { 9, 7, 5, 3, 1 }; // illegal, array length must be provided
    std::array<int> myArray { 9, 7, 5, 3, 1 }; // illegal, array length must be provided
    ```

- However, since C++17, one is allowed to omit type and size.

    ```cpp
    std::array myArray { 9, 7, 5, 3, 1 }; // The type is deduced to std::array<int, 5>
    std::array myArray { 9.7, 7.31 }; // The type is deduced to std::array<double, 2>
    ```

- Values can be assigned using an initializer list too

    ```cpp
    std::array<int, 5> myArray;
    myArray = { 0, 1, 2, 3, 4 }; // okay
    myArray = { 9, 8, 7 }; // okay, elements 3 and 4 are set to zero!
    myArray = { 0, 1, 2, 3, 4, 5 }; // not allowed, too many elements in initializer list!
    ```

- The `at()` function for bound checking

    ```cpp
    std::array myArray { 8, 3, 5, 7, 9 };
    myArray.at(1) = 6; // array element 1 is valid, sets array element 1 to value 6
    myArray.at(9) = 2; // array element 9 is invalid, throws an error
    ```

`std::array` will clean up after itself after it goes out of scope.

## Size and sort

- The `size()` function can be used to retrieve the length of `std::array`.

    ```cpp
    std::array myArray { 9.0, 7.2, 5.4, 3.6, 1.8 };
    std::cout << "length: " << myArray.size() << '\n';
    ```

- Since `std::array` doesn't decay to a pointer when passed to a function, the `size()` function will work even when called from within a function.

    ```cpp
    #include <array>
    #include <iostream>

    void printLength(const std::array<double, 5> myArray)
    {
    	std::cout << "length: " << myArray.size() << "\n";
    }
    int main()
    {
    	std::array myArray { 9.0, 7.2, 5.4, 3.6, 1.8 };
    	printLength(myArray);
    }
    ```

    Here `std::array` is passed by **constant** reference, this is to prevent the compiler from making a copy of the `std::array` when passed to function (for performance reasons).

- While `size()` returns array length, `sizeof()` on a native fixed array returns the actual size of the array in memory.
- Since the length is always known, range-based for-loops work with `std::array`.

    ```cpp
    for (int element : myArray):
    	std::cout << element << ' ';
    ```

- A `std::array` can be sorted using `std::sort` present in the `<algorithm>` header

    ```cpp
    #include <algorithm> // for std::sort
    #include <array>
    #include <iostream>
     
    int main()
    {
        std::array myArray { 7, 3, 1, 9, 5 };
        std::sort(myArray.begin(), myArray.end()); // sort the array forwards
    //  std::sort(myArray.rbegin(), myArray.rend()); // sort the array backwards
     
        for (int element : myArray)
            std::cout << element << ' ';
     
        std::cout << '\n';
     
        return 0;
    }
    ```

## Manually indexing `std::array` via size_type

- What's wrong with the code below ?

    ```cpp
    #include <iostream>
    #include <array>
     
    int main()
    {
        std::array myArray { 7, 3, 1, 9, 5 };

        // Iterate through the array and print the value of the elements
        for (int i{ 0 }; i < myArray.size(); ++i)
            std::cout << myArray[i] << ' ';
     
        std::cout << '\n';
     
        return 0;
    }
    ```

    - The `size()` function and the array index parameter operator "**[]**" uses a type called **size_type**, which is defined by the C++ standard as an **unsigned int** type. In the loop, **i** is a signed int, therefore the comparison `i < myArray.size()` and `myArray[i]` have **type** **mismatches**.
    - This being said, **size_type** isn't a global type (like `int` or `std::size_t`) and is defined inside the definition of `std::array`. This would imply, to use **size_type**, one has to prefix it with the full array type. So something like this : `std::array<int, 5>::size_type`
- Correcting the code above we get :

    ```cpp
    #include <array>
    #include <iostream>
     
    int main()
    {
        std::array myArray { 7, 3, 1, 9, 5 };
     
        // std::array<int, 5>::size_type is the return type of size()!
        for (std::array<int, 5>::size_type i{ 0 }; i < myArray.size(); ++i)
            std::cout << myArray[i] << ' ';
     
        std::cout << '\n';
     
        return 0;
    ```

- To make it more readable, one can use `std::size_t` instead

    ```cpp
    for (std::size_t i { 0 }; i < myArray.size(); ++i)
    	std::cout << myArray[i] << ' ';		
    ```

- All of this can be avoided if **range-based for loops (for each)** are used in the 1st place.
- While all of this seems fine, one shouldn't skip over the **wrap-around** issue that looms unsigned integers.

    ```cpp
    // this cause an infinite loop to be created
    for (auto i{ myArray.size() - 1 }; i >= 0; --i)
    	std::cout << myArray[i] << ' ';
    ```

    Going around this would require the for loop to be tweaked:

    ```cpp
    for (auto i { myArray.size() }; i-- > 0; )
    	std::cout << myArray[i];
    ```

    - The condition runs before every iteration, including the first
    - i is `myArray.size() - 1` as i was decremented in the condition.
    - When i is 0 and about to wrap, the condition is no longer true

## Array of struct

- `std::array` isn't limited to numbers as element, it can accommodate every type that can be used in a regular array.

    ```cpp
    #include <array>
    #include <iostream>

    struct House
    {
    	int number{};
    	int stories{};
    	int roomsPerStory{};
    };
    int main()
    {
    	std::array <House, 3> houses{};
    	houses[0] = { 13, 4, 30 };
      houses[1] = { 14, 3, 10 };
      houses[2] = { 15, 3, 40 };
    	for (const auto& house : houses)
    	{
    		std::cout << "House number " << house.number << " has " << (house.stories * house.roomsPerStory) << " rooms\n";
    	}
    	return 0
    }
    // House number 13 has 120 rooms ..
    ```

- Unfortunately, the below will result in an error. Although one can initialize `std::array` as below given its elements are simple types (int / std::string), it doesn't work with types that need multiple values to be createdc.

    ```cpp
    std::array<House, 3> houses{
    	{ 13, 4, 30 },
    	{ 14, 3, 10 },
    	{ 15, 3, 40 }
    }
    ```

- To understand as to why this is the case, consider the snippet below:

    ```cpp
    struct Array
    {
    	int value[3]{};
    }
    int main()
    {
    	Array array{
    			11,
    			12,
    			13
    	};
    	return 0;
    } 
    ```

    This words without issues and so does `std::array` if used with `int` elements. When a `struct` is instantiated, one can initialize all of its members. However, were one to try and create an `Array` of `Houses`. 

    ```cpp
    struct House
    {
        int number{};
        int stories{};
        int roomsPerStory{};
    };
     
    struct Array
    {
        // This is now an array of House
        House value[3]{};
    };
     
    int main()
    {
        // If we try to initialize the array, we get an error.
        Array houses{
            { 13, 4, 30 },
            { 14, 3, 10 },
            { 15, 3, 40 }
        };
     
        return 0;
    }
    ```

    When braces are used inside initializations, the compiler will try to initialize one member of the `struct` for each pair of braces. 

    ```cpp
    // Instead of this 
    Array houses{
        { 13, 4, 30 }, // value[0]
        { 14, 3, 10 }, // value[1]
        { 15, 3, 40 }  // value[2]
    };
    // The compiler does this
    Array houses{
        { 13, 4, 30 }, // value
        { 14, 3, 10 }, // ???
        { 15, 3, 40 }  // ???
    };
    ```

    Circumventing this would require one to tweak the initialization 

    ```cpp
    Array houses{
    	{ {13, 4, 30} , {14, 3, 10} , {15, 3, 40} },//value
    }
    ```

Long story short, `std::array` is a great replacement for built-in fixed arrays. It's efficient and doesn't use any more memory than built-in fixed arrays. The only apparent downsides are:

- one has to explicitly specify the array length
- signed/unsigned issues with size and indexing

# P.6.16 - An introduction to std::vector

- `std::vector` makes working with dynamic arrays safer and easier, making it quite the versatile tool. This allows one to create arrays and have their lengths set at run-time without the need to explicitly allocate and deallocate memory using **new** and **delete**.

    ```cpp
    #include <vector>
    // Unnecessary to specify length at declaration
    std::vector<int> array;
    std::vector<int> array2 = { 9, 7, 5, 3, 1 };
    std::vector<int> array3 { 9, 7, 5, 3, 1 };
    ```

- Array elements can be accessed using the `[]` operator

    ```cpp
    array[5] = 2;
    array.at(5) = 3;
    ```

- One can assign values to `std::vector` using an initializer-list

    ```cpp
    array = { 0, 1, 2, 3, 4 }; // array length is now 5
    ```

- When a vector variable goes out of scope, it **automatically deallocates** memory it controls, helping prevent memory leaks.
- Unlike built-in dynamic arrays which don't know the length of the array they are pointing towards, `std::vector` keeps track of its length. The `size()` function would function on them.
- **Resizing** a `std::vector` is as simple as calling the `resize()` function:

    ```cpp
    #include <iostream>
    #include <vector>

    int main()
    {
    	std::vector<int> array { 0, 1, 2 };
    	array.resize(5);

    	for (int i : array)
    		std::cout<< i << ' '; // 0 1 2 0 0 
    	return 0;
    }
    ```

    - Existing element values are preserved
    - New elements are initialized to the default value for the type (0 for integers).

    ```cpp
    std::vector array { 0, 1, 2, 3, 4 };
    array.resize(3);
    for (int i : array)
    	std::cout<< i << ' '; // 0 1 2
    ```

    - Resizing is computationally **expensive**, and must be used wisely. If one needs a vector to be of a specific size, but isn't aware of its values at the point of declaration, one can create a vector with default elements.

    ```cpp
    std::vector<int> array(5);
    for (int i : array)
    	std::cout << i << ' '; // 0 0 0 0 0 
    ```

- Type **bool** of `std::vector` will compact 8 booleans into a byte.

    ```cpp
    std::vector<bool> array { true, false, false, true, true };
    for (int i : array)
    	std::cout << i << ' '; // 1 0 0 1 1
    ```

# P.6.17 - Introduction to iterators

- **Iterators** are objects designed to traverse through a container (values in an array or characters in a string) providing access to each element along the way.
- Containers may provide different kinds of iterators. An array container offers a :
    - forward iterator that traverses the array in a forward order
    - reverse iterator that does the opposite
- Once the appropriate iterator is created, the programmer can freely traverse and access elements of a certain container.
    - ++ operator is used to move from one element to another
    - * is used to access the current element

## Pointers as an iterator

- Pointers are the simplest kind of iterator, which works for data stored sequentially.

    ```cpp
    #include <array>
    #include <iostream>

    int main()
    {
    	std::array data{ 0, 1, 2, 3, 4};
    	auto begin{ &data[0] };
    	auto end{ begin + std::size(data) };

    	for (auto ptr{ being }; ptr != end; ++ptr)
    		std::cout << *ptr << " "; // 0 1 2 3 4
    ```

- One might be tempted to calculate the end marker using `int* end{ &array[std::size(array)] };`. But this causes undefined behaviour as `array[std::size(array)]` access an element that's off the end of the array. Instead, use this `int* end{ &array[0] + std::size(array) };`

## Standard library iterators and range-based for loops

- Iterating being a common operations, standard libraries offer direct support for iteration. One can simply use `begin()` and `end()` to ask a container for its endpoints.

    ```cpp
    auto begin{ array.begin() };
    auto end{ array.end() };
    ```

- All types that have `begin` and `end` member functions or can be used with `std::being` and `std::end` are usable in range-based for-loops.

    ```cpp
    std::array array{ 1, 2, 3 };
    for (int i : array)
    	std::cout << i << ';
    ```

    - Behind the scenes, the range-based for-loops calls `begin()` and `end()` of the type to iterate over. While `std::array`, C-style fixed array have access to begin and end function , the range base for-loops can be applied on them.
    - This however is not the case for dynamic arrays as there's not `std::end` function.
- Range-base for-loops aren't the only thing that make use of iterators, they're also prominent in `std::sort` and other algorithms.

## Iterator invalidation (dangling iterators)

- Similar to pointers and references, iterators can be left **dangling** if elements being iterated over changes address or are destroyed. When this happens, the iterator is said to be **invalidated**.
- Some operations that modify containers (adding an element to `std::vector`) can cause the elements in the container to change address. Resulting in existing iterators to those elements becoming invalid.

    ```cpp
    #include <iostream>
    #include <vector>

    int main()
    {
    	std::vector v { 1, 2, 3, 4, 5, 6, 7 };
    	auto it{ v.begin() }
    	++it;
    	std::cout << *it << '\n';
    	v.erase(it);
    	++it; // undefined behaviour 
    	std::cout << *it << '\n'; // undefined behaviour 
    ```

# P.6.18 - Introduction to standard library algorithms

The C++ standard library comes with a bunch of handy function which are efficient, tested and maintained. And it's advised to use these functions instead of coding the same from scratch. 

Following are the category of functionality provided by the algorithms in the library:

- **Inspectors** : Used to view data in a container (read only). Eg: searching and counting.
- **Mutators** : Used to modify data in a container. Eg: sorting and shuffling
- **Facilitators** : Used to generate a result based on values of data members. Eg: multiply values, or objects that determine what order pairs of elements should be sorted in.

## Using `std::find` to find element by value and condition

- `std::find` searches for 1st occurrence of a value in a container.
    - It takes 3 parameters,
        - an iterator to the starting element in the sequence.
        - an iterator to the ending element in the sequence
        - a value to search for
    - An iterator is returned pointing tot he element (if found) or the end of the container.
    - Example

        ```python
        #include <algorithm>
        #include <array>
        #include <iostream>
         
        int main()
        {
          std::array arr{ 13, 90, 99, 5, 40, 80 };
         
          std::cout << "Enter a value to search for and replace with: ";  
          int search{};
          int replace{};
          std::cin >> search >> replace;
         
          // Input validation omitted
         
          // std::find returns an iterator pointing to the found element (or the end of the container)
          // we'll store it in a variable, using type inference to deduce the type of
          // the iterator (since we don't care)
          auto found{ std::find(arr.begin(), arr.end(), search) };
         
          // Algorithms that don't find what they were looking for return the end iterator.
          // We can access it by using the end() member function.
          if (found == arr.end())
          {
            std::cout << "Could not find " << search << '\n';
          }
          else
          {
            // Override the found element.
            *found = replace;
          }
         
          for (int i : arr)
          {
            std::cout << i << ' ';
          }
         
          std::cout << '\n';
         
          return 0;
        }
        ```

- Sometimes, one would want to check if there's a value in the container that matches some condition (eg: string that contains a specific substring) rather than an exact value. Here's where `std::find_if` comes into play.
    - It works similarly to `std::Find`, instead of passing a value to search for a callable object (such as a function pointer) is passed.
    - Example

        ```python
        #include <algorithm>
        #include <array>
        #include <iostream>
        #include <string_view>

        bool containsNut(std::string_view str)
        {
        	return (str.find("nut") != std::string_view::npos);
        }
        int main()
        {
        	std::array<std::string_view, 4> arr{ "apple", "banana", "walnut" };
        	auto found{ std::find_if(arr.being(), arr.end(), containsNut) };
        	
        	if (found == arr.end())
        	{
        		std::cout << "No nuts \n";
        	}
        	else
        	{
        		std::cout << *found << "\n";
        	}
        	return 0;
        }
        ```

## Using `std::count` and `std::count_if` to count occurrences

```python
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

bool containsNut(std::string_view, str)
{
	return (str.find("nut") != std::string_view::pos)
}
int main()
{
	std::array<std::string_view, 5> arr{ "apple", "banana", "walnut", "lemon", "peanut" };
	auto nuts{ std::count_if(arr.begin(), arr.end(), containsNut) };
	std::cout << "Counted " << nuts << " nut(s)\n";
  return 0;
}
```

## Using `std::sort` to custom sort and `std::for_each`

- While `std::sort` can perform standard sort, there exists a version that allows one to pass a third parameter and perform the sort as one pleases.
- Example

    ```python
    #include <algorithm>
    #include <array>
    #include <iostream>

    bool greater(int a, int b)
    {
    	return (a > b)
    }
    int main()
    {
    	std::array arr{ 13, 90, 99, 5, 40, 80 };
    	std::sort(arr.begin(), arr.end(), greater);
    	for (int i : arr)
    	{
    		std::cout << i << ' ';
    	}
    return 0;
    }
    ```

    - Inner working

        ```python
        #include <functional> // std::function
        #include <iostream>
        #include <iterator>
        #include <utility>
         
        // sort accepts a comparison function
        void sort(int *begin, int *end, std::function<bool(int, int)> compare)
        {
          for (auto startElement{ begin }; startElement != end; ++startElement)
          {
            auto smallestElement{ startElement };
            
            for (auto currentElement{ std::next(startElement) }; currentElement != end; ++currentElement)
            {
              // the comparison function is used to check if the current element should be ordered
              // before the currently "smallest" element.
              if (compare(*currentElement, *smallestElement))
              {
                smallestElement = currentElement;
              }
            }
         
            std::swap(*startElement, *smallestElement);
          }
        }
         
        int main()
        {
          int array[]{ 2, 1, 9, 4, 5 };
         
          // use std::greater to sort in descending order
          // (We have to use the global namespace selector to prevent a collision
          // between our sort function and std::sort.)
          ::sort(std::begin(array), std::end(array), std::greater{});
         
          for (auto i : array)
          {
            std::cout << i << ' ';
          }
         
          std::cout << '\n';
         
          return 0;
        }
        ```

- `std::for_each` useful when we want to perform the same operation on every element in the list.
- Example

    ```python
    #include <algorithm>
    #include <array>
    #inlude <iostream>

    void doubleNumber(int &i)
    {
    	i *= 2
    }
    main()
    {
    	std::array arr{ 1, 2, 3, 4 };
    	std::for_each(arr.begin(), arr.end(), doubleNumber);
    	for (int i : arr)
    	{
    		std::cout << i << ' ';
    	}
    	std::cout << '\n';
    	return 0;
    }

    # Using range based for-loop
    for (auto& i : arr)
    {
    	doubleNumber(i)
    }
    ```

    - One might ask why prefer `std::for_each` over range based for-loop
        - If auto is not used, it might result in an implicit conversion.
        - One could forget `&` and due to which the array wouldn't be affected.
        - `std::next()` can be used with `std::for_each` which can help advance the pointer one element and begin the loop there.

            `std::for_each(std::next(arr.begin()), arr.end(), doubleNumber); // [1, 4, 6, 8]`

Most algorithms in the algorithms library don't guarantee a particular order of execution. Care ought to be taken when using these algorithms to ensure that functions passed don't assume any particular ordering.

- The following algorithms do guarantee sequential execution: `std::for_each`, `std::copy`, `std::copy_backward`, s`td::move`, and `std::move_backward`.

# P.6.x - Comprehensive quiz

## Summary

- **Arrays** allows one to store and access multiple variables of the same type through a single identifier. Array elements can be accessed using **[]**. They can be initialized using initializer list or uniform initialization.
- **Fixed arrays** ought to have a length that's set at compile time. They usually decay into a pointer when evaluated or passed to a function.
- **Loops**  can be used to iterate through an array. Range based for loops are useful when the array hasn't decayed to a pointer.
- Arrays can be made **multi-dimensional** using multiple indices.
- Arrays can be used to do **C-style** strings.
- Pointers are variables that store the memory address of another variable. The **address-of-operator** (&) can be used to get the address of a variable. The **dereference operator** (*) can be used to get the value that a pointer points at.
- A **null pointer** is a pointer that's pointing at nothing. Pointers can be made null by initializing or assigning the value **nullptr** to them. Dereferencing a null pointer can let all hell break loose. Deleting a null pointer does nothing.
- A pointer to an array doesn't know how large the array it is pointing to is. Therefore **sizeof()** and range-based for-loops won't work.
- The **new** and **delete** operators can be used to dynamically allocate memory for a pointer variable or array. Although it's unlikely to happen, operator **new** can fail if the operating system runs out of memory.
- Make sure to use the array delete (**delete[]**) when deleting an array. Pointers pointing to deallocated memory is called dangling pointers.
- **Failing** to delete dynamically allocated memory can result in memory leaks when the last pointer to the memory goes out of scope.
- Normal variables are allocated from limited memory called the **stack**. Dynamically allocated variables are allocated form a general pool of memory called **heap**.
- A pointer to a **const** value treats the value it's pointing to as **const**.

    ```cpp
    int value{ 5 };
    const int *ptr{ &value };
    ```

- A **const** pointer is a pointer whose value can't be changed after initialization.

    ```cpp
    int value{ 5 };
    int *const ptr{ &value }; 
    ```

- A reference is an alias to another variable. They are declared using an ampaersand (&), but this doesn't mean address-of in this context. References are implicitly **const** - they must be initialized with a value and a new value can't be assigned to them. They can be used to prevent copies from being made when passing data to or from a function.
- The member selection operator (→) can be used to select a member from a pointer to a struct. It combines both, a dereference and normal member access (.).
- Void pointers can point to any type of data. They can't be referenced directly. One can use **static_cast** to convert them back to their original pointer type.
- Pointers to pointers allow us to create a pointer that points to another pointer.
- **std::array**  provides all the functionality of C++ built-in arrays (and more) in a form that won't decay into a pointer. These should be preferred over built-in fixed arrays.
- **std::vector** provides dynamic array functionality, handles its own memory management and remembers its size. These should be preferred over built-in dynamic arrays.