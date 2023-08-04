#pragma once
#ifndef TRIPLE_DES_H
#define TRIPLE_DES_H

#include <string>
#include <math.h>
using namespace std;
class TripleDES {
public:
    // Constructor for 2-Key Triple DES (16-byte key).
    TripleDES(const string& key1, const string& key2);

    // Constructor for 3-Key Triple DES (24-byte key).
    TripleDES(const string& key1, const string& key2, const string& key3);

    // Encrypts the plaintext using Triple DES.
    string encrypt(string& plaintext);

    // Decrypts the ciphertext using Triple DES.
    string decrypt(string& ciphertext);

private:
    string key1_; // First 8 bytes of the 2-key or 3-key Triple DES key.
    string key2_; // Second 8 bytes of the 3-key Triple DES key (if applicable).
    string key3_; // Third 8 bytes of the 3-key Triple DES key (if applicable).

    // Helper functions for encryption and decryption.
    //Key rotation will be apart of the des_encrypt function
    //once the other parts are completed
    string des_encrypt(const string& input, const string& subkey);
    string des_decrypt(const string& input, const string& subkey);
    string apply_padding(string& input);
    string remove_padding(string& input);

    // XOR two strings of equal length.
    string xor_strings(const string& str1, const string& str2);
    //To binary
    string toBinary(int num);
    int toDecimal(string binary);
};

#endif // TRIPLE_DES_H
TripleDES::TripleDES(const string& key1, const string& key2){
    key1_ = key1;
    key2_ = key2;
    key3_ = "";
}
TripleDES::TripleDES(const string& key1, const string& key2, const string& key3){
    key1_ = key1;
    key2_ = key2;
    key3_ = key3;
}
string TripleDES::encrypt(string& plaintext){
    //In construction
    return apply_padding(plaintext);
}
string TripleDES::decrypt(string& ciphertext){
    //In construction
    return remove_padding(ciphertext);
}
string TripleDES::toBinary(int num){
    string binary = "";
    int comparer;
    for (int i = 7; i >= 0; i--){
        comparer = num - pow(2,i);
        if (comparer >= 0){
            binary = binary + "1";
            num = num - pow(2,i);
        }
        else{
            binary = binary + "0";
        }
    }
    return binary;
}
int TripleDES::toDecimal(string binary){
        int num = 0;
        for (int i = 0; i < 8; i++){
            if (binary[i] == '1'){
                num = num + pow(2, i);
            }
        }
        return num;
}
string TripleDES::apply_padding(string& input){
    int length = input.length();
    string output = input;
    int paddingBits;
    if (length % 64 != 0){
        paddingBits = 64 - (length % 64);
    }
    for (int i = 0; i < paddingBits - 8; i++){
        output = output + "0";
    }
    output = output + toBinary(paddingBits);
    return output;
}
string TripleDES::remove_padding(string& input){
    string lastByte = "";
    string output = "";
    int length = input.length();
    for (int i = 0; i < 8; i++){
        lastByte = lastByte + input[length - 8 + i];
    }
    int paddingBits = toDecimal(lastByte);
    for (int i = 0; i < (length - paddingBits); i++){
        output = output + input[i];
    }
    return output;
}