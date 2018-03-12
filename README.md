# rational-numbers

## How to use
Rational numbers class. Stores numbers in the format `2/3`. Creation:

``` rational a(2, 3); rational a = {2, 3}; rational a; ```

You can be added, substract, multiply and divide two rational numbers. 
For example add two rational numbers:

``` 
rational a(2, 3);
rational b(2, 3);
rational c = a + b;
```

```
rational a(2, 3);
rational b(2, 3);
a += b
```

You can compare two rational numbers. For example compare two numbers:

```
rational a(2, 3);
rational b(2, 3);
if (a == b)
```

```
rational a(2, 3);
rational b(2, 3);
if (a > b)
```

```
rational a(0, 1);
if (!a) // return false
rational a(2, 3)
if (!a) // return true
```

You can use input and output for rational numbers. For example:

```
rational a;
cin >> a;
cout << a;
```

## Tests
Main.cpp by default run tests for rational numbers. Check test.cpp for more information.

<hr>
