#pragma once
#ifndef KEY_ROTATION_H
#define KEY_ROTATION_H

#include <string>
using namespace std;

struct arr56{
    char array[56];
};
class keyRotation{
    private:
        int PC1[56] = {
            57, 49,  41,  33,  25,  17,  9,
            1,  58,  50,  42,  34,  26,  18,
            10,  2,  59,  51,  43,  35,  27,
            19, 11,   3,  60,  52,  44,  36,
            63, 55,  47,  39,  31,  23,  15,
            7,  62,  54,  46,  38,  30,  22,
            14,  6,  61,  53,  45,  37,  29,
            21, 13,   5,  28,  20,  12,   4
        };
        char key[64];
        int PC2[48] = {
            14,  17,  11,  24,   1,   5,
            3,   28,  15,   6,  21,   10,
            23,  19,  12,   4,  26,    8,
            16,   7,  27,  20,  13,    2,
            41,  52,  31,  37,  47,   55,
            30,  40,  51,  45,  33,   48,
            44,  49,  39,  56,  34,   53,
            46,  42,  50,  36,  29,   32
        };
        int left_shift[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
        char c[28];
        char d[28];
        int round;
    public:
        keyRotation(string key);
        arr56 permutation();
        string nextRound();
        void getOrigianlBlocks();
        int getRound(){return round;};
};

#endif
keyRotation::keyRotation(string key){
    //Convert key to char array
    for (int i = 0; i < 64; i++){
        this->key[i] = key[i];
    }
    getOrigianlBlocks();
    round = 0;
};
arr56 keyRotation::permutation(){
    arr56 arrayStruct;
    char* key_plus = arrayStruct.array;
    for (int i = 0; i < 56; i++){
        key_plus[i] = key[PC1[i] - 1];
    }
    return arrayStruct;
};
void keyRotation::getOrigianlBlocks(){
    arr56 block = permutation();
    for (int i = 0; i < 28; i++){
        c[i] = block.array[i];
        d[i] = block.array[28+i];
    }
};
string keyRotation::nextRound(){
    //Shift left
    int shift = left_shift[round];
    int temp_c[2];
    int temp_d[2];
    temp_c[0] = c[0];
    temp_d[0] = d[0];
    if (shift == 2){
        temp_c[1] = c[1];
        temp_d[1] = d[1];
    }
    for (int i = 0; i < 28 - shift; i++){
        c[i] = c[i+shift];
        d[i] = d[i+shift];
    }
    if (shift == 1){
        c[27] = temp_c[0];
        d[27] = temp_d[0];
    }
    else{
        c[26] = temp_c[0];
        c[27] = temp_c[1];

        d[26] = temp_d[0];
        d[27] = temp_d[1];
    }
    //Concentrate c and d
    char cd[56];
    for (int i = 0; i < 28; i++){
        cd[i] = c[i];
        cd[i+28] = d[i];
    }
    string key_round = "";
    //Final permuation
    for (int i = 0; i < 48; i++){
        key_round = key_round + cd[PC2[i] - 1];
    }
    round++;
    return key_round;
}