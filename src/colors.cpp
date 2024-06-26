#include "colors.h"
using namespace std;


const Color darkgrey = {25, 27, 35, 255};
const Color green = {47, 230, 23, 255};
const Color red = {232, 18, 18, 255};
const Color orange = {226, 116, 17, 255};
const Color yellow = {237, 234, 4, 255};
const Color purple = {166, 0, 247, 255};
const Color cyan = {21, 204, 209, 255};
const Color blue = {33, 64, 216, 255};
const Color darkBlue = {44, 44, 127, 255};
const Color lightBlue = {59, 85, 162, 255};
const Color lightGreen = {102, 255, 102, 230};
const Color lightWhite = {255, 255, 255, 30};
const Color lightestGreen = {0, 255, 0, 160};
const Color NoColor = {0, 0, 0, 0};

vector<Color> GetCellColors(){
    return {darkgrey, green, red, orange, yellow, purple, cyan, blue};
}