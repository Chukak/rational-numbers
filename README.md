# rational-numbers

## How to use
Rational numbers class. Stores numbers in the format `2/3`. Creation:

```cpp
rational a(2, 3); rational a = {2, 3}; rational a; 
```

You can be added, substract, multiply and divide two rational numbers. 
For example add two rational numbers:

```cpp
rational a(2, 3);
rational b(2, 3);
rational c = a + b;
```

```cpp
rational a(2, 3);
rational b(2, 3);
a += b
```

You can compare two rational numbers. For example compare two numbers:

```cpp
rational a(2, 3);
rational b(2, 3);
if (a == b)
```

```cpp
rational a(2, 3);
rational b(2, 3);
if (a > b)
```

You can check `true` or `false` rational. For example:

```cpp
rational a(0, 1);
bool c = r ? true : false; // c == false
if (!a) { ... }
rational a(2, 3)
bool c = r ? true : false; // c = true
if (a) { ... } 
```

You can use input and output for rational numbers. For example:

```cpp
rational a;
cin >> a;
cout << a;
```

You can use rational in vector, map, tuple, set. For example:

```cpp
vector<rational> a = {{2, 1}, {3, 4}};
set<rational> a = {{2, 1}, {3, 4}};

tuple<rational, rational, rational> a = make_tuple(rationa(2, 1), rational(3, 4), rational(5, 4));

map<rational, int> a; 
rational r= {2, 1};
map[r] = 1;
```

## Tests
Main.cpp by default run tests.
File test.cpp contains more information.

<hr>
