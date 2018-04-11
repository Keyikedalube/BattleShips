/*
 * Battle Ships game
 */

#include "Battle Ships.h"

BattleShip::BattleShip()
{
    x = y = 0;
    user_ship = computer_ship = 0;
    game_play = 100;
    dash = COORDINATE_SIZE + 3;
    temporary = 0;
    // have to manually assign 0 to array in C++
    for (x = 0; x < COORDINATE_SIZE; x++)
        for (y = 0; y < COORDINATE_SIZE; y++)
            grid_layout[x][y] = 0;
}

void BattleShip::separator()
{
    cout << "  ";
    for (x = 0; x < dash; x++)
        cout << "-";
    cout << endl;
}

void BattleShip::top_bottom_grid()
{
    cout << "   ";
    for (x = 0; x < COORDINATE_SIZE; x++)
        cout << x;
    cout << endl;
}

bool BattleShip::evaluate_user_input(int coordinate)
{
    if (coordinate >= COORDINATE_SIZE || coordinate < 0) {
        cout << "\tCoordinate exceeds the grid size!\n\tReenter the coordinate again...\n";
        return false;
    }
    return true;
}

int BattleShip::get_coordinate(char coordinate)
{
    while (true) {
        cout << "Enter " << coordinate << " coordinate: ";
        cin >> temporary;
        if (evaluate_user_input(temporary) == false)
            continue;
        else
            break;
    }
    return temporary;
}

void BattleShip::generate_random_number()
{
        x = rand() % 10;
        y = rand() % 10;
}

void BattleShip::get_x_y(char who)
{
    // u for user
    // c for computer; will generate pseudo random numbers
    // p as in computer 'play' to avoid pseudorandom numbers for trading off more cpu execution with speed
    if (who == 'u') {
        x = get_coordinate('x');
        y = get_coordinate('y');
    } else if (who == 'c') {
        srand(time(0));
        generate_random_number();
    } else
        generate_random_number();
}

void BattleShip::game_counter()
{
    separator();
    cout << "Turns left: " << game_play << endl;
    separator();
}

void BattleShip::game_message()
{
    cout << "**** Welcome to Battle Ships game ****\n";
    cout << "Right now the sea is empty...\n\n";
}

void BattleShip::print_grid()
{
    top_bottom_grid();
    separator();
    for (x = 0; x < COORDINATE_SIZE; x++) {
        // left index
        cout << x << " |";
        for (y = 0; y < COORDINATE_SIZE; y++) {
            // actual grid body
            if (grid_layout[x][y] == 1)
                // printing user ship
                cout << "@";
            else if (grid_layout[x][y] == 3)
                // printing busted computer ship
                cout << "x";
//            else if (grid_layout[x][y] == 11)
//                // computer ship; only for checking if pseudorandom number works or not
//                cout << "$";
            else
                cout << " ";
        }
        // right index
        cout << " | " << x << endl;
    }
    separator();
    top_bottom_grid();
}

void BattleShip::user_places_ships()
{
    cout << "\nDeploy your 5 ships in the sea.\n";
    for (int choice = 1; choice <= 5; choice++) {
        while (true) {
            get_x_y('u');
            if (grid_layout[x][y] == 1)
                cout << "\tYou already deployed your ship here\n";
            else {
                // 1 will indicate user ship
                grid_layout[x][y] = 1;
                cout << "\tShip " << choice << " deployed\n";
                user_ship++;
                break;
            }
        }
    }
}

void BattleShip::computer_places_ships()
{
    cout << "\nComputer is deploying ships\n";
    for (int choice = 1; choice <= 5; choice++) {
        while (true) {
            get_x_y('c');
            if (grid_layout[x][y] != 11 && grid_layout[x][y] != 1) {
                // 11 will indicate computer ship
                grid_layout[x][y] = 11;
                computer_ship++;
                break;
            }
        }
        cout << "\tShip " << choice << " DEPLOYED.\n";
    }
    cout << endl;
}

void BattleShip::battle()
{
    while (game_play != 0 && user_ship != 0 && computer_ship != 0) {
        game_counter();
        cout << "YOUR TURN\n";
        user_attacks();
        cout << "COMPUTER'S TURN\n";
        computer_attacks();
        game_play -= 2;
        cout << endl;
    }
}

/*
 * Numbers from 1 to 10 are used for recording user's action
 * 1:   User ship
 * 2:   Friendly fired
 * 3:   Sunk enemy's ship
 * 4:   Missed area, so user doesn't guess the same coordinates again
 * 25:  A special value for avoiding overwriting; both by user and computer
 */
void BattleShip::user_attacks()
{
    while (true) {
        get_x_y('u');
        if (grid_layout[x][y] == 1) {
            cout << "\tBoom! You sunk your own ship!\n";
            grid_layout[x][y] = 2;
            user_ship--;
            break;
        } else if (grid_layout[x][y] == 11) {
            cout << "\tBoom! You sunk a ship!\n";
            grid_layout[x][y] = 3;
            computer_ship--;
            break;
        } else if (grid_layout[x][y] == 2 || grid_layout[x][y] == 3 || grid_layout[x][y] == 4 || grid_layout[x][y] == 25)
            cout << "\tYou guessed this coordinates before.\n\tGuess again...\n";
        else if (grid_layout[x][y] == 13)
            cout << "\tComputer busted your ship here.\n\tGuess again...\n";
        else {
            cout << "\tYou missed!\n";
            if (grid_layout[x][y] != 14)
                // don't overwrite the value guessed by computer
                grid_layout[x][y] = 4;
            else
                grid_layout[x][y] = 25;
            break;
        }
    }
}

/*
 * Numbers from 11 to 20 are used for recording computer's action
 * 11:  Computer ship
 * 12:  Friendly fired
 * 13:  Sunk enemy's ship
 * 14:  Missed area, so computer doesn't guess the same coordinates again
 * 25:  A special value for avoiding overwriting; both by computer and user
 */
void BattleShip::computer_attacks()
{
    while (true) {
        get_x_y('p');
        if (grid_layout[x][y] == 11) {
            cout << "\tDang! computer busted its own ship\n";
            grid_layout[x][y] = 12;
            computer_ship--;
            break;
        } else if (grid_layout[x][y] == 1) {
            cout << "\tBoom! Computer busted one of your ships.\n";
            grid_layout[x][y] = 13;
            user_ship--;
            break;
        } else if (grid_layout[x][y] == 3 || grid_layout[x][y] == 12 || grid_layout[x][y] == 13 ||
                   grid_layout[x][y] == 14 || grid_layout[x][y] == 25)
            cout << "\tComputer guessed the same area.\n\tGuessing again...\n";
        else {
            cout << "\tComputer missed.\n";
            if (grid_layout[x][y] != 4)
                // don't overwrite the value guessed by user
                grid_layout[x][y] = 14;
            else
                grid_layout[x][y] = 25;
            break;
        }
    }
}

void BattleShip::who_won()
{
    cout << "\nUser's ship: " << user_ship << " | Computer's ship: " << computer_ship << endl;
    if (user_ship > computer_ship)
        cout << "Hooray! You won the game!\n";
    else if (user_ship == computer_ship)
        cout << "The game ends in draw.\n";
    else
        cout << "The computer won.\n";
}

int main()
{
    BattleShip game;

    game.game_message();
    game.print_grid();

    game.user_places_ships();
    game.computer_places_ships();
    game.print_grid();

    game.battle();
    game.print_grid();

    game.who_won();

    return 0;
}
