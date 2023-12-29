/**
* Agac ve yigin kullanarak son kalan agacın yaprak olmayan elemanlarının toplamının ascii karşılığını ekrana yazdıran program
* Veri yapıları 1. öğretim B grubu
* 2. ödev
* 24-12-2023
* Muhammet Enes Nas B211210006
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "Avlagaci.hpp"
#include "Yigin.hpp"
#include "Dugum.hpp"
#include <climits>
#include <iomanip>
using namespace std;

char intToAscii(int value)
{
    if (value >= 0 && value <= 127)
    {
        return char(value);
    }
    else
    {
        cerr << "Hata: Geçersiz ASCII değeri!" << endl;
        return '\0';
    }
}

void enKucuk(Yigin *yaprakYiginDizisi, int satirSayisi, int &minIndex)
{
    int enKucukDeger = yaprakYiginDizisi[0].tepe();
    for (int i = 0; i < satirSayisi; i++)
    {
        int tepeDeger = yaprakYiginDizisi[i].tepe();
        if (tepeDeger < enKucukDeger)
        {
            enKucukDeger = tepeDeger;
            minIndex = i;
        }
    }
    yaprakYiginDizisi[minIndex].al();
}

void enBuyuk(Yigin *yaprakYiginDizisi, int satirSayisi, int &maxIndex)
{
    int enBuyukDeger = yaprakYiginDizisi[0].tepe();

    for (int i = 0; i < satirSayisi; i++)
    {
        int tepeDeger = yaprakYiginDizisi[i].tepe();
        if (tepeDeger > enBuyukDeger)
        {
            enBuyukDeger = tepeDeger;
            maxIndex = i;
        }
    }
    yaprakYiginDizisi[maxIndex].al();
}

int main()
{
    ifstream dosya("Veri.txt");
    if (!dosya.is_open())
    {
        cerr << "Hata: Dosya acilamadi!" << std::endl;
        return -1;
    }

    string satir;
    int satirSayisi = 0;

    while (getline(dosya, satir))
    {
        satirSayisi++;
    }
    dosya.clear();
    dosya.seekg(0);

    AvlAgaci *avlAgacDizisi = new AvlAgaci[satirSayisi];
    Yigin *yaprakYiginDizisi = new Yigin[satirSayisi];

    for (int i = 0; i < satirSayisi; i++)
    {
        getline(dosya, satir);
        stringstream ss(satir);
        int eleman;
        ss >> eleman;
        avlAgacDizisi[i].ekle(eleman);

        while (ss >> eleman)
        {
            avlAgacDizisi[i].sayi = i + 1;
            avlAgacDizisi[i].ekle(eleman);
        }
        avlAgacDizisi[i].yapraklariYiginaEkle(yaprakYiginDizisi[i]);
    }
    int ascii;
    char c;
    int minIndex, maxIndex;
    for (int i = 0; i < satirSayisi; i++)
    {
        ascii = avlAgacDizisi[i].toplamYaprakOlmayanDugumler() % (90 - 65 + 1) + 65;
        c = intToAscii(ascii);
        if (c != '\0')
        {
            cout << c;
        }
    }
    system("cls");
    while (true)
    {

        minIndex = maxIndex = 0;

        // EN KÜÇÜK
        enKucuk(yaprakYiginDizisi, satirSayisi, minIndex);

        if (yaprakYiginDizisi[minIndex].boyut == -1)
        {
            avlAgacDizisi[minIndex].Clear();
            for (int i = minIndex; i < satirSayisi; i++)
            {
                yaprakYiginDizisi[i] = yaprakYiginDizisi[i + 1];

                avlAgacDizisi[i] = avlAgacDizisi[i + 1];
            }
            satirSayisi--;
            for (int i = 0; i < satirSayisi; i++)
            {
                yaprakYiginDizisi[i].boyut = yaprakYiginDizisi[i].boyutYedek;
                ascii = avlAgacDizisi[i].toplamYaprakOlmayanDugumler() % (90 - 65 + 1) + 65;
                c = intToAscii(ascii);
                if (c != '\0')
                {
                    cout << c;
                }
            }
            system("cls");

            continue;
        }

        // EN BÜYÜK
        enBuyuk(yaprakYiginDizisi, satirSayisi, maxIndex);

        if (yaprakYiginDizisi[maxIndex].boyut == -1)
        {
            avlAgacDizisi[maxIndex].Clear();
            for (int i = maxIndex; i < satirSayisi; i++)
            {
                yaprakYiginDizisi[i] = yaprakYiginDizisi[i + 1];

                avlAgacDizisi[i] = avlAgacDizisi[i + 1];
            }
            satirSayisi--;
            for (int i = 0; i < satirSayisi; i++)
            {
                yaprakYiginDizisi[i].boyut = yaprakYiginDizisi[i].boyutYedek;
                ascii = avlAgacDizisi[i].toplamYaprakOlmayanDugumler() % (90 - 65 + 1) + 65;
                c = intToAscii(ascii);
                if (c != '\0')
                {
                    cout << c;
                }
            }
            system("cls");
        }
        if (satirSayisi == 1)
        {
            ascii = avlAgacDizisi[0].toplamYaprakOlmayanDugumler() % (90 - 65 + 1) + 65;
            c = intToAscii(ascii);
            cout << "==========================================" << endl;
            cout << "|                                        |" << endl;
            cout << "|                                        |" << endl;
            cout << "|           "
                 << "Son Karakter: " << c << "              |" << endl;

            cout << "|           "
                 << "AVL No: " << avlAgacDizisi[0].sayi << setw(19) << "|" << endl;
            cout << "|                                        |" << endl;
            cout << "|                                        |" << endl;
            cout << "==========================================" << endl;
            avlAgacDizisi[0].Clear();
            break;
        }
    }
    delete[] yaprakYiginDizisi;
    delete[] avlAgacDizisi;
    return 0;
}
