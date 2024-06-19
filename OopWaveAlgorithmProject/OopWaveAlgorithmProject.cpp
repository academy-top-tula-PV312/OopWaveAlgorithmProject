#include <iostream>
#include "WaveAlgorithm.h"

int main()
{
    WaveAlgorithm wa;
    if (!wa.MapFromFile("map.dat"))
        return -1;
    
    wa.Show();
        
    if (wa.MakeWaves())
    {
        wa.Show();
        wa.MakePath();
        wa.ShowPath();
    }
    else
        std::cout << "path not found!\n";

}
