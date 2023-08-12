#include "triple_des.h"
#include "translate.h"
#include <iostream>
using namespace std;

int main()
{
    string done = "";
    while (done != "Q" && done != "q")
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
            if (inputForm == 2)
            {
                if (text.length() % 2 == 1)
                {
                    throw invalid_argument("Hex input must have an even length");
                }
                for (int i = 0; i < text.length(); i++)
                {
                    if (!((text[i] >= '0' && text[i] <= '9') || (text[i] >= 'a' && text[i] <= 'f') || (text[i] >= 'A' && text[i] <= 'F')))
                    {
                        throw invalid_argument("Invalid character in Hex");
                    }
                }
            }
            int length = text.length();
            int fragmentLength;
            if (inputForm == 1)
            {
                fragmentLength = 8;
            }
            else
            {
                fragmentLength = 16;
            }
            int amountOfFragment = length / fragmentLength;
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
                if (inputForm == 1)
                {
                    fragmnets[i] = trns.fromTextToBinary(fragmnets[i]);
                }
                else
                {
                    fragmnets[i] = trns.fromHexToBinary(fragmnets[i]);
                }
            }
            cout << "Enter the key: " << endl;
            string key;
            cin >> key;
            while (key.length() != 16 && key.length() != 24)
            {
                cout << "Key must have 16 or 24 characters. Please try again: " << endl;
                cin >> key;
            }
            int numOfKey = key.length() / 8;
            string keys[numOfKey];
            for (int i = 0; i < numOfKey; i++)
            {
                keys[i] = "";
                for (int j = 0; j < 8; j++)
                {
                    keys[i] = keys[i] + key[(i * 8) + j];
                }
                keys[i] = trns.fromTextToBinary(keys[i]);
            }

            bool hasThirdKey = false;
            if (numOfKey == 3)
            {
                hasThirdKey = true;
            }
            TripleDES object = TripleDES(keys[0], keys[1]);
            if (hasThirdKey)
            {
                object = TripleDES(keys[0], keys[1], keys[2]);
            }

            string outputHex = "";
            string outputText = "";
            for (int i = 0; i < amountOfFragment; i++)
            {
                if (choice == 1)
                {
                    fragmnets[i] = object.encrypt(fragmnets[i]);
                }
                else
                {
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
        }
        catch (invalid_argument &e)
        {
            cout << e.what() << endl;
        }
        catch (...)
        {
            cout << "An error has occured" << endl;
        }
        
        cout << "Enter any key to retry, or \"q\" to exit: " << endl;
        cin >> done;
    }
    return 0;
}