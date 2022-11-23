#include "dsets.h"

#include <exception>
#include <algorithm>
#include <iostream>

void DisjointSets::addelements(std::vector<int> v)
{
    num_sets += v.size();
    for (const int n : v)
    {
        elems_.insert({n, -1});
    }
}

int DisjointSets::find(int elem) const
{
    if (elems_.find(elem) == elems_.end())
    {
        throw std::invalid_argument("Elem doesn't exist");
    }

    int to_return = elem;

    while (elems_.at(to_return) >= 0)
    {
        to_return = elems_.at(to_return);
    }

    return to_return;
}

void DisjointSets::setunion(int a, int b)
{
    int root_a = find(a);
    int root_b = find(b);

    if (root_a == root_b)
        return;

    if (size(a) > size(b))
    {
        elems_.at(root_a) += elems_.at(root_b);
        elems_.at(root_b) = root_a;
    }
    else
    {
        elems_.at(root_b) += elems_.at(root_a);
        elems_.at(root_a) = root_b;
    }

    --num_sets;
}

int DisjointSets::size(int elem) const
{
    return std::abs(elems_.at(find(elem)));
}

void DisjointSets::print() const
{
    for (const auto &p : elems_)
    {
        std::cout << p.first << " : " << p.second << std::endl;
    }
    std::cout << std::endl;
}

bool DisjointSets::isunited() const
{
    return num_sets == 1;
}

int DisjointSets::getNumSets() const
{
    return num_sets;
}