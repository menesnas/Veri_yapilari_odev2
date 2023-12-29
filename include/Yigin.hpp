#ifndef Yigin_hpp
#define Yigin_hpp
using namespace std;


class Yigin
{
private:
    int *dizi;
    int kapasite;

public:
    int boyut = -1;
    int boyutYedek;
    Yigin();

    Yigin(int kapasite);

    bool bos();

    void ekle(int eleman);

    // Yığın dolu mu?
    bool dolu();
    int tepe();
    void al();
    ~Yigin();
};

#endif