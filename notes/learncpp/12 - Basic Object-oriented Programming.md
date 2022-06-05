# 12 - Basic Object-oriented Programming

# 12.1 - Introduction

- The following analogy helps get a better grasp of what OOP is. Take a look around oneself, ideally one would be surrounded by a plethora of objects (including oneself), each having two major components:
    - A list of relevant properties: weight colour, size, shape etc.
    - A number of behaviours it can exhibit: reflective, warm, smelly etc.
    
    These properties and behaviours are inseparable.
    
- OOP allows us to to create objects that tie together both properties and behaviours into a self-contained, reusable package.
- This allows for programs to be written in a more modular fashion, making it easier to write and understand providing a high degree of code reusability.
- OOP brings several other useful concept to the table:
    - inheritance
    - encapsulation
    - abstraction
    - polymorphism

 

# 12.2 - Classes and class members

- C++ provides a number of fundamental data types like char, int, long, etc to aide with solving relatively simple problems.
- Solving complex problems using fundamental data types can prove to be difficult. Therefore C++ allows one to define their own data types to better solve the problem at hand. Enumerated types and structs allow us to do just that.

## Classes and Member Functions

- In the world of OOP, we’d want our types not only to hold data, but also provide functions that work with the data as well. In C++, this is done via the class keyword.
    - Example
        
        In C++ classes and structs are essentially the same
        
        ```cpp
        struct DateStruct
        {
        	int year {};
        	int month {};
        	int day {};
        };
        DateStruct today { 2020, 10, 14 }; // use uniform initialization
        
        class Dateclass
        {
        public:
        	int m_year {};
        	int m_month {};
        	int m_day {};
        };
        DateClass today { 2020, 10, 14 }; // declare a variable of class DateClass
        ```
        
- Just like a struct declaration, a class declaration **doesn’t allocate any memory**. It only defines what the class looks like.
- In addition to holding data, classes (and structs) can also contain functions. Functions defined inside a class are called **member functions** or **methods**.
    - Example
        
        ```cpp
        # include <iostream>
        
        class DateClass
        {
        public:
        	int m_year {};
        	int m_month {};
        	int m_day {};
        	
        	void print()
        	{
        		std::cout << m_year << "/" << m_month << "/" <<m_day;
        	}
        
        int main()
        {
        	DateClass today { 2020, 10, 14 };
        
        	today.m_day = 16; // use member selection operator to select a member variable of the class
          today.print(); // use member selection operator to call a member function of the class
        									// 2020/10/16
        	return -;
        }
        
        ```
        
        - `m_day`, `m_month` and `m_year` refers to the associated object. If one called “tomorrow.print()”, `m_day` would refer to `tomorrow.m_day` instead. In this way the associated object is implicitly passed to the member function. For this reason it’s called **implicit object**.
    - Example using structs
        
        ```cpp
        #include <iostream>
        
        struct DateStruct
        {
            int year {};
            int month {};
            int day {};
        };
        
        void print(const DateStruct& date)
        {
            std::cout << date.year << '/' << date.month << '/' << date.day;
        }
        
        int main()
        {
            DateStruct today { 2020, 10, 14 }; // use uniform initialization
        
            today.day = 16; // use member selection operator to select a member of the struct
            print(today);
        
            return 0;
        }
        ```
        
    - With non-member functions (like in the example using structs), one has to pass data to the function. With member functions, one can assume that the function has an implicit object of the class to work with.
    - By convention, **class names** should begin with an **upper-case letter**.
    - With normal **non-member function**, a function can’t call a function that’s defined “below” it (without a forward declaration). This limitation doesn’t apply for **member function**.
        
        ```cpp
        void x()
        {
        // You can't call y() from here unless the compiler has already seen a forward declaration for y()
        }
        
        void y()
        {
        }
        
        class foo
        {
        public:
             void x() { y(); } // okay to call y() here, even though y() isn't defined until later in this class
             void y() { };
        };
        ```
        

## Member Types

- In addition to member variables and member functions., `classes` can have member types or nested types
    
    ```cpp
    class Calculator
    {
    public:
    	using number_type = int;
    	std::vector<number_type> m_resultHistory{};
    	number_type add(number_type a, number_type b)
    	{
    		auto result{ a + b };
    		m_resultHistory.push_back(result);
    		return result;
    	}
    };
    
    int main()
    {
    	Calculator calculator;
    	std::cout << calculator.add(4,6) << "\n";
    	std::cout << calculator.add(40,60) << "\n";
    	for (Calculator::number_type result : calculator.m_resultHistory)
    	{
    		std::cout << result << "\n";
    	}
    }
    ```
    
- In such contexts, class name acts like a namespace for the nested type (e.g. from outside the class, `number_type` can be accessed in the following fashion  `Calculator::number_type`)
- Generally, nested types should only be used when the nested type is used exclusively within that class.
- **In C**, structs only have data members, not member functions
    - Are structs also classes ?
        
        In C++, after designing classes (using the class keyword), Bjarne Stroustrup spent some amount of time considering whether structs (which were inherited from C) should be granted the ability to have member functions. Upon consideration, he determined that they should, in part to have a unified ruleset for both. So although we wrote the above programs using the class keyword, we could have used the struct keyword instead.
        
        Many developers (including myself) feel this was the incorrect decision to be made, as it can lead to dangerous assumptions. For example, it’s fair to assume a class will clean up after itself (e.g. a class that allocates memory will deallocate it before being destroyed), but it’s not safe to assume a struct will. Consequently, we recommend using the struct keyword for data-only structures, and the class keyword for defining objects that require both data and functions to be bundled together.
        
    
    ℹ️ This object contains both member data and member functions, so we should use a class. We should not use structs for objects that have member functions.
    
- It turns out that the C++ standard library is full of classes, std::string, std::vector, and std::array are all class types. So when an object is created of the mentioned class types, a class object is created.
    
    ```cpp
    #include <string>
    #include <array>
    #include <vector>
    #include <iostream>
    
    int main()
    {
        std::string s { "Hello, world!" }; // instantiate a string class object
        std::array<int, 3> a { 1, 2, 3 }; // instantiate an array class object
        std::vector<double> v { 1.1, 2.2, 3.3 }; // instantiate a vector class object
    
        std::cout << "length: " << s.length() << '\n'; // call a member function
    
        return 0;
    }
    ```
    
- The class keyword lets us create a custom type in C++ that can contain both member variables and member functions.
- Create a class called IntPair that holds two integers. This class should have two member variables to hold the integers. You should also create two member functions: one named “set” that will let you assign values to the integers, and one named “print” that will print the values of the variables.
    
    ```cpp
    class IntPair
    {
    public:
    	int m_var1 {};
    	int m_var2 {};
    	
    	void set(int a, int b)
    	{
    		m_var1 = a;
    		m_var2 = b;
    	}
    	void print()
    	{
    		std::cout << m_var1 << " " << m_var2;
    	}
    
    int main()
    {
    	IntPari ip;
    	ip.set(2, 3);
    	ip.print();
    
    	return 0;
    }
    ```
    

# 12.3 - Public vs private access specifiers

- Members declared within **structs** by default have public access, i.e. they can be accessed by anyone (including from code that exists outside the struct or class). These members are called **public members**.
    
    ```cpp
    struct DateStruct // members are public by default
    {
        int month {}; // public by default, can be accessed by anyone
        int day {}; // public by default, can be accessed by anyone
        int year {}; // public by default, can be accessed by anyone
    };
    
    int main()
    {
        DateStruct date;
        date.month = 10;
        date.day = 14;
        date.year= 2020;
    
        return 0;
    }
    ```
    
- Members declared within **classes** by default have private access, i.e. they can only be accessed by members of the own
    
    ```cpp
    class DateClass // members are private by default
    {
        int m_month {}; // private by default, can only be accessed by other members
        int m_day {}; // private by default, can only be accessed by other members
        int m_year {}; // private by default, can only be accessed by other members
    };
    
    int main()
    {
        DateClass date;
        date.m_month = 10; // error
        date.m_day = 14; // error
        date.m_year = 2020; // error
    
        return 0;
    }
    ```
    
- C++ provides 3 different access specifier keywords: public, private and protected.
- A class can have multiple specifiers. In general, member variables are usually made **private** and member functions **public**.
    - Example
        
        ```cpp
        #include <iostream>
        
        class DateClass // members are private by default
        {
        	int m_month {}; // private by default, can only be accessed by other members
        	int m_day {}; // private by default, can only be accessed by other members
        	int m_year {}; // private by default, can only be accessed by other members
        
        public:
        	void setDate(int month, int day, int year)
        	{
        		m_month = month;
        		m_day = day;
        		m_year = year;
        	}
        
        	void print()
        	{
        		std::cout << m_month << '/' << m_day << '/' << m_year;
        	}
        
        	// Note the addition of this function
        	void copyFrom(const DateClass& d)
        	{
        		// Note that we can access the private members of d directly
        		m_month = d.m_month;
        		m_day = d.m_day;
        		m_year = d.m_year;
        	}
        };
        
        int main()
        {
        	DateClass date;
        	date.setDate(10, 14, 2020); // okay, because setDate() is public
        
        	DateClass copy {};
        	copy.copyFrom(date); // okay, because copyFrom() is public
        	copy.print();
        	std::cout << '\n';
        
        	return 0;
        }
        ```
        
        - The group of public members of a class are often referred to as **public interface**. The public interface defines how programs using the class with interact with the class.
        - C++ works on a per-class basis, not a per-object basis. This means when a function has access to the private members of a class, it can access the private members of any object of that class type that it can see.
            - In the above example, copyFrom() is a member of DateClass, which gives it access to the private members of DateClass.
            - This means copyFrom() can not only directly access the private members of the implicit object it is operating on (copy), it also means it has direct access to the private members of DateClass parameter d!
            - If parameter d were some other type, this would not be the case.
- Struct vs class
    - A class defaults its members to private. A struct defaults its members to public.
    - Structs inherit from other classes publicly and classes inherit privately.

# 12.4 - Access functions and encapsulation

