#pragma once

#include <unordered_map>
#include <vector>

// Implemented as an unordered map because indexing is not necessarily ordered!!
class DisjointSets
{
public:
    void addelements(std::vector<int> v);
    int find(int) const;
    void setunion(int, int);
    int size(int) const;
    void print() const;

    bool isunited() const;
    int getNumSets() const;

private:
    int num_sets = 0;
    std::unordered_map<int, int> elems_;
};