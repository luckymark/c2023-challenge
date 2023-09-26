//
// Created by cz241 on 9/26/2023.
//

#ifndef C2023_CHALLENGE_CRYPTER_H
#define C2023_CHALLENGE_CRYPTER_H

#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

extern char pswMap[];
char BinToChar(char s,char w);
string CharToBin(char a);

string Encrypt(string str);
string Decrypt(string str);
string ZipString(string str);
string UnZipString(string str);
#endif //C2023_CHALLENGE_CRYPTER_H
