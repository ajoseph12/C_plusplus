# O - Bit Manipulation

# O.1 - Bit flags and bit manipulation via std::bitset

On modern computers the smallest addressable unit of memory is a byte. So all object need to be assigned a unique address which must have a size of at least 1 byte. While this is fine more most objects, this is a wasteful practice when dealing with boolean objects, that take either 0 or 1 as value. 

To this end it would make sense to pack 8 individual boolean values into a single byte. Doing this would require one to be able to manipulate objects at a bit level, called **bit manipulation**. 

- **Bit flags** - name given to bits when individual bits of an object are used as Boolean values. A big flag is defined in the following manner :

        #include <bitset> // for std::bitset
        std::bitset<8> mybitset {}; // 8 bits in size means room for 8 flags

- Bit numbering is usually effectuated from right to left :

        76543210  Bit position       00000101  Bit sequence // positions 0 and 2 have value 0

## Manipulating bits via std::bitset

std::bitset provides 4 key functions that are useful for performing bit manipulation

- test() : allows one to query whether a bit is 0 or 1
- set() : allows one to turn a bit on  (does nothing if bit is already on)
- reset() : allows one to turn a bit off (does nothing if bit is already off)
- flip() : allows one to flip a bit value from a 0 to a 1 and vice versa

    #include <bitset>
    #include <iostream>
     
    int main()
    {
        std::bitset<8> bits{ 0b0000'0101 }; // we need 8 bits, start with bit pattern 0000 0101
        bits.set(3); // set bit position 3 to 1 (now we have 0000 1101)
        bits.flip(4); // flip bit 4 (now we have 0001 1101)
        bits.reset(4); // set bit 4 back to 0 (now we have 0000 1101)
     
        std::cout << "All the bits: " << bits << '\n';
        std::cout << "Bit 3 has value: " << bits.test(3) << '\n';
        std::cout << "Bit 4 has value: " << bits.test(4) << '\n';
     
        return 0;
    }
    
    // All the bits: 00001101
    // Bit 3 has value: 1
    // Bit 4 has value: 0

# O.2 - Bitwise operators

C++ provides the following 6 bit manipulation operators called **bitwise** operators

- 1100 >> 3 is 0001
- 0011 << 2 is 1100

![O%20Bit%20Manipulation/Untitled.png](O%20Bit%20Manipulation/Untitled.png)

## Aren't << and >> used for output and input?

In this program, the operator << knows when to shift to the right and when to output a value.

- std::cout has **overloaded** operator that performs console outputting that bit operation.
- when the complier sees the left of  operator << is std::cout, it knows that it should call the version of operator << that std::cout overloaded to do output.
- If <<'s left operand is integral type, the compiler enables bit-shifting behavior

    #include <iostream>
     
    int main()
    {
        unsigned int x { 0b0100 };
        x = x << 1; // use operator<< for left shift
        std::cout << std::bitset<4>{ x }; // use operator<< for output
    		std::bitset<4> x{ 0b0110 };
    		std::cout << x << 1 << '\n'; // print value of x (0110), then 1
    		std::cout << (x << 1) << '\n'; // print x left shifted by 1 (1100)
        return 0;
    }
    # output : 1000

## Bitwise Operators

- Bitwise NOT (~) : flips the bits in a byte (0 to 1 and 1 to 0)
    - flipping 4 bits : ~0100 is 1011
    - flipping 8 bits : ~0000 0100 is 1111 1011

    0100 is equal to 0000 0100, however the not operation results in different values.

- Bitwise OR (|) : works more like the logical OR counterpart
    - 0101 | 0110 = 0111
- Bitwise AND (&) : works more like the logical AND counterpart
    - 0101 & 0110 = 0100
- Bitwise XOR (^) : evaluates to 1 if and only if one of its operands is true
    - 0101 ^ 0110 = 0101

    #include <iostream>
    #include <bitset>
    
    int main()
    {
    	std::cout << std:bitset<4>{~0b0100u} ;
    	std::cout << (std::bitset<4>{0b0101} | std::bitset<4>{0b0110}); 
    	std::cout << (std::bitset<4>{0b0101} & std::bitset<4>{0b0110});
    	std::cout << (std::bitset<4>{0b0101} ^ std:bitset<4>{0b0110});
    }
    # output
    1011
    0111
    0100
    0101

## Bitwise Assignment Operators

Similar to arithmetic assignment operators

    int main()
    {
    	std::bitset<4> bits {0b0100};
    	bits >>= 1 // instead of bits = bits >> 1
    	std::cout << bits;
    }

![O%20Bit%20Manipulation/Untitled%201.png](O%20Bit%20Manipulation/Untitled%201.png)

    // QUIZ : A bitwise rotation is like a bitwise shift, except that any bits shifted off 
    // one end are added back to the other end. For example 0b1001 << 1 would be 0b0010, 
    // but a left rotate by 1 would result in 0b0011 instead. Implement a function 
    // that does a left rotate on a std::bitset<4>. For this one, it's okay to use 
    // std::bitset<4>::test() and std::bitset<4>::set().
    
    #include <iostream>
    #include <bitset>
     
    std::bitset<4> rotl(std::bitset<4> bits)
    {
    // Your code here
    }
     
    int main()
    {
    	std::bitset<4> bits1{ 0b0001 };
    	std::cout << rotl(bits1) << '\n';
     
    	std::bitset<4> bits2{ 0b1001 };
    	std::cout << rotl(bits2) << '\n';
     
    	return 0;
    }

# O.3 - Bit manipulation with bitwise operators and bit masks

A **bit mask** is a predefined set of bits that's used to select which specific bits will be modified by subsequent operations. 

## Defining bit masks

Following are ways to define bit masks

    // in C++ 14
    constexpr std::uint_fast8_t mask0{0b000'0001 } // represents bit 0
    
    // in C++ 11 and earlier 
    constexpr std::uint_fast8_t mask0{ 0x1 } // hex for 0000 0001
    constexpr std::uint_fast8_t mask0{ 1 << 0 } // // 0000 0001

## Testing, setting resetting and flipping

- The code below tests to see if a bit is on or off. The and (&) bitwise operator is used to do this.

        #include <stream>
        int main()
        {
        	constexpr std::uint_fast8_t mask0{ 0b0000'0001 }; // represents 0
        	constexpr std::uint_fast8_t mask1{ 0b0000'0010 }; // represents 1
        	std::uint_fast8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
        	
        	std::cout << "bit 0 is" << ((flags&mask0)? "on\n" :"of\n");  // bit 0 is on
        	std::cout << "bit 1 is" << ((flags&mask1)? "on\n" : "of\n"); // bit 0 is off
        	return 0;
        }

- The code below sets a bit on (turn it on) using the OR (|) bitwise operator

        #include <stream>
        int main()
        {
        	constexpr std::uint_fast8_t mask1{ 0b0000'0010 }; // represents 1
        	std::uint_fast8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
        	
        	std::cout << "bit 1 is" << ((flags&mask1)? "on\n" : "of\n") // bit 1 is off
        	flags |= mask1
        	std::cout << "bit 1 is" << ((flags&mask1)? "on\n" : "of\n") // bit 1 is on
        	return 0;
        }
        
        // to turn on multiple bits, one can do the following 
        flags |= (mask4 | mask5); // turn bits 4 and 5 on at the same time

- Clearing a bit (turning it off) would required one to use bitwise AND (&) and NOT (~) operators

        #include <stream>
        int main()
        {
        	constexpr std::uint_fast8_t mask2{ 0b0000'0100 }; // represents 1
        	std::uint_fast8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
        	
        	std::cout << "bit 2 is" << ((flags&mask1)? "on\n" : "of\n") // bit 2 is on
        	flags &= ~mask2
        	std::cout << "bit 2 is" << ((flags&mask1)? "on\n" : "of\n") // bit 2 is off
        	return 0;
        }
        
        // multiple bit can be turned off at the same time 
        flags &= ~(mask4 | mask5); // turn bits 4 and 5 off at the same time

- Flipping a bit state would require the usage of XOR

        #include <stream>
        int main()
        {
        	constexpr std::uint_fast8_t mask2{ 0b0000'0100 }; // represents 1
        	std::uint_fast8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
        	
        	std::cout << "bit 2 is" << ((flags&mask1)? "on\n" : "of\n") // bit 2 is on
        	flags ^= mask2
        	std::cout << "bit 2 is" << ((flags&mask1)? "on\n" : "of\n") // bit 2 is off
        	flags ^= mask2
        	std::cout << "bit 2 is" << ((flags&mask1)? "on\n" : "of\n") // bit 2 is on
        	return 0;
        }
        
        // multiple bits can be flipped simultaneously 
        flags ^= (mask4 | mask5); // flip bits 4 and 5 at the same time

Long story short, it'd make more sense using bitmasks over functionalities like test, set or flip as one can handle multiple bit while employing the latter. 

## Bit masks and std::bitset

    int main()
    {
    	constexpr std::bitset<8> mask0{ 0b0000'0001 };
    	constexpr std::bitset<8> mask1{ 0b0000'0010 };
    	constexpr std::bitset<8> mask2{ 0b0000'0100 };
    
    	std::bitset<8> flags{ 0b0000'0101 };
    	
    	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
    	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");
    	flags ^= (mask1 | mask2); // flip bits 1 and 2
     
    	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
    	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");
    	flags |= (mask1 | mask2); // turn bits 1 and 2 on
     
    	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
    	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");
    	flags &= ~(mask1 | mask2); // turn bits 1 and 2 off
     
    	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
    	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");
     
    	return 0;
    }

## When are bit flags most useful?

    int main()
    {
        // Define a bunch of physical/emotional states
        std::bitset<8> isHungry{    0b0000'0001 };
        std::bitset<8> isSad{        0b0000'0010 };
        std::bitset<8> isMad{        0b0000'0100 };
        std::bitset<8> isHappy{        0b0000'1000 };
        std::bitset<8> isLaughing{    0b0001'0000 };
        std::bitset<8> isAsleep{    0b0010'0000 };
        std::bitset<8> isDead{        0b0100'0000 };
        std::bitset<8> isCrying{    0b1000'0000 };
    
    
        std::bitset<8> me{}; // all flags/options turned off to start
        me |= isHappy | isLaughing; // I am happy and laughing
        me &= ~isLaughing; // I am no longer laughing
    
        // Query a few states (we use the any() function to see if any bits remain set)
        std::cout << "I am happy? " << (me & isHappy) << '\n';
        std::cout << "I am laughing? " << (me & isLaughing) << '\n';
    
        return 0;
    }

- The above program don't actually save any memory - 8 booleans take about 8 bytes +  1 byte for the flag.
- Bit flags make the most sense when one has many identical flag variables, Eg: In the example above instead of having one person (me), imagine one has 100. And if 8 booleans were used per person, this would tally up to 800 bytes of memory.
    - With bit flags, one one would use 8 bytes for bit masks, and 100 bytes for bit flag ( 1 per person) tallying up to 108 bytes of memory
- Imagine if one has a function that could take any combination of 32 different options. One way to write the function would be to use 32 individual boolean parameters. Additionally, calling the function is going to be equally messy.

        void someFunction(bool option1, bool option2, bool option3, bool option4, bool option5, 
        	bool option6, bool option7, bool option8, bool option9, bool option10, bool option11, 
        	bool option12, bool option13, bool option14, bool option15, bool option16, bool option17,
        	bool option18, bool option19, bool option20, bool option21, bool option22, bool option23,
        	bool option24, bool option25, bool option26, bool option27, bool option28, bool option29, 
        	bool option30, bool option31, bool option32);	
        someFunction(false, false, false, false, false, false, false, false, false, true,
        	false, false, false, false, false, false, false, false, false, false, false, 
        	false, false, false, false, false, false, false, false, false, false, true);

    - Instead the function could be defined using flags, and can be called using bitwise operators

            void someFunction(std::bitset<32> options);
            someFunction(option10 | option32)

## Bit masks involving multiple bits

    #include <cstdint>
    #include <iostream>
    
    int main()
    {
        constexpr std::uint_fast32_t redBits{ 0xFF000000 };
        constexpr std::uint_fast32_t greenBits{ 0x00FF0000 };
        constexpr std::uint_fast32_t blueBits{ 0x0000FF00 };
        constexpr std::uint_fast32_t alphaBits{ 0x000000FF };
        
        std::cout << "Enter a 32-bit RGBA color value in hexadecimal (e.g. FF7F3300): ";
        std::uint_fast32_t pixel{};
        std::cin >> std::hex >> pixel; // std::hex allows us to read in a hex value
        
        // use Bitwise AND to isolate red pixels,
        // then right shift the value into the lower 8 bits
        // (we're not using brace initialization to avoid a static_cast)
        std::uint_fast8_t red = (pixel & redBits) >> 24;
        std::uint_fast8_t green = (pixel & greenBits) >> 16;
        std::uint_fast8_t blue = (pixel & blueBits) >> 8;
        std::uint_fast8_t alpha = pixel & alphaBits;
        
        
        std::cout << "Your color contains:\n";
        std::cout << std::hex; // print the following values in hex
        std::cout << static_cast<int>(red) << " red\n";
        std::cout << static_cast<int>(green) << " green\n";
        std::cout << static_cast<int>(blue) << " blue\n";
        std::cout << static_cast<int>(alpha) << " alpha\n";
        
        return 0;
    }

![O%20Bit%20Manipulation/Untitled%202.png](O%20Bit%20Manipulation/Untitled%202.png)

## Summary

- To query bit states, one can use bitwise AND

    if (flags & option4) // if option4 is set, do something

- To set bits (turn on), one can use bitwise OR

    flags |= option4; // turns option 4 on
    flags |= (option4 | option5); // turns option 4 and 5 on

- To clear bits (turn off), one can use bitwise AND and NOt

    flags &= ~option4; // turn option 4 off
    flags &= ~(option4 | option5); // turns option 4 and 5 on

- To flip bit states, we use bitwise XOR

    flags ^= option4; // flips option 4 
    flags ^= (option4 | option5) // flip options 4 and 5

# O.4 - Converting between Binary and Decimal

- Take the decimal number 5623, we understand that these digits mean (5 * 1000) + (6 * 100) + (2 * 10) + (3 * 1).
- Binary number can be expressed in a similar fashion too. Take the example of 0101 1110 which can be expressed as (0 * 128) + (1 * 64) + (0 * 32) + (1 * 16) + (1 * 8) + (1 * 4) + (1 * 2) + (0 * 1) = 94. Below is another example:

![O%20Bit%20Manipulation/Untitled%203.png](O%20Bit%20Manipulation/Untitled%203.png)

## Methods for Decimal to Binary Conversion and Adding in Binary

**Method 1** : continually dividing the decimal number by 2 and noting down the remainders. The binary value is constructed at the end from the remainders, from the bottom up.

- Converting 148  from decimal to binary.
- 148 decimal = 1001 0100 binary.

![O%20Bit%20Manipulation/Untitled%204.png](O%20Bit%20Manipulation/Untitled%204.png)

**Method 2** : working backwards to figure out what each of the bits must be. An easier method with small binary numbers. Taking the example of decimal number 148

- 128 is the largest power of 2 that's smaller than 148
- Is 148 > 128? Yes : 128 bit must be 1 (148 - 128 =20, which means we need to find bits worth 20 more)
- Is 20 ≥ 64? No : so 64 must be 0

- Is 20 ≥ 32? No : so 32 bit must be 0
- Is 20 ≥ 16? Yes : so 16 bit must be 1
- Is 4 ≥ 8? No : so 8 bit must be 0

![O%20Bit%20Manipulation/Untitled%205.png](O%20Bit%20Manipulation/Untitled%205.png)

- is 4 ≥ 4? No : so 4 bit must be 1 (1.4 -4 = 0)

**Adding in binary**

![O%20Bit%20Manipulation/Untitled%206.png](O%20Bit%20Manipulation/Untitled%206.png)

# Signed numbers and two's complement

- Signed integers are typically stored using a method know as the two's complement.
    - In 2's complement, the left most bit is the signed bit
    - 0 sign bit means number is positive and 1 sign bit means number is negative
- Positive signed numbers are represented in binary just like positive unsigned numbers (with the sign bit set to 0)
- Negative signed numbers are represented in binary as the bitwise inverse of the positive number, plus 1. 1 is added else 0 would have two values 0000 and 1111

![O%20Bit%20Manipulation/Untitled%207.png](O%20Bit%20Manipulation/Untitled%207.png)

![O%20Bit%20Manipulation/Untitled%208.png](O%20Bit%20Manipulation/Untitled%208.png)

- **Convert binary tow's complement**
    - If the sign bit is 0, the conversion is similar to that of unsigned
    - If the sign bit is 1, then we invert the bits, add 1, then convert to decimal

![O%20Bit%20Manipulation/Untitled%209.png](O%20Bit%20Manipulation/Untitled%209.png)

- **Why type matters?**
    - Consider binary 1011 0100, this would equate to 180 where the binary type to be standard unsigned binary number
    - If the same value was stored in 2s complement, it would be -76
    - Therefore the type of the variable determines how a variable's value is encoded into binary and decoded back into a value.