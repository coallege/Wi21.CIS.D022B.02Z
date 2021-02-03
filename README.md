# Wi21.CIS.D022B.02Z

*CIS 22B - Intermediate Programming Methodologies in C++*

<img src="misc/icon0_500px.png" width="300px"/>

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

Constructor uniform field initialization:

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
