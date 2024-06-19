#include "WaveAlgorithm.h"

const Map& WaveAlgorithm::GetMap()
{
    return map;
}

const Path& WaveAlgorithm::GetPath()
{
    return path;
}

bool WaveAlgorithm::MapFromFile(std::string fileName)
{
    std::fstream streamMap;
    streamMap.open(fileName, std::ios::in);

    if (!streamMap.is_open()) return false;

    int bufferSize{ 1024 };
    char* buffer = new char[bufferSize];

    int row{};
    while (!streamMap.eof())
    {
        map.push_back(std::vector<int>());

        streamMap.getline(buffer, bufferSize);

        for (int column{}; column < std::strlen(buffer); column++)
        {
            CellType cell{};
            switch (buffer[column])
            {
            case '#': cell = CellType::Wall; break;
            case ' ': cell = CellType::Space; break;
            case 's': 
            case 'S': cell = CellType::Start;
                      start = Cell{ row, column };
                      break;
            case 'f':
            case 'F': cell = CellType::Finish; 
                      finish = Cell{ row, column };
                      break;
            default:
                break;
            }
            map[row].push_back(cell);
        }
        row++;
    }
    streamMap.close();

    return true;
}

bool WaveAlgorithm::MakeWaves()
{
    Fronts fronts;
    bool frontCurrent{ false };
    int frontNumber{ 1 };
    bool isFinished{ true };

    fronts[frontCurrent].push_back(start);
    
    bool isFinded{ false };

    while(!isFinded)
    {
        fronts[!frontCurrent].clear();

        for (auto cellCurrent : fronts[frontCurrent])
        {
            for (auto cellOffset : Offset)
            {
                Cell cellNew = cellCurrent + cellOffset;

                if (cellNew.Row < 0 || cellNew.Row >= map.size()
                    || cellNew.Column < 0 || cellNew.Column >= map[0].size())
                    continue;
                if (map[cellNew.Row][cellNew.Column] == CellType::Space
                    || map[cellNew.Row][cellNew.Column] == CellType::Finish)
                {
                    fronts[!frontCurrent].push_back(cellNew);
                    map[cellNew.Row][cellNew.Column] = frontNumber;
                    if (cellNew == finish)
                    {
                        isFinded = true;
                        break;
                    }
                }
            }
            if (isFinded) break;
        }
        frontCurrent = !frontCurrent;
        frontNumber++;
    }

    return isFinished;
}

void WaveAlgorithm::Show()
{
    for (int row{}; row < map.size(); row++)
    {
        for (int column{}; column < map[row].size(); column++)
        {
            if (map[row][column] == CellType::Wall)
                std::cout << "##";
            else if(map[row][column] == CellType::Space)
                std::cout << "  ";
            else if(map[row][column] == CellType::Finish)
                std::cout << " F";
            else
                std::cout << std::setw(2) << map[row][column];
        }
        std::cout << "\n";
    }
}
