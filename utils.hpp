#ifndef UTILS_HPP
#define UTILS_HPP

#include <tuple>
#include <string>

using namespace std;

string split_string(string &line, char delimiter);
tuple<int, int, float> getValues(string& line);

#endif