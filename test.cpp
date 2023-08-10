#include "triple_des.h"

int main(){
    string key0 = "0";
    string key1 = "0001001100110100010101110111100110011011101111001101111111110001";
    TripleDES encryption = TripleDES(key1, key0);
    string plain = "1000010111101000000100110101010000001111000010101011010000000101";
    string cipher = encryption.decrypt(plain);
}