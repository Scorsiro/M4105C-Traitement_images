// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "MyImage.hpp"
#include <time.h>
#include "MyThresholdDialog.hpp"
#include "MyThicknessDialog.hpp"
#include "MyRotateDialog.hpp"
#include "MyHistogram.hpp"
#include "wx/colordlg.h"

wxDEFINE_EVENT(MON_EVENEMENT, wxCommandEvent);

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};


class MyPanel: public wxPanel
{
public:
    MyPanel( wxWindow *parent ) ;
    ~MyPanel() ;
    void OpenImage(wxString fileName);
    void OnPaint(wxPaintEvent &WXUNUSED(event));
    void MirrorImage(bool horizontal);
    void BlurImage();
    void RotationImage(int id);
    void NegativeImage();
    void ThresholdImage();
    void OnThresholdImage(wxCommandEvent & event) ;
    void RotateImage();
    MyImage* getImagePtr();
    void setColor(wxColour color);
    wxColour getColor();
    int getThickness();
    void setThickness(int thickness);
    void ThicknessDraw();
    void OnClick(wxMouseEvent &event);
    void InitDraw();
    void startDraw(wxMouseEvent &event);
    void stopDraw(wxMouseEvent &event);
    void Previous();
    void Next();
    void RedrawImage();
    void ChooseColor();
    void updateImageCopy();
    //wxDECLARE_EVENT_TABLE();
private:
    MyImage *m_image ;		// used to load and process the image
    MyImage *m_image_copy;
    wxBitmap m_bitmap ;	// used to display the image
    int m_width;
    int m_height;
    wxColour color;
    int thickness;
};

/*wxBEGIN_EVENT_TABLE(MyPanel, wxPanel)
EVT_LEFT_DOWN(MyPanel::startDraw)
EVT_LEFT_UP(MyPanel::stopDraw)
wxEND_EVENT_TABLE()*/


class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    MyPanel *m_panel; // the panel inside the main frame
    void OnProcessImage(wxCommandEvent& event);
	void OnHello(wxCommandEvent& event);
	void OnOpenImage(wxCommandEvent& event);
	void OnSaveImage(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnEnCours(wxCommandEvent& event);
	void OnLarge(wxCommandEvent& event);
	void OnDraw(wxCommandEvent& event);
};



enum
{
	ID_Hello = 1,
	ID_About = 2,
	ID_EnCours = 3,
	ID_PlusLarge = 4,
	ID_MoinsLarge = 5,
	ID_Open = 6,
	ID_Save = 7,
	ID_MiroirHorizontal = 8,
	ID_MiroirVertical = 9,
	ID_Blur = 10,
	ID_RotationPlus90 = 11,
	ID_RotationMoins90 = 12,
	ID_Rotation180 = 13,
	ID_Negative = 14,
	ID_Desaturate = 15,
	ID_Threshold = 16,
	ID_Posterize = 17,
	ID_Rotation = 18,
	ID_NombreCouleurs = 19,
	ID_Contrast = 20,
	ID_Dither = 21,
	ID_Color = 22,
	ID_Thinner = 23,
	ID_Thicker= 24,
	ID_ThresholdScroll = 25,
	ID_Previous = 26,
	ID_Next = 27,
	ID_ThicknessSroll = 28
};



IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
	MyFrame *frame = new MyFrame( wxT("munier_adli_sajkiewicz"), wxPoint(50, 50), wxSize(450, 340) );
	frame->Show( true );
	return true;
}


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    this->m_panel = new MyPanel(this);
    wxFrame::Centre(wxBOTH);
    wxStatusBar *statusBar = CreateStatusBar(1,wxSTB_DEFAULT_STYLE,0,"SatusBar");
    SetStatusText(wxT("La barre de status fonctionne très simplement !!!"));


	wxMenu *menuFile = new wxMenu ;
	wxMenu *menuProcess = new wxMenu;
	wxMenu *menuHelp = new wxMenu ;
	wxMenu *menuDraw = new wxMenu;


	menuFile->Append(ID_Hello, wxT("Hello...\tCtrl-H")) ;
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello) ;

	menuFile->Append(ID_Open, wxT("Open")) ;
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, ID_Open) ;

	menuFile->Append(ID_Save, wxT("Save")) ;
	Bind(wxEVT_MENU, &MyFrame::OnSaveImage, this, ID_Save) ;

	menuFile->Append(ID_PlusLarge, wxT("Plus Large\tCtrl-+"));
	Bind(wxEVT_MENU, &MyFrame::OnLarge, this, ID_PlusLarge);

	menuFile->Append(ID_MoinsLarge, wxT("Moins Large\tCtrl--"));
	Bind(wxEVT_MENU, &MyFrame::OnLarge, this, ID_MoinsLarge);

	menuFile->Append(ID_About, wxT("About"));
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, ID_About);

	menuFile->Append(wxID_EXIT) ;
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;


	menuProcess->Append(ID_MiroirHorizontal,wxT("Horizontal Mirror"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MiroirHorizontal);

	menuProcess->Append(ID_MiroirVertical,wxT("Vertical Mirror"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MiroirVertical);

	menuProcess->Append(ID_Blur,wxT("Blur"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Blur);

	menuProcess->Append(ID_RotationPlus90,wxT("Rotation +90"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_RotationPlus90);

	menuProcess->Append(ID_RotationMoins90,wxT("Rotation -90"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_RotationMoins90);

	menuProcess->Append(ID_Rotation180,wxT("Rotation 180"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Rotation180);

	menuProcess->Append(ID_Negative,wxT("Negative"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Negative);

	menuProcess->Append(ID_Desaturate,wxT("Desaturate"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Desaturate);

	menuProcess->Append(ID_Threshold,wxT("Threshold"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Threshold);

	menuProcess->Append(ID_Posterize,wxT("Posterize"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Posterize);

	menuProcess->Append(ID_Rotation,wxT("Rotation"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Rotation);

	menuProcess->Append(ID_NombreCouleurs,wxT("Colors Number"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_NombreCouleurs);

	menuProcess->Append(ID_Contrast,wxT("Contrast"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Contrast);

	menuProcess->Append(ID_Dither,wxT("Dither...\tCtrl-D")); // raccourci ctrl -D pour dithering
    Bind(wxEVT_MENU, &MyFrame::OnProcessImage,this,ID_Dither);


	menuHelp->Append(ID_EnCours, wxT("En Cours"));
	Bind(wxEVT_MENU, &MyFrame::OnEnCours, this, ID_EnCours);


	/*wxMenu* menuColor = new wxMenu;

    menuColor->AppendRadioItem(ID_Red, wxT("Red"));
    Bind(wxEVT_MENU, &MyFrame::OnDraw, this, ID_Red);

    menuColor->AppendRadioItem(ID_Green, wxT("Green"));
    Bind(wxEVT_MENU, &MyFrame::OnDraw, this, ID_Green);

    menuColor->AppendRadioItem(ID_Blue, wxT("Blue"));
    Bind(wxEVT_MENU, &MyFrame::OnDraw, this, ID_Blue);

    menuDraw->AppendSubMenu(menuColor, wxT("Color"));*/

    menuDraw->Append(ID_Color,wxT("Choose Color"));
    Bind(wxEVT_MENU, &MyFrame::OnDraw, this, ID_Color);


    wxMenu* menuThickness = new wxMenu;

    menuThickness->Append(ID_Thinner, "Thinner");
    Bind(wxEVT_MENU, &MyFrame::OnDraw, this, ID_Thinner);
    menuThickness->Append(ID_Thicker, "Thicker");
    Bind(wxEVT_MENU, &MyFrame::OnDraw, this, ID_Thicker);
    menuThickness->Append(ID_ThicknessSroll, "Set Thickness");
    Bind(wxEVT_MENU, &MyFrame::OnDraw, this, ID_ThicknessSroll);

    menuDraw->AppendSubMenu(menuThickness, wxT("Thickness"));

    menuDraw->Append(ID_Previous, wxT("Previous"));
    Bind(wxEVT_MENU, &MyFrame::OnDraw, this, ID_Previous);
    menuDraw->Append(ID_Next, wxT("Next"));
    Bind(wxEVT_MENU, &MyFrame::OnDraw, this, ID_Next);

	//Bind(wxEVT_LEFT_UP, &MyPanel::OnClick(wxMouseEvent event), this, ID_Draw);
	//(MyPanel::OnClick)



	wxMenuBar *menuBar = new wxMenuBar ;
	menuBar->Append( menuFile, wxT("File" )) ;
	menuBar->Append( menuHelp, wxT("Help" )) ;
	menuBar->Append(menuProcess, wxT("Process"));
	menuBar->Append(menuDraw, wxT("Draw"));
	SetMenuBar(menuBar) ;
	SetStatusBar(statusBar);
}


void MyFrame::OnProcessImage(wxCommandEvent& event){
    switch (event.GetId()){
    case ID_MiroirHorizontal:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->MirrorImage(true);
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_MiroirVertical:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->MirrorImage(false);
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Blur:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->BlurImage();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_RotationPlus90:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->RotationImage(event.GetId());
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_RotationMoins90:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->RotationImage(event.GetId());
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Rotation180:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->RotationImage(event.GetId());
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Negative:
        if (this->m_panel->getImagePtr()!=nullptr){
            clock_t debut = clock();
            this->m_panel->NegativeImage();
            clock_t fin = clock();
            double total = ((double)(fin-debut))/((double)CLOCKS_PER_SEC);
            this->SetStatusText(wxT("Temps d'éxecution : ")+wxString::Format(wxT("%lf"),total)+wxT(" secondes"));

        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Desaturate:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->getImagePtr()->Desaturate();
            Refresh();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Threshold:
        if (this->m_panel->getImagePtr()!=nullptr){
            wxImage imageCopy = this->m_panel->getImagePtr()->Copy() ;
            this->m_panel->ThresholdImage();
            *(this->m_panel->getImagePtr()) = imageCopy.Copy();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Posterize:
        if (this->m_panel->getImagePtr()!=nullptr){
            m_panel->getImagePtr()->Posterize();
            Refresh();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Rotation:
        if (this->m_panel->getImagePtr()!=nullptr){
            this->m_panel->RotateImage();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_NombreCouleurs:
        if (this->m_panel->getImagePtr()!=nullptr){
            wxString message;
            message.sprintf("%i couleurs", m_panel->getImagePtr()->NombreCouleurs());
            wxLogMessage(message);
            //wxString::Format(wxT("%lf"),total)
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Contrast:
        if (this->m_panel->getImagePtr()!=nullptr){
                MyHistogram* histo = new MyHistogram(m_panel->getImagePtr());
                int min, max;
                histo->GetBorderValues(&min,&max);
                m_panel->getImagePtr()->EnhenceContrast(min,max);
                Refresh();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    case ID_Dither :
        if ( this->m_panel->getImagePtr() != nullptr) {
             this->m_panel->getImagePtr()->Dither() ;
             Refresh();
        }
        else wxLogMessage(wxT("Aucune image chargée"));
        break;
    default:
        break;
    }
    m_panel->updateImageCopy();
}

void MyFrame::OnDraw(wxCommandEvent& event){
        switch (event.GetId()){
        case ID_Color:
            m_panel->ChooseColor();
            break;
        case ID_Thinner:
            m_panel->setThickness(m_panel->getThickness()-1);
            break;
        case ID_Thicker:
            m_panel->setThickness(m_panel->getThickness()+1);
            break;
        case ID_ThicknessSroll:
            m_panel->ThicknessDraw();
            break;
        case ID_Previous:
            if (this->m_panel->getImagePtr()!=nullptr){
                m_panel->Previous();
                Refresh();
            }
            else wxLogMessage(wxT("Aucune image chargée"));
            break;
        case ID_Next:
            if (this->m_panel->getImagePtr()!=nullptr){
                m_panel->Next();
                Refresh();
            }
            else wxLogMessage(wxT("Aucune image chargée"));
            break;
        default:
            break;
        }
}

void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage(wxT("Hello world from wxWidgets!"));
}

void MyFrame::OnOpenImage(wxCommandEvent& event)
{
    wxString filename = wxFileSelector("Choose a file to open");
    if (!filename.empty()){
        this->m_panel->OpenImage(filename);
    }
}

void MyFrame::OnSaveImage(wxCommandEvent& event)
{
    wxString filename = wxSaveFileSelector("", "PNG Image|*.png|BMP Image|*.bmp|JPEG Image|*.jpg", "image");
        if(filename!=wxEmptyString)

        {

                this->m_panel->getImagePtr()->SaveFile(filename);
        }
}


void MyFrame::OnLarge(wxCommandEvent& event)
{
    int width;
    int height;
    this->GetSize(&width,&height);
	if (event.GetId()==4){
        this->SetSize((width+100),height);
	}
	else this->SetSize((width-100),height);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxLogMessage(wxT("Auteur : Tom Munier - 2016"));
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}

void MyFrame::OnEnCours(wxCommandEvent& event)
{
	wxLogMessage(wxT("En Construction"));
}



MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent){
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this) ;
    Bind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this) ;

    this->m_image = nullptr;
    this->m_image_copy = nullptr;
    this->color = *wxBLACK;
    this->thickness = 1;
};

MyPanel::~MyPanel(){
    delete(this->m_image);
    delete(this->m_image_copy);
};

MyImage* MyPanel::getImagePtr(){
    return this->m_image;
}

void MyPanel::setColor(wxColour color){
    this->color = color;
}

wxColour MyPanel::getColor(){
    return color;
}

int MyPanel::getThickness(){
    return thickness;
}

void MyPanel::setThickness(int thickness){
    this->thickness = thickness;
}

void MyPanel::ThicknessDraw(){
    MyThicknessDialog *dlg = new MyThicknessDialog(this, color, -1, wxT("Thickness"), wxDefaultPosition, wxSize(250,180));
    if (dlg->ShowModal() == wxID_OK) {
        setThickness(dlg->m_thickness->GetValue());
    }
}

void MyPanel::OpenImage(wxString fileName){
    //if (this->getImagePtr()!=nullptr){
        //this->m_image->Destroy();

    //}
    delete(this->m_image);
    //this->m_image = nullptr;
    delete(this->m_image_copy);
    //m_image_copy = nullptr;

    this->m_image = new MyImage(fileName);
    this->m_image_copy = new MyImage(fileName);
    this->m_width = m_image->GetWidth();
    this->m_height = m_image->GetHeight();
    this->SetSize(this->m_width,this->m_height);
    this->GetParent()->SetClientSize(this->m_width,this->m_height);
    Refresh();
};

void MyPanel::OnPaint(wxPaintEvent &WXUNUSED(event)){
    wxPaintDC dc(this);
    if (this->m_image!=nullptr) {
            this->m_bitmap = wxBitmap(*this->m_image);
            dc.DrawBitmap(this->m_bitmap,0,0);
    }
};

void MyPanel::MirrorImage(bool horizontal){
    this->m_image->Mirror(horizontal);
    Refresh();
}

void MyPanel::BlurImage(){
    *this->m_image = this->m_image->Blur(5);
    Refresh();
}

void MyPanel::RotationImage(int id){
    if (id==ID_RotationPlus90){
        *this->m_image = this->m_image->wxImage::Rotate90(true);
        //this->m_image = this->m_image->Rotate90();
        this->m_width = m_image->GetWidth();
        this->m_height = m_image->GetHeight();
        this->SetSize(this->m_width,this->m_height);
        this->GetParent()->SetClientSize(this->m_width,this->m_height);
    }
    else if (id==ID_RotationMoins90){
        *this->m_image = this->m_image->wxImage::Rotate90(false);
        this->m_width = m_image->GetWidth();
        this->m_height = m_image->GetHeight();
        this->SetSize(this->m_width,this->m_height);
        this->GetParent()->SetClientSize(this->m_width,this->m_height);
    }
    else *getImagePtr() = getImagePtr()->Rotate180();
    Refresh();
}

void MyPanel::NegativeImage(){
    this->m_image->Negative();
    Refresh();
}

/*void MyPanel::ThresholdImage(){
    MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
    dlg->ShowModal() ;
    this->m_image->Threshold(dlg->m_threshold->GetValue());
    Refresh();
}
*/

//Version de ThresholdImage du TP7

void MyPanel::ThresholdImage(){
    //Sauvegarder l'image courante
    wxImage imageCopy = this->getImagePtr()->Copy() ;
    MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
    int reponse = dlg->ShowModal();

    if(reponse == wxID_CANCEL){
        // rétablir l'image originale grace à la sauvegarde
        *(this->getImagePtr()) = imageCopy.Copy();
        Refresh();
    }




}

void MyPanel::OnThresholdImage(wxCommandEvent& event){
    int val = event.GetInt();

    if(this->getImagePtr() != nullptr){

        this->getImagePtr()->Threshold(val);
        Refresh();
    } else {

        wxLogMessage("image non chargée") ;

    }


}



void MyPanel::RotateImage(){
    MyRotateDialog *dlg = new MyRotateDialog(this, -1, wxDefaultPosition, wxSize(250,140));
    if (dlg->ShowModal() == wxID_OK){
        switch(dlg->RadioBox1->GetSelection()){
        case 0:
            RotationImage(ID_RotationPlus90);
            break;
        case 1:
            RotationImage(ID_Rotation180);
            break;
        case 2:
            RotationImage(ID_RotationMoins90);
            break;
        default:
            break;
        }
    }
    else dlg->Destroy();
}

void MyPanel::OnClick(wxMouseEvent &event){
        this->getImagePtr()->Draw(event.GetPosition(), getColor(), thickness);
        Refresh();
}

void MyPanel::InitDraw(){
    Bind(wxEVT_LEFT_DOWN, &MyPanel::startDraw, this);
    Bind(wxEVT_LEFT_UP, &MyPanel::stopDraw, this);
    //updateImageCopy();
    //m_image_copy = this->getImagePtr()->copyImage();

}

void MyPanel::startDraw(wxMouseEvent &event){
    if (getImagePtr()!=nullptr){
        getImagePtr()->setOldPoint(event.GetPosition());
        unsigned int n = m_image_copy->m_draw_steps.size();
        if (n>0){
            //for(int i=m_image->drawStep; i<=n; i++){
            while (m_image_copy->drawStep!=m_image_copy->m_draw_steps.size()){
                m_image_copy->m_draw_steps.pop_back();
                m_image_copy->m_line_color.pop_back();
                m_image_copy->m_line_thickness.pop_back();
            }
        }
        Bind(wxEVT_MOTION, &MyPanel::OnClick, this);
    }
    else wxLogMessage(wxT("Aucune image chargée"));
}

void MyPanel::stopDraw(wxMouseEvent &event){
    Unbind(wxEVT_MOTION, &MyPanel::OnClick, this);
    m_image_copy->m_draw_steps.push_back(m_image->m_line);
    m_image->m_line.clear();
    m_image_copy->m_line_color.push_back(color);
    m_image_copy->m_line_thickness.push_back(thickness);
    m_image_copy->drawStep++;
}

void MyPanel::Previous(){
    if (m_image_copy->drawStep>0){
        m_image_copy->drawStep--;
        RedrawImage();
    }
}

void MyPanel::Next(){
    if (m_image_copy->drawStep < m_image_copy->m_draw_steps.size()){
        m_image_copy->drawStep++;
        RedrawImage();
    }
}

void MyPanel::RedrawImage(){
    //*this->getImagePtr() = *m_image_copy;
    this->m_image = m_image_copy->copyImage();
    for (unsigned int i=0; i<m_image->drawStep; i++){
        std::vector<wxPoint> line = m_image->m_draw_steps.at(i);
        wxColour line_color = m_image->m_line_color.at(i);
        int line_thickness = m_image->m_line_thickness.at(i);
        for (unsigned int j=1; j<line.size()-1; j++){
            m_image->Redraw(line.at(j-1), line.at(j), line_color, line_thickness);
        }
    }
}

void MyPanel::ChooseColor(){
    wxColourDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK)
    {
        wxColourData retData = dialog.GetColourData();
        wxColour col = retData.GetColour();
        setColor(col);
        InitDraw();
    }
}

void MyPanel::updateImageCopy(){
    m_image_copy = this->getImagePtr()->copyImage();
    if (!m_image_copy->m_line_color.empty()) m_image_copy->m_line_color.clear();
    if (!m_image_copy->m_line_thickness.empty()) m_image_copy->m_line_thickness.clear();
    if (!m_image_copy->m_draw_steps.empty()) m_image_copy->m_draw_steps.clear();
    if (!m_image_copy->m_line.empty()) m_image_copy->m_line.clear();
    m_image_copy->drawStep = 0;
}
