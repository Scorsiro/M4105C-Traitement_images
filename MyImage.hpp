#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "opencv_bridge.h"
#include <vector>

class MyImage: public wxImage {
public:
    MyImage(const wxString& fileName) ;
    MyImage(wxImage image) ;
    MyImage() ;
    ~MyImage() ;
    void Negative();
    void Desaturate();
    void Threshold(int seuil);
    void Mirror(bool horizontally);
    wxImage Rotate90();
    void Posterize();
    int NombreCouleurs();
    void EnhenceContrast(int minValue, int maxValue);
    void Dither(); // Dither tp9
    void Draw(wxPoint point, wxColour color, int thickness);
    void Redraw(wxPoint pointA, wxPoint pointB, wxColour color, int thickness);
    wxPoint getOldPoint();
    void setOldPoint(wxPoint point);
    MyImage* copyImage();
    std::vector<wxPoint> m_line;
    std::vector<wxColour> m_line_color;
    std::vector<int> m_line_thickness;
    std::vector<std::vector<wxPoint>> m_draw_steps;
    unsigned int drawStep;
private:
    IplImage* iplImage;
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