- In OOP, Encapsulation (also called **information hiding**) is the process of keeping the implementation details of an object hidden away from users. In doing so, users can access the objects using a public interface without the need of understanding the implementation behind the object.
- In C++ encapsulation is implemented via access specifiers. Typically,
    - all member variables are made private (hiding implementation details)
    - all member functions are made public (exposing interface for the user)

## Benefits of encapsulation

- **Benefit 1**: encapsulated classes are easier to use and reduce the complexity of your programs
    - With a fully encapsulated class, one only needs to know what member functions are publicly available, what arguments they take and what values they return. It doesn’t matter how the class was implemented internally.
    - All of the classes in C++ standard library are encapsulated. It would be a world of pain were one required to understand the functioning of each class in order to be able to use them.
- **Benefit 2**: encapsulated classes help protect your data and prevent misuse
    - Just like how one doesn’t have strict control over global variables, public members of a class suffer the same fate (to a smaller extend).
        - Example
            
            ```python
            class IntArray
            {
            public:
                int m_array[10];
            };
            
            int main()
            {
                IntArray array;
                array.m_array[16] = 2; // invalid array index, now we overwrote memory that we don't own
            }
            ```
            
            - User can easily modify the value of array, and even potentially pass an invalid index leading to errors.
            
            ```python
            class IntArray
            {
            private:
                int m_array[10]; // user can not access this directly any more
            
            public:
                void setValue(int index, int value)
                {
                    // If the index is invalid, do nothing
                    if (index < 0 || index >= std::size(m_array))
                        return;
            
                    m_array[index] = value;
                }
            };
            ```
            
            - However, if more control were placed, the indices can be validated before using to access / modify array elements.
    - It help protect the integrity of the program
- **Benefit 3**: encapsulated classes are easier to change
    - Consider the following example:
        - Example
            
            ```python
            #include <iostream>
            
            class Something
            {
            public:
                int m_value1;
                int m_value2;
                int m_value3;
            };
            
            int main()
            {
                Something something;
                something.m_value1 = 5;
                std::cout << something.m_value1 << '\n';
            }
            ```
            
        
        While this program works fine, were one to decide to rename `m_value`, or change its type, we’d break this program and others that uses the `Something` class.
        
    - Encapsulation gives us the ability to change how classes are implemented without breaking all of the programs that use them.
        - Example
            
            ```cpp
            #include <iostream>
            
            class Something
            {
            private:
                int m_value1;
                int m_value2;
                int m_value3;
            
            public:
                void setValue1(int value) { m_value1 = value; }
                int getValue1() { return m_value1; }
            };
            
            int main()
            {
                Something something;
                something.setValue1(5);
                std::cout << something.getValue1() << '\n';
            }
            
            // Changing it to the one below
            
            #include <iostream>
            
            class Something
            {
            private:
                int m_value[3]; // note: we changed the implementation of this class!
            
            public:
                // We have to update any member functions to reflect the new implementation
                void setValue1(int value) { m_value[0] = value; }
                int getValue1() { return m_value[0]; }
            };
            
            int main()
            {
                // But our program still works just fine!
                Something something;
                something.setValue1(5);
                std::cout << something.getValue1() << '\n';
            }
            ```
            
- **Benefit 4**: encapsulated classes are easier to debug
    - When the programs (using a class) fails, it’s usually due to an erroneous value of the member variables.
        - Were direct access of these variables possible, tracking down which piece of code was responsible for having modified the value would be a gargantuan task.
        - However, were member variables modified by passing through member functions. We can simply add a break point at the function and see which call to it assigned an erroneous value to a member variable.

## Access functions

- A short public function whose job is to retrieve or change the value of a private member variable.
    - Example
        
        ```cpp
        class MyString
        {
        private:
            char* m_string; // we'll dynamically allocate our string here
            int m_length; // we need to keep track of the string length
        
        public:
            int getLength() { return m_length; } // access function to get value of m_length
        };
        ```
        
- Access function are of two kinds:
    - **Getters**: also sometimes called **accessors**, these functions return the value of a private member variable. They should provide “read-only” access to data. Therefore, the best practice is that they should return by value or const reference (not by non-const reference).
    - **Setters**: also called **mutators**, these functions set the value of a private member variable.
    - Example
        
        ```cpp
        class Date
        {
        private:
            int m_month;
            int m_day;
            int m_year;
        
        public:
            int getMonth() { return m_month; } // getter for month
            void setMonth(int month) { m_month = month; } // setter for month
        
            int getDay() { return m_day; } // getter for day
            void setDay(int day) { m_day = day; } // setter for day
        
            int getYear() { return m_year; } // getter for year
            void setYear(int year) { m_year = year; } // setter for year
        };
        ```
        
- Pragmatic approach towards access function creation
    - If nobody outside the class needs to access a member, don’t provide access function for that member.
    - If someone outside your class needs to access a member, think about whether you can expose a behavior or action instead (e.g. rather than a setAlive(bool) setter, implement a kill() function instead).
    - If you can’t, consider whether you can provide only a getter

# 12.5 - Constructors

- When all members of a class are public **aggregate initializers** are used to initialize the class.
    - Example
        
        ```bash
        class Foo
        {
        public:
            int m_x {};
            int m_y {};
        };
        
        int main()
        {
            Foo foo { 6, 7 }; // list-initialization
        
            return 0;
        }
        ```
        
    
    This however wouldn’t work if the members were private. In this case **constructor** ought to be used.
    
- **Constructor** is a special kind of class member that’s automatically called when an object of that class is created. They **are** typically **used to**:
    - initialize member variables of the class to appropriate user-provided values
    - perform step up steps necessary for the class to be used.
- Following are the **naming rules** of constructors:
    - They must have the same name as the class (with the same capitalization)
    - They must not have a return type (no void either)

## Constructor Initializations

- While default constructor work just fine  for initializing classes with default values, sometimes a user would like to initialize classes with custom values. Fortunately, constructors can also be declared with parameters.
- Example of **direct- and list-initialization** using constructors with parameters
    
    ```cpp
    #include <cassert>
    
    class Fraction
    {
    private:
        int m_numerator {};
        int m_denominator {};
    
    public:
        Fraction() // default constructor
        {
             m_numerator = 0;
             m_denominator = 1;
        }
    
        // Constructor with two parameters, one parameter having a default value
        Fraction(int numerator, int denominator=1)
        {
            assert(denominator != 0);
            m_numerator = numerator;
            m_denominator = denominator;
        }
    
        int getNumerator() { return m_numerator; }
        int getDenominator() { return m_denominator; }
        double getValue() { return static_cast<double>(m_numerator) / m_denominator; }
    };
    
    int main ()
    {
    	Fraction fiveThirds{ 5, 3 }; // List initialization, calls Fraction(int, int)
    	Fraction threeQuarters(3, 4); // Direct initialization, also calls Fraction(int, int)
    	Fraction six{ 6 }; // calls Fraction(int, int) constructor, second parameter uses default value of 1	
    	return 0;
    }
    ```
    
    - Here we have two constructor, one that will be called in a default case and another called if values are passed.
    - These two constructors can coexist peacefully in the same class due to function overloading.
    - One can define as many constructors as one wants, as long as each has a unique signature: number and type of parameters.
    - **Favor brace initialization to initialize class objects.**
- Example of **copy initialization** using equals with classes
    - Like with fundamental variables, it’s possible also to initialize classes using copy initialization
    
    ```cpp
    Fraction six = Fraction{ 6 }; // Copy initialize a Fraction, will call Fraction(6, 1)
    Fraction seven = 7; // Copy initialize a Fraction.  The compiler will try to find a way to convert 7 to a Fraction, which will invoke the Fraction(7, 1) constructor.
    ```
    
    ⚠️ This initialization is not recommended as it may be less efficient.
    

## Default Constructors

- In the above examples we saw two constructors declared within the class, one with default values and another which accepts user values. The default constructor is **redundant** can be replaced.
    - Example
        
        ```cpp
        #include <cassert>
        
        class Fraction
        {
        private:
            int m_numerator {};
            int m_denominator {};
        
        public:
            // Default constructor
            Fraction(int numerator=0, int denominator=1)
            {
                assert(denominator != 0);
        
                m_numerator = numerator;
                m_denominator = denominator;
            }
        
            int getNumerator() { return m_numerator; }
            int getDenominator() { return m_denominator; }
            double getValue() { return static_cast<double>(m_numerator) / m_denominator; }
        };
        
        int main ()
        { 
        	Fraction zero; // will call Fraction(0, 1)
        	Fraction zero{}; // will call Fraction(0, 1)
        	Fraction six{ 6 }; // will call Fraction(6, 1)
        	Fraction fiveThirds{ 5, 3 }; // will call Fraction(5, 3)
        	return 0;
        }
        ```
        
- The **rules** about defining **functions** that have **default parameters apply to constructors too**. I.e. defining a function with default parameters, all default parameters must follow any non-default parameters,
    - If the rules isn’t followed, it may produce unexpected results for classes that have multiple default parameters of different types
        
        ```cpp
        class Something
        {
        public:
        	// Default constructor
        	Something(int n = 0, double d = 1.2) // allows us to construct a Something(int, double), Something(int), or Something()
        	{
        	}
        };
        
        int main()
        {
        	Something s1 { 1, 2.4 }; // calls Something(int, double)
        	Something s2 { 1 }; // calls Something(int, double)
        	Something s3 {}; // calls Something(int, double)
        
        	Something s4 { 2.4 }; // will not compile, as there's no constructor to handle Something(double)
        
        	return 0;
        }
        ```
        
        - `Something s4 { 2.4 }`  doesn’t work as planned as the rules how arguments match with default parameters won’t allow us to skip the left most parameter.
        - If we want to be able to construct a `Something` with only a `double`, we’ll need to add a second (non-default) constructor:
            
            ```cpp
            Something(double d)
            	{
            	}
            ```
            
            ⚠️ It needs to be non-default cause, `Something s3 {};` wouldn’t know which constructor to call.
            
