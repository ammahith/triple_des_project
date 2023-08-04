#include "key_rotation.h"
#include "triple_des.h"

int main(){
    string key = "0001001100110100010101110111100110011011101111001101111111110001";
    //Test padding
    TripleDES object0 = TripleDES(key, "0");
    string input = "1111";
    string padding = object0.encrypt(input);
    string noPadding = object0.decrypt(padding);
    assert(noPadding == input);
    //Test key roataion
    keyRotation object = keyRotation(key);
    for (int i = 0; i < 16; i++){
        key = object.nextRound();
    }
}