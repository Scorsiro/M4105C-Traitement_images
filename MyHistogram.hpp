#ifndef MYHISTOGRAM_H
#define MYHISTOGRAM_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "MyImage.hpp"

class MyHistogram {
public:
    MyHistogram(MyImage* image);
    void GetBorderValues(int *minValue, int *maxValue);
private:
    MyImage* image;
    unsigned char* tableau;

};

#endif // MYHISTOGRAM_H
