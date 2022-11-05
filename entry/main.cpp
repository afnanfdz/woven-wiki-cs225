/**
 * @file main.cpp
 *
 * Expected to be used for quick testing. A new entryfile should be made
 * if we expect to be doing something very often.
 */

#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "utils.h"

using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

int main()
{
    shrinkCategories("../data/wiki-topcats-categories.txt", "../data/gendata/cats.txt", 50);
    return 0;
}