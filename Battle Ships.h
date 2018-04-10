/*
 * main.cpp contains the implementation for all the methods of class BattleShip
 */

#include <iostream>
#include <cstdlib>

using namespace std;

class BattleShip
{
    static const int COORDINATE_SIZE = 10;
    // the sea
    int grid_layout[COORDINATE_SIZE][COORDINATE_SIZE];
    // x and y coordinates
    int x, y;
    // ship count
    int user_ship, computer_ship;
    // game goes for 100 turns; 50 for user and 50 for computer
    int game_play;
    // for printing '-'
    int dash;
    // store input from user
    int temporary;

public:
    BattleShip();

    // some minor sub modules that will be called by other modules
    void separator();
    void top_bottom_grid();
    bool evaluate_user_input(int);
    int get_coordinate(char);
    void generate_random_number();
    void get_x_y(char);
    void game_counter();

    // game setting up
    void game_message();
    void print_grid();

    // game begins
    void user_places_ships();
    void computer_places_ships();

    // battle in the arena!
    void battle();
    void user_attacks();
    void computer_attacks();

    // credit the winner
    void who_won();
};
