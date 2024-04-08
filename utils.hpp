#ifndef UTILS_HPP
#define UTILS_HPP


#include <tuple>
#include <string>
#include <fstream>
#include <string.h>

#define DEBUG(EXCEPTION)                                                \
    fprintf(stderr, "%s:%d: ERROR: %s", __FILE__, __LINE__, EXCEPTION); \
    exit(1)

#define TEST_CASE_FILENAME(FILENAME, FILE_INDEX) \
    FILENAME = "testCases/trab2grafo_"; \
    FILENAME.append(to_string(FILE_INDEX)); \
    FILENAME.append(".txt"); \

using namespace std;

enum GRAPH_METHOD
{
    GRAPH = 1,
    ADJ_LIST,
    ADJ_MATRIX,
    TREE,
};

string chooseTestCase(ifstream &in);
GRAPH_METHOD chooseMethods();
pair<int, int> chooseDistance();
string splitString(string &line, char delimiter);
tuple<int, int, float> getValues(string &line);

class PC_INFO
{
private:
    clock_t lastCPU, lastSysCPU, lastUserCPU;
    int numProcessors;
    int memory;
    double cpu;
    int vmemory;
    
public:
    PC_INFO()
    {
        this->initCPU();
    };
    
protected:
    int parseLine(char *line);
    void initCPU();
    int getVirtualMemoryUsage();
    int getPhysicalMemoryUsage();
    double getCPUPercentUsage();
public:
    void show(ofstream &out, double time_taken);
};

#endif
