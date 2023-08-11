#pragma once
#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <string>
#include <math.h>
using namespace std;

class translate
{
private:
public:
    string fromTextToBinary(string &str);
    string fromBinaryToHex(string &binary);
    string fromHexToBinary(string &hex);
};
#endif

string translate::fromTextToBinary(string &str)
{
    int ascii[str.length()];
    string result = "";
    for (int i = 0; i < str.length(); i++)
    {
        ascii[i] = str[i];
        for (int j = 7; j >= 0; j--)
        {
            if (ascii[i] - pow(2, j) < 0)
            {
                result = result + "0";
            }
            else
            {
                result = result + "1";
                ascii[i] = ascii[i] - pow(2, j);
            }
        }
    }
    return result;
}
string translate::fromBinaryToHex(string& binary){
    int ascii[binary.length()/8];
    string result = "";
    char letter;
    int length = binary.length();
    int hex[2];
    for (int i = 0; i < length/8; i++){
        ascii[i] = 0;
        for (int j = 0; j < 8; j++){
            if (binary[(i*8)+j] == '1'){
                ascii[i] = ascii[i] + pow(2, 7 - j);
            }
        }
        hex[0] = ascii[i]/16;
        hex[1] = ascii[i]%16;
        for (int element: hex){
            if (element > 9){
                element= element + 55;
            }
            else{
                element = element + '0';
            }
            letter = element;
            result = result + letter;
        }
    }
    return result;
}

string translate::fromHexToBinary(string& hex){
    string result = "";
    int ten;
    int unit;
    int num;
    for (int i = 0; i < hex.length(); i++){
        if (hex[i] > '9'){
            num = hex[i] - 55;
        }
        else{
            num = hex[i] - '0';
        }
        if (i%2 == 0){
            ten= num;
        }
        else{
            unit = num;
            num = ten*16 + unit;
            for (int j = 7; j >=0; j--){
                if (num - pow(2,j) < 0){
                    result = result + "0";
                }
                else{
                    result = result + "1";
                    num = num - pow(2,j);
                }
            }
        }

    }
    return result;
}