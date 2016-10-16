#include "LuminositeDialog.h"

LuminositeDialog::LuminositeDialog(
	wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style )
: wxDialog( parent, id, title, pos, size, style )
{
	m_luminosite = new wxSlider( this, wxID_ANY, 128, 0, 255, wxPoint(20,10), wxSize(100,50),wxEVT_SCROLL_THUMBTRACK );
	m_luminosite->Bind(wxEVT_SCROLL_THUMBTRACK,&LuminositeDialog::OnScroll,this); //Connexion
	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(20,60), wxDefaultSize, 0 );
	m_cancelButton = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxPoint(120,60), wxDefaultSize, 0 );
}

//Destructeur
LuminositeDialog::~LuminositeDialog(){
    //Déconnexion
    m_luminosite->Unbind(wxEVT_SCROLL_THUMBTRACK, &LuminositeDialog::OnScroll, this) ;
}

void LuminositeDialog::OnScroll(wxScrollEvent &event){

    wxCommandEvent outEvent(MON_EVENEMENT1) ;	// création d'un événement propre
    outEvent.SetInt(m_luminosite->GetValue()) ;	// stockage de la valeur du luminosité dans l'événement
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel


}
