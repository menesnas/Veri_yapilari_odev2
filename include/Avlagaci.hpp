#ifndef AvlAgaci_hpp
#define AvlAgaci_hpp
#include "Yigin.hpp"
#include "Dugum.hpp"
using namespace std;

class AvlAgaci
{
private:
    Dugum *kok;
    Dugum *ekle(Dugum *kok, int veri);
    int dengele(Dugum *dugum);
    int yukseklik(Dugum *dugum);
    Dugum *sagaDon(Dugum *y);
    Dugum *solaDon(Dugum *x);
    void postorderYapraklariYiginaEkle(Dugum *kok, Yigin &yaprakYigin);
    void temizle(Dugum *kok);
    int toplamYaprakOlmayanDugumler(Dugum *kok);
    bool DugumSil(Dugum *&subNode);

public:
    int sayi;
    bool bos();
    AvlAgaci();
    void ekle(int veri);

    void yapraklariYiginaEkle(Yigin &yaprakYigin);
    int toplamYaprakOlmayanDugumler();
    void Clear();
    ~AvlAgaci();
};
#endif