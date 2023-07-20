#pragma once
#ifndef TRIPLE_DES_H
#define TRIPLE_DES_H

#include <string>

class TripleDES {
public:
    // Constructor takes a 16-byte key (128-bit) or a 24-byte key (192-bit).
    TripleDES(const std::string& key);

    // Encrypts the plaintext using Triple DES in CBC mode with PKCS#7 padding.
    std::string encrypt(const std::string& plaintext);

    // Decrypts the ciphertext using Triple DES in CBC mode with PKCS#7 padding.
    std::string decrypt(const std::string& ciphertext);

private:
    // The 16-byte key (128-bit) or 24-byte key (192-bit).
    std::string key_;

    // Subkeys for each round of Triple DES.
    std::string subkeys_[3];

    // Helper functions for encryption and decryption.
    void generate_subkeys();
    std::string des_encrypt(const std::string& input, const std::string& subkey);
    std::string des_decrypt(const std::string& input, const std::string& subkey);
    std::string apply_padding(const std::string& input);
    std::string remove_padding(const std::string& input);

    // XOR two strings of equal length.
    std::string xor_strings(const std::string& str1, const std::string& str2);
};
#endif // TRIPLE_DES_H
