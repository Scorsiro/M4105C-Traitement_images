#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "opencv_bridge.h"

class MyImage: public wxImage {
public:
    MyImage(const wxString& fileName) ;
    MyImage(wxImage image) ;
    MyImage() ;
    void Negative();
    void Desaturate();
    void Threshold(int seuil);
    void Mirror(bool horizontally);
    wxImage Rotate90();
    void Posterize();
    int NombreCouleurs();
    void EnhenceContrast(int minValue, int maxValue);
    void Draw(wxPoint point, int color);
    wxPoint getOldPoint();
    void setOldPoint(wxPoint point);
private:
    wxPoint oldPoint;
};

/*enum
{
ID_Red = 22,
ID_Green = 23,
ID_Blue = 24
};
*/
#endif
