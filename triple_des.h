#pragma once
#ifndef TRIPLE_DES_H
#define TRIPLE_DES_H

#include <string>
using namespace std;
class TripleDES {
public:
    // Constructor for 2-Key Triple DES (16-byte key).
    TripleDES(const string& key);

    // Constructor for 3-Key Triple DES (24-byte key).
    TripleDES(const string& key1, const string& key2, const string& key3);

    // Encrypts the plaintext using Triple DES.
    string encrypt(const string& plaintext);

    // Decrypts the ciphertext using Triple DES.
    string decrypt(const string& ciphertext);

private:
    string key1_; // First 8 bytes of the 2-key or 3-key Triple DES key.
    string key2_; // Second 8 bytes of the 3-key Triple DES key (if applicable).
    string key3_; // Third 8 bytes of the 3-key Triple DES key (if applicable).

    // Helper functions for encryption and decryption.
    //Key rotation will be apart of the des_encrypt function
    //once the other parts are completed
    string des_encrypt(const string& input, const string& subkey);
    string des_decrypt(const string& input, const string& subkey);
    string apply_padding(const string& input);
    string remove_padding(const string& input);

    // XOR two strings of equal length.
    string xor_strings(const string& str1, const string& str2);
};

#endif // TRIPLE_DES_H
