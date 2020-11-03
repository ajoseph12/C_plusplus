#include <iostream>
#include <array>
#include <vector>


struct player
{
    std::string name;
    std::vector<int> cards;
};

int getNumOfPlayers()
{
    int num_players{0};
    std::cout << "Please enter number of players : ";
    std::cin >> num_players;
    
    return num_players;
}

void dohere(std::vector<player>& players)
{
    for (auto p : players)
    {
        p.name = "Allwyn";
    }
    
}

void hit(std::vector<int>& cards, int times)
{
    
}

int main()
{
    int num_players{getNumOfPlayers()};
//    std::vector<player> players(num_players);
    
//    dohere(players);
    
    std::vector<int> array(num_players);
    for (int i : array)
        std::cout << i << ' ';
    std::cout << "size of : " << array.size();
    return 0;
}

