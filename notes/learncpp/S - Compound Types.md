# S - Compound Types

# S.4.4b - An introduction to std::string

- Usage of strings would first need one to use the **#include <string>** header. Once this is done one can define variables of type std::string.

    ```cpp
    std::string myName{"John"}; // initialise myName with string literal "John"
    myName = "Doe"; // assign variable myName the string literal "John"
    ```

- String input/output is pretty much straight forward (when string value is initialized in the program). However, things could get a little weird while accepting user string inputs.
    - When using ">>" operator to extract a string from cin, >> only r**eturns character up to the first whitespace** it encounters.

    ```cpp
    #include <string>
    #include <iostream>
     
    int main()
    {
        std::cout << "Enter your full name: ";
        std::string name;
        std::cin >> name; // this won't work as expected since std::cin breaks on whitespace
     
        std::cout << "Enter your age: ";
        std::string age;
        std::cin >> age;
     
        std::cout << "Your name is " << name << " and your age is " << age << '\n';
     
        return 0;
    }
    // Enter your full name: John Doe 
    // Enter your age: Your name is John and your age is Doe (What the!!!)
    ```

    - Hence, in the example above, only "John" was extracted and saved into the variable "name", while "Doe" remained inside std::cin awaiting the next extraction.
    - And when >> was used to extract age, "Doe" was extracted instead, dismissing one's chance to input age.
- **std::getline()** : used to read a full line of input string

    ```cpp
    int main()
    {
        std::cout << "Enter your full name: ";
        std::string name{};
        std::getline(std::cin, name); // read a full line of text into name
     
        std::cout << "Enter your age: ";
        std::string age{};
        std::getline(std::cin, age); // read a full line of text into age
     
        std::cout << "Your name is " << name << " and your age is " << age << '\n';
     
        return 0;
    }	
    // Enter your full name: John Doe 
    // Enter your age: 22
    // Your name is John Done and your age is Doe 22
    ```

- **Mixing std::cin and std::getline()** may cause unexpected behaviour

    ```cpp
    #include <string>
    #include <iostream>
     
    int main()
    {
        std::cout << "Pick 1 or 2: ";
        int choice{};
        std::cin >> choice;
     
    // std::cin.ignore(32676, 'n');

        std::cout << "Now enter your name: ";
        std::string name{};
        std::getline(std::cin, name);
     
        std::cout << "Hello, " << name << ", you picked " << choice << '\n';
     
        return 0;
    }
    // Pick 1 or 2: 2
    // Now enter your name: Hello, , you picked 2
    ```

    - When using cin, not only does it capture the value, it also captures the newline.
    - So when 2 is entered, what's captured is "2\n". 2 is then extracted towards the variable *choice*, leaving the new line stuck in the input stream.
    - Then when std::getline() goes to read the name, it sees "\n" is already in the stream and assumes an empty string was entered.
    - A good way to go bout this is, after reading a value with std::cin, remove the newline from the stream. 32767 is picked because it's the largest signed value guaranteed to fit in a (16-byte) integer on all platforms.

        ```cpp
        std::cin.ignore(32767, '\n') // ignore up to 32767 characters until \n is removed
        //technically correct way of doing it
        #include <limits>
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore unlimited characters until a \n is removed
        ```

- The **+** **operator** can be used to **concatenate** two strings, while the **+= operator** can be used to **append** a string at the end of an existing string.
- **variable_name.length()** can be used to determine the **length** of a string.
- **Quiz** : Write a program that asks the user to enter their full name and their age. As output, tell the user how many years they’ve lived for each letter in their name (for simplicity, count spaces as a letter).

    ```cpp
    #include <iostream>
    #include <string>

    using namespace std ;

    int main()
    {
        cout << "First name : ";
        string name;
        getline(cin, name);
        
        cout << "Enter age : ";
        float age {};
        cin >> age;
        cin.ignore();
            
        cout << "Last name : ";
        string l_name;
        getline(cin, l_name);
      
        name += l_name;
        
        cout << "You've lived " << age / name.length() << " years for each letter in your name \n";

    }
    ```

# S.4.5 - Enumerated types

