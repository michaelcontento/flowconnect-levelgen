#include <iostream>

#define LEFT_STR 'l'
#define LEFT_ID 1

#define RIGHT_STR 'r'
#define RIGHT_ID 2

#define UP_STR 'u'
#define UP_ID 4

#define DOWN_STR 'd'
#define DOWN_ID 8

#define MAX_NUMBER 3
#define SIZE 3
#define SLOTS ((SIZE * SIZE) - 1)

char current[SLOTS + 1] = {0};
int startPos = -1;

bool isEmpty(const int pos)
{
    if (pos == -1) {
        return false;
    }
    
    return (current[pos] == ' ');
}

int conv2to1(const int x, const int y)
{
    if (x >= SIZE || x < 0) {
        return -1;
    }
    if (y >= SIZE || y < 0) {
        return -1;
    }
    
    return (y * SIZE) + x;
}

void conv1to2(const int pos, int& x, int& y)
{
    x = pos % SIZE;
    y = pos / SIZE;
}

int getPos(const int pos, const int direction)
{
    int x = 0;
    int y = 0;
    conv1to2(pos, x, y);

    if (direction == LEFT_ID) {
        x -= 1;
    } else if (direction == RIGHT_ID) {
        x += 1;
    } else if (direction == DOWN_ID) {
        y += 1;
    } else if (direction == UP_ID) {
        y -= 1;
    }

    return conv2to1(x, y);
}

char idToStr(const int id)
{
    if (id == RIGHT_ID) {
        return RIGHT_STR;
    } else if (id == LEFT_ID) {
        return LEFT_STR;
    } else if (id == DOWN_ID) {
        return DOWN_STR;
    } else if (id == UP_ID) {
        return UP_STR;
    }
    return '#';
}

void walk(const int pos, const int depth)
{
    if (depth == SLOTS) {
        current[pos] = 'r';
        std::cout << "lvl!";
        for (int i = 0; i <= SLOTS; ++i) {
            if (i == pos) {
                std::cout << MAX_NUMBER;
            }
            if (i == startPos) {
                std::cout << 1;
            }
            std::cout << current[i];
        }
        std::cout << std::endl;
        return;
    }

    int newPos;
    char last[SLOTS + 1];
    memcpy(last, current, SLOTS + 1);

    for (auto direction : {RIGHT_ID, LEFT_ID, DOWN_ID, UP_ID} ) {
        newPos = getPos(pos, direction);
        if (isEmpty(newPos)) {
            current[pos] = idToStr(direction);
            walk(getPos(pos, direction), depth + 1);
            memcpy(current, last, SLOTS + 1);
        }
    }
}

int main(int argc, const char * argv[])
{
    std::cout << "# START LEVEL-GEN" << std::endl;
    std::cout << "cat!" << SIZE << "x" << SIZE << " level gen" << std::endl;
    std::cout << "pag!" << SIZE << "x" << SIZE << " level gen" << std::endl;

    for (int i = 0; i <= SLOTS; ++i) {
        current[i] = ' ';
    }

    for (startPos = 0; startPos <= SLOTS; ++startPos) {
        walk(startPos, 0);
    }

    std::cout << "# END LEVEL-GEN" << std::endl;
    return 0;
}

