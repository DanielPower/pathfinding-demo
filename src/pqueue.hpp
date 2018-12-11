#pragma once
#include <queue>
using namespace std;

/*
 * STL implementation of a priority queue does not allow access to the underlying vector
 * We require access to this vector to visualize the open list
 * Passing greater makes this a min queue. This will likely not need to change in our implementation
 */
template<class T>
class pQueue : public priority_queue<T, std::vector<T>, std::greater<T>> {
public:
	vector<int>& get_vec() { return c; }
};