- Despite C++ containing quite a few built in datatypes, it might not be sufficient. To this end, C++ contains capabilities that allow programmers to create their own data-types. Such datatypes are called **user-defined** data types.
- **Enumerated type** : simplest user-defined data type, also called **enumeration** or **enum**. It's a data type where every possible value is defined as a symbolic constant (called an **enumerator**). Enumerations are defined using the **enum** keyword.

    ```cpp
    enum Colour
    {
        // Here are the enumerators
        // These define all the possible values this type can hold
        // Each enumerator is separated by a comma, not a semicolon
        COLOUR_BLACK,
        COLOUR_RED,
        COLOUR_BLUE,
        COLOUR_GREEN,
        COLOUR_WHITE,
        COLOUR_CYAN,
        COLOUR_YELLOW,
        COLOUR_MAGENTA, // see note about trailing comma on the last enumerator below
    }; // however the enum itself must end with a semicolon
     
    // Define a few variables of enumerated type Colour
    Colour paint = COLOUR_WHITE;
    Colour house (COLOUR_BLUE);
    Colour apple { COLOUR_RED };
    ```

    - Defining any user-defined data-type doesn't allocate any memory.
    - When a variable of the data-type is defined (variable paint in the above example), memory is allocated at that time.

## Enum scope and value

- Enums without a name are called **anonymous enums**. The names often begin with a capital letter.
- Since enumerators are placed into the same namespace as the enumeration, an enumerator name can't be used in multiple enumerations within the same namespace.
- Consequently, it's common to prefix enumerators (ANIMAL_, or COLOUR_) to prevent naming conflicts and for better code documentation.

```cpp
enum Colour
{
RED,
BLUE, // BLUE is put into the global namespace
GREEN
};
 
enum Feeling
{
HAPPY,
TIRED,
BLUE // error, BLUE was already used in enum Colour in the global namespace
};
```

- Ideally, each enumerator is automatically assigned an integer value based on its position in the enumeration list. First enumerator is assigned 0, and each following enumerator has a value 1 greater than the previous enumerator.
- It is possible to have custom initializations for enumerators.
- When enumerators are assigned the same value, they become non distinct - ANIMAL_HORSE and ANIMAL_GIRAFFE - can be used interchangeably. Better to avoided

```cpp
// define a new enum named Animal
enum Animal
{
    ANIMAL_CAT = -3,
    ANIMAL_DOG, // assigned -2
    ANIMAL_PIG, // assigned -1
    ANIMAL_HORSE = 5,
    ANIMAL_GIRAFFE = 5, // shares same value as ANIMAL_HORSE
    ANIMAL_CHICKEN // assigned 6
};
```

## Enum type evaluation and input/output

- Since enumerated values evaluate to integers, they can be assigned to integer variables. Which also means they can be output as integers.

    ```cpp
    int mypet = ANIMAL_PIG;
    std::cout << ANIMAL_HORSE // 5
    ```

- Errors and work-arounds
    - The compiler will not allow converting integers to an enumerated value. However, one can force its conversion.
    - Additionally, neither will the compiler will let one input an enum using std::cin, a workaround is using "static_cast" yet again.
    - Each enumerator type is considered a distinct type. Consequently, trying to assign enumerators from one enum type to another enum type will cause a compiler error.

        ```cpp
        Animal animal = 5 // compiler error
        // Work around
        Animal animal = static_cast<Animal>(5); // ugly

        Colour colour;
        std::cin >> colour; // compiler error
        // Work around
        int inputcolour;
        std::cin >>  inputcolour;
        Colour colour { static_cast<Colour>(inputColour) };
        ```

- To use a different integer type for enumerators, say to save bandwidth when networking an enumerator, it can be specified at the enum declaration. Additionally, since enumerators aren't used for arithmetic or comparisons, it can be defined as an unsigned integer. If the definition is changed, it should also be reflected in the forward declaration - if one is used.

    ```cpp
    enum Colour : std::uint_least8_t;
    // .. some code .. //
    enum Colour : std::uint_least8_t
    {
    	COLOUR_BLACK,
    	COLOUR_RED,..
    };
    ```

## Purpose of enumerators

