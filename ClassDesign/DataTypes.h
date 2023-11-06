//
// Created by cz241 on 11/3/2023.
//

#ifndef C2023_CHALLENGE_DATATYPES_H
#define C2023_CHALLENGE_DATATYPES_H

#include <string>

using namespace std;


enum class PieceStatus {
    None,
    Black,
    White
};

extern PieceStatus MapData[15][15];
extern PieceStatus CurrentPlayer;

#endif //C2023_CHALLENGE_DATATYPES_H
