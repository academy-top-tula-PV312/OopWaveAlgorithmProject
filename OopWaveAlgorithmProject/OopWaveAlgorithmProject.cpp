#include <iostream>
#include "WaveAlgorithm.h"

int main()
{
    WaveAlgorithm wa;
    if (wa.MapFromFile("map.dat"))
    {
        wa.Show();
        
        wa.MakeWaves();

        std::cout << "\n";
        wa.Show();

    }
        
}