- Extremely useful for code-documentation and readability purposes, when a specific pre-defined set of states ought to be defined.

    ```cpp
    // Without enum
    int readFileContents()
    {
        if (!openFile())
            return -1;
        if (!readFile())
            return -2;
        if (!parseFile())
            return -3;
     
        return 0; // success
    } // using magic numbers like this isn’t very descriptive. 
    // An alternative method would be through use of an enumerated type:

    enum ParseResult
    {
    	SUCCESS = 0,
    	ERROR_OPENING_FILE = -1
    	ERROR_READING_FILE = -2
    	ERROR_PARSING_FILE = -3
    }
    ParseResult readFileContents()
    {
        if (!openFile())
            return ERROR_OPENING_FILE;
        if (!readFile())
            return ERROR_READING_FILE;
        if (!parsefile())
            return ERROR_PARSING_FILE;
     
        return SUCCESS;
    }
    // This is much easier to read and understand than using magic number return values. 
    // Furthermore, the caller can test the function’s return value against the 
    // appropriate enumerator, which is easier to understand than testing the return 
    // result for a specific integer value.
    if (readFileContents() == SUCCESS)
    	// doSomething
    else
     // print error message
    ```

- Enumerate types are best used when defining a set of related identifiers.

    ```cpp
    #include <iostream>
    #include <string>
     
    enum ItemType
    {
        ITEMTYPE_SWORD,
        ITEMTYPE_TORCH,
        ITEMTYPE_POTION
    };
     
    std::string getItemName(ItemType itemType)
    {
        if (itemType == ITEMTYPE_SWORD)
            return std::string("Sword");
        if (itemType == ITEMTYPE_TORCH)
            return std::string("Torch");
        if (itemType == ITEMTYPE_POTION)
            return std::string("Potion");
     
        // Just in case we add a new item in the future and forget to update this function
        return std::string("???");
    }
     
    int main()
    {
        // ItemType is the enumerated type we've defined above.
        // itemType (lower case i) is the name of the variable we're defining (of type ItemType).
        // ITEMTYPE_TORCH is the enumerated value we're initializing variable itemType with.
        ItemType itemType = ITEMTYPE_TORCH;
     
        std::cout << "You are carrying a " << getItemName(itemType) << "\n";
     
        return 0;
    }
    ```

## Quiz

- Define an enumerated type to choose between the following monster races: orcs, goblins, trolls, ogres, and skeletons.
- Define a variable of the enumerated type you defined in question 1 and assign it the troll enumerator.

    ```cpp
    enum Monster
    {
    	MONSTER_ORCS,
    	MONSTER_GOBLINS,
    	MONSTER_TROLLS,
    	MONSTER_OGRES,
    	MONSTER_SKELETONS,
    }

    Monster variable = MONSTER_TROLLS
    ```

# S.4.5a - Enum classes

- Although enumerated types are distinct types in C++, they are not type safe.

    ```cpp
    #include <iostream>
     
    int main()
    {
        enum Colour
        {
            RED, // RED is placed in the same scope as Colour
            BLUE
        };
     
        enum Fruit
        {
            BANANA, // BANANA is placed in the same scope as Fruit
            APPLE
        };
    	
        Colour colour = RED; // Colour and RED can be accessed in the same scope (no prefix needed)
        Fruit fruit = BANANA; // Fruit and BANANA can be accessed in the same scope (no prefix needed)
     
        if (colour == fruit) // The compiler will compare a and b as integers
            std::cout << "colour and fruit are equal\n"; // and find they are equal!
        else
            std::cout << "colour and fruit are not equal\n";
     
        return 0;
    }
    ```

    In the above example, both variables "colour" and "fruit" will have the value - as they are assigned enumerator values of integer types that are declared first in their respective enumerations. Consequently, the output will be "colour and fruit are equal". This is undesirable since they aren't intended to be comparable, enumerator classes is a way around this.

