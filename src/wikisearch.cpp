/**
 * @file Implementations of basic methods for WikiSearch
 */

#include "wikisearch.h"

WikiSearch::WikiSearch() {}

void WikiSearch::importData(string file_dir)
{
    // Calls graph's own importData function
    graph_.importData(file_dir);
}

void WikiSearch::print() const
{
    graph_.print();
}