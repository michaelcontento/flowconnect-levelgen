#include <iostream>
#include <math.h>

#define LEFT_STR 'l'
#define RIGHT_STR 'r'
#define UP_STR 'u'
#define DOWN_STR 'd'

#define SIZE 9
#define SLOTS ((SIZE * SIZE) - 1)
#define LINES_PER_START_POS (ceil(400.0 / (SIZE * SIZE)))

#if (SIZE == 4)
    #define MAX_NUMBER 4
    #define FALLBACK_DEPTH 0
#elif (SIZE == 5)
    #define MAX_NUMBER 6
    #define FALLBACK_DEPTH 0
#elif (SIZE == 6)
    #define MAX_NUMBER 10
    #define FALLBACK_DEPTH 0
#elif (SIZE == 7)
    #define MAX_NUMBER 13
    #define FALLBACK_DEPTH 2
#elif (SIZE == 8)
    #define MAX_NUMBER 16
    #define FALLBACK_DEPTH 2
#elif (SIZE == 9)
    #define MAX_NUMBER 20
    #define FALLBACK_DEPTH 3
#else
    #define MAX_NUMBER 2
#endif

char current[SLOTS + 1] = {0};
int startPos = -1;
int count = 0;
int fallback = 0;
int endPostCounter = 0;
bool repeatingAllowed = false;
bool endPosUsed[SLOTS + 1] = {false};
char directions[] = {RIGHT_STR, LEFT_STR, DOWN_STR, UP_STR};

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

inline int getPos(const int& pos, const char& direction)
{
    static int tmpX = 0;
    static int tmpY = 0;

    conv1to2(pos, tmpX, tmpY);

    if (direction == LEFT_STR) {
        tmpX -= 1;
    } else if (direction == RIGHT_STR) {
        tmpX += 1;
    } else if (direction == DOWN_STR) {
        tmpY += 1;
    } else if (direction == UP_STR) {
        tmpY -= 1;
    }

    return conv2to1(tmpX, tmpY);
}

void printLine(const int& pos)
{
    if (!endPosUsed[pos]) {
        ++endPostCounter;
    }
    endPosUsed[pos] = true;
    current[pos] = 'r';
    ++count;
    repeatingAllowed = false;

    if (SIZE > 5) {
       fallback = (SIZE * SIZE) / 2;
    }

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
}

bool has_repeating_parts()
{
    if (SIZE == 4) {
        return false;
    }

    if (repeatingAllowed) {
        return false;
    }

    static char buf[5] = {0};
    static int pos = 0;

    memset(buf, 0, 5);
    pos = startPos;

    for (int i = 0; i <= SLOTS; ++i) {
        buf[0] = buf[1];
        buf[1] = buf[2];
        buf[2] = buf[3];
        buf[3] = current[pos];
        pos = getPos(pos, current[pos]);

        if (i < 3) {
            continue;
        }

        if (buf[3] == ' ') {
            return false;
        }

        if (buf[0] == buf[1] && buf[1] == buf[2]) {
            if (rand() > (RAND_MAX * 0.9999)) {
                repeatingAllowed = true;
                return false;
            } else {
                return true;
            }
        }
    }
    return false;
}

void walk(const int pos, const int depth)
{
    if (endPostCounter >= LINES_PER_START_POS) {
        return;
    }
    
    if (has_repeating_parts()) {
        return;
    }
    
    if (depth == SLOTS && !endPosUsed[pos]) {
        printLine(pos);
        return;
    }

    static char last[SLOTS + 1][SLOTS + 1];

    bool found = false;
    for (auto direction : directions) {
        if (isEmpty(getPos(pos, direction))) {
            found = true;
            memcpy(last[depth], current, SLOTS + 1);

            current[pos] = direction;
            walk(getPos(pos, direction), depth + 1);

            memcpy(current, last[depth], SLOTS + 1);

            if (fallback > 0) {
                --fallback;
                return;
            }
        }
    }

    if (!found) {
        fallback = FALLBACK_DEPTH;
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
        for (int i = 0; i <= SLOTS; ++i) {
            endPosUsed[i] = false;
        }
        endPostCounter = 0;

        std::cerr << startPos << std::endl;
        walk(startPos, 0);

        char tmp = directions[0];
        directions[0] = directions[1];
        directions[1] = directions[2];
        directions[2] = directions[3];
        directions[3] = tmp;
    }

    std::cout << "# levels: " << count << std::endl;
    return 0;
}