- The **enum classes** (also called a **scoped enumerator**), makes enumerations strongly types and scoped. A class is defined using the keyword **class**.

    ```cpp
    #include <iostream>
     
    int main()
    {
        enum class Colour // "enum class" defines this as a scoped enumeration instead of a standard enumeration
        {
            RED, // RED is inside the scope of Colour
            BLUE
        };
     
        enum class Fruit
        {
            BANANA, // BANANA is inside the scope of Fruit
            APPLE
        };
     
        Colour colour = Colour::RED; // note: RED is not directly accessible any more, we have to use Colour::RED
        Fruit fruit = Fruit::BANANA; // note: BANANA is not directly accessible any more, we have to use Fruit::BANANA
    	
        if (colour == fruit) // compile error here, as the compiler doesn't know how to compare different types Colour and Fruit
            std::cout << "colour and fruit are equal\n";
        else
            std::cout << "colour and fruit are not equal\n";
     
        return 0;
    }
    ```

    Normal enumerators are placed in the same scope as the enumeration itself, so it typically can be accessed directly. However, the strong scoping rule of enum class means that all enumerators are considered part of the enumeration. So a scope qualifier ought to be used to access the enumerator ( Colour::RED), helping keep name pollution and conflicts down.

- This being said, enumerations from the same class can be compared

    ```cpp
    int main()
    { // bananl stuff from above
    	Colour colour = Colour::RED;
    	if (colour == Colour::RED)
    		std::cout << "Colour Red";
    	else
    		std::cout << "Not Red";
    }
    ```

- With enum classes, the compiler will no longer implicitly convert enumerator values to integers - a blessing in disguise. However, one can explicitly convert an enum class enumerator to int using static_cast.

    ```cpp
    #include <iostream>
     
    int main()
    {
        enum class Colour
        {
            RED,
            BLUE
        };
     
        Colour colour = Colour::BLUE;
     
        std::cout << colour; // won't work, because there's no implicit conversion to int
        std::cout << static_cast<int>(colour); // will print 1
     
        return 0;
    }
    ```

Just stick to enum class instead of standard enum

# S.4.7 - Structs

C++ allows one to create user-defined aggregate data types. An **aggregate data type** is a data type that groups multiple individual variables together. **Struct** is one of the simplest aggregate data types.

## Declaring, accessing and initialising structs

- Declaration of a **struct** is done using the **struct** keyword. The below example tells the compiler that one is defining a struct named Employee. It has three variables, which are termed **members** (or fields). By convention struct names begin with capital letters.

    ```cpp
    struct Employee
    {
    	short id;
    	int age;
    	double wage;
    }
    ```

- To use the Employee struct, one can simply declare a variable of type employee. In the example below, a variable of type Employee named joe is defined. As with normal variables, defining a struct variable allocates memory to that variable. Multiple variables with the same struct type can be defined.

    ```cpp
    Employee joe;
    Employee todd;
    ```

- When a variable is defined as *Employee joe*, joe refers to the entire struct (which contains member modules). To access these member, a dot (.) called the **member selection operato**r is used.  As with normal variables, struct member variables are not initialized and will typically contain junk (must be manually initialised).

    ```cpp
    Employee joe; // create an Employee struct for Joe
    joe.id = 14; // assign a value to member id within struct joe
    joe.age = 32; // assign a value to member age within struct joe
    joe.wage = 24.15; // assign a value to member wage within struct joe
    ```

- Struct member variables act like normal variables, enabling normal operations on them.

    ```cpp
    int totalAge{ joe.age + frank.age };
     
    if (joe.wage > frank.wage)
        std::cout << "Joe makes more than Frank\n";
    else if (joe.wage < frank.wage)
        std::cout << "Joe makes less than Frank\n";
    else
        std::cout << "Joe and Frank make the same amount\n";
     
    // Frank got a promotion
    frank.wage += 2.50;
     
    // Today is Joe's birthday
    ++joe.age; // use pre-increment to increment Joe's age by 1
    ```

- Initialising structs by assigning values can be performed faster using an **initializer list**. This allows for simultaneous initialisation of all members of the struct.

    ```cpp
    struct Employee
    {
        short id;
        int age;
        double wage;
    };
     
    Employee joe{ 1, 32, 60000.0 }; // joe.id = 1, joe.age = 32, joe.wage = 60000.0
    Employee frank{ 2, 28 }; // frank.id = 2, frank.age = 28, frank.wage = 0.0 (default initialization)
    ```

    If the initialiser list doesn't contain an initialiser for some elements , they are assigned a default value.