- If one defines a class without constructors, C++ will automatically generate a public constructor. This sometimes is called **implicit constructor**.
    - Consider the following example
        
        ```cpp
        class Date
        {
        private:
            int m_year{ 1900 };
            int m_month{ 1 };
            int m_day{ 1 };
        
            // No user-provided constructors, the compiler generates a default constructor.
        };
        
        int main()
        {
            Date date{};
        
            return 0;
        }
        ```
        
        - The Date class has no constructors. Therefore, the compiler will generate a default constructor that allows us to create a `Date`
         object without arguments.
        - When the generated default constructor is called, members will still be initialized if they have non-static member initializers
- If ones class has a constructor, the implicitly generated constructors will not be provided.
- If ones class has another constructor and one want to allow default construction, one can:
    - either add default arguments to every parameter of a constructor with parameters, or
    - explicitly define a default constructor.
    - A third option is to use a default keyword to tell the compiler to create a default constructor for us anyway:
        
        ```cpp
        class Date
        {
        private:
            int m_year{ 1900 };
            int m_month{ 1 };
            int m_day{ 1 };
        
        public:
            // Tell the compiler to create a default constructor, even if
            // there are other user-provided constructors.
            Date() = default;
        
            Date(int year, int month, int day) // normal non-default constructor
            {
                m_year = year;
                m_month = month;
                m_day = day;
            }
        };
        
        int main()
        {
            Date date{}; // date is initialized to Jan 1st, 1900
            Date today{ 2020, 10, 14 }; // today is initialized to Oct 14th, 2020
        
            return 0;
        }
        ```
        
        - Using `= default` expresses better what your intentions are (To create a default constructor).
        - It’s safer, because it can zero-initialize members even if they have not been initialized at their declaration.
    
    **If you have constructors in your `class` and need a default constructor that does nothing (e.g. because all your members are initialized using non-static member initialization), use `= default`**
    

## Classes containing classes and constructor notes

- A `class` may contain another class as a member variable.
- By default when, the outer class is constructed, the member variables will have their default constructors called. This happens before the body of the constructor executes.
    - Example
        
        ```cpp
        #include <iostream>
        
        class A
        {
        public:
            A() { std::cout << "A\n"; }
        };
        
        class B
        {
        private:
            A m_a; // B contains A as a member variable
        
        public:
            B() { std::cout << "B\n"; }
        };
        
        int main()
        {
            B b;
            return 0;
        }
        
        A
        B
        ```
        
        - When variable `b` is constructed, the `B()` constructor is called.
        - Before Before the body of the constructor executes, `m_a` is initialized, calling the `class A` default constructor.
        - This prints “A”. Then control returns back to the `B` constructor, and the body of the B constructor executes
- Constructor notes
    - Constructors don’t create objects - the compiler sets up the memory allocation for the object prior to the constructor call.
    - Constructors serve two purposes:
        - Determine who is able to create an object, as the object of a class can only be created if a matching constructor can be found.
        - Used to initialize objects
    - **Always initialize all member variables in your objects.**

# 12.6 - Constructor member initializer lists

- Previously we have seen initialization of class members in the constructor using the assignment operator.
    - Example
        
        ```cpp
        class Something
        {
        private:
        	int m_value1 {};
        	double m_value2 {};
        	char m_value3 {};
        
        public:
        	Something()
        	{
        		m_value1 = 1;
        		m_value2 = 1.1;
        		m_value3 = 'c';
        	}
        };
        ```
        
        - When class constructor is executed, m_value1, m_value2 and m_value3 are created. Then the body of the constructor is run, where the member data variables are assigned values.
- While the syntax in the example above is valid, it could be  **less** **efficient**. **Additionally**, some data types (eg **const** and **reference** variables) must be initialized on the line they are declared.
    - Example
        
        ```cpp
        class Something
        {
        private:
            const int m_value;
        
        public:
            Something()
            {
                m_value = 1; // error: const vars can not be assigned to
            }
        };
        
        int main()
        {
        	const int m_value; // error: const vars must be initialized with a value
          m_value = 5; //  error: const vars can not be assigned to
        	return 0;
        }
        ```
        

## Member initializer list

