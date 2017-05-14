FibonacciHeap
=============

An efficient, straightforward and user friendly implementation of the *minimum fibonacci heap* data structure written in C++. It uses template in order to make it generic, as long as the user points to a comparation function when invoking the constructor.

It supports

* Instantiation

```cpp
//int compar(int a, int b) is a comparation function
FibonacciHeap<int> *fh = new FibonacciHeap<int>(compar);
```

* Insertion

```cpp
fh->push(5);
```

* Size verification

```cpp
int size = fh->size();
```

* Top element verification

```cpp
int top = fh->top();
```

* Reseting entails memory liberation

```cpp
fh->reset();
```
