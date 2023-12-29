/**
* Agac ve yigin kullanarak son kalan agacın yaprak olmayan elemanlarının toplamının ascii karşılığını ekrana yazdıran program
* Veri yapıları 1. öğretim B grubu
* 2. ödev
* 24-12-2023
* Muhammet Enes Nas B211210006
*/
#include "Dugum.hpp"
#include "Yigin.hpp"
#include <iostream>
using namespace std;

Yigin::Yigin() : kapasite(200), boyut(0)
{
    dizi = new int[kapasite];
}

Yigin::Yigin(int kapasite) : kapasite(kapasite), boyut(0)
{
    dizi = new int[kapasite];
}

bool Yigin::bos()
{
    return boyut == -1;
}

void Yigin::ekle(int eleman)
{
    if (!dolu())
    {
        boyut++;
        dizi[boyut] = eleman;
        boyutYedek = boyut;
    }
    else
    {
        cerr << "Hata: Yigin dolu!" << endl;
    }
}

bool Yigin::dolu()
{
    return boyut == kapasite;
}
int Yigin::tepe()
{
    if (!bos())
    {
        return dizi[boyut];
    }
    else
    {
        return -1;
    }
}
void Yigin::al()
{
    boyut--;
}

Yigin::~Yigin()
{

    delete[] dizi;
}