- To solve this problem C++ provides a way to initialize class member variables via a **member initializer list**.
- Revisiting the [above](https://www.notion.so/12-Basic-Object-oriented-Programming-8e9eb8c3b45b4c77862ef5c65dce0c1e) example
    
    ```cpp
    #include <iostream>
    
    class Something
    {
    private:
        int m_value1 {};
        double m_value2 {};
        char m_value3 {};
    
    public:
        Something() : m_value1{ 1 }, m_value2{ 2.2 }, m_value3{ 'c' } // Initialize our member variables
        {
        // No need for assignment here
        }
    
        void print()
        {
             std::cout << "Something(" << m_value1 << ", " << m_value2 << ", " << m_value3 << ")\n";
        }
    };
    
    int main()
    {
        Something something{};
        something.print();
        return 0;
    }
    ```
    
- One can even pass initialization list by tweaking the constructor a bit.
    
    ```cpp
    Something(int value1, double value2, char value3='c')
            : m_value1{ value1 }, m_value2{ value2 }, m_value3{ value3 } // directly initialize our member variables
        {
        // No need for assignment here
        }
    ```
    
- It’s recommended to use member initialization list to initialize your class member variables instead of assignment.
- Initializing array members example
    
    ```cpp
    class Something
    {
    private:
        const int m_array[5];
    
    public:
        Something(): m_array { 1, 2, 3, 4, 5 } // use uniform initialization to initialize our member array
        {
        }
    
    };
    ```
    
- Initializing members variables that are classes
    
    ```cpp
    #include <iostream>
    
    class A
    {
    public:
        A(int x = 0) { std::cout << "A " << x << '\n'; }
    };
    
    class B
    {
    private:
        A m_a {};
    public:
        B(int y)
            : m_a{ y - 1 } // call A(int) constructor to initialize member m_a
        {
            std::cout << "B " << y << '\n';
        }
    };
    
    int main()
    {
        B b{ 5 };
        return 0;
    }
    ```
    
    - When variable `b` is constructed, the `B(int)` constructor is called with value 5.
    - Before the body of the constructor of class `B` executes, `m_a` is initialized calling constructor of class `A` with value 4.
    - The control then returns back to the `B` constructor, and the body of the B constructor executes.

## Formatting your initializer lists

- If the initializer list fits in a single line the following format can be adopted:
    
    ```cpp
    public:
        Something() : m_value1{ 1 }, m_value2{ 2.2 }, m_value3{ 'c' } // everything on one line
        {
        }
    ```
    
- If the initializer list doesn’t fit in a single line, the following format can be adopted:
    
    ```cpp
    Something(int value1, double value2, char value3='c') // this line already has a lot of stuff on it
            : m_value1{ value1 }, m_value2{ value2 }, m_value3{ value3 } // so we can put everything indented on next line
        {
        }
    ```
    
- If all of the initializer don’t fit in a single line, one can space it out
    
    ```cpp
    Something(int value1, double value2, char value3='c', float value4=34.6f) // this line already has a lot of stuff on it
          : m_value1{ value1 } // one per line
          , m_value2{ value2 }
          , m_value3{ value3 }
          , m_value4{ value4 }
      {
      }
    ```
    
- Variables in an initializer list aren’t initialized in the order that they are specified in the initializer list. Rather they are initialized in the order in which they are declared in the class.
- For **optimal** **results**, the following recommendation ought to be followed:
    - Member variables shouldn’t be initialized such that they are dependent on other member variables being initialized first. I.e. one must ensure that member variables are properly initialized even if the ordering is different.
    - Initialize variables in the initializer list in the same order in which they are declared in your class

# 12.7 - Non-static member initialization

- Writing a class usually entails the use of multiple constructors, having to specify default values for all constructors results in redundant code.
- Additionally, updating the default value of a member would require one to modify each constructor respectively.
    
    ```cpp
    #include <iostream>
    
    class Rectangle
    {
    private:
        double m_length{ 1.0 };
        double m_width{ 1.0 };
    
    public:
    
        Rectangle(double length, double width)
            : m_length{ length },
              m_width{ width }
        {
            // m_length and m_width are initialized by the constructor (the default values aren't used)
        }
    
        Rectangle(double length)
            : m_length{ length }
        {
            // m_length is initialized by the constructor.
            // m_width's default value (1.0) is used.
        }
    
        void print()
        {
            std::cout << "length: " << m_length << ", width: " << m_width << '\n';
        }
    
    };
    
    int main()
    {
        Rectangle x{ 2.0, 3.0 };
        x.print(); // length: 2.0, width: 3.0
    
        Rectangle y{ 4.0 };
        y.print();
    
        return 0; // length: 4.0, width: 1.0
    }
    ```
    
- It’s hence possible to give non-static class member a default initialization
    - Example
        
        ```cpp
        #include <iostream>
        
        class Rectangle
        {
        private:
            double m_length{ 1.0 }; // m_length has a default value of 1.0
            double m_width{ 1.0 }; // m_width has a default value of 1.0
        
        public:
            void print()
            {
                std::cout << "length: " << m_length << ", width: " << m_width << '\n';
            }
        };
        
        int main()
        {
            Rectangle x{}; // x.m_length = 1.0, x.m_width = 1.0
            x.print();
        
            return 0;
        }
        ```
        
- However, note that constructors still determine what kind of objects may be created.
    - Example
        
        ```cpp
        #include <iostream>
        
        class Rectangle
        {
        private:
            double m_length{ 1.0 };
            double m_width{ 1.0 };
        
        public:
        
            // note: No default constructor provided in this example
        
            Rectangle(double length, double width)
                : m_length{ length },
                  m_width{ width }
            {
                // m_length and m_width are initialized by the constructor (the default values aren't used)
            }
        
            void print()
            {
                std::cout << "length: " << m_length << ", width: " << m_width << '\n';
            }
        
        };
        
        int main()
        {
            Rectangle x{}; // will not compile, no default constructor exists, even though members have default initialization values
        
            return 0;
        }
        ```
        
- If a default initialization value is provided and the constructor initializes the member via the member initializer list, the member initializer list will take precedence
    - Example
        
        ```cpp
        #include <iostream>
        
        class Rectangle
        {
        private:
            double m_length{ 1.0 };
            double m_width{ 1.0 };
        
        public:
        
            Rectangle(double length, double width)
                : m_length{ length },
                  m_width{ width }
            {
                // m_length and m_width are initialized by the constructor (the default values aren't used)
            }
        
            Rectangle(double length)
                : m_length{ length }
            {
                // m_length is initialized by the constructor.
                // m_width's default value (1.0) is used.
            }
        
            void print()
            {
                std::cout << "length: " << m_length << ", width: " << m_width << '\n';
            }
        
        };
        
        int main()
        {
            Rectangle x{ 2.0, 3.0 };
            x.print();
        
            Rectangle y{ 4.0 };
            y.print();
        
            return 0;
        }
        ```
        
- Initializing members using non-static member initialization requires using either an equals sign, or a brace (uniform) initializer -- the parenthesis initialization form doesn’t work here
    
    ```cpp
    class A
    {
        int m_a = 1;  // ok (copy initialization)
        int m_b{ 2 }; // ok (brace initialization)
        int m_c(3);   // doesn't work (parenthesis initialization)
    };
    ```
    

# 12.8 - Overlapping and delegating constructors

- When a new object is instantiated the object’s constructor is called implicitly. And more often that one can imagine these constructors have overlapping functionality.
    - Example
        
        ```cpp
        class Foo
        {
        public:
            Foo()
            {
                // code to do A
            }
        
            Foo(int value)
            {
                // code to do A
                // code to do B
            }
        };
        
        // code to do A is required by both constructors, the code is duplicated in each constructor.
        ```
        
    - To deal with this one can make use of a process called **delegating constructors** (or **constructor chaining**).  This allows constructors to call other constructors from the same class.
        - Example 1
            
            ```cpp
            class Foo
            {
            private:
            
            public:
                Foo()
                {
                    // code to do A
                }
            
                Foo(int value): Foo{} // use Foo() default constructor to do A
                {
                    // code to do B
                }
            
            };
            ```
            
        - Example 2
            
            ```cpp
            #include <string>
            #include <iostream>
            
            class Employee 
            {
            private:
            	int m_id{};
            	std::string m_name{};
            
            public:
            Employee(int id=0, const std::string& name=""):
                    m_id{ id }, m_name{ name }
                {
                    std::cout << "Employee " << m_name << " created.\n";
                }
            
                // Use a delegating constructor to minimize redundant code
                Employee(const std::string& name) : Employee{ 0, name }
                { }
            };
            ```
            
- Pointers concerning delegating
    - A constructor that delegates to another constructor is not allowed to do any member initialization. So ones constructors can delegate or initialize not both.
    - It is possible for one constructor to delegate to another constructor, which delegates it back to the first constructor. This forms an infinite loop, and will cause your program to run out of stack space and crash.
- Since constructors and either initialize or delegate, this leads to a challenge if the default constructor does some common initialization and this “common initialization” is required by another constructor
    - Example
        
        ```cpp
        class Foo
        {
        private:
            const int m_value { 0 };
        
        public:
            Foo()
            {
                 // code to do some common setup tasks (e.g. open a file or database)
            }
        
            Foo(int value) : m_value { value } // we must initialize m_value since it's const
            {
                // how do we get to the common initialization code in Foo()?
            }
        
        };
        ```
        
    - A solution would be to used a normal (non-constructor) member function to handle the common setup tasks
        
        ```cpp
        #include <iostream>
        
        class Foo
        {
        private:
            const int m_value { 0 };
        
            void setup() // setup is private so it can only be used by our constructors
            {
                // code to do some common setup tasks (e.g. open a file or database)
                std::cout << "Setting things up...\n";
            }
        
        public:
            Foo()
            {
                setup();
            }
        
            Foo(int value) : m_value { value } // we must initialize m_value since it's const
            {
                setup();
            }
        
        };
        
        int main()
        {
            Foo a;
            Foo b{ 5 };
        
            return 0;
        }
        ```
        
- Sometimes one might want to reset a class back to its default state. To do so a new class object can be created, followed by using assignment to overwrite the values in the object one would want to reset.
    - Example
        
        ```cpp
        #include <iostream>
        
        class Foo
        {
        private:
            int m_a{ 5 };
            int m_b{ 6 };
        
        public:
            Foo()
            {
            }
        
            Foo(int a, int b)
                : m_a{ a }, m_b{ b }
            {
            }
        
            void print()
            {
                std::cout << m_a << ' ' << m_b << '\n';
            }
        
            void reset()
            {
                *this = Foo(); // create new Foo object, then use assignment to overwrite our implicit object
            }
        };
        
        int main()
        {
            Foo a{ 1, 2 };
            a.reset();
        
            a.print();
        
            return 0;
        }
        ```
        

# 12.9 - Destructors

- A special kind of class member function that is executed when an object of that class is destroyed. While constructors are used to initialize a class, destructors are used to help clean up.
- Class destructor is automatically called to do any necessary clean up before the object is removed from memory.
- For simple classes (those that just initializes values of normal member variables) a destructor is not needed. However, if the class object is holding any resources (e.g. dynamic memory, or a file) or if one needs to do maintenance of any sorts before the object is destroyed, destructors come in handy
- A few rules concerning destructors:
    - They must have the same name as the class, preceded by a tilde (~)
    - They can’t take any arguments
    - They have no return type
    
    Implicit calling of destructors is encouraged, there are rarely cases where one would want to clean up an object more than once.
    
    - Example
        
        ```cpp
        #include <iostream>
        #include <cassert>
        #include <cstddef>
        
        class IntArray
        {
        private:
        	int* m_array{};
        	int m_length{};
        
        public:
        	IntArray(int length) // constructor
        	{
        		assert(length > 0);
        
        		m_array = new int[static_cast<std::size_t>(length)]{};
        		m_length = length;
        	}
        
        	~IntArray() // destructor
        	{
        		// Dynamically delete the array we allocated earlier
        		delete[] m_array;
        	}
        
        	void setValue(int index, int value) { m_array[index] = value; }
        	int getValue(int index) { return m_array[index]; }
        
        	int getLength() { return m_length; }
        };
        
        int main()
        {
        	IntArray ar ( 10 ); // allocate 10 integers
        	for (int count{ 0 }; count < ar.getLength(); ++count)
        		ar.setValue(count, count+1);
        
        	std::cout << "The value of element 5 is: " << ar.getValue(5) << '\n';
        
        	return 0;
        } // ar is destroyed here, so the ~IntArray() destructor function is called here
        ```
        
- Constructors are called when an object is created and destructors when an object is destroyed, the following example demonstrates this.
    
    ```cpp
    #include <iostream>
    
    class Simple
    {
    private:
        int m_nID{};
    
    public:
        Simple(int nID)
            : m_nID{ nID }
        {
            std::cout << "Constructing Simple " << nID << '\n';
        }
    
        ~Simple()
        {
            std::cout << "Destructing Simple" << m_nID << '\n';
        }
    
        int getID() { return m_nID; }
    };
    
    int main()
    {
        // Allocate a Simple on the stack
        Simple simple{ 1 };
        std::cout << simple.getID() << '\n';
    
        // Allocate a Simple dynamically
        Simple* pSimple{ new Simple{ 2 } };
    
        std::cout << pSimple->getID() << '\n';
    
        // We allocated pSimple dynamically, so we have to delete it.
        delete pSimple;
    
        return 0;
    } // simple goes out of scope here
    
    // Constructing Simple 1
    // 1
    // Constructing Simple 2
    // 2
    // Destructing Simple 2
    // Destructing Simple 1
    ```
    
- RAII (Resource Acquisition Is Initialization) is a programming technique whereby resource use is tied to the lifetime of objects with automatic duration (e.g. non-dynamically allocated objects). It is implemented via classes with constructors and destructors.
- Note that if you use the exit() function, your program will terminate and no destructors will be called. Be wary if you’re relying on your destructors to do necessary cleanup work

# 12.10 - The hidden “this” pointer

- “When a member function is called, how does C++ keep track of which object it was called on?”. The answer is that C++ utilizes a hidden pointer named “this”
    - Example
        
        ```cpp
        class Simple
        {
        private:
            int m_id;
        
        public:
            Simple(int id)
                : m_id{ id }
            {
            }
        
            void setID(int id) { m_id = id; }
            int getID() { return m_id; }
        };
        int main()
        {
            Simple simple{1};
            simple.setID(2);
            std::cout << simple.getID() << '\n';
        
            return 0;
        }
        
        //  2
        ```
        
        - When one calls `simple.setID(2)`; C++ knows that function setID() should operate on object simple, and that m_id actually refers to simple.m_id.

## All about *this pointer

- From the above example when calling `simple.setID(2);` one would have the impression that `setID` is being called using a single argument. When in reality, when compiled this is how the compiler converts it
    - `setID(&simple, 2)` - a standard function call, where the object `simple` is passed by address as an argument to the function)
    - `ptr->age = 5` ???
        
        ```cpp
        struct Person
        {
        	int age;
        	double weight;
        };
        Person person;
        Person *ptr = &person
        
        (*ptr).age = 5
        ptr->age = 5
        ```
        
- This being said, since the function call now has an added argument, the member function definition needs to be modified to accept this argument as a parameter. Consequently it’s modified as below
    - `void setID(int id) {Simple* const this,  int id) { this->m_id = id }`
    - When a compiler compiles a normal member function, by default it adds a parameter to the function named “this” (a hidden const pointer that holds the address of the object the member function was called)
    - Additionally, inside a member function, any class variables (functions and variables) also needs to be updated so they refer to the object the member function was called on.This is easily done by adding a “this->” prefix to each of them
- Long story short:
    - `simple.setID(2)` get compiled to  `setID(&simple, 2)` .
    - Inside setID(), the “this” pointer holds the address of object simple.
    - Any member variables inside `setID` are prefixed with “this→”. o when we say `m_id = id`, the compiler is actually executing `this->m_id = id`, which in this case updates simple.m_id to id.
