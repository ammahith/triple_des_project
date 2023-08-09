#include "key_rotation.h"
#include "triple_des.h"
#include "function.h"

int main(){
    string key = "0001001100110100010101110111100110011011101111001101111111110001";
    
    //Test function
    string input0 = "1100110000000000110011001111111111110000101010101111000010101010";
    string subKey = "000110110000001011101111111111000111000001110010";
    f func = f(input0,subKey);
    string final = func.execute();

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