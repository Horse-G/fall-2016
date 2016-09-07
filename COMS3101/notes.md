# C++ Language, COMS3101
Notes

## C++ Language Tutorial, 2016-09-07
### Basics of C++
#### Structure of a program
The best way to begin understanding a new language is by understanding how an example 'Hello World' program works:
```c++
// my first program in C++
#include <iostream>

int main()
{
	std::cout << "Hello World!";
}
```
Let's break it down line by line:

1. two slashes mark a single line comment. Any characters contained in such a comment are ignored by the compiler (they don't affect the behavior of the program). They are helpful to make short explanations regarding the code or program - here it is being used as an introductory description.
2. lines starting with the hash character are known as **preprocessor directives**, and that is because they are interpreted before compilation of the program begins. `#include` tells the compiler to "include" a file in the compilation, which in this case is the standard C++ header known as `iostream`, where this header allows for the performance of standard input and output operations.
3. blank lines are similar to single line comments in that they have no effect on the behavior of the program. However, they may allow for increased readability.
4. 

#### Variables and types
#### Constants
#### Operators
#### Basic input/output

### Program structure
#### Control structures
#### Functions
#### Overloads and templates
#### Name visibility
### Compound data types
#### Arrays
#### Character sequences
#### Pointers
#### Dynamic memory
#### Data structures
#### Other data types
### Classes
#### Classes I
#### Classes II
#### Special members
#### Friendship and inheritance
#### Polymorphism
### Other language features
#### Type conversions
#### Exceptions
#### Preprocessor directives
### C++ Standard Library
#### Input/output with files
