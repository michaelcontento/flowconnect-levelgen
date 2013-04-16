#include <iostream>

#define LEFT_STR 'l'
#define LEFT_ID 1

#define RIGHT_STR 'r'
#define RIGHT_ID 2

#define UP_STR 'u'
#define UP_ID 4

#define DOWN_STR 'd'
#define DOWN_ID 8

#define RETURN_DEPTH 20
#define SIZE 9

#if (SIZE == 4)
    #define MAX_NUMBER 4
#elif (SIZE == 5)
    #define MAX_NUMBER 6
#elif (SIZE == 6)
    #define MAX_NUMBER 10
#elif (SIZE == 7)
    #define MAX_NUMBER 13
#elif (SIZE == 8)
    #define MAX_NUMBER 16
#elif (SIZE == 9)
    #define MAX_NUMBER 20
#else
    #define MAX_NUMBER 2
#endif

#define SLOTS ((SIZE * SIZE) - 1)

char current[SLOTS + 1] = {0};
int startPos = -1;
int count = 0;
bool endPosUsed[SLOTS + 1] = {false};
int endPosCounter = 0;
int directions[] = {RIGHT_ID, LEFT_ID, DOWN_ID, UP_ID};
int tmpX = 0;
int tmpY = 0;

inline bool isEmpty(const int& pos)
{
    if (pos == -1) {
        return false;
    }
    
    return (current[pos] == ' ');
}

inline int conv2to1(const int& x, const int& y)
{
    if (x >= SIZE || x < 0) {
        return -1;
    }
    if (y >= SIZE || y < 0) {
        return -1;
    }
    
    return (y * SIZE) + x;
}

inline void conv1to2(const int& pos, int& x, int& y)
{
    x = pos % SIZE;
    y = pos / SIZE;
}

inline int getPos(const int& pos, const int& direction)
{
    conv1to2(pos, tmpX, tmpY);

    if (direction == LEFT_ID) {
        tmpX -= 1;
    } else if (direction == RIGHT_ID) {
        tmpX += 1;
    } else if (direction == DOWN_ID) {
        tmpY += 1;
    } else if (direction == UP_ID) {
        tmpY -= 1;
    }

    return conv2to1(tmpX, tmpY);
}

inline char idToStr(const int& id)
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

void printLine(const int& pos)
{
    endPosUsed[pos] = true;
    current[pos] = 'r';
    ++endPosCounter;
    ++count;

    std::cout << "lvl!";
    for (int i = 0; i <= SLOTS; ++i) {
        if (i == pos) {
            std::cout << MAX_NUMBER;
        } else if (i == startPos) {
            std::cout << 1;
        }
        std::cout << current[i];
    }
    std::cout << std::endl;

    int tmp = directions[0];
    for (int i = 0; i < 3; ++i) {
        directions[i] = directions[i + 1];
    }
    directions[3] = tmp;
}

void walk(const int pos, const int depth)
{
    if (depth == SLOTS && !endPosUsed[pos]) {
        printLine(pos);
        return;
    }

    for (auto direction : directions) {
        if (isEmpty(getPos(pos, direction))) {
            char last[SLOTS + 1];
            memcpy(last, current, SLOTS + 1);

            current[pos] = idToStr(direction);
            walk(getPos(pos, direction), depth + 1);

            memcpy(current, last, SLOTS + 1);

            if (depth > RETURN_DEPTH) {
                return;
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    std::cout << "cat!" << SIZE << "x" << SIZE << " level gen" << std::endl;
    std::cout << "pag!" << SIZE << "x" << SIZE << " level gen" << std::endl;

    for (int i = 0; i <= SLOTS; ++i) {
        current[i] = ' ';
    }

    for (startPos = 0; startPos <= SLOTS; ++startPos) {
        endPosCounter = 0;
        for (int i = 0; i <= SLOTS; ++i) {
            endPosUsed[i] = false;
        }
        walk(startPos, 0);
    }

    std::cout << "# levels: " << count << std::endl;
    return 0;
}

