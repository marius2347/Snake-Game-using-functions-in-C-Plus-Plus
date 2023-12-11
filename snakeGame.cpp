// Snake Game

#include <iostream>
#include <conio.h> // console input output for the player input
#include<time.h> // to generate random fruits from time to time
#include<windows.h> // for sleep function
using namespace std;
bool gameOver; // when the game is over

// buffer
char outputbuf[1300];

// map size
const int width = 50;
const int height = 25;

// head of the snake, fruit position, score 
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; // vectors with 101 elements on axis X and Y
int nTail; // the length of the tail

// track the direction using enumation
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir; // holds the direction of the snake

// setup the game at the beggining of the game
void Setup() {
    gameOver = false;
    dir = STOP; // the snake will not move until we start moving it
    x = width / 2; // position of the head of the snake, it will be in the middle
    y = height / 2; // the snake will be centered on the map
    fruitX = rand() % width;  // fruit random on the map on axis X (random value from 0 to width - 1)
    fruitY = rand() % height; // fruit random on the map on axis Y (random value from 0 to height - 1)
    score = 0; // score 0 at the start of the game
    std::cout.rdbuf()->pubsetbuf(outputbuf, sizeof(outputbuf));
    ios::sync_with_stdio(false);   
}

// draw a map
void Draw() {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0}); // console window for the game
    CONSOLE_CURSOR_INFO info; // remove the first console cursor
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    for (int i = 0; i < width + 2; i++)  // display the top border of the map
        cout << "#";
    cout << endl; // move to the next line

    // print the map
    for (int i = 0; i < height; i++) { // for height of the map
        for (int j = 0; j < width; j++) { // for width  of the map
            if (j == 0) // if is the first field, for the wall character in the left side
                cout << "#";
            if (i == y && j == x) // i and y for the height & j and x for the width (for the head of the snake)
                cout << "O";
            else if (i == fruitY && j == fruitX) // to print the fruit
                cout << "F";
            else
                {
                    bool print = false; // keep track whether we print the head segment or we not
                    for (int k = 0; k < nTail; k++) { // going every element of our element
                        
                        if (tailX[k] == j && tailY[k] == i) { // if it is at the right position
                            cout << "o"; // print the tail
                            print = true;
                        }   
                        
                    }
                    if (!print) // print after every row
                            cout << " ";
                }
            if (j == width - 1) // last field, for the wall character in the right side
                cout << "#";
        }
        cout << endl;
    }
     for (int i = 0; i < width + 2; i++)  // display the bottom border of the map
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

// input for player (control)
void Input() {

 if (_kbhit())
 {
  switch (_getch())
  {
    case 'a':
    if (dir == RIGHT) // can t go in the back direction
        break;         
    dir = LEFT;
    break;

    case 'd':
    if (dir == LEFT) // can t go in the back direction
        break;
    dir = RIGHT;
    break;

    case 'w':
    if (dir == DOWN) // can t go in the back direction
        break;           
    dir = UP;
    break;

    case 's':
    if (dir == UP) // can t go in the back direction
        break;   
    dir = DOWN;
        break;
    case 'x':
        gameOver = true;
        break;
  }
 }
}

// logic of the game
void Logic() {
    int prevX = tailX[0]; // remember the previous coordonate on X of the tail
    int prevY = tailY[0]; // remember the previous coordonate on Y of the tail
    int prev2X, prev2Y;
    tailX[0] = x; // first element to follow the head on X
    tailY[0] = y; // first element to follow the head on Y
    for (int i = 1; i < nTail; i++) { // to go through the length of the tail
        prev2X = tailX[i]; // remember the current position (axis X) of the segment
        prev2Y = tailY[i]; // remember the current position (axis Y) of the segment
        tailX[i] = prevX; // change them to previous values on axis X
        tailY[i] = prevY; // change them to previous values on axis Y
        prevX = prev2X; // swap the positions on X
        prevY = prev2Y; // swap the positions on Y
    }
    switch(dir) { // switch to direction
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    // // if the head hit the right or left wall or bottom or top wall is gameover
    // if (x > width || x < 0 || y > height || y < 0) {
    //     gameOver = true;
    // }
    
    // reset the game from the opposite side after gameOver and score, tail back to 0
    if (x > width) {
        score = 0;
        x = x - width;
        nTail = 0;
    }   
        
    if (x < 0) {
        score = 0;
        x = x + width;
        nTail = 0;
    }
    
    if (y > height) {
        score = 0;
        y = y - height;
        nTail = 0;
    }   
        
    if ( y < 0) {
        score = 0;
        y = y + height;
        nTail = 0;
    }
    for (int i = 0; i < nTail; i++) // check if we hit the tail
        if (tailX[i] == x && tailY[i] == y) 
            {
                nTail = 0;
                if (x > width) {
                    score = 0;
                    x = x - width;
                }   
                    
                if (x < 0) {
                    score = 0;
                    x = x + width;
                }
                
                if (y > height) {
                    score = 0;
                    y = y - height;
                }   
                    
                if ( y < 0) {
                    score = 0;
                    y = y + height;
                }
                
            }
    // if we ate the fruit increases the score with 10 points and the tail by +1 and put the next fruit on another random position
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;  // again fruit random on the map on axis X (random value from 0 to width - 1)
        fruitY = rand() % height; // again fruit random on the map on axis Y (random value from 0 to height - 1)
        nTail++; // increase the tail
    }
}

int main() {
   
    // running the game
    srand(time(NULL)); // for random fruit positions
    Setup();
    while(!gameOver) {
        Draw();
        Input();
        Logic();
        // make the snake run slower left right down and up
        if (dir == LEFT || dir == RIGHT) {
            Sleep(35);
        }

        Sleep(70);

        if (dir == UP || dir == DOWN){
            Sleep(70);
        }
    }
    return 0;
}