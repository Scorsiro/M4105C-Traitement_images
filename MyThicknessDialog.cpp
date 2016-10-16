#include "MyThicknessDialog.hpp"


MyThicknessDialog::MyThicknessDialog(
	wxWindow* parent, wxColour color, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style)
: wxDialog( parent, id, title, pos, size, style ), m_color(color)
{
    Bind(wxEVT_PAINT, &MyThicknessDialog::OnPaint, this) ;
	m_thickness = new wxSlider( this, wxID_ANY, 128, 0, 40, wxPoint(20,10), wxSize(100,50),wxEVT_SCROLLBAR);
	m_thickness->Bind(wxEVT_SCROLL_THUMBTRACK,&MyThicknessDialog::OnScroll,this);
	m_thickness->Bind(wxEVT_SCROLL_TOP,&MyThicknessDialog::OnScroll,this);
	m_thickness->Bind(wxEVT_SCROLL_BOTTOM,&MyThicknessDialog::OnScroll,this);
	m_thickness->Bind(wxEVT_SCROLL_LINEUP,&MyThicknessDialog::OnScroll,this);
	m_thickness->Bind(wxEVT_SCROLL_LINEDOWN,&MyThicknessDialog::OnScroll,this);
	m_thickness->Bind(wxEVT_SCROLL_PAGEUP,&MyThicknessDialog::OnScroll,this);
	m_thickness->Bind(wxEVT_SCROLL_PAGEDOWN,&MyThicknessDialog::OnScroll,this);
	m_thickness->Bind(wxEVT_SCROLL_THUMBRELEASE,&MyThicknessDialog::OnScroll,this);
	m_thickness->Bind(wxEVT_SCROLL_CHANGED,&MyThicknessDialog::OnScroll,this);
	//m_iplImage = cvCreateImage(cvSize(50, 50),8,3);
    m_image = new wxImage(100,75);
    m_bitmap = wxBitmap(*m_image);

    m_iplImage = cvCreateImage(cvSize(100, 80),8,3);
    cvSet(m_iplImage, cvScalar(255,255,255));
    cvLine(m_iplImage, cvPoint(10, 40), cvPoint(90,40), CV_RGB(m_color.Red(),m_color.Green(),m_color.Blue()), m_thickness->GetValue(),8);
    unsigned char* outBuffer = (unsigned char *) malloc(100*80*3);
    IplImageToBuffer(m_iplImage, outBuffer);
    cvReleaseImage(&m_iplImage);
    m_image->SetData(outBuffer);
    Refresh();

	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(20,100), wxDefaultSize, 0 );
	m_cancelButton = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxPoint(120,100), wxDefaultSize, 0 );
}

//Destructeur
MyThicknessDialog::~MyThicknessDialog(){
    //Déconnexion
    //m_thickness->Unbind(wxEVT_SCROLL_THUMBTRACK, &MyThicknessDialog::OnScroll, this) ;
    free(m_image->GetData());
    delete(&m_bitmap);
}

void MyThicknessDialog::OnPaint(wxPaintEvent &WXUNUSED(event)){
    wxPaintDC dc(this);
    if (this->m_image!=nullptr) {
            //wxLogMessage(wxT("Salut !"));
            this->m_bitmap = wxBitmap(*this->m_image);
            dc.DrawBitmap(this->m_bitmap,130,10);
    }
};

void MyThicknessDialog::OnScroll(wxScrollEvent &event){
    //wxLogMessage(wxT("Salut !"));
    //unsigned char* buffer = m_image->GetData();
    m_iplImage = cvCreateImage(cvSize(100, 80),8,3);
    cvSet(m_iplImage, cvScalar(255,255,255));
    //BufferToIplImage(buffer, m_iplImage);
    cvLine(m_iplImage, cvPoint(10, 40), cvPoint(90,40), CV_RGB(m_color.Red(),m_color.Green(),m_color.Blue()), m_thickness->GetValue(),8);
    unsigned char* outBuffer;
    outBuffer = (unsigned char *) malloc(100*80*3);
    IplImageToBuffer(m_iplImage, outBuffer);
    cvReleaseImage(&m_iplImage);
    m_image->SetData(outBuffer);
    Refresh();
}
