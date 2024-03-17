#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#define Size 301
using namespace std;
ifstream fin("distribution.txt");
void setUp(float freq_eng[])
{
    for(int i = 0; i < 26; ++i)
        fin >> freq_eng[i];
}
void freqWord(char text[], float freq[], int n)
{
    for(int i = 0; i < 26; ++i)
        freq[i] = 0;
    for(int i = 0; i <= n; ++i)
    {
        if('a' <= text[i] and text[i] <= 'z')
            freq[int(text[i] - 'a')]++;
        if('A' <= text[i] and text[i] <= 'Z')
            freq[int(text[i] - 'A')]++;
    }
}
void normHist(float freq[])
{
    float s = 0;
    for(int i = 0; i < 26; ++i)
        s += freq[i];
    for(int i = 0; i < 26; ++i)
        freq[i] = float(freq[i] / s * 100);
}
float chiSquared(float freq[], float freq_eng[], int n)
{
    float s = 0;
    for (int i = 0; i < 26; ++i)
        s = s + (freq[i] - freq_eng[(i + n) % 26]) * (freq[i] - freq_eng[(i + n) % 26]) / freq_eng[(i + n) % 26];
    return s;
}
int chiSquaredSol(float freq[], float freq_eng[])
{
    float dist, mini = INT_MAX;
    int min_p;
    for(int i = 0; i < 26; ++i)
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
