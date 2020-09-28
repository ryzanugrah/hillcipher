/*
Anggota Kelompok : 	140810180005 - Fauzan Akmal hariz
					140810180013 - Alvin
					140810180049 - Rizky Anugerah
kelas	: A
Program	: Hill Chiper - Key Finder
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>

using namespace std;

int gcd(int m, int n)
{
    if (n > m)
        swap(m, n);

    do
    {
        int temp = m % n;
        m = n;
        n = temp;
    } while (n != 0);

    return m;
}

int findInvers(int m, int n)
{
    int t0 = 0, t1 = 1, invers, q, r, b = m;
    while (r != 1)
    {
        q = m / n;
        r = m % n;
        invers = t0 - q * t1;
        if (invers < 0)
        {
            invers = b - (abs(invers) % b);
        }
        else
        {
            invers %= b;
        }
        t0 = t1;
        t1 = invers;
        m = n;
        n = r;
    }
    return invers;
}

void findKey()
{
    //deklarasi
    string plainteks, cipherteks;
    int key[2][2], det, detInv, adj[2][2], plainteksInv[2][2], plainMatrix[2][2], cipMatrix[2][2], counter;
    int p, c;
    int transpose[2][2];

    //input plainteks
    cout << "Masukan Plainteks : ";
    cin.ignore();
    getline(cin, plainteks);

    //assign plainteks ke plainMatrix
    counter = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            p = toupper(plainteks[counter]) - 65;
            plainMatrix[i][j] = p;
            counter++;
        }
    }

    //input cipherteks
    cout << "Masukan Cipherteks : ";
    getline(cin, cipherteks);

    //assign cipherteks ke cipMatrix
    counter = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            c = toupper(cipherteks[counter]) - 65;
            cipMatrix[i][j] = c;
            counter++;
        }
    }

    //mencari determinan
    det = (plainMatrix[0][0] * plainMatrix[1][1]) - (plainMatrix[0][1] * plainMatrix[1][0]);
    if (gcd(det, 26) == 1)
    {
        //mencari inverse dari determinan
        detInv = findInvers(26, det);

        //menghitung matriks adjoin
        adj[0][0] = plainMatrix[1][1];
        adj[0][1] = (-1) * plainMatrix[0][1];
        adj[1][0] = (-1) * plainMatrix[1][0];
        adj[1][1] = plainMatrix[0][0];

        //menghitung matriks invers dari plainteks
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                plainteksInv[i][j] = detInv * adj[i][j];
                if (plainteksInv[i][j] < 0)
                {
                    plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j]) % 26);
                }
                else
                {
                    plainteksInv[i][j] = plainteksInv[i][j];
                    plainteksInv[i][j] = plainteksInv[i][j] % 26;
                }
            }
        }

        //mencari key
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                key[i][j] = 0;
                for (int k = 0; k < 2; k++)
                {
                    key[i][j] += (plainteksInv[i][k] * cipMatrix[k][j]);
                }
                key[i][j] %= 26;
            }
        }

        //output key
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                transpose[j][i] = key[i][j];
            }
        }

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << (transpose[i][j]) << "\t";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Determinan tidak relatif prima dengan jumlah huruf" << endl;
        cout << "Key tidak dapat dicari" << endl << endl;
    }
    system("pause");
    system("cls");
}

int main()
{
    bool menuActive = true;
    int key[2][2];
    key[0][0] = 7;
    key[0][1] = 8;
    key[1][0] = 19;
    key[1][1] = 3;
    int pil;
    while (menuActive)
    {
        cout << "\nPROGRAM KEY FINDER-HILL CHIPER" << endl;
        cout<<"=============================="<<endl;
        cout << "Menu : " << endl;
        cout << "1. Cari Key" << endl;
        cout << "2. Keluar" << endl;
        cout << "Pilih Menu : ";
        cin >> pil;
        switch (pil)
        {
        case 1:
            cout << endl;
            findKey();
            break;
        case 2:
            menuActive = false;
            break;
        default:
            cout << "\nPilihan salah" << endl;
            break;
        }
    }
}