- Consider the example where multiple objects are created of the same class type
    
    ```cpp
    int main()
    {
        Simple A{1}; // this = &A inside the Simple constructor
        Simple B{2}; // this = &B inside the Simple constructor
        A.setID(3); // this = &A inside member function setID
        B.setID(4); // this = &B inside member function setID
    
        return 0;
    }
    ```
    
    “this” pointer alternately holds the address of object A or B depending on whether we’ve called a member function on object A or B.
    

## Explicitly referencing “this”

- Most of the time, one wouldn’t need to explicitly reference “this” pointer. Below are a few examples where explicit reference can come in handy.
- First, If one has a constructor (or member function) that has a parameter with the same name as a member variable, “this” can be used to disambiguate them
    - Example
        
        ```cpp
        class Something
        {
        private:
            int data;
        
        public:
            Something(int data)
            {
                this->data = data; // this->data is the member, data is the local parameter
            }
        };
        ```
        
        Although this is acceptable coding practice, we find using the “m_” prefix on all member variable names provides a better solution by preventing duplicate names altogether!
        
- Second, it can sometimes be useful to have a class member function return the object it was working with as a return value
    - The primary reason behind this is to allow a series of member functions to be “chained” together, so several member functions can be called on the same object.
    - Consider the following example:
        - `std::cout << "Hello, " << userName;` , where `std::cout` is an object, and operator `<<` is a member function that operates on that object.
        - the compiler evaluate the above code snippet as:
         `(std::cout << "Hello, ") << userName;`,
        - First, operator `<<` uses `std::cout` and the string literal “Hello, ” to print “Hello, ” to the console. However, since this is part of an expression, operator `<<` also needs to return a value (or void).
        - If operator<< returned void, you’d end up with this: `(void) << userName;`, which doesn’t make sense (and the compiler would throw an error).
        - Instead, operator `<<` returns *this, which in this context is the `std::cout` object. That way after the first operator `<<` has been evaluated, we get:
        `(std::cout) << userName;`
    - A use case
        - Classical scenario
            
            ```cpp
            class Calc
            {
            private:
                int m_value{0};
            
            public:
            
                void add(int value) { m_value += value; }
                void sub(int value) { m_value -= value; }
                void mult(int value) { m_value *= value; }
            
                int getValue() { return m_value; }
            };
            
            #include <iostream>
            int main()
            {
                Calc calc{};
                calc.add(5); // returns void
                calc.sub(3); // returns void
                calc.mult(4); // returns void
            
                std::cout << calc.getValue() << '\n';
                return 0;
            }
            ```
            
        - Chaining scenario
            
            ```cpp
            class Calc
            {
            private:
                int m_value{};
            
            public:
                Calc& add(int value) { m_value += value; return *this; }
                Calc& sub(int value) { m_value -= value; return *this; }
                Calc& mult(int value) { m_value *= value; return *this; }
            
                int getValue() { return m_value; }
            };
            
            #include <iostream>
            int main()
            {
                Calc calc{};
                calc.add(5).sub(3).mult(4);
            
                std::cout << calc.getValue() << '\n';
                return 0;
            }
            ```
            

## Summary

- The “this” pointer is a hidden parameter implicitly added to any non-static member function. Most of the time, you will not need to access it directly, but you can if needed.
- It’s worth noting that “this” is a const pointer - you can change the value of the underlying object it points to, but you can not make it point to something else!
- By having functions that would otherwise return void return *this instead, you can make those functions chainable. This is most often used when overloading operators for your classes

# 12.11 - Class code and header files

## Defining member functions outside the class defintion

- Examples of classes observed until now were relatively simple, hence implementing member functions within the class itself didn’t affect the readability/understandability of the class.
    - Example
        
        ```cpp
        class Date
        {
        private:
            int m_year;
            int m_month;
            int m_day;
        
        public:
            Date(int year, int month, int day)
            {
                setDate(year, month, day);
            }
        
            void setDate(int year, int month, int day)
            {
                m_year = year;
                m_month = month;
                m_day = day;
            }
        
            int getYear() { return m_year; }
            int getMonth() { return m_month; }
            int getDay()  { return m_day; }
        };
        ```
        
