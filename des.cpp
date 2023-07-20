#include <iostream>
#include <math.h>
#include <string>
using namespace std;
//Author: Duc Doan
//Date created: March 12th
//Last modification: March 14th
//Purpose: Simplified DES encryption 8 rounds

string divideRight(string original)
{
    string r;
    int size = original.length()/2;
    char* array = new char[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = original[i + size];
    }
    r = string(array);
    array = nullptr;
    delete[] array;
    
    return r;
}
string divideLeft(string original)
{
    string l;
    int size = original.length()/2;
    char* array = new char[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = original[i];
    }
    l = string(array);
    array = nullptr;
    delete[] array;
    
    return l;
}

string binaryAdd(string bi1, string bi2)
{

    string total;
    int size = bi1.length();
    char* array = new char[size];
    for (int i = 0; i < size; i++)
    {
        if ((bi1[i] == '1') == (bi2[i] == '1'))
        {
            array[i] = '0';
        }
        else
        {
            array[i] = '1';
        }
    }
    total = string(array);
    array = nullptr;
    delete[] array;
    
    return total;
}
int toColumn(string arr)
{
    int col;
    if (arr[0] == '1')
    {
        col = 1;
    }
    else
    {
        col = 0;
    }
    return col;
}
int toRow(string arr){
    int row = 0;
    for (int i = 1; i < 4; i++){
        if (arr[i] == '1'){
            row = row + pow(2, 3 - i );
        }
    }
    return row;
}
string checkSBox1(int column, int row)
{
    string Sbox1[2][8] = {"101", "010", "001", "110", "011", "100", "111", "000",
                          "001", "100", "110", "010", "000", "111", "101", "011"};
    char* array = new char[3];
    string result;
    for (int i = 0; i < 3; i++)
    {
        array[i] = Sbox1[column][row][i];
    }
    result = string(array);
    array = nullptr;
    delete[] array;
    
    return result;
}
string checkSBox2(int column, int row)
{
    string Sbox2[2][8] = {"100", "000", "110", "101", "111", "001", "011", "010",
                          "101", "011", "000", "111", "110", "010", "001", "100"};
    char* array = new char[3];
    string result;
    for (int i = 0; i < 3; i++)
    {
        array[i] = Sbox2[column][row][i];
    }
    result = string(array);
    array = nullptr;
    delete[] array;
    
    return result;
}
string connect(string array1, string array2)
{
    int size = array1.length();
    char* array = new char[2*size];
    string result;
    for (int i = 0; i < size; i++)
    {
        array[i] = array1[i];
    }
    for (int i = 0; i < size; i++)
    {
        array[i + size] = array2[i];
    }
    result = string(array);
    array = nullptr;
    delete[] array;
    
    return result;
}
string funct(string r, string key, int round)
{

    string expanded;
    char* expandedArr = new char[8];
    expandedArr[0] = r[0];
    expandedArr[1] = r[1];
    expandedArr[2] = r[3];
    expandedArr[3] = r[2];
    expandedArr[4] = r[3];
    expandedArr[5] = r[2];
    expandedArr[6] = r[4];
    expandedArr[7] = r[5];

    expanded = string(expandedArr);
    expandedArr = nullptr;
    delete[] expandedArr;
    

    string key_round;
    char* keyArr = new char[8];
    for (int i = 0; i < 8; i++)
    {
        keyArr[i] = key[(round + i) % 9];
    }
    key_round = string(keyArr);
    keyArr = nullptr;
    delete[] keyArr;
    

    string sum = binaryAdd(expanded, key_round);
    string sum_left;
    sum_left = divideLeft(sum);
    string sum_right;
    sum_right = divideRight(sum);

    return connect(checkSBox1(toColumn(sum_left), toRow(sum_left)), checkSBox2(toColumn(sum_right), toRow(sum_right)));
}

int main()
{
    int round;
    string p;
    string c;
    string k;
    string p_left;
    string p_right;
    string temp;
    
    p = "001100001010";
    cout << "Plain text: " << p << endl;
    
    k = "111000101";
    cout << "Enter key: " << k << endl;
    

    
    for (int m = 0; m < 8; m++)
    {   
        cout << "Round " << m + 1 << ": ";
        
        p_left = divideLeft(p);
        p_right = divideRight(p);

        temp = p_left;
        p_left = p_right;
        p_right = funct(p_right, k, m);
        p_right = binaryAdd(temp, p_right);
        p = connect(p_left, p_right);
        cout << p << endl;
    }
    
}