# 6 - Object Scope and Conversions

# 6.1 - Compound statements (blocks)

A compound statement (a block or block statement) is a group of zero or more statements treated by the compiler as it were a single statement. 

    int add(int x, int y)
    { // block
        return x + y;
    } // end block
     
    int main()
    { // outer block
     
        // multiple statements
        int value {};
     
        { // inner/nested block
            add(3, 4);
        } // end inner/nested block
     
        return 0;
     
    } // end outer block

Blocks come in real handy with if statements. By default **if statements** executes only a single statement, given that the condition evaluates to true. However, the single statement can be replaced by a block statement. 

    if (value >= 0)
        { // start of nested block
            std::cout << value << " is a positive integer (or zero)\n";
            std::cout << "Double this number is " << value * 2 << '\n';
        } // end of nested block
        else
        { // start of another nested block
            std::cout << value << " is a negative integer\n";
            std::cout << "The positive of this number is " << -value << '\n';
        } // end of another nested block

Block nesting is another possibility - a block within a block within a block 

    if (value >  0)
        { // nesting level 2
            if ((value % 2) == 0)
            { // nesting level 3
                std::cout << value << " is positive and even\n";
            }
            else
            { // also nesting level 3
                std::cout << value << " is positive and odd\n";
            }
        }

The nesting level in the above function is 3. And it's generally advised to not exceed 3 nested blocks.

# 6.2 - User-defined namespaces

Sometimes different files belonging to the same project are bound to have functions that go by the same name and take the same number of arguments. Durning compilation, an error will then be thrown by the linker as it wouldn't be able to resolve the as to which function to point towards. This is where namespaces come into play, it helps resolve this ambiguity.

## Defining namespaces

In C++ this is done using the **namespace** keyword. 

    // foo.cpp
    namespace foo // define a namespace named foo
    {
    	int getSomething(int x, int y)
    	{ // This belongs to namespace foo
    		return x+y
    	}
    }
    
    // goo.cpp
    namespace goo // define a namespace named foo
    {
    	int getSomething(int x, int y)
    	{ // This belongs to namespace goo
    		return x+y
    	}
    }
    
    //main.cpp
    int getSomething(int x, int y);
    int main()
    {
    	std::cout << doSomething(4, 3) << '\n'; // ERROR : unresolved external symbol !!!!
      return 0;
    }

Essentially in the program above the compiler was satisfied by the forward declaration, but the linker could not find a definition for **getSomething()** in the global namespace. This is because both versions of **getSomething()** aren't anymore in the global namespace. 

The compiler can be told which getSomething() function to use via the **scope resolution** or via **using statements**

## The resolution operator (::)

Using the scope resolution operator (::) the compiler can be told in to which namespace should it be scoping for an identifier. 

    #include <iostream>
     
    namespace foo // define a namespace named foo
    {
        // This doSomething() belongs to namespace foo
        int doSomething(int x, int y)
        {
            return x + y;
        }
    }
     
    namespace goo // define a namespace named goo
    {
        // This doSomething() belongs to namespace goo
        int doSomething(int x, int y)
        {
            return x - y;
        }
    }
     
    int main()
    {
        std::cout << foo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace foo
    		std::cout << goo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace goo    
    		return 0;
    }

- **Scope resolution** can be used without any preceding namesapce (eg ::doSomething). In such a case the identifier is looked for in the global namespace.

## Declaring namespaces

- It’s legal to declare namespace blocks in multiple locations (either across multiple files, or multiple places within the same file). All declarations within the namespace are considered part of the namespace.

        // circle.h
        #if !defined(CIRCLE_H)
        #define CIRCLE_H
        namespace basicMath
        {
            inline constexpr double pi{ 3.14 };
        }
        #endif
        
        // growth.h
        #if !defined(GROWTH_H)
        #define GROWTH_H 
        namespace basicMath
        {
            // the constant e is also part of namespace basicMath
            inline constexpr double e{ 2.7 };
        }
        #endif
        
        // main.cpp
        #include "circle.h" // for basicMath::pi
        #include "growth.h" // for basicMath::e
        #include <iostream>
        int main()
        {
            std::cout << basicMath::pi << '\n';
            std::cout << basicMath::e << '\n';
            return 0;
        }

**Do not add custom functionality to the std namespace. This is because has a special rule that prohibits extension of the existing code with user code.** 

- When the code is separated into multiple files, one will have to use namespace in the header and source files

        // add.h
        #if !defined(ADD_H)
        #define ADD_H
        namespace basicMath
        {
            // function add() is part of namespace basicMath
            int add(int x, int y);
        }
        #endif
        
        // add.cpp
        #include "add.h"
        namespace basicMath
        {
            // define the function add()
            int add(int x, int y)
            {
                return x + y;
            }
        }
        
        // main.cpp
        #include "add.h" // for basicMath::add()
        #include <iostream>
        int main()
        {
            std::cout << basicMath::add(4, 3) << '\n';
            return 0;
        }

- Namespaces can be nested within other namespaces, and it's essentially done in two ways.

        // METHOD ONE
        {
            namespace goo // goo is a namespace inside the foo namespace
            {
                int add(int x, int y)
                {
                    return x + y;
                }
            }
        }
        int main()
        {
            std::cout << foo::goo::add() << '\n';
            return 0;
        }	
        
        // METHOD TWO
        namespace foo::goo // goo is a namespace inside the foo namespace (C++17 style)
        {
                int add(int x, int y)
                {
                    return x + y;
                }
        }
         
        int main()
        {
            std::cout << foo::goo::add() << '\n';
            return 0;
        }

