#include <iostream>
#include "WaveAlgorithm.h"

int main()
{
    WaveAlgorithm wa;
    if (wa.MapFromFile("map.dat"))
        wa.Show();
}
