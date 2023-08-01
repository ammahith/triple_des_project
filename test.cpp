#include "key_rotation.h"

int main(){
    string key = "0001001100110100010101110111100110011011101111001101111111110001";
    keyRotation object = keyRotation(key);
    for (int i = 0; i < 16; i++){
        key = object.nextRound();
    }
}