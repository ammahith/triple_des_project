#include "triple_des.h"
#include "translate.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "3DES Encryption and Decription" << endl;
    cout << "Padding mode: Zeroes" << endl;
    cout << "Select action: " << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    int choice = 0;
    try
    {
        while (!(cin >> choice) || (choice != 1 && choice != 2))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again: " << endl;
        }

        bool hasPaddings = false;
        cout << "Choose input format:" << endl;
        cout << "1. English" << endl;
        cout << "2. Hex" << endl;
        int inputForm;
        while (!(cin >> inputForm) || (inputForm != 1 && inputForm != 2))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again: " << endl;
        }

        char answer;
        if (choice == 1)
        {
            cout << "Enter plaintext: " << endl;
        }
        else if (choice == 2)
        {
            cout << "Does plaintext include paddings: Y/N" << endl;
            while (!(cin >> answer) || (toupper(answer) != 'Y' && toupper(answer) != 'N'))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please try again: " << endl;
            }
            cout << "Enter ciphertext: " << endl;
        }
        translate trns;
        string text;
        cin >> text;
        if (inputForm == 2){
            for (int i = 0; i < text.length(); i++){
                if (!((text[i] >= '0' && text[i] <= '9') 
                || (text[i] >= 'a' && text[i] <= 'f') 
                || (text[i] >= 'A' && text[i] <= 'F'))){
                    throw invalid_argument("Invalid character in Hex");
                }
            }
        }
        int length = text.length();
        int fragmentLength;
        if (inputForm == 1){
            fragmentLength = 8;
        }
        else{
            fragmentLength = 16;
        }
        int amountOfFragment = length/fragmentLength;
        if (length % fragmentLength != 0)
        {
            amountOfFragment++;
        }
        string fragmnets[amountOfFragment];
        for (int i = 0; i < amountOfFragment; i++)
        {
            int j = 0;
            fragmnets[i] = "";
            while (j < fragmentLength && (i * fragmentLength) + j < length)
            {
                fragmnets[i] = fragmnets[i] + text[(i * fragmentLength) + j];
                j++;
            }
            if (inputForm == 1){
                fragmnets[i] = trns.fromTextToBinary(fragmnets[i]);
            }
            else{
                fragmnets[i] = trns.fromHexToBinary(fragmnets[i]);
            }   
        }
        cout << "Enter the first key: " << endl;
        string key1;
        cin >> key1;
        while (key1.length() != 8)
        {
            cout << "Key must have 8 characters, including white space. Please try again: " << endl;
            cin >> key1;
        }
        key1 = trns.fromTextToBinary(key1);

        cout << "Enter the second key: " << endl;
        string key2;
        cin >> key2;
        while (key2.length() != 8)
        {
            cout << "Key must have 8 characters, including white space. Please try again: " << endl;
            cin >> key2;
        }
        key2 = trns.fromTextToBinary(key2);

        cout << "Use third key? Y/N" << endl;
        char thirdKey;
        string key3;
        bool hasThirdKey = false;
        while (!(cin >> thirdKey) || (toupper(thirdKey) != 'Y' && toupper(thirdKey) != 'N'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again: " << endl;
        }
        if (toupper(thirdKey) == 'Y')
        {
            hasThirdKey = true;
            cout << "Enter the third key: " << endl;
            cin >> key3;
            while (key3.length() != 8)
            {
                cout << "Key must have 8 characters, including white space. Please try again: " << endl;
                cin >> key3;
            }
            key3 = trns.fromTextToBinary(key3);
        }
        TripleDES object = TripleDES(key1, key2);
        if (hasThirdKey){
            object = TripleDES(key1, key2, key3);
        }

        string outputHex = "";
        string outputText = "";
        for (int i = 0; i < amountOfFragment; i++){
            if (choice == 1){
                fragmnets[i] = object.encrypt(fragmnets[i]);
            }
            else{
                if (toupper(answer) == 'Y' && i == amountOfFragment - 1)
                {
                    hasPaddings = true;
                }
                fragmnets[i] = object.decrypt(fragmnets[i], hasPaddings);
            }
            outputHex = outputHex + trns.fromBinaryToHex(fragmnets[i]);
            outputText = outputText + trns.fromBinaryToText(fragmnets[i]);
        }
        cout << "Result in Hex: " << endl;
        cout << outputHex << endl;
        cout << "Result in English: " << endl;
        cout << outputText << endl;
        return 0;
    }
    catch(invalid_argument& e){
        cout << e.what() << endl;
        return -1;
    }
    catch (...)
    {
        cout << "An error has occured" << endl;
        return -1;
    }
}