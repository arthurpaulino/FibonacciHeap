# FibonacciHeap
An implementation of the *minimum fibonacci heap* data structure written in C++. The constructor requires a pointer to a comparision function.
* Instantiation
```cpp
//int compar(int a, int b) is a comparision function
FibonacciHeap<int> *fh = new FibonacciHeap<int>(compar);
```
* Insertion
```cpp
fh->push(5);
```
* Popping
```cpp
int pop = fh->pop();
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
