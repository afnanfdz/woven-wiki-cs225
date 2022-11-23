#include "dset.h"

#include <exception>
#include <algorithm>
#include <iostream>

void DisjointSets::addelements(int num)
{
    num_sets += num;
    for (int i = 0; i < num; i++)
    {
        elems_.push_back(-1);
    }
}

int DisjointSets::find(int elem) const
{
    if (std::size_t(elem) >= elems_.size())
    {
        std::__throw_invalid_argument("Elem larger than elem size");
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
    for (size_t i = 0; i < elems_.size(); i++)
    {
        if (i >= 0 && i < 10)
        {
            std::cout << " ";
        }

        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i : elems_)
    {
        if (i >= 0 && i < 10)
        {
            std::cout << " ";
        }
        std::cout << i << " ";
    }
    std::cout << std::endl
              << std::endl;
}

bool DisjointSets::isunited() const
{
    return num_sets == 1;
}