#pragma once
#ifndef TRIPLE_DES_H
#define TRIPLE_DES_H

#include <string>

class TripleDES {
public:
    // Constructor for 2-Key Triple DES (16-byte key).
    TripleDES(const std::string& key);

    // Constructor for 3-Key Triple DES (24-byte key).
    TripleDES(const std::string& key1, const std::string& key2, const std::string& key3);

    // Encrypts the plaintext using Triple DES.
    std::string encrypt(const std::string& plaintext);

    // Decrypts the ciphertext using Triple DES.
    std::string decrypt(const std::string& ciphertext);

private:
    std::string key1_; // First 8 bytes of the 2-key or 3-key Triple DES key.
    std::string key2_; // Second 8 bytes of the 3-key Triple DES key (if applicable).
    std::string key3_; // Third 8 bytes of the 3-key Triple DES key (if applicable).

    // Helper functions for encryption and decryption.
    std::string des_encrypt(const std::string& input, const std::string& subkey);
    std::string des_decrypt(const std::string& input, const std::string& subkey);
    std::string apply_padding(const std::string& input);
    std::string remove_padding(const std::string& input);

    // XOR two strings of equal length.
    std::string xor_strings(const std::string& str1, const std::string& str2);
};

#endif // TRIPLE_DES_H
