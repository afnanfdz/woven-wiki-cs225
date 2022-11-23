#pragma once

#include <vector>

class DisjointSets
{
public:
    void addelements(int);
    int find(int) const;
    void setunion(int, int);
    int size(int) const;
    void print() const;

    bool isunited() const;

private:
    int num_sets = 0;
    std::vector<int> elems_;
};