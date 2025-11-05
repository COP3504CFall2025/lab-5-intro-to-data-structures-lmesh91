#ifdef MAIN

//#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
//#include "LLDQ.hpp"
//#include "LLQ.hpp"
//#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    ABQ<int> example;
    example.enqueue(1);
    example.enqueue(2);
    example.dequeue();
    example.enqueue(3);
    std::cout << example.peek() << std::endl;
    example.printForward();
    example.dequeue();
    example.dequeue();
    return 0;
}


#endif