
#include <iostream>
#include <cstring>

struct WeightMap
{
    char name;
    int weight;
};
int main()
{
    std::string o = "bourgeiose";
    int i = 0;
    WeightMap map[100];
    while (o[i] != '\0')
    {
        map[i].name = o[i];
        std::cout << map[i++].name;
    }


    return 0;
}