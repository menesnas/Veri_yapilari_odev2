/**
* Agac ve yigin kullanarak son kalan agacın yaprak olmayan elemanlarının toplamının ascii karşılığını ekrana yazdıran program
* Veri yapıları 1. öğretim B grubu
* 2. ödev
* 24-12-2023
* Muhammet Enes Nas B211210006
*/
#include "Avlagaci.hpp"
#include "Dugum.hpp"
#include "Yigin.hpp"
#include <iostream>
using namespace std;


// AVL ağacına düğüm ekleme işlemi
Dugum* AvlAgaci::ekle(Dugum *kok, int veri)
{
    if (kok == nullptr)
        return new Dugum(veri);

    // Benzersiz eleman kontrolü
    if (veri < kok->veri)
        kok->sol = ekle(kok->sol, veri);
    else if (veri > kok->veri)
        kok->sag = ekle(kok->sag, veri);

    // AVL ağacını dengele
    int denge = dengele(kok);

    // Denge faktörü negatifse sol tarafta bir düzensizlik var
    if (denge > 1)
    {
        if (veri < kok->sol->veri)
        {
            // Sol-sol durumu
            return sagaDon(kok);
        }
        else
        {
            // Sol-sağ durumu
            kok->sol = solaDon(kok->sol);
            return sagaDon(kok);
        }
    }

    // Denge faktörü pozitifse sağ tarafta bir düzensizlik var
    if (denge < -1)
    {
        if (veri > kok->sag->veri)
        {
            // Sağ-sağ durumu
            return solaDon(kok);
        }
        else
        {
            // Sağ-sol durumu
            kok->sag = sagaDon(kok->sag);
            return solaDon(kok);
        }
    }

    // Denge faktörü 1 veya -1 ise düğüm dengededir
    return kok;
}

// AVL ağacı için dengeleme işlemi
int AvlAgaci::dengele(Dugum *dugum)
{
    if (dugum == nullptr)
        return 0;
    return yukseklik(dugum->sol) - yukseklik(dugum->sag);
}

// Ağaçtaki bir düğümün yüksekliğini hesapla
int AvlAgaci::yukseklik(Dugum *dugum)
{
    if (dugum == nullptr)
        return 0;
    return 1 + max(yukseklik(dugum->sol), yukseklik(dugum->sag));
}

// Sağa dönüş yap
Dugum* AvlAgaci::sagaDon(Dugum *y)
{
    Dugum *x = y->sol;
    Dugum *T2 = x->sag;

    x->sag = y;
    y->sol = T2;

    return x;
}

// Sola dönüş yap
Dugum* AvlAgaci::solaDon(Dugum *x)
{
    Dugum *y = x->sag;
    Dugum *T2 = y->sol;

    y->sol = x;
    x->sag = T2;

    return y;
}

// Ağacı postorder şekilde dolaşarak yaprakları yığına ekleyen yardımcı fonksiyon
void AvlAgaci::postorderYapraklariYiginaEkle(Dugum *kok, Yigin &yaprakYigin)
{
    if (kok != nullptr)
    {
        postorderYapraklariYiginaEkle(kok->sol, yaprakYigin);
        postorderYapraklariYiginaEkle(kok->sag, yaprakYigin);
        if (kok->sol == nullptr && kok->sag == nullptr)
        {
            yaprakYigin.ekle(kok->veri);
        }
    }
}
void AvlAgaci::temizle(Dugum *kok) // bellek temizliği
{
    if (kok != nullptr)
    {
        temizle(kok->sol);
        temizle(kok->sag);
        delete kok;
    }
}
int AvlAgaci::toplamYaprakOlmayanDugumler(Dugum *kok)
{
    if (kok == nullptr)
        return 0;

    // Eğer düğüm yaprak değilse, değerini toplama ekle
    if (kok->sol != nullptr || kok->sag != nullptr)
        return kok->veri + toplamYaprakOlmayanDugumler(kok->sol) + toplamYaprakOlmayanDugumler(kok->sag);
    else
        return 0;
}
bool AvlAgaci::DugumSil(Dugum *&subNode)
{
    Dugum *delNode = subNode;

    if (subNode->sag == nullptr)
        subNode = subNode->sol;
    else if (subNode->sol == nullptr)
        subNode = subNode->sag;
    else
    {
        delNode = subNode->sol;
        Dugum *parentNode = subNode;
        while (delNode->sag != nullptr)
        {
            parentNode = delNode;
            delNode = delNode->sag;
        }
        subNode->veri = delNode->veri;
        if (parentNode == subNode)
            subNode->sol = delNode->sol;
        else
            parentNode->sag = delNode->sol;
    }
    delete delNode;
    return true;
}

bool AvlAgaci::bos()
{
    return kok == nullptr;
}
AvlAgaci::AvlAgaci() : kok(nullptr) {}

void AvlAgaci::ekle(int veri)
{
    kok = ekle(kok, veri);
}

void AvlAgaci::yapraklariYiginaEkle(Yigin &yaprakYigin)
{
    postorderYapraklariYiginaEkle(kok, yaprakYigin);
}
int AvlAgaci::toplamYaprakOlmayanDugumler()
{
    return toplamYaprakOlmayanDugumler(kok);
}
void AvlAgaci::Clear()
{
    while (!bos())
        DugumSil(kok);
}
AvlAgaci::~AvlAgaci()
{
    Clear();
}