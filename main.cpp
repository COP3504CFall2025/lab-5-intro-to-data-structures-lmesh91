#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    ABDQ<int> example;
    example.pushFront(1);
    example.pushBack(2);
    example.pushFront(3);
    example.pushBack(4);
    example.pushFront(5);
    example.pushBack(6);
    example.pushFront(7);
    example.PrintForward();
    std::cout << "-----------" << std::endl;
    example.popBack();
    example.popBack();
    example.popBack();
    example.popBack();
    example.PrintForward();
    return 0;
}


#endif