- Starting from C++11, it's possible to give a non-static (normal) struct member a default value. However this syntax is incompatible with the initializer list and uniform initialisation syntax.

    ```cpp
    struct Rectangle
    {
        double length{ 1.0 }; // non-static member initialization
        double width{ 1.0 };
    };
     
    int main()
    {
        Rectangle x; // length = 1.0, width = 1.0         (WILL COMPILE)
        x.length = 2.0; // you can assign other values like normal

    		Rectangle y{ 2.0, 2.0 }; // uniform initialization (WILL COMPILE C++14 onwards)
     
        return 0;
    ```

## Structs and functions and nested structs

- A big advantage of using structs over individual variables is that one can pass the entire struct to a function that need to work with members.

    ```cpp
    #include <iostream>
     
    struct Employee
    {
        short id;
        int age;
        double wage;
    };
     
    void printInformation(Employee employee)
    {
        std::cout << "ID:   " << employee.id << "\n";
        std::cout << "Age:  " << employee.age << "\n";
        std::cout << "Wage: " << employee.wage << "\n";
    }
     
    int main()
    {
        Employee joe { 14, 32, 24.15 };
        Employee frank { 15, 28, 18.27 };
     
        // Print Joe's information
        printInformation(joe);
     
        std::cout << '\n';
     
        // Print Frank's information
        printInformation(frank);
     
        return 0;
    }
    ```

- A function can also return a struct, **which is one of the few ways a function can return multiple values**.

    ```cpp
    struct Point3d
    {
    	double x;
    	double y;
    	double z;
    };

    Point3d getZeroPoint()
    {
    	// One can create a variable and return its value
    	Point3d temp { 0.0, 0.0, 0.0 };
    	return tmp;
    }
    Point3d getZeroPoint2()
    {
    	// one can directly return, as the type (Point3d) has
    	// been defined during function declaration, so doing 
    	// it again would be redundant
    	return { 0.0, 0.0, 0.0 };
    }
    Point3d getZeroPoint3()
    {
        // We can use empty curly braces to zero-initialize all
        // members of `Point3d`.
        return {};
    }
    int main()
    {
        Point3d zero{ getZeroPoint() };
     
        if (zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0)
            std::cout << "The point is zero\n";
        else
            std::cout << "The point is not zero\n";
     
        return 0;
    }
    ```

- Structs can contain other structs

    ```cpp
    struct Employee
    {
        short id;
        int age;
        double wage;
    };
     
    struct Company
    {
        Employee CEO; // Employee is a struct within the Company struct
        int numberOfEmployees;
    };
    Company myCompany;
    ```

    In the above example, if one wanted to know the CEO's salary, one should simply use member selection process twice : *myCompany.CEO.wage*;

- One can even use nested initializer for nested structs.

    ```cpp
    struct Employee
    {
        short id;
        int age;
        double wage;
    };
     
    struct Company
    {
        Employee CEO; // Employee is a struct within the Company struct
        int numberOfEmployees;
    };
     
    Company myCompany{{ 1, 42, 60000.0 }, 5 };
    ```

## Struct size and data structure alignment

- Typically the size of a struct is the sum of the size of all its members, ... but not always.
- Consider the employee struct. Assuming that short is 2 bytes, int is 4 bytes and double is 8 bytes, one would expect Employees to be 2+4+8=14 bytes. But is this the case?

    ```cpp
    struct Employee
    {
        short id;
        int age;
        double wage;
    };
     
    int main()
    {
        std::cout << "The size of Employee is " << sizeof(Employee) << "\n";
     
        return 0;
    }
    // The size of Employee is 16
    ```

    It turns out, one can only determine the lower limit of the structure size, and it could very well be larger. In the above example the size of the struct is 16 instead of 14 bytes. This compiler sometimes adds gaps (for performance reasons) into structs called **padding**.

- To **access structs across multiple files** one simply needs to add it to a header file and then add *# include header* at the beginning of which ever file would need to access it.

# S.7.x - Chapter 57 summary and quiz

- std::strings offers an easy and safe was to deal with text strings. String literals are always placed within double quotes.
- Enumerator type lets one define ones own type where all possible values are enumerated. Great for categorizing.
- Enum classes work like enums but offer more type safety and don't pollute the encapsulating namespace quite as much.
- Structs offer a way to group related variables into a single structure and access them using the (.) operator.