- Since typing out the namespace for nested namespace to access their functions can be painful, C++ allows one to create **namespace aliases**

        #include <iostream>
        namespace foo::goo 
        {
                int add(int x, int y)
                {
                    return x + y;
                }
        }
        int main()
        {
        	namespace boo = foo::goo; // boo now refers to foo::goo
         
        	std::cout << boo::add() << '\n'; // This is really foo::goo::add()
         
        	return 0;

- When should one indulge in namespaces?
    - To separate application-specific code from code that might be reusable later.
    - When one writes library code intended for distribution

# 6.3 - Local variables

An identifiers scope determines where an identifier can be accessed in its source code. Scope is a compile time property.

- Local variables have **block scope**, i.e they're in scope from the point of definition to the end of the block they are defined within.

        int main()
        {
            int i { 5 }; // i enters scope here
            double d { 4.0 }; // d enters scope here
         
            return 0;
        } // i and d go out of scope here

- Although, function parameters are not defined inside function body, for typical functions they can be considered to be a part of the scope of the function body block.

        int max(int x, int y) // x and y enter scope here
        {
            // assign the greater of x or y to max
            int max{ (x > y) ? x : y }; // max enters scope here
         
            return max;
        } // x, y, and max leave scope here here

- All variables names within a scope must be unique,
- A **variable's duration** is determines the rules concerning the creation and destruction of the variable.
- Local variables in nested blocks work similarly to local variables in function block

        int main() // outer block
        {
            int x { 5 }; // x enters scope and is created here
         
            { // nested block
                int y { 7 }; // y enters scope and is created here
            } // y goes out of scope and is destroyed here
         
            // y can not be used here because it is out of scope in this block
         
            return 0;
        } // x

- The **linkage** property of an identifier determines whether other declarations of that name refer to the same object or not. Local variables have no linkage, i.e each declaration refers to a unique object.

        int main()
        {
            int x { 2 }; // local variable, no linkage
         
            {
                int x { 3 }; // this identifier x refers to a different object than the previous x
            }
         
            return 0;
        }

- If a variable is only used within a nested block, it should be defined inside that nested bloc
- A variable’s **scope** determines where the variable is accessible. **Duration** defines the rules that govern when a variable is created and destroyed. A variable’s **lifetime** is the actual time between its creation and destruction

# 6.4 - Introduction to global variables

- By convention, global variables are declared at the top of the file,  below the include statements and above any code.

        #include <iostream>
         
        // Variables declared outside of a function are global variables
        int g_x {}; // global variable g_x
         
        void doSomething()
        {
            // global variables can be seen and used everywhere in the file
            g_x = 3;
            std::cout << g_x << '\n';
        }
         
        int main()
        {
            doSomething();
            std::cout << g_x << '\n';
         
            // global variables can be seen and used everywhere in the file
            g_x = 5;
            std::cout << g_x << '\n';
         
            return 0;
        }

    Consider using a g” or “g_” prefix for global variables to help differentiate them from local variables.

- Global variables have file scope (informally called global scope or global namespace scope). This mean they are visible from the point of declaration until the end of the file they are declared within.
- Global variables are create when the program starts and destroyed when it ends. This is called **static duration**, such variables are also called static variables.
- Global initializations

        int g_x; // no explicit initializer (zero-initialized by default)
        int g_y {}; // zero initialized
        int g_z { 1 }; // initialized with value

- Just like local variables, global variables can be constant.

        #include <iostream>
         
        const int g_x; // error: constant variables must be initialized
        constexpr int g_w; // error: constant variables must be initialized
         
        const int g_y { 1 };  // const global variable g_y, initialized with a value
        constexpr int g_z { 2 }; // constexpr global variable g_z, initialized with a value

- Avoid initializing non-constant global variables.

# 6.5 - Variable shadowing (name hiding)

- Shadowing of local variables

        int main()
        { // outer block
            int apples { 5 }; // here's the outer block apples
         
            { // nested block
                // apples refers to outer block apples here
                std::cout << apples << '\n'; // print value of outer block apples
                int apples{ 0 }; // define apples in the scope of the nested block
         
                // apples now refers to the nested block apples
                // the outer block apples is temporarily hidden
                apples = 10; // this assigns value 10 to nested block apples, not outer block apples
                std::cout << apples << '\n'; // print value of nested block apples
            } // nested block apples destroyed
            std::cout << apples << '\n'; // prints value of outer block apples
         
            return 0;
        } //
        
        5
        10
        5

    Where apples not defined in the nested block, the output would have been 5, 10, 10

- Shadowing of global variables

        #include <iostream>
        int value { 5 }; // global variable
         
        void foo()
        {
            std::cout << "global variable value: " << value << '\n'; // value is not shadowed here, so this refers to the global value
        }
         
        int main()
        {
            int value { 7 }; // hides the global variable value until the end of this block
            ++value; // increments local value, not global value
            std::cout << "local variable value: " << value << '\n';
            foo();
            return 0;
        } // local value is destroyed
        
        local variable value: 8
        global variable value: 5

- Once can use :: prefix to over-ride the local variable shadow

        int g_x {1}; // global variable g_x
        
        int main()
        {
            int g_x {10};
            std::cout<< ::g_x <<std::endl;
        }

- In general one must avoid variable shadowing as it can lead to inadvertent errors. Just use different names in case of local shadowing and use "g_" prefix with global variables to avoid in global shadowing.

# 6.6 - Internal linkage

An identifier with internal linkage can be seen and used within a single file, but it's not accessible from other files (not exposed to the linker).

- Global variables with internal linkage are sometimes called **internal variables**.

    // non-constant globals have external linkage by default, but can be given
    // internal linkage via "static" keyword 
    static int g_x;  
    const int g_y { 1 }; // const globals have internal linkage by default
    constexpr int g_z { 2 }; // constexpr globals have internal linkage by default

- Despite the rule that an object of function can't have more than one definition either within a file or a program, internal objects (and functions) that are defined in different files are considered to be independent entities (even if they are referred to by the same name).
- Since linkage is a property of an identifier (not a variable), function identifiers have the same linkage property that variable identifier do.

    add.cpp
    // This function is declared as static, and can now be used only within this file
    // Attempts to access it from another file via a function forward declaration will fail
    static int add(int x, int y)
    {
        return x + y;
    }
    main.cpp
    #include <iostream>
    int add(int x, int y); // forward declaration for function add
    int main()
    {
        std::cout << add(3, 4) << '\n';
        return 0;
    }

# 6.7 - External Linkage

An identifier with external linage can be used both, from within the file it is defined in and other files.

- Functions have external linkage by default, as one can call a function from one file defined in another file.
- Global variables with external linkage are sometimes called **external variables**. To make constant global variables external one can use the **extern** keyword.

        int g_x { 2 }; // non-constant globals are external by default
         
        extern const int g_y { 3 }; // const globals can defined as extern, making them external
        // constexpr globals can defined as extern, making them external (but this is useless, 
        // see the note in the next section)
        extern constexpr int g_z { 3 }; 
         
        int main()
        {
            return 0;

- TO use external global variable that has been defined in another file, one must place a forward declaration for the global variable in files wishing to access the variable.

        // a.cpp
        int g_x { 2 }; // non-constant globals have external linkage by default
        extern const int g_y { 3 }; // this extern gives g_y external linkage
        
        // main.cpp
        extern int g_x; // this extern is a forward declaration of a variable named g_x that is defined somewhere else
        extern const int g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else
         
        int main()
        {
            std::cout << g_x; // prints 2
            return 0;
        }

- **Warnings**
    - To define uninitialized non-const global variable, do not use the extern keyword, else C++ will assume that a forward declaration is trying to be made.
    - Although constexpr variables can be given external linkage, they can not be forward declared, so there is no value in giving them external linkage.
- Function forward declarations don’t need the extern keyword - the compiler is able to tell whether you’re defining a new function or making a forward declaration based on whether you supply a function body or not.

        // non-constant 
        int g_x; // variable definition (can have initializer if desired)
        extern int g_x; // forward declaration (no initializer)
         
        // constant
        extern const int g_y { 1 }; // variable definition (const requires initializers)
        extern const int g_y; // forward declaration (no initializer)

- File scope and global scope

        // global.cpp
        int g_x { 2 }; // non-constant globals have external linkage by default
        
        // main.cpp
        extern int g_x; // this extern is a forward declaration of a variable named g_x that is defined somewhere else
        int main()
        {
            std::cout << g_x; // prints 2
            return 0;
        }

    - Variable "g_x" has file scope within global.cpp - can be used from the point of definition until the end of the file.
    - Inside main.cpp, the forward declaration of "g_x" also has file scope - used from the point of declaration until end of the file.
    - Long story short, “file scope” is more often applied to global variables with internal linkage, and “global scope” to global variables with external linkage (since they can be used across the whole program, with the appropriate forward declarations).
    - Initialization of global variables happens as a part of program startup and it essentially happens in two phases:
        - Phase 1 : **static initialization**, global variables with constexpr initializers are initialized to assigned values. Additionally, global variables without initializers are zero-initialized.
        - Phase 2 : **dynamic initialization**,  global variables with non-contsexpr initializers are initialized. Below is an example of non-constexpr

            int init()
            {
                return 5;
            } 
            int g_something{ init() }; // non-constexpr initialization

    - Summary

        // External global variable definitions:
        int g_x;                       // defines non-initialized external global variable (zero initialized by default)
        extern const int g_x{ 1 };     // defines initialized const external global variable
        extern constexpr int g_x{ 2 }; // defines initialized constexpr external global variable (
         
        // Forward declarations
        extern int g_y;                // forward declaration for non-constant global variable
        extern const int g_y;          // forward declaration for const global variable
        extern constexpr int g_y;      // not allowed: constexpr variables can't be forward declared

    # 6.8 - Global constants and inline variables

    Sometimes one would want to access throughout ones code (across multiple files). Instead of redefining constants in every file, it's better to declare it at a central location and use them where ever needed.

    ## Global constants as internal variables

    The most common way to effectuate this would be:

    - Create a header file to hold these constants
    - Define a namespace in the header file
    - Add all constants into the namespace
    - #include header file wherever needed.

        heade
        #ifdef CONSTANTS_H
        #define CONSTANS_H
        namespace constants
        {
        	// constants have internal linkage by default
          constexpr double pi { 3.14159 };
          constexpr double avogadro { 6.0221413e23 };
          constexpr double my_gravity { 9.2 }; // m/s^2 -- gravity is light on this planet
          // ... other related constants
        }
        #endif
        }
        main.cpp
        int main()
        {
            std::cout << "Enter a radius: ";
            int radius{};
            std::cin >> radius;
         
            std::cout << "The circumference is: " << 2 * radius * constants::pi;
        }

    ## Global constants as external variables

    The above method has a few potential downsides.  Every time constants.h gets #included into a different code file each of it contents are copied into the included code file.So, if constants get included in 20 different files, its duplicated 20 times. This introduces two challenges:

    - Changing a single constant value would require recompiling every file that includes the constants header, which can lead to lengthy rebuild times for larger projects.
    - If the constants are large in size, it can occupy a lot of memory

    One way of avoiding this would be by turning constants to external variables, by doing so we'll have a single variable shared across all files. So one can define the constants in a .cpp file and insert all its headers into a header file.

        // constants.cpp
        namespace constants
        {
            // actual global variables
            extern const double pi { 3.14159 };
            extern const double avogadro { 6.0221413e23 };
            extern const double my_gravity { 9.2 }; // m/s^2 -- gravity is light on this planet
        }
        
        // constants.h
        #ifndef CONSTANTS_H
        #define CONSTANTS_H
         
        namespace constants
        {
            // since the actual variables are inside a namespace, the forward declarations need to be inside a namespace as well
            extern const double pi;
            extern const double avogadro;
            extern const double my_gravity;
        }
         
        #endif
        
        // main.cpp
        #include "constants.h" // include all the forward declarations
         
        int main()
        {
            std::cout << "Enter a radius: ";
            int radius{};
            std::cin >> radius;
         
            std::cout << "The circumference is: " << 2 * radius * constants::pi;
        }

    This ensures that symbolic constants get instantiated only once (in constants.cpp), instead of once every time constant.h is #included. Any changes made to constants.cpp would only require recompiling constants.cpp

    This way of defining constant however does come with its own set of caveats:

    - The constants defined in .cpp file are now compile-time constants only within the file within which they are actually defined, and not anywhere else they are used. Hence, outside of constants.cpp they can't be used anywhere that required a compile-time constant
    - The compiler may not be able to optimize these as much

    ## Global constants as inline variables

    C++17 introduced a new concept called **inline variables**. These are variables that are allowed to be defined in multiple files without violating the "one definition rule". This being said, such variables have two restrictions to that must be respected:

    - All definitions of the inline variable must be identical.
    - The inline variable definition must be present in every file that uses the variable.

        // constants.h
        #ifndef CONSTANTS_H
        #define CONSTANTS_H
         
        // define your own namespace to hold constants
        namespace constants
        {
            inline constexpr double pi { 3.14159 }; // note: now inline constexpr
            inline constexpr double avogadro { 6.0221413e23 };
            inline constexpr double my_gravity { 9.2 }; // m/s^2 -- gravity is light on this planet
            // ... other related constants
        }
        #endif
        
        // main.cpp
        #include "constants.h"
         
        int main()
        {
            std::cout << "Enter a radius: ";
            int radius{};
            std::cin >> radius;
         
            std::cout << "The circumference is: " << 2 * radius * constants::pi;
        }

    **One can include constants.h into as many files as one wants, but these variables will only be instantiated once and shared across all code files.**

    # 6.9 - Why global variables are evil?

    ## Why non-const global variables are evil?

    - Their value can be changed by any function that calls it. And there's no easy way to know that this will happen, making the program's state unpredictable.

            int g_mode; // declare global variable (will be zero-initialized by default)
             
            void doSomething()
            {
                g_mode = 2; // set the global g_mode variable to 2
            }
             
            int main()
            {
                g_mode = 1; // note: this sets the global g_mode variable to 1.  It does not declare a local g_mode variable!
             
                doSomething();
             
                // Programmer still expects g_mode to be 1
                // But doSomething changed it to 2!
             
                if (g_mode == 1)
                    std::cout << "No threat detected.\n";
                else
                    std::cout << "Launching nuclear missiles...\n";
             
                return 0;
            }	

    - During debugging, one will need to scour through all files which has made a call to the variable. Hence, it'd be wise to declare the variable as close as possible to the file that's calling it.
    - Global variables make programs modular and less flexible. A function that only uses its parameters has no side-effects and is perfectly module. Additionally, a void using global variables in from important decision point (use in a conditional statement)

    Long story short, use local instead of global variables wherever possible. 

    ## Global variable usage and precautions

    Any use of global variables should meet the following two criteria :

    - The variables should only represent one thing in the program
    - Its use must be ubiquitous throughout the program.

    Protecting oneself from global destruction

    - Prefix, all non-namespaced global variables with "g" or "g_", or put them in a namespace

            // NOT THIS
            constexpr double gravity { 9.8 }; // unclear if this is a local or global variable from the name
            int main()
            {
                return 0;
            }
            
            // THIS
            namespace constants
            {
                constexpr double gravity { 9.8 };
            }
            int main()
            {
                return 0;
            }

    - Encapsulating global variables: First make the variable static so it can only be directly accessed from the file it's declared within. Second provide external global "access functions" to work with variable. These functions can ensure proper usage is maintained. Additionally, updating the implementation would only require one update the access function and not all instance of global variable usage amongst files.

            // NOT THIS
            namespace constants
            {
                extern const double gravity { 9.8 }; 
            // has external linkage, is directly accessible by other files
            }
            
            // THIS
            namespace constants
            {
                static const double gravity { 9.8 }; // has internal linkage, is accessible only by this file
            }
             
            double getGravity() // this function can be exported to other files to access the global outside of this file
            {
                // We could add logic here if needed later
                // or change the implementation transparently to the callers
                return constants::gravity;
            }

    - If global variables ought to be used within stand-alone functions, pass it as an argument. This way, were one to decide to change the value or use  a different one, the argument can be varied.

            // NOT THIS 
            namespace constants
            {
                constexpr double gravity { 9.8 };
            }
            // This function is only useful for calculating your instant velocity 
            // based on the global gravity
            double instantVelocity(int time)
            {
                return constants::gravity * time;
            }
            int main()
            {
                std::cout << instantVelocity(5);
            }
            
            // THIS 
            namespace constants
            {
                constexpr double gravity { 9.8 };
            }
             
            // This function can calculate the instant velocity for any gravity 
            // value (more useful)
            double instantVelocity(int time, double gravity)
            {
                return gravity * time;
            }
            int main()
            {
                std::cout << instantVelocity(5, constants::gravity); // pass our constant to the function as a parameter
            }

    - What's the best naming prefix for a global variable ?

        //

# 6.10 - Static local variables

- Global variables have static durations, i.e. they are created when program starts and are destroyed when the program ends
- The **static** keyword gives a global identifier **internal linkage**, which means the identifier can only be used in the file within which it's defined.
- Local variables have static duration : created at the point of definition and destroyed when the block is exited.
- **static** keyword changes local variable duration from **automatic** to **static**. The code snippet below shows the difference between variables with static and automatic durations:

        // BY DEFAULT (AUTOMATIC)
        void incrementAndPrint()
        {
            int value{ 1 }; // automatic duration by default
            ++value;
            std::cout << value << '\n';
        } // value is destroyed here
         
        int main()
        {
            incrementAndPrint();  // 2
            incrementAndPrint();  // 2
            incrementAndPrint();  // 2
            return 0;
        }
        
        // STATIC
        void incrementAndPrint()
        {
        		// static duration via static keyword.  This initializer is only 
            // executed once.
            static int s_value{ 1 };    ++s_value;
            std::cout << s_value << '\n';
        } // s_value is not destroyed here, but becomes inaccessible because 
          // it goes out of scope
        int main()
        {
            incrementAndPrint(); // 2
            incrementAndPrint(); // 3
            incrementAndPrint(); // 4
            return 0;
        }

    Just like we use “g_” to prefix global variables, it’s common to use “s_” to prefix static (static duration) local variables

- One of the most common uses for static duration local variables is for unique ID generators. Imagine a program where one has similar objects (a game where you’re being attacked by many zombies). If a defect is noticed, it'd be near impossible to pin-point as to which object is the cause, this however is not the case if each object is given a unique identifier.

        int generateID()
        {
            static int s_itemID{ 0 };
            return s_itemID++; // makes copy of s_itemID, increments the real s_itemID, then returns the value in the copy
        }

- Static variable offer some of the benefits of global variables (don't get destroyed until end of program), while limiting their visibility to block scope (variable cannot be accessed outside the block). This makes them safe for use even if one changes their values regularly.

# 6.11 - Scope, duration and linkage summary

Since the cocepts scope, linkage and summary can often get confusing, this lesson will focus on summarizing each of these concepts in a effort to alivate the confusion.

## Scope summary

An identifier's scope determines if it can be accessed within the source code. 

- Variables with **llocal/block scope** can only be accessed within the block they are declared within. This includes:
    - Local varaiables
    - Function paarameters
    - User-defined type definitions ( like enums and classes) declared a block
- Varaiables and functions with **global scope / file scope** can be accesssed anywhere in the file, This includes:
    - Global variables
    - Functions
    - User-defined type defintions (such as enums and classes) declared inside a namespace or in the global space.

## Duration summary

A variable's duration determines when it's created and destroyed.

- Variables with **automatic duration** are created at the point of definition and destroyed when the block they're a part of is exited. This includes:
    - Local variables
    - Function parameters
- Variables with **static durations** are created when the program begins and destroyed when it ends. This includes:
    - Global variables
    - Static local variables
- Variables with **dynamic duration** are created and destroyed by the programmer at request.
    - Dynamically allocated variables

## Linker summary

An identifier's linkage determines whether multiple instance of the identifier refers to the same identifier or not.

- An identifier with **no linkage** means the identifier only refers to itself, This includes:
    - Local variables
    - User-defined type definition (such as enums and classes) defined inside a block
- An identifier with **internal linkage** can be accessed anywhere within the file it's declared within. This includes:
    - Static global variables (initialized or uninitialized)
    - Static functions
    - Const global variables
    - Functions declared within an un-named namespace
    - User-defined type definitions (such as enums and classes) declared inside an unnamed namespace.
- An identifier with **external linkage** can be accessed anywhere within the file it's declared, or any other files. This includes:
    - Functions
    - Non-const global variables (initialized or uninitialized)
    - Extern const global variables
    - Inline const global variables
    - User-defined type definitions (such as enums and classes) declared inside a namespace or in the global space.

Identifiers with external linkage will generally cause a duplicate definition linker error if the definitions are compiled into more than one .cpp file (due to the violation of the one-definition rule). There are a few exceptions to this rule, types, templates, and inline functions and variables). Additionally, functions have external linkage by default. They can be made **static** keyword. 

The chart below summarizes variable scope, duration and linkage.

![6%20Object%20Scope%20and%20Conversions/Untitled.png](6%20Object%20Scope%20and%20Conversions/Untitled.png)

Forward declarations can be used to access a function or variable in another file. 

![6%20Object%20Scope%20and%20Conversions/Untitled%201.png](6%20Object%20Scope%20and%20Conversions/Untitled%201.png)

When used as part of the identifier declaration, the **static** and **extern** keywords are called **storage-class** specifiers. C++ supports 4 active storage class specifier:

![6%20Object%20Scope%20and%20Conversions/Untitled%202.png](6%20Object%20Scope%20and%20Conversions/Untitled%202.png)

# 6.12 - Using statements

If one were to use a the standard library and its functionalities, the statements ought to be prefixed by "std::", which could get repetitive and annoying, Using statements helps simply things.

- **Using declarations** helps simplify things.

        #include <iostream>
        int main()
        {
           using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout
           cout << "Hello world!"; // so no std:: prefix is needed here!
         
           return 0;
        } // the using declaration expires here

    The "using declaration using std::cout" tell the compiler that one is going to use the object **cout** from the **std namespace.** So whenever it sees cout it will assume that std::cout was meant. In case of name collisions, std::cout will be preferred over others.

- The **using directive** is another way to simply the use of library functionalities

        #include <iostream>
        int main()
        {
           using namespace std; // this using directive tells the compiler that we're using everything in the std namespace!
           cout << "Hello world!"; // so no std:: prefix is needed here!
           return 0;
        }

    The "using directive using namespace std;" tells the compiler that we want to use everything in the std namespace, so if the compiler finds a name it doesn't recognize, it will check the **std namespace**. 

- Limiting scope of using **declarations** and **directives**.
    - Using **declarations** and **directives** within a block would apply the using statement only within that block. This reduces the chances of naming collisions
    - Introducing using **declarations** and **directives** with a global scope could increase the chances of naming collisions to occur.

**Prefer the use of directives (locally) than declarations**

- Cancelling or replacing a **using** statement

    int main()
    {
        using namespace Foo;
     
        // there's no way to cancel the "using namespace Foo" here!
        // there's also no way to replace "using namespace Foo" with a different using statement
     
        return 0;
    } // using namespace Foo ends here
    
    // Limiting the scope is the best way to cancel out using statements. 
    int main()
    {
        {
            using namespace Foo;
            // calls to Foo:: stuff here
        } // using namespace Foo expires
     
        {
            using namespace Goo;
            // calls to Goo:: stuff here
        } // using namespace Goo expires
     
        return 0;
    }

# 6.13 - Typedefs and type aliases

**Typedefs or Type definition** allow the programmer to create an alias for a data type, and use alias name instead of actual type name. 

    typedef double distance_t; // define distance_t as an alias for type double
    // the following two arguments are equivalent
    double howFar;
    distance_t howFar;

- By convention **typedef** names are delared using a "_t" suffix. This helps indicate that the identifier represents a type, and not a variable or a function.
- Typedefs and type aliases follow the same scoping rules as variables. Were they to be placed within a function, they can only be accessed by it. And were they to be placed in the global scope, all functions would be able to access them.

This being said typedef comes with its own list of issues:

- Easy to forget the syntax : typedef distance_t double; or **typedef double distance_t**;
- Syntax for typedefs get ugly with more complex types.

## Type aliases

**Type aliases** helps address the aforementioned issues of **typedefs** by suggesting an improved syntax

    typedef double distance_t; // defines distance as an alias for type double
    using distance_t = double // difine distance_t as an alias for type double

Type aliases are more cleaner and must be the one preferred.

- Type aliases allows for easier code maintenance. If one would want to change they type of variables across variables (say student id), the change has to only be effectuated at one place. However this must be done with caution as changing varaible types could result in unexpected behaviour (int to floating point division)
- Type aliases also come into good use during cross platform use of a similar type. Eg: Some platforms an **int** is 2 bytes while other it's 4 bytes, so cross platfrom programs use type aliases such as int8_t, uint8_t, int16_t etc.

In order to ensure that aliased type resolves to a type of the right size, type aliases are used in conjunction with preprocessor directives. On machines where integers are only 2 bytes, INT_2_BYTES can be defined else it moves onto the second set of declarations. 

- This is exactly how the fixed width integers (like int8_t) that were introduced in C++11
- This is also where the issue with int8_t being treated as a char comes from -- int8_t is a type alias of char, and thus is just an alias for a char rather than being a unique type

    #ifdef INT_2_BYTES // int is 2 bytes
    using int8_t = char; // 1 byte
    using int16_t = int; // 2 bytes
    using int32_t = long;
    #else // where int is 4 bytes
    using int8_t = char; // 2 bytes
    using int16_t = short; // 4 bytes
    using int32_t = int;
    #endif

![6%20Object%20Scope%20and%20Conversions/Screen_Shot_2020-02-04_at_6.44.34_AM.png](6%20Object%20Scope%20and%20Conversions/Screen_Shot_2020-02-04_at_6.44.34_AM.png)

In advanced C++, one will often have to deal with complex types. 

    std::vector<std::pair<std::string,int> > pairlist;
    bool hasDuplicates(std::vector<std::pair<std::string,int> > pairlist)
    {
    }
    // Using type aliases
    using parlist_t = std::vector<std::pair<std::string,int> > ;
    pairlist_t pairlist;
    bool hasDuplicates(pairlist_t, pairlist)
    {
    }

Soooo much better

[Quiz question 1](https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/)

    using error_t = int;
    error_t printData()

# 6.14 - The auto keyword

    double d{ 5.0 };

If C++ alrady knows 5.0 is a double literal, why explicity specify it? Wouldn't it be much less hassle if it were possible to tell the variable to assume the proper type based on the value one is initialising it with.

- **Type inference** for initialized variables : when intializing variables, the **auto** keyword can be used in place of the **type** (int, char double etc), requesting the compiler to infer the variable's type.

        // with variables
        auto d{ 5.0 }; // 5.0 is a double literal, so d will be type double
        auto i{ 1 + 2 }; // 1 + 2 evaluates to an int, so i will be type int
        
        // with function return values
        int add(int x, int y)
        { 
        	return x+y;
        }
        int main()
        {
        	auto sum { add(5, 6) };
        	return 0;
        }

- **Type inference** for C++14 : the **auto** keyword has been extended to able to deduce a function's return type with C++14.  This being said, it's best to avoid using type inference for function return types.

        auto add(int x, int y)
        {
        	return x+y;
        }	

- **Trailing return type** : auto can be used to declare functions using a trailing return syntax, where the return type is specified after the funciton prototype.

        int add(int x, int y); // instead of this
        auto add(int x, int y) -> int // this

- **Type inference** for function parameter type :

        void addAndPrint(auto x, auto y) // only valid starting in C++20
        {
            std::cout << x + y;
        }
         
        int main()
        {
            addAndPrint(2, 3); // int
            addAndPrint(4.5, 6.7); // double

    Starting in C++20, the auto keyword can be used as a shorthand way to create function templates, so the above code will compile and run

# 6.15 - Implicit type conversion (coercion)

Initially, we have seen that a variable is stored as a sequence of bits, and its data type tell the compiler how to interpret the bits. Say one has been given the code snippet below 

    float f { 3 } ;

In this case the compiler can't simply copy int value 3 into float variable f. Instead it first needs to convert the integer value 3 to floating point number which can then be assigned to float variable f

The process of converting a value from one data-type to another is called **type conversion**. Type conversion can happen in many different case:

- When assigning or initializing a variable with a value of a different data type.

        double d{ 3 }; // initialize double variable with integer value 3
        d = 6; // assign double variable the integer value 6

- When passing a value to a function where the function parameter is of a different data type.

        vvoid example (long l)
        {}
        example(3) // pass integer value 3 to a function expecting a long parameter

- When returning a value from a function where the function return type is of a different data type.

        float doSomething()
        { return 3.0 // Return double value 3.0 back to caller through float return type
        }

- Using a binary operator with operands of different types

        	double division { 3.0/4 }; // division with a double and an integer

## Implicit type conversion

Also called automatic type conversion,, is when the compiler automatically transforms one datatype to another. In the examples above, implicit conversion will be used. Implicit conversions are of two types : promotions and conversions.

- **Numeric promotion** : when one fundamental data type is converted into a value of a larger fundamental data type from the same family.

        long l{ 64 }; // widen the integer 64 into a long
        double d{ 0.12f }; // promote the float 0.12 into a double

- While numeric promotion cover any type of promotion, there exits two other types of terms with specific meanings:
    - **Integral promotion** : involves conversion of integer types narrower than int (bool, char, unsigned char ..) to an int or unsigned int.
    - **Floating point promotion** : involves conversion of a float to a double
- **Numeric conversions** : When a value is converted from a large type to a similar smaller type, or between different types. Unlike promotions which are always safe, conversion may or may not result in loss of data. Hence code with implicit conversion often causes compiler to display a warning.

        double d{ 3 }; // convert integer 3 to a double (between different types)
        short s{ 2 }; // convert integer 2 to a short (from larger to smaller type within same type family)
        
        int main()
        {
            int i{ 30000 };
            char c = i; // chars have range -128 to 127
         
            std::cout << static_cast<int>(c);
         
            return 0; // 48
        }

- Conversions that could cause loss of information (float to int) are called **narrowing conversions**. Since information loss is generally undesirable, brace initializations don't allow narrowing conversions.

        double d{ 10.0 };
        int i{ d }; // Error: A double can store values that don't fit into an int

## Evaluating arithmetic expressions

When evaluating expressions, the compiler breaks each expression down into individual subexpressions. The arithmetic operators require their operands to be of the same type. To ensure this, the compiler uses the following rules. 

- If an operand is an integer that is narrower than int, it'll undergo integral promotion to int or unsigned int.
- If operands still don't match, the compiler finds the highest priority operand and implicitly converts the other operands to match.
- The priority of operands are as follows:
    - long double (highest)
    - double
    - float
    - unsigned long long
    - long long
    - unsigned long
    - long
    - unsigned int
    - int (lowest)
- One can see the arithmetic conversion take place via the **typeid** operator, which can be used to show the resulting type of an expression.

        #include <iostream>
        #include <typeinfo> // for typeid()
         
        int main()
        {
            short a{ 4 };
            short b{ 5 };
            std::cout << typeid(a + b).name() << " " << a + b << '\n'; // show us the type of a + b
        																															 // int 9
            return 0;
        }

    Since shorts are integers, they are promoted to ints before being added.

        #include <iostream>
        #include <typeinfo> // for typeid()
         
        int main()
        {
            double d{ 4.0 };
            short s{ 2 };
            std::cout << typeid(d + s).name() << ' ' << d + s << '\n'; // show us the type of d + s
        																															 // double 5.0
            return 0;
        }

    In this case, the short undergoes integral promotion to an int. However, the int and double still do not match. Since double is higher on the hierarchy of types, the integer 2 gets converted to the double 2.0.

- However conversions can cause some interesting issues

        std::cout << 5u - 10; // 5u means treat 5 as an unsigned integer : 4294967291

    In this case, the signed integer 10 is promoted to an unsigned integer (which has higher priority), and the expression is evaluated as an unsigned int. Since -5 can’t be stored in an unsigned int, the calculation wraps around, and we get an answer we don’t expect. Another reason to **avoid unsigned integers**.

# 6.16 - Explicit type conversion (casting) and static_cast

Say we have float f = 10/4, since both operands are integers, not implicit conversion will take place, resulting in f = 2.0. Of course this can be avoided by manually modifications such as f = 10.0/4.0. However, manual intervention wouldn't be possible were we dealing with variables. 

    int i1 { 10 };
    int i2 { 4 };
    float f { i1 / i2 }; 

Type casting helps resolve the problem. In C++, there exists 5 different types of casts : C-style casts, static casts, const casts, dynamic casts, and reinterpret casts. The latter four are sometimes referred to as **named cast**.

**Avoid const casts and reinterpret casts unless you have a very good reason to use them.**

- **C-style cast**

        int i1 { 10 };
        int i2 { 4 };
        float f { float(i1) / i2 }; // in C it is "float f { (float)i1 / i2 };"

    This cast can perform a variety of different conversions depending on the context. As a result, this cast is at risk of being inadvertently misused and not producing the expected behaviour, something which is easily avoidable by using the C++ casts instead.

- **Static cast**

    The **static_cast** operator is used to convert a value of one type to a value of another type. 

        char c { 'a' };
        std::cout << c << ' ' << static_cast<int>(c) << '\n'; // prints a 97

    The operator takes a single value as input and outputs the same value converted to the type specified in the angled brackets. 

        int i1 { 10 };
        int i2 { 4 };
        float f { static_cast<float>(i1) / i2 }; // in C it is "float f { (float)i1 / i2 };"

    The main **advantage** of static_cast is that it provides compile time type-checking, making it harder to make an inadvertent error. **Favor static_cast when you need to convert a value from one type to another type**.

    - Additionally, static_cast can be used to make implicit type conversions clear

            int i { 48 };
            char ch = i; // implicit conversion
            
            int i { 48 };
            // explicit conversion from int to char, so that a char is assigned to variable ch
            char ch = static_cast<char>(i);

        Here one explicitly tells the complier that one is aware of any anomalous behaviour that might result in the during the conversion.

# 6.17 - Unnamed and inline namespaces

## Unnamed namespaces

An **unnamed namespace** is a namespace that is defined without a name 

    #include <iostream>
    namespace // unamed namespace
    {
    		void doSomething() // can only be accessed in this file
    		{
    				std::cout << "v1\n";
    		}
    }
    int main()
    {
    		doSomething(); // one can call doSomething() without a namespace prefix
    		return 0;
    }

- A function defined within an unnamed namespace is tantamount to declaring a function within the parent namespace (which in the case above is the global namespace). That's why *doSomething()* can be called from anywhere.
- **Advantage** : the contents of an unnamed namespace is treated as if they has internal linkage, which means that the contents of an unnamed namespace can't be seen outside of the file within which the namespace is declared. This is tantamount to static functions.
- **Use** : When one has a lot of content that ought to stay local to a file, a unnamed namespace is used to instead of individually marking all declarations as **static**.

## Inline namespace

Consider the following example: 

    void doSomething()
    {
    		std::cout << "v1\n";
    }
    int main()
    {
    		doSomething();  // prints v1
    		return 0;
    }

Pretty straight forward. Say now you put together a newer more efficient version of doSomething, you could do one of two thing:

- Effectuate changes directly to the current function - increasing the risk of break the code during compile and run, due to added functionalities
- Make a copy of the function with a different version name. But over course of multiple changes one could end up with functions having approximately the same name :  doSomething_v1(), doSomething_v2()...

Or one can simply use the inline namespace

    inline namespace v1 // declare an inline namespace named v1
    {
        void doSomething()
        {
            std::cout << "v1\n";
        }
    }
     
    namespace v2 // declare a normal namespace named v2
    {
        void doSomething()
        {
            std::cout << "v2\n";
        }
    }
     
    int main()
    {
        v1::doSomething(); // calls the v1 version of doSomething()
        v2::doSomething(); // calls the v2 version of doSomething()
        doSomething(); // calls the inline version of doSomething() (which is v1)
        return 0;
    }

- In the above example, callers to doSomething() will get v1 of the function.
- Callers who want to explicitly use v2 of the function can use the "v2" before the resolution operator.

Preserving existing program, while allowing interested users to take advantage of the newer functionality.

# 6.x - Summary and quiz

- **Compound statement** or **block** : a group of zero or more statements that is treated by the compiler as if it were a single statement. Blocks begin with '{' and ends with '}' and the statements go in-between.
- **User-defined namespaces** : namespaces defined by the user. Namespaces provided by C++ (such as the *global namespace*) or by libraries (such as *namespace std*) don't come under this category.
- **Scope resolution operator** (::) : tells the compiler that the identifier present by the right-hand operand should be looked for in the scope of the left-hand operand. Global namespace is assumed in case left hand operand is not specified.
- **Local variables** :
    - Have **block scope**, i.e they are in-scope from the point of definition to the end of the block they are defined within.
    - Have **automatic storage duration**, i.e created at the point of definition and destroyed at the end of the block they are defined in.
- A name declared in a nested block can **shadow** or **name hide** an identically named variable in an outer block. Avoid this
- **Global variables** :
    - Have **file scope**, i.e they are visible from the point of declaration until the end of the file they are declared in.
    - Have **static duration**, i.e created when the program starts and destroyed when it ends. Local variables can be given static duration using the **static** keyword. Avoid dynamic initialization of static variables whenever possible.
- **Linkage** : an identifier's linkage determines whether other declarations of that name refer to the same object or not. Local variables have no linkage.
    - **Internal linkage** : can be seen and used within a single file, but it's not accessible from other files
    - **External linkage** :  can be both seen and used from file it's defined within and other files.
- Avoid non-const global variables whenever possible. Const globals are generally acceptable. Use **inline variables** for global constants.
- **Using statements** (includes using declarations and using directive) : used to avoid having to qualify identifiers with an explicit name namespace. To be generally avoided.
- **Typedefs and Type aliases** : allows a programmer to create an alias for a data type. Its usage can add legibility and reduce maintenance of code.
- **Auto** :
    - Can be used for **type inference/deduction**, which will infer a variable's type from its initializer.
    - Can be used as a function return type to have the compiler inter the function's return type from the its return statement.
- **Implicit type conversion** : performed whenever one data type is expected, but a different data type is supplied - compiler takes matter into own hands.
    - **Numeric promotion (widening)** : when a value from one fundamental data type is converted to a value of a larger fundamental data type from the same family (short to int).
    - **Numeric conversion** : when values are converted from larger to a smaller type (int to short) or between different type families (int to double).
    - **Narrowing conversions** : conversions that can cause loss of data.
- **Explicit type conversion** : when an explicit request is made by the programmer for a conversion via **cast.**
    - **Cast** : a request by the programmer to perform an explicit type conversion.
    - C++ supports, C-style casts, static casts, const casts, dynamic casts, and reinterpret casts.
    - Generally one should avoid C-style casts, const casts, and reinterpret casts.
    - *static_cast* is used to convert a value from one type to a value of another type.
- **Unnamed namespaces** : implicitly treats all contents of the namespace as if it had internal linkage. C++ also supports **inline namespaces** which provides a primitive versioning capabilities for namespaces.