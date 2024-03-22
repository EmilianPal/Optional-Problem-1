#include <iostream>
#include <fstream>
#include <cstring>
#define Size 301
using namespace std;
ifstream fin("distribution.txt");
void setUp(float freq_eng[])
{
    //This function will receive the values of the percentage of appearance of each letter in the words of the English language
    //The function will receive an array of at least 26 elements and will not return anything
    for(int i = 0; i < 26; ++i)
        fin >> freq_eng[i];
}
void freqWord(char text[], float freq[], int n)
{
    //This function will receive an array of string and it will count the appearance of each letter inside the word inside an array.
    //Each letter is placed in a position equal to its place in the alphabet - 1.
    //text[i] - 'a' is meant to represent said position
    for(int i = 0; i < 26; ++i)
        freq[i] = 0;
    for(int i = 0; i <= n; ++i)
    {
        if('a' <= text[i] and text[i] <= 'z')
            freq[text[i] - 'a']++;
        if('A' <= text[i] and text[i] <= 'Z')
            freq[text[i] - 'A']++;
    }
}
void normHist(float freq[])
{
    //This function will change the values of the histograph into a percentage
    float s = 0;
    for(int i = 0; i < 26; ++i)
        s += freq[i];
    for(int i = 0; i < 26; ++i)
        freq[i] = float(freq[i] / s * 100);
}
float chiSquared(float freq[], float freq_eng[], int n)
{
    //This function will compute the Chi squared distance between a histograph and a Caesar encryption of the English alphabet by the value n
    //the value n is added to the freq_eng's index to simulate the letters being shifted by the cypher with a value of n
    //This function will return an int
    float s = 0;
    for (int i = 0; i < 26; ++i)
        s = s + (freq[i] - freq_eng[(i + n) % 26]) * (freq[i] - freq_eng[(i + n) % 26]) / freq_eng[(i + n) % 26];
    return s;
}
int chiSquaredSol(float freq[], float freq_eng[])
{
    //This function will return the shift of the text with the lowest Chi Squared distance
    //min_p is an int between 0 and 25
    float dist, mini;
    int min_p = 0;
    mini = chiSquared(freq, freq_eng, 0);
    for(int i = 1; i < 26; ++i)
    {
        dist = chiSquared(freq, freq_eng, i);
        if(mini > dist)
        {
            mini = dist;
            min_p = i;
        }
    }
    return min_p;
}
void decrypt(char text[], int n, int sol, char decrypted[])
{
    //This function will place within the decrypted function the rough decryption of the text by shifting every character within text by n characters
    strcpy(decrypted, "");
    for(int i = 0; i <=  n; ++i)
    {
        if('a' <= text[i] && text[i] <= 'z')
            decrypted[i] = 'a' + int((text[i]- 'a' + sol) % 26);
        else if('A' <= text[i] && text[i] <= 'Z')
            decrypted[i] = 'A' + int((text[i] - 'A' + sol) % 26);
        else decrypted[i] = text[i];
    }
}
int main()
{
    float freq[26], freq_eng[26];
    char text[Size], decrypted[Size];
    int n, sol, option = 1;
    setUp(freq_eng);
    cout << "1. Decipher the example text;\n2. Decipher an inputted text;\n0. Quit.\n";
    while(option)
    {
        cout << "Select an option: "; cin >> option;
        if(option >= 1 && option <= 2)
        {
            if(option == 1)
            {
                strcpy(text, "Uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr, ");
                strcat(text, "uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud.");
                cout << text << '\n';
            }
            else if(option == 2)
            {
                cout << "Input text: ";
                cin.ignore();
                cin.getline(text, Size);
            }
            n = strlen(text);
            freqWord(text, freq, n);
            normHist(freq);
            sol = chiSquaredSol(freq, freq_eng);
            decrypt(text, n, sol, decrypted);
            cout << decrypted << '\n';
        }
    }
    return 0;
}
