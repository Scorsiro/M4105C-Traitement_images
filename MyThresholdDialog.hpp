#ifndef MYTHREESHOLDDIALOG_H
#define MYTHREESHOLDDIALOG_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

wxDECLARE_EVENT(MON_EVENEMENT, wxCommandEvent);

class MyThresholdDialog : public wxDialog
{
private:
	wxButton* m_okButton;
	wxButton* m_cancelButton;
public:
	wxSlider* m_threshold;
	MyThresholdDialog( wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = wxSL_HORIZONTAL );
	~MyThresholdDialog();
	void OnScroll(wxScrollEvent& event) ;


};


#endif
