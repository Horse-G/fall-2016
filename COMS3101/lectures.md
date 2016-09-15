# C++ Language, COMS3101
## Lecture 01, 2016-09-06
I skipped this class because I am a dummy.

## Lecture 02, 2016-09-13
Lecture notes will not be exhaustive. The example programs are also extremely simplistic.

There will be 4 homeworks, for 70% of the grade. Due every Friday. Only submit _source files_ and only to Courseworks.

### Last time
Covered C, control statements, basic data types, arrays, the String class

### Now
Everything that works in C works in C++.

C++ uses object oriented programming.

### Functions
If you don't write a return, the compiler will do whatever it feels like.
```c++
<return_type> fn_name(arguments)
{
	// function body
}
```

### Pointers
'&' accesses the address of a variable.

### Structures

```c++
typedef struct
{
	int a,b,c;
	float x,y,z;
} myStruct;

myStruct m;
m.a = 1;
```