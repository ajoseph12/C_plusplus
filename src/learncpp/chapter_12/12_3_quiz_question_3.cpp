//
//  12_3_quiz_question_3.cpp
//  learncpp
//
//  Created by allwyn joseph on 3/20/22.
//  Copyright © 2022 allwyn joseph. All rights reserved.
//

#include <iostream>

class Stack
{
    int arr[10] {};
    int idx_ptr {0};
    
public:
    void reset()
    {
        idx_ptr = 0;
    }
    bool push(int a)
    {
        if (idx_ptr < (sizeof(arr)/sizeof(arr[0])))
        {
            arr[idx_ptr] = a;
            idx_ptr += 1;
            return 1;
        }
        else
            return 0;
    }
    int pop()
    {
        assert (idx_ptr);
        
        int poped_item { arr[idx_ptr ] };
        arr[idx_ptr] = 0;
        idx_ptr -= 1;
        
        return poped_item;
    }
    void print()
    {
        std::cout << "( ";
        for(int i{ 0 }; i < idx_ptr; i++)
            std::cout << arr[i] << " ";
        std::cout << ")\n";
    }
};

int main()
{
    
    Stack stack;
    stack.reset();
    
    stack.print();
    
    stack.push(5);
    stack.push(3);
    stack.push(8);
    stack.print();
    
    stack.pop();
    stack.print();
    
    stack.pop();
    stack.pop();
    
    stack.print();
    
    return 0;
}
