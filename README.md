# Wi21.CIS.D022B.02Z

*CIS 22B - Intermediate Programming Methodologies in C++*

<img src="misc/icon0_500px.png" width="300px"/>

What|Opens|Closes
-|-|-
[lab01](lab01)|`01/05`|`01/15`
[lab02](lab02)|`01/03`|`02/05`
[lab03](lab03)|`02/06`|`02/19`
[lab04](lab04)|`02/06`|`03/05`
[lab05](lab05)|`02/06`|`03/19`

## Reasons why you shouldn't steal my code:

- You learn nothing
- You make me look bad
- My code looks bad
- My coding style is somewhat unconventional
- You're going to have a difficult time explaining how things work if you get caught
- You're breaking the [De Anza Academic Honesty Policy](ACADEMIC_HONESTY.md)

## Anyways

You know, this course looks like it's going to be a whole lot of suffering if I
don't figure out how to code effectively.

The prof for this course seems pretty baller.
I think this is going to be a fun one.

## Learnings

This is just stuff I figured out or learned by doing assignments in here.
There's way more actual other cool stuff that I learned during this time but I
wouldn't really say that this course was the cause of it.

### Constructor uniform field initialization:

```cpp
// as seen in @coalpha/coalpha.github.io/cxx/constructor_initializer.cxx
class NoError {
   char c;
public:
   NoError(int c): c(c) {};
};

class HasError {
   char c;
public:
   HasError(int c): c{c} {};
};
```

### Exceptions (bad)

```cpp
// etc
throw {} catch (...) {};
```

### Member function pointers

```cpp
template<class Clazz, class ...Ts>
using method = void (Clazz::*)(Ts ...args);
```

### cin to string

```cpp
string hello;
cin >> hello; // with "hello world"
```

### set and map kinda

I'm not writing an example for how to use these.

## Class Retrospective

During this quarter, the only thing I really learned from class was vectors
maybe and C++ object orientation. That'd be constructors, copy constructors,
operator overloading, virtual functions, constructor inheritance, constructor
order, and maybe the existence of `std::map` and `std::set`. Overall during my
entire quarter in and out of class, I learned surprisingly little. The largest
personal learning event that happened was me trying to use non-standard C++ to
make cursed arrays.
See [@coalpha/coalpha.github.io/cxx/ary{,2}.cxx](https://github.com/coalpha/coalpha.github.io/tree/master/cxx). One thing I learned while doing lab_5.1 was CRTP, which is a really
cool pattern. Could probably use that instead of virtual functions in a lot of
cases.

Overall, I guess the class was okay, I suppose. The professor was understanding,
accessible, and willing to help out. Honestly, that's already good in my book.
But he was also funny and never got mad, actually so yeah, bonus. Having the
course on discord is a big plus because it meant that I could actually meet and
talk to some of the students... kinda.
