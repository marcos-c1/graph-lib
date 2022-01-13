#include "utils.hpp"

string split_string(string &line, char delimiter)
{
    string aux = "";
    int i;
    for(i = 0; i < line.size(); i++)
    {
        if(line.at(i) == delimiter)
        {
            line.erase(0, i+1);
            return aux;
        }
        aux.push_back(line[i]);
    }
    line.erase(0, i+1);
    return aux;
}
tuple<int, int, float> getValues(string& line)
{
    unsigned int v1, v2;
    float w = 0;
    int arguments = 1;
    while(!line.empty()) 
    {
        string ptr = split_string(line, ' ');
        switch(arguments)
        {
            case 1: v1 = stoull(ptr); break;
            case 2: v2 = stoull(ptr); break;
            case 3: w = stold(ptr); break;
        }
        arguments++;
    }
    return make_tuple(v1, v2, w);
}