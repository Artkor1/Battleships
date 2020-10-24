#include <iostream>

using namespace std;

class Game
{
    string first_player;
    string second_player;
    char first_grid[12][12];        //first player ships
    char second_grid[12][12];       //second player ships
    //1-10 is the playing board
    //0-nothing 1-my ship S
    char first_shots[12][12];       //first player shots
    char second_shots[12][12];      //second player shots
    //1-10 is the playing board
    //0-nothing   o-empty    x-hit   X-hit and sunk

    int first_ships[5];
    int second_ships[5];
    //0-carrier 5 long
    //1-battleship 4 long
    //2-cruiser  3 long
    //3-submarine 3 long
    //4-destroyer 2 long
    //0-still swimming      1-sunk
    int first_score;
    int second_score;

public:
    Game();
    void choose_mode();
    void choose_diff();
    void setup();
    void random_setup(int player);
    void ship_random(int length, int player);
    void player_setup(int player);
    void ship_setup(string name, int length, int player);
    int find_x(string coordinates);
    int find_y(string coordinates);
    bool update_grid(int x, int y, int grid, char symbol);
    void take_turns();
    void player_turn(int player);
    void computer_turn();
    void computer_easy();
    void computer_hard();
    int count_empty(int x, int y);
    void is_sunk(int x, int y, int player);
    bool is_over();
    void reset();
    void display_grid(int player);
    void display_board(int player);
    void display_scores();
};