- However as a class gets longer and more complicated, having member function definitions inside the class can make it harder to manage and work with.
- Fortunately C++ offers a way to separate the declaration portion of the class from the initialization portion. To do so, one needs to simply prefix the function name with the class name followed by :: .
    - Example 1
        
        ```cpp
        class Date
        {
        private:
            int m_year;
            int m_month;
            int m_day;
        
        public:
            Date(int year, int month, int day);
        
            void SetDate(int year, int month, int day);
        
            int getYear() { return m_year; }
            int getMonth() { return m_month; }
            int getDay()  { return m_day; }
        };
        
        // Date constructor
        Date::Date(int year, int month, int day)
        {
            SetDate(year, month, day);
        }
        
        // Date member function
        void Date::SetDate(int year, int month, int day)
        {
            m_month = month;
            m_day = day;
            m_year = year;
        }
        ```
        
    - Example 2: externally defined constructor with a member initialization list:
        
        [This](https://www.notion.so/12-Basic-Object-oriented-Programming-8e9eb8c3b45b4c77862ef5c65dce0c1e) becomes
        
        ```cpp
        class Calc
        {
        private:
            int m_value = 0;
        
        public:
            Calc(int value=0);
        
            Calc& add(int value);
            Calc& sub(int value);
            Calc& mult(int value);
        
            int getValue() { return m_value; }
        };
        
        Calc::Calc(int value): m_value(value)
        {
        }
        
        Calc& Calc::add(int value)
        {
            m_value += value;
            return *this;
        }
        
        Calc& Calc::sub(int value)
        {
            m_value -= value;
            return *this;
        }
        
        Calc& Calc::mult(int value)
        {
            m_value *= value;
            return *this;
        }
        ```
        

## Putting class definition in a header file

- Just like function declarations that can be put in a header file to facilitate reuse in multiple files or projects, classes are no different.
- Traditionally, the class definition is put in a header file of the same name as the class, and member function defined outside the class are put in a .cpp file of the same name as the class.
    - Date.hpp file
        
        ```cpp
        #ifndef DATE_H
        #define DATE_H
        
        class Date
        {
        private:
            int m_year;
            int m_month;
            int m_day;
        
        public:
            Date(int year, int month, int day);
        
            void SetDate(int year, int month, int day);
        
            int getYear() { return m_year; }
            int getMonth() { return m_month; }
            int getDay()  { return m_day; }
        };
        
        #endif
        ```
        
    - Date.cpp file
        
        ```cpp
        #incldue "Date.hpp"
        
        // Date constructor 
        Date::Date(int year, int month, int day)
        {
            SetDate(year, month, day);
        }
        
        // Date member function
        void Date::SetDate(int year, int month, int day)
        {
            m_month = month;
            m_day = day;
            m_year = year;
        }
        ```
        
        Now if any other header or code file wants to use the Date class can simply `#include "Date.hpp"`
        
- With proper guards, defining a class in a header file shouldn’t violate the one-definition rule
- Member functions defined inside the class definition are considered implicitly **inline**. **Inline function** are exempt from the one definition rule per program. Therefore there’s no problem defining trivial member functions (such as access functions) inside the class definition itself.
- Member functions defined outside the class definition are treated like normal functions, and are subject to the one definition per program part of the one-definition rule. Therefore, those functions should be defined in a code file, not inside the header.
- Having non-trivial member function declared within the class definition can have the following downsides:
    - Clutters up the code
    - If a change is brought about within the member function code, all the files using the class functionality ought to be recompiled and this could be time consuming. On the contrary, were one to decide to have a separate file for non-trivial functions, only this file ought to be recompiled where any changes to be made to the member functions.
- Deciding what goes into the .hpp and .cpp files
    - For class that aren’t reusable, define them in the single .cpp file they’re used in.
    - For classes used in multiple files, or intended for general use, define them in a .hpp file having the same name as the class.
    - Trivial member functions (trivial constructors or destructors, access functions, etc…) can be defined inside the class.
    - Non-trivial member functions should be defined in a .cpp file that has the same name as the class.
- Default parameters for member functions should be declared in the class definition (in the header file), where they can be seen by whomever #includes the header.

# 12.12 - Const class objects and member functions

In the previous chapters we saw that the `const` keyword can be used with fundamental data types to render it constant, additionally, all constant variables must be initialised at compile time.

## Const classes, member functions

- Instantiated **class** objects can be made **constant** using the `const` keyword.
    - Example
        
        ```cpp
        const Date date1; // initialize using default constructor
        const Date date2(2020, 10, 16); // initialize using parameterized constructor
        const Date date3 { 2020, 10, 16 }; // initialize using parameterized constructor (C++11)
        ```
        
- Once const class object has been initialized via constructor, any attempt to modify the member variables of the object is disallowed - changing directly or through member function calls.
    - Example
        
        ```cpp
        class Something
        {
        public:
            int m_value {};
        
            Something(): m_value{0} { }
        
            void setValue(int value) { m_value = value; }
            int getValue() { return m_value ; }
        };
        
        int main()
        {
            const Something something{}; // calls default constructor
        
            something.m_value = 5; // compiler error: violates const
            something.setValue(5); // compiler error: violates const
        
            return 0;
        }
        ```
        
- The following example will also cause a compile error: `std::cout << something.getValue()`
    - This is because const class object can only explicitly call const member functions.
    - **Const member function** is a member function that guarantees that it will not modify the object or call any non-const member function - which could potentially modify the object.
    - To make `getValue()` a const member function, one can simply append the const keyword to the function prototype.
    - Example
        
        ```cpp
        class Something
        {
        public:
            int m_value {};
        
            Something(): m_value{0} { }
        
            void resetValue() { m_value = 0; }
            void setValue(int value) { m_value = value; }
        
            int getValue() const { return m_value; } // note addition of const keyword after parameter list, but before function body
        };
        ```
        
    - Example with member functions defined outside the class definition
        
        ```cpp
        class Something
        {
        public:
            int m_value {};
        
            Something(): m_value{0} { }
        
            void resetValue() { m_value = 0; }
            void setValue(int value) { m_value = value; }
        
            int getValue() const; // note addition of const keyword here
        };
        
        int Something::getValue() const // and here
        {
            return m_value;
        }
        ```
        
- Additionally, were any const member function to attempt to change the value of a member variable, or call a non-constant member function, a compiler error would be thrown.
    - Example
        
        ```cpp
        class Something
        {
        public:
            int m_value {};
        
            void resetValue() const { m_value = 0; } // compile error, const functions can't change member variables.
        };
        ```
        

## Const reference and msc

- While instantiating const class objects is one way to create const objects, a more common way to get a constant object is by passing an object to a function by **const reference**.
    - Passing class arguments by value could cause the program to be less efficient.
    - Reference is make const to prevent the function from inadvertently changing the argument.
    - Const reference allow the function to work with R-values (e.g. literals), which can be passed as const references, but not non-const reference
    - Example
        
        ```cpp
        class Date
        {
        private:
            int m_year {};
            int m_month {};
            int m_day {};
        
        public:
            Date(int year, int month, int day)
            {
                setDate(year, month, day);
            }
        
            // setDate() cannot be const, modifies member variables
            void setDate(int year, int month, int day)
            {
                m_year = year;
                m_month = month;
                m_day = day;
            }
        
            // The following getters can all be made const
            int getYear() const { return m_year; }
            int getMonth() const { return m_month; }
            int getDay() const { return m_day; }
        };
        
        // note: We're passing date by const reference here to avoid making a copy of date
        void printDate(const Date& date)
        {
            std::cout << date.getYear() << '/' << date.getMonth() << '/' << date.getDay() << '\n';
        }
        
        int main()
        {
            Date date{2016, 10, 16};
            printDate(date);
        
            return 0;
        }
        ```
        
- When a member function is constant, the hidden *this pointer is also const, which means all members are treated as const within that function.
    - Therefore, a const member function can not return a non-const reference to a member, as that would allow the caller to have non-const access to that const member.
    - Const member functions can return const references to members.
- Although it is not done very often, it is possible to overload a function in such a way to have a const and non-const version of the same function.
    - Example
        
        ```cpp
        #include <string>
        
        class Something
        {
        private:
            std::string m_value {};
        
        public:
            Something(const std::string& value=""): m_value{ value } {}
        
            const std::string& getValue() const { return m_value; } // getValue() for const objects (returns const reference)
            std::string& getValue() { return m_value; } // getValue() for non-const objects (returns non-const reference)
        };
        
        int main()
        {
        	Something something;
        	something.getValue() = "Hi"; // calls non-const getValue();
        
        	const Something something2;
        	something2.getValue(); // calls const getValue();
        
        	return 0;
        }
        ```
        
- Because passing objects by const reference is common, your classes should be const-friendly. That means making any member function that does not modify the state of the class object const!

# 12.13 - Static member variables

## The basics

- In the previous lessons we have witnessed how static variables are able to maintain their values across multiple function calls.
- Static keyword when applied to global variables restricts their usage within the file they are defined in.
- In this chapter we speak about the static keyword’s application on to class member variables.
- Consider the following examples:
    - example 1: without static member variables
        
        ```cpp
        #include <iostream>
        
        class Something
        {
        public:
            int m_value{ 1 };
        };
        
        int main()
        {
            Something first;
            Something second;
        
            first.m_value = 2;
        
            std::cout << first.m_value << '\n';
            std::cout << second.m_value << '\n';
        
            return 0;
        }
        // 2 
        // 1
        ```
        
    - example 2: with static member variables
        
        ```cpp
        #include <iostream>
        
        class Something
        {
        public:
            static int s_value;
        };
        
        int Something::s_value{ 1 };
        
        int main()
        {
            Something first;
            Something second;
        
            first.s_value = 2;
        
            std::cout << first.s_value << '\n';
            std::cout << second.s_value << '\n';
            return 0;
        }
        // 2 
        // 2
        ```
        
        - Here the member `s_value` is shared between all class objects
- Static members exist even if no object of class has been instantiated, they are created when the program starts and are destroyed when the program ends.
    - It helps to think of static members as belonging to the class itself and not to the object of the class.
    - `s_value` in the example [above](https://www.notion.so/12-Basic-Object-oriented-Programming-8e9eb8c3b45b4c77862ef5c65dce0c1e) exists independently of any class objects, it can directly be accessed using the class name and scope resolution operator (`Something::s_value`)
    - Example
        
        ```cpp
        #include <iostream>
        
        class Something
        {
        public:
            static int s_value; // declares the static member variable
        };
        
        int Something::s_value{ 1 }; // defines the static member variable (we'll discuss this section below)
        
        int main()
        {
            // note: we're not instantiating any objects of type Something
        
            Something::s_value = 2;
            std::cout << Something::s_value << '\n';
            return 0;
        }
        ```
        
- **Access static members by class name using the scope resolution operator rather than through the object of a class.**

## Defining and initializing

- When a static variable is defined inside a class, we’re in essence signaling  to the compiler the existence of a static variable (much like a forward declaration)
- Since static members are not part of the individual class objects (they are treated like global variables and get initialized when the program starts), one must explicitly defined the static member outside the class in the global scope.
- Static member definitions aren’t subject to access controls: one can define and initialize the variable even if it’s declared as private or protected
- If class is defined in a `.h` file, the static member definition is usually placed in the associated code file (`.cpp`). If the class is defined in a `.cpp` file, the static member definition gets placed underneath the class definition get
- Below are a few shortcuts to defining and initializing static members;
    - When static member is a const integral type or a const enum, the static member can be initialized inside the class definition
        
        ```cpp
        class Whatever
        {
        public:
        	static const int s_value{ 4 }; // a static const int can be declared and initialized directly
        };
        ```
        
    - Static constexpr can be initialized inside the class definition
        
        ```cpp
        #include <array>
        
        class Whatever
        {
        public:
            static constexpr double s_value{ 2.2 }; // ok
            static constexpr std::array<int, 3> s_array{ 1, 2, 3 }; // this even works for classes that support constexpr initialization
        };
        ```
        
- Example
    
    ```cpp
    #include <iostream>
    
    class Something
    {
    private:
        static inline int s_idGenerator { 1 }; // C++17
    //  static int s_idGenerator;              // Use this instead for C++14 or older
        int m_id { };
    
    public:
        Something()
        : m_id { s_idGenerator++ } // grab the next value from the id generator
        {}
    
        int getID() const { return m_id; }
    };
    
    // For C++14 or older, we have to initialize the non-const static member outside the class definition
    // Note that we're defining and initializing s_idGenerator even though it is declared as private above.
    // This is okay since the definition isn't subject to access controls.
    // int Something::s_idGenerator { 1 }; // start our ID generator with value 1 (uncomment for C++14 or older)
    
    int main()
    {
        Something first;
        Something second;
        Something third;
    
        std::cout << first.getID() << '\n';
        std::cout << second.getID() << '\n';
        std::cout << third.getID() << '\n';
        return 0;
    }
    ```
    

# 12.14 - Static member function

- From the previous chapter we saw that static member variables belong to the class instead of a class object. But what if these members were private?
    - Example
        
        ```cpp
        class Something
        {
        private:
            static int s_value;
        
        };
        
        int Something::s_value{ 1 }; // initializer, this is okay even though s_value is private since it's a definition
        
        int main()
        {
            // how do we access Something::s_value since it is private?
        }
        ```
        
        - Here `s_value` can’t be accessed directly because it’s private.
        - We could easily create a normal public member function to access the value of `s_value`, but this would then entail the declaration of a class object to access the function
- An optimal way of accessing static private members would be through static member functions
    - Example
        
        ```cpp
        class Something
        {
        private:
        	static int s_value;
        public:
        	static int getValue() { return s_value; } // static member function 
        };
        
        int Something::s_value{ 1 }; // initializer
        
        int main()
        {
        	std::cout << Something::getValue() << “\n”;
        }
        ```
        
        - Since static functions aren’t attached to a particular object, they can be called directly by using the class name and scope resolution operator
- Following are two peculiarities of static member functions:
    - They don’t have *this pointer. This makes sense as they are attached to a class rather than class objects.
    - Static member functions can directly access other static members but not non-static members. This is because non-static members must belong to a class object, and static member functions have no class objects to work with.
- Like as with classical member functions, static member functions can too be declared outside the class
    - Example
        
        ```cpp
        class IDGenerator
        {
        private:
            static int s_nextID; // Here's the declaration for a static member
        
        public:
             static int getNextID(); // Here's the declaration for a static function
        };
        
        // Here's the definition of the static member outside the class.  Note we don't use the static keyword here.
        // We'll start generating IDs at 1
        int IDGenerator::s_nextID{ 1 };
        
        // Here's the definition of the static function outside of the class.  Note we don't use the static keyword here.
        int IDGenerator::getNextID() { return s_nextID++; }
        
        int main()
        {
            for (int count{ 0 }; count < 5; ++count)
                std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';
        
            return 0;
        
        The next ID is: 1
        The next ID is: 2
        The next ID is: 3
        The next ID is: 4
        The next ID is: 5//
        ```
        
- While writing classes with all static members (monostates) can be useful, they come with a few potential downfalls.
    - Since static members are instantiated only once, there’s no way to have multiple copies of a pure static class (without cloning and rename the class).
    - A pure static class holds a similar place as global variables. The members of such a class can modified by any piece of code and could potentially wreak havoc.
- C++ doesn’t support static constructors
    - While one can initialize normal member variables via the constructor, it would make sense to initialize static member variables via a static constructor, **but no, it’s not possible with C++**.
    - One can initialize the static member variable at the point of definition (even if it is private).
        - Example
            
            ```cpp
            class MyClass
            {
            public:
            	static std::vector<char> s_mychars;
            };
            
            std::vector<char> MyClass::s_mychars{ 'a', 'e', 'i', 'o', 'u' }; // initialize static variable at point of definition
            ```
            
    - If initializing ones static member variable requires executing code (e.g. a loop), there are many different, somewhat obtuse ways of doing this. One way that works with all variables, static or not, is to use a lambda and call it immediately.
        - Example
            
            ```cpp
            class MyClass
            {
            public:
                static std::vector<char> s_mychars;
            };
            
            std::vector<char> MyClass::s_mychars{
              []{ // The parameter list of lambdas without parameters can be omitted.
                  // Inside the lambda we can declare another vector and use a loop.
                  std::vector<char> v{};
            
                  for (char ch{ 'a' }; ch <= 'z'; ++ch)
                  {
                      v.push_back(ch);
                  }
            
                  return v;
              }() // Call the lambda right away
            };
            ```
            

# 12.15 - Friend functions and classes

- There exists certain situations in which classes and functions outside these classes got to work closely together. For example, one might have a class to store data and another to display data, though these classes are separate, they are closely tied.
- There exists two methods to allow function access private class data:
    - Have the display code use publicly exposed functions of the stored class. This can unfortunately clutter storage class (due to the need to define them) and leaves the members of the class exposed for any unsolicited edits/misuse.
    - Use a friend class of function. This gives display code access to the private details of the storage class while keeping everybody else out.
- A function that can access the private members of a class as though it was a member of the class is called a **friend function.** Following is the format to declare a friend function
    
    `friend data_type func_name()`
    
    - Example 1
        
        ```cpp
        class Accumulator
        {
        private:
        	int m_value { 0 };
        	// Make reset() a friend of this class
        	friend void reset(Accumulator& accumulator);
        };
        // reset() is now a friend of the accumulator class
        void reset(Accumulator& accumulator)
        {
        	accumulator.m_value = 0;
        }
        int main()
        {
        	Accumulator acc;
        	acc.add(5); // add 5 to the accumulator
        	reset(acc); // reset the accumulaor to 0
        	return 0;
        }
        ```
        
        - Object `acc` is passed to `reset()` . Since `reset()` ain’t a member of the class, it doesn’t have the *this pointer.
    - Example 2
        
        ```cpp
        class Value
        {
        private:
            int m_value{};
        
        public:
            Value(int value)
                : m_value{ value }
            {
            }
        
            friend bool isEqual(const Value& value1, const Value& value2);
        };
        
        bool isEqual(const Value& value1, const Value& value2)
        {
            return (value1.m_value == value2.m_value);
        }
        
        int main()
        {
            Value v1{ 5 };
            Value v2{ 6 };
            std::cout << std::boolalpha << isEqual(v1, v2);
        
            return 0;
        }
        ```
        
- A function can be the friend of multiple classes at once. It can therefore access the private members from multiple classes
    - Example
        
        ```cpp
        #include <iostream>
        
        class Humidity; // This is a class prototype that tells the compiler that we are going to define a class called Humidity in the future. Without this line, the compiler would tell us it doesn’t know what a Humidity is when parsing the prototype for printWeather() inside the Temperature clas
        
        class Temperature
        {
        private:
            int m_temp {};
        
        public:
            Temperature(int temp=0)
                : m_temp { temp }
            {
            }
        
            friend void printWeather(const Temperature& temperature, const Humidity& humidity);
        };
        
        class Humidity
        {
        private:
            int m_humidity {};
        
        public:
            Humidity(int humidity=0)
                : m_humidity { humidity }
            {
            }
        
            friend void printWeather(const Temperature& temperature, const Humidity& humidity);
        };
        
        void printWeather(const Temperature& temperature, const Humidity& humidity)
        {
            std::cout << "The temperature is " << temperature.m_temp <<
               " and the humidity is " << humidity.m_humidity << '\n';
        }
        
        int main()
        {
            Humidity hum{10};
            Temperature temp{12};
        
            printWeather(temp, hum);
        
            return 0;
        }
        ```
        
- Making a **class a friend** of another would give all of the member of the friend class access to the private member of the other class.
    - Example
        
        ```cpp
        #include <iostream>
        
        class Storage
        {
        private:
            int m_nValue {};
            double m_dValue {};
        public:
            Storage(int nValue, double dValue)
               : m_nValue { nValue }, m_dValue { dValue }
            {
            }
        
            // Make the Display class a friend of Storage
            friend class Display;
        };
        
        class Display
        {
        private:
            bool m_displayIntFirst;
        
        public:
            Display(bool displayIntFirst)
                 : m_displayIntFirst { displayIntFirst }
            {
            }
        
            void displayItem(const Storage& storage)
            {
                if (m_displayIntFirst)
                    std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
                else // display double first
                    std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
            }
        };
        
        int main()
        {
            Storage storage{5, 6.7};
            Display display{false};
        
            display.displayItem(storage);
        
            return 0;
        }
        ```
        
        - Even though `Display` is not a friend of `Storage`, it doesn’t have direct access to the *this pointer of storage.
        - Just because `Display` is a friend of `Storage` doesn’t mean `Storage` is a friend of `Display`.
- One can also choose to make a **single member function a friend** instead of an entire class.
    - Example
        
        ```cpp
        #include <iostream>
        
        class Storage; // forward declaration for class Storage
        
        class Display
        {
        private:
        	bool m_displayIntFirst {};
        
        public:
        	Display(bool displayIntFirst)
        		: m_displayIntFirst { displayIntFirst }
        	{
        	}
        
        	void displayItem(const Storage& storage); // forward declaration above needed for this declaration line
        };
        
        class Storage // full definition of Storage class
        {
        private:
        	int m_nValue {};
        	double m_dValue {};
        public:
        	Storage(int nValue, double dValue)
        		: m_nValue { nValue }, m_dValue { dValue }
        	{
        	}
        
        	// Make the Display::displayItem member function a friend of the Storage class (requires seeing the full declaration of class Display, as above)
        	friend void Display::displayItem(const Storage& storage);
        };
        
        // Now we can define Display::displayItem, which needs to have seen the full definition of class Storage
        void Display::displayItem(const Storage& storage)
        {
        	if (m_displayIntFirst)
        		std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
        	else // display double first
        		std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
        }
        
        int main()
        {
            Storage storage(5, 6.7);
            Display display(false);
        
            display.displayItem(storage);
        
            return 0;
        }
        ```
        
        - This might seem like a pain, but this is fortunately due to the fact that we’re trying to do everything within the same file.
        - A better solution would be to put each class definition into a separate header file, with member function definitions in the corresponding `.cpp` files. That way, all of the class definitions would have been visible immediately in the .cpp files, and no rearranging of classes or functions is necessary!
    - Making a specific member function a friend requires the entire class definition of the member to be seen by the class it’s trying to be friend off.

# 12.16 - Anonymous objects

- In certain cases, one would only temporarily require a variable
    - Example
        
        ```cpp
        #include <iostream>
        
        int add(int x, int y)
        {
        	int sum{ x + y };
        	return sum;
        }
        
        int main()
        {
            std::cout << add(5, 3) << '\n';
        
            return 0;
        }
        ```
        
        Here `sum` only serves as a placeholder, it contributes very little to the task the program is trying to accomplish.
        
- Enter **anonymous objects**.
    - These are object without any name, and hence there’s no way to refer to them beyond the point they are created ****
    - Consequently, they have no expression scope, i.e. they are created, evaluated and destroyed all within a single expression.
    - Example 1
        
        ```cpp
        #include <iostream>
        
        int add(int x, int y)
        {
            return x + y; // an anonymous object is created to hold and return the result of x + y
        }
        
        int main()
        {
            std::cout << add(5, 3) << '\n';
        
            return 0;
        }
        ```
        
        When the expression `x+y` is evaluated, the result is placed in an anonymous object. A copy of the anonymous object is then returned to the caller by value and the object is destroyed.
        
    - Example 2 - anonymous objects as function parameters
        
        ```cpp
        #include <iostream>
        
        void printValue(int value)
        {
            std::cout << value;
        }
        
        int main()
        {
            printValue(5 + 3);
        
            return 0;
        }
        ```
        
        In this case, the expression 5 + 3 is evaluated to produce the result 8, which is placed in an anonymous object. A copy of this anonymous object is then passed to the printValue() function, (which prints the value 8) and then is destroyed.
        
- **Anonymous class objects**
    - This can be done by creating objects like normal but omitting the variable name
        
        ```cpp
        Cents cents{ 5 };
        Cents{ 7 };
        ```
        
        `Cents{ 7 }` will create an anonymous Cents object, initialize it with the value 7, and then destroy it
        
    - Example
        
        ```cpp
        #include <iostream>
        
        class Cents
        {
        private:
            int m_cents{};
        
        public:
            Cents(int cents)
                : m_cents { cents }
            {}
        
            int getCents() const { return m_cents; }
        };
        
        void print(const Cents& cents)
        {
           std::cout << cents.getCents() << " cents\n";
        }
        
        // CLASSICAL CASE
        int main()
        {
            Cents cents{ 6 };
            print(cents);
        
            return 0;
        }
        
        // ANONYMOUS CASE
        int main()
        {
            print(Cents{ 6 }); // Note: Now we're passing an anonymous Cents value
        
            return 0;
        }
        
        ```
        
    - Complex Example
        
        ```cpp
        #include <iostream>
        
        class Cents
        {
        private:
            int m_cents{};
        
        public:
            Cents(int cents)
                : m_cents { cents }
            {}
        
            int getCents() const { return m_cents; }
        };
        
        Cents add(const Cents& c1, const Cents& c2)
        {
            Cents sum{ c1.getCents() + c2.getCents() };
            return sum;
        }
        
        // CLASSICAL VERSION
        int main()
        {
            Cents cents1{ 6 };
            Cents cents2{ 8 };
            Cents sum{ add(cents1, cents2) };
            std::cout << "I have " << sum.getCents() << " cents.\n";
        
            return 0;
        }
        
        // SHORT VERSION
        
        Cents add(const Cents& c1, const Cents& c2)
        {
            // List initialization looks at the return type of the function
            // and creates the correct object accordingly.
            return { c1.getCents() + c2.getCents() }; // return anonymous Cents value
        }
        int main()
        {
        	Cents cent1{ 6 };
        	Cents cent2{ 8 };
        	std::cout << "I have " << add(cent1, cent2).getCents() << " cents.\n";
        
            return 0;
        }
        
        // SHORTER VERSION
        
        Cents add(const Cents& c1, const Cents& c2)
        {
            // List initialization looks at the return type of the function
            // and creates the correct object accordingly.
            return { c1.getCents() + c2.getCents() }; // return anonymous Cents value
        }
        int main()
        {
        	std::cout << "I have " << add(cent1{ 6 }, cent2{ 8 }).getCents() << " cents.\n";
        
            return 0;
        }
        ```
        
- Long story short, anonymous object are primarily used to pass or return values without having create of temporary variables. Memory allocated dynamically is also done so anonymously (which is why its address must be assigned to a pointer, otherwise we’d have no way to refer to it).

# 12.17 - Nested types in classes

- Below is an example of class and enum within the same program
    
    ```cpp
    #include <iostream>
    
    enum class FruitType
    {
    	apple,
    	banana,
    	cherry
    };
    
    class Fruit
    {
    private:
    	FruitType m_type {};
    	int m_percentageEaten { 0 };
    
    public:
    
    	Fruit(FruitType type) :
    		m_type { type }
    	{
    	}
    
    	FruitType getType() const { return m_type;  }
    	int getPercentageEaten() const { return m_percentageEaten;  }
    };
    
    int main()
    {
    	Fruit apple { FruitType::apple };
    
    	if (apple.getType() == FruitType::apple)
    		std::cout << "I am an apple";
    	else
    		std::cout << "I am not an apple";
    
    	return 0;
    }
    ```
    
- While the above program seems correct, it’s a little weird that `FruitType` exists independently from `Fruit`.
- Much like functions and data can be members of a class, in C++, types can also be defined (nested) inside of a class
    - Example
        
        ```cpp
        #include <iostream>
        
        class Fruit
        {
        public:
        	// Note: we've moved FruitType inside the class, under the public access specifier
        	enum FruitType
        	{
        		apple,
        		banana,
        		cherry
        	};
        
        private:
        	FruitType m_type {};
        	int m_percentageEaten { 0 };
        
        public:
        
        	Fruit(FruitType type) :
        		m_type { type }
        	{
        	}
        
        	FruitType getType() const { return m_type;  }
        	int getPercentageEaten() const { return m_percentageEaten;  }
        };
        
        int main()
        {
        	// Note: we access the FruitType via Fruit now
        	Fruit apple { Fruit::apple };
        
        	if (apple.getType() == Fruit::apple)
        		std::cout << "I am an apple";
        	else
        		std::cout << "I am not an apple";
        
        	return 0;
        }
        ```
        
    - `FruitType` is now defined within the class under the public access specifier.
    - Classes essentially act as namespace for any nested types.
    - In the above example were we to use “enum class” instead, we would have had to qualify the enum type with a scope qualifier (eg `Fruit::FruitType:`). This double-scoping is unnecessary, so a normal enum was used.
- C++ also lets one define other types within as class, such as typedefs, type aliases, and even other classes.
- Like any normal member, nested classes have the same access to members of the enclosing class that the enclosing class does.
    - However the nested class does not have any special access to the “this” pointer of the enclosing class.
    - Additionally, nested type can’t be forward declared.

# 12.18 - Timing your code

- The **chrono** library in C++ come with the functionality of timing ones code. And one can put into use these functionalities by encapsulating all of it into a class and making use of it through defined objects.
    - The Timer class
        
        ```cpp
        #include <chrono>
        
        class Timer
        {
        private:
        	// Type aliases to make accessing nested type easier 
        	using clock_type = std::chrono::steady_clock;
        	using second_type = std::chrono::duration<double, std::ration<1> >;
        	std::chorno::time_point<clock_type> m_beg { clock_type::now() };
        
        public:
        	void reset()
        	{
        		m_beg = clock_type::now();
        	}
        	double elapsed() const
        	{
        		return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
        	}
        };
        ```
        
    - Simple example
        
        ```cpp
        #include <iostream>
        
        int main()
        {
        	Timer t;
        	std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";
        	return 0;
        }
        ```
        
    - Selection sort example 1
        
        ```cpp
        #include <array>
        #include <chrono> // for std::chrono functions
        #include <cstddef> // for std::size_t
        #include <iostream>
        #include <numeric> // for std::iota
        
        const int g_arrayElements { 10000 };
        
        class Timer
        {
        private:
            // Type aliases to make accessing nested type easier
            using clock_type = std::chrono::steady_clock;
            using second_type = std::chrono::duration<double, std::ratio<1> >;
        
            std::chrono::time_point<clock_type> m_beg{ clock_type::now() };
        
        public:
        
            void reset()
            {
                m_beg = clock_type::now();
            }
        
            double elapsed() const
            {
                return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
            }
        };
        
        void sortArray(std::array<int, g_arrayElements>& array)
        {
        
            // Step through each element of the array
            // (except the last one, which will already be sorted by the time we get there)
            for (std::size_t startIndex{ 0 }; startIndex < (g_arrayElements - 1); ++startIndex)
            {
                // smallestIndex is the index of the smallest element we’ve encountered this iteration
                // Start by assuming the smallest element is the first element of this iteration
                std::size_t smallestIndex{ startIndex };
        
                // Then look for a smaller element in the rest of the array
                for (std::size_t currentIndex{ startIndex + 1 }; currentIndex < g_arrayElements; ++currentIndex)
                {
                    // If we've found an element that is smaller than our previously found smallest
                    if (array[currentIndex] < array[smallestIndex])
                    {
                        // then keep track of it
                        smallestIndex = currentIndex;
                    }
                }
        
                // smallestIndex is now the smallest element in the remaining array
                // swap our start element with our smallest element (this sorts it into the correct place)
                std::swap(array[startIndex], array[smallestIndex]);
            }
        }
        
        int main()
        {
            std::array<int, g_arrayElements> array;
            std::iota(array.rbegin(), array.rend(), 1); // fill the array with values 10000 to 1
        
            Timer t;
        
            sortArray(array);
        
            std::cout << "Time taken: " << t.elapsed() << " seconds\n";
        
            return 0;
        }
        ```
        
        On the author’s machine, three runs produced timings of 0.15, 0.14, and 0.16. So we can say around 0.15 seconds.
        
    - Selection sort example 2 (`std::sort`)
        
        ```cpp
        #include <algorithm> // for std::sort
        #include <array>
        #include <chrono> // for std::chrono functions
        #include <cstddef> // for std::size_t
        #include <iostream>
        #include <numeric> // for std::iota
        
        const int g_arrayElements { 10000 };
        
        class Timer
        {
        private:
            // Type aliases to make accessing nested type easier
            using clock_type = std::chrono::steady_clock;
            using second_type = std::chrono::duration<double, std::ratio<1> >;
        
            std::chrono::time_point<clock_type> m_beg{ clock_type::now() };
        
        public:
        
            void reset()
            {
                m_beg = clock_type::now();
            }
        
            double elapsed() const
            {
                return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
            }
        };
        
        int main()
        {
            std::array<int, g_arrayElements> array;
            std::iota(array.rbegin(), array.rend(), 1); // fill the array with values 10000 to 1
        
            Timer t;
        
            std::ranges::sort(array); // Since C++20
            // If your compiler isn't C++20-capable
            // std::sort(array.begin(), array.end());
        
            std::cout << "Time taken: " << t.elapsed() << " seconds\n";
        
            return 0;
        }
        ```
        
        On the author’s machine, this produced results of: 0.00004, 0.00006, and 0.00005. So basically right around 0.00005. 10000 times faster !!!
        
- Caveats concerning the use of a timer
    - One needs to ensure that a release build target is being used, not a debug build target. Debug build targets typically turn optimization off, which could have a significant impact on the results.
    - Timing will be influenced by other things one’s system may be doing in the background - for better results make sure that your system isn’t doing anything CPU or RAM or ROM intensive. Tests must then be conducted at least 3 times and the results averaged to arrive at robust resutls.
    - Third, when doing comparisons between two sets of code, be wary of what may change between runs that could impact timing.
        - Your system may have kicked off an antivirus scan in the background, or maybe you’re streaming music now when you weren’t previously.
        - Randomization can also impact timing. If we’d sorted an array filled with random numbers, the results could have been impacted by the randomization. Randomization can still be used, but ensure you use a fixed seed so the randomization is identical each run.
    - Results obtained are only valid for one’s machine’s architecture, OS, compiler and system specs.

# 12.x - Chapter 12 comprehensive quiz

- Classes allow one to create one’s own data types and functions that work on that data. Data and functions inside a class are called **members**. To access the members, the ‘.’ operator is used or ‘→’ (~ (*ptr).) if one is accessing the member though a pointer.
- Access specifiers allow one to specify who can access the members of a class. **Public** members can be accessed by anybody, **private** members can only be accessed by other members of the class.
- Encapsulation is the process of making all of one’s member data private, to disallow direct access. This helps protect the class from misuse.
- Constructors are a special type of member function that allows one to initialize objects of a class. A constructor that takes no parameters (or has all default parameters) is called a **default constructor**. Classes must be provided with at least one constructor.
- **Member initializers lists** allows one to initialize member variables through a constructor
- **Non-static member** initialization allows one to directly specify default values for member variables when they are initialized.
- **Constructors** are allowed to call other constructors (called **delegating** constructors or constructor **chaining**)
- **Destructors** are a special type of member function that allow your class to clean up after itself. Any kind of deallocation or shutdown routines should be executed from here.
- All member functions have a hidden ***this** pointer that points to the class being modified.
- It’s **good programming** style to put class definitions in a header file of the same name as the class, and define class functions in a `.cpp` file of the same name as the class. This also helps with **circular dependencies**.
- **Member functions** can and should be made **const** if they don’t modify the state of the class. **Const** class objects can only call **const member functions**.
- **Static member variables** are shared among all objects of the class. Although they can be accessed through a class object, they can also be accessed through a scope resolution operator (recommended).
- **Friend functions** are treated like members of a class and hence can access class’s private data directly. **Friend classes** are classes where all members of the class are considered friend functions.
- It’s possible to create **anonymous** **class** **objects** for the purpose of evaluation or returning a value.
- One can also nest types within a class. This is often used with enums related to class, but can be done with other types if desired.