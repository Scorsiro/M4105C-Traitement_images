#ifndef LUMINOSITEDIALOG_H
#define LUMINOSITEDIALOG_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

wxDECLARE_EVENT(MON_EVENEMENT1, wxCommandEvent);

class LuminositeDialog : public wxDialog
{
    public:
        LuminositeDialog( wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = wxSL_HORIZONTAL );

        ~LuminositeDialog();


    protected:
    wxSlider* m_luminosite;


	void OnScroll(wxScrollEvent& event) ;

    private:
        wxButton* m_okButton;
        wxButton* m_cancelButton;
};

#endif // LUMINOSITEDIALOG_H
