#ifndef MYTHICKNESSDIALOG_H
#define MYTHICKNESSDIALOG_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "opencv_bridge.h"


class MyThicknessDialog : public wxDialog
{
private:
	wxButton* m_okButton;
	wxButton* m_cancelButton;
	IplImage* m_iplImage;
	wxImage* m_image;
	wxBitmap m_bitmap;
	wxColour m_color;
public:
	wxSlider* m_thickness;
	MyThicknessDialog( wxWindow* parent, wxColour color, wxWindowID id = wxID_ANY,
		const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = wxSL_HORIZONTAL);
	~MyThicknessDialog();
	void OnPaint(wxPaintEvent &WXUNUSED(event));
	void OnScroll(wxScrollEvent& event) ;


};


#endif
