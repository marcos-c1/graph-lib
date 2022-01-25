#include "utils.hpp"

string chooseTestCase(ifstream &in)
{
    int opt; string filename;
    cout << "\t Estudo de Caso\n\n";
    cout << "1- trab2grafo_1.txt" << endl;
    cout << "2- trab2grafo_2.txt" << endl;
    cout << "3- trab2grafo_3.txt" << endl;
    cout << "4- trab2grafo_4.txt" << endl;
    cout << "5- trab2grafo_5.txt\n\n> ";
    cin >> opt;
    
    TEST_CASE_FILENAME(filename, opt);
    
    switch(opt)
    {
        case 1:  in.open(filename, in.in); break;
        case 2: in.open(filename, in.in); break;
        case 3: in.open(filename, in.in); break;
        case 4: in.open(filename, in.in); break;
        case 5: in.open(filename, in.in); break;
        default: DEBUG("Estudo de caso inválido."); break;
    } 
    if (!in)
    {
        DEBUG("Não pode abrir o arquivo!\n");
    }
    string outputFilename = "results/";
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    outputFilename.append(filename.substr(10, 22) + "__");
    outputFilename.append(to_string(now->tm_mday) + to_string(now->tm_mon) +  to_string(now->tm_year) + to_string(now->tm_hour) + to_string(now->tm_min));
    outputFilename.append(".txt");
    return outputFilename;
}

GRAPH_METHOD chooseMethods()
{
    GRAPH_METHOD method;
    int n;
    cout << "\tBiblioteca de Grafos" << endl << endl;
    cout << "1- Grafo\n2- Lista de adjacência\n3- Matrix de adjacência\n4- Árvore\n\n> ";
    cin >> n;
    switch (n)
    {
    case 1:
        method = GRAPH;
        break;
    case 2:
        method = ADJ_LIST;
        break;
    case 3:
        method = ADJ_MATRIX;
        break;
    case 4:
        method = TREE;
        break;
    default:
        DEBUG("Método inválido!\n");
    }
    return method;
}

string splitString(string &line, char delimiter)
{
    string aux = "";
    int i;
    for (i = 0; i < line.size(); i++)
    {
        if (line.at(i) == delimiter)
        {
            line.erase(0, i + 1);
            return aux;
        }
        aux.push_back(line[i]);
    }
    line.erase(0, i + 1);
    return aux;
}

pair<int, int> chooseDistance()
{
    int v_init, v_end;
    cout << "\tCaminho do Djikstra" << endl << endl;
    cout << "Vértice inicial: ";
    cin >> v_init;
    cout << "Vértice final: ";
    cin >> v_end;
    cout << endl;
    return make_pair(v_init, v_end); 
}
tuple<int, int, float> getValues(string &line)
{
    unsigned int v1, v2;
    float w = 0;
    int arguments = 1;
    while (!line.empty())
    {
        string ptr = splitString(line, ' ');
        switch (arguments)
        {
        case 1:
            v1 = stoull(ptr);
            break;
        case 2:
            v2 = stoull(ptr);
            break;
        case 3:
            w = stold(ptr);
            break;
        }
        arguments++;
    }
    return make_tuple(v1, v2, w);
}

int PC_INFO::parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int PC_INFO::getVirtualMemoryUsage(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = PC_INFO::parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int PC_INFO::getPhysicalMemoryUsage(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

void PC_INFO::initCPU(){
    FILE* file;
    struct tms timeSample;
    char line[128];

    PC_INFO::lastCPU = times(&timeSample);
    PC_INFO::lastSysCPU = timeSample.tms_stime;
    PC_INFO::lastUserCPU = timeSample.tms_utime;

    file = fopen("/proc/cpuinfo", "r");
    PC_INFO::numProcessors = 0;
    while(fgets(line, 128, file) != NULL){
        if (strncmp(line, "processor", 9) == 0) PC_INFO::numProcessors++;
    }
    fclose(file);
}

double PC_INFO::getCPUPercentUsage(){
    struct tms timeSample;
    clock_t now;
    double percent;

    now = times(&timeSample);
    if (now <= PC_INFO::lastCPU || timeSample.tms_stime < PC_INFO::lastSysCPU ||
        timeSample.tms_utime < PC_INFO::lastUserCPU){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        percent = (timeSample.tms_stime - PC_INFO::lastSysCPU) +
            (timeSample.tms_utime - PC_INFO::lastUserCPU);
        percent /= (now - PC_INFO::lastCPU);
        percent /= PC_INFO::numProcessors;
        percent *= 100;
    }
    PC_INFO::lastCPU = now;
    PC_INFO::lastSysCPU = timeSample.tms_stime;
    PC_INFO::lastUserCPU = timeSample.tms_utime;

    return percent;
}

void PC_INFO::show(ofstream &out, double time_taken)
{
    PC_INFO::memory = PC_INFO::getPhysicalMemoryUsage();
    PC_INFO::vmemory = PC_INFO::getVirtualMemoryUsage();
    PC_INFO::cpu = PC_INFO::getCPUPercentUsage();
    out << "Memoria usada: " << PC_INFO::memory << " KB " <<  endl;
    out << "Memoria virtual usada: " << PC_INFO::vmemory << " KB " << endl;
    out << "Consumo de CPU: " << PC_INFO::cpu << "%" << endl;
    out << "Tempo de Execução: " << fixed << time_taken << setprecision(5) << " seg" << endl;
}