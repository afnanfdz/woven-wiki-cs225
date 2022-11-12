/**
 * @file main.cpp
 *
 * Expected to be used for quick testing. A new entryfile should be made
 * if we expect to be doing something very often.
 */

#include <unordered_map>
#include <utility>

using namespace std;

int main()
{
    unordered_map<int *, int *> m{{new int(5), new int(6)}};

    for (pair<int *, int *> p : m)
    {
        delete p.second;
        delete p.first;
    }
}