#include "MyImage.hpp"


MyImage::MyImage(const wxString& fileName)
: wxImage(fileName)
{
}

MyImage::MyImage(wxImage image)
: wxImage(image)
{
}

MyImage::MyImage()
: wxImage()
{
}

void MyImage::Negative(){

    unsigned char* buffer = this->GetData();

    for (int i=0; i<this->GetHeight()*this->GetWidth()*3; i++){
        buffer[i] = 255-buffer[i];
    }


    /*for (int i=0; i<this->GetHeight()*this->GetWidth()*3; i++){
            *buffer = 255-(*buffer);
            buffer++;
    }*/

    //this->SetData(buffer);

}

void MyImage::Desaturate(){
    //L = 0.2126 R + 0.7152 V + 0.0722 B
    unsigned char* buffer = this->GetData();
    for (int i=0; i<this->GetHeight()*this->GetWidth(); i++){
        int l = 0.2126*buffer[3*i] + 0.7152*buffer[3*i+1] + 0.0722*buffer[3*i+2];
        for (int j=0; j<3; j++){
            buffer[3*i+j] = l;
        }
    }

}

void MyImage::Threshold(int seuil){
    this->Desaturate();
    unsigned char* buffer = this->GetData();
    for (int i=0; i<this->GetHeight()*this->GetWidth(); i++){
        int l;
        if (buffer[i*3]<seuil){
            l = 0;
        }
        else {
            l = 255;
        }
        for (int j=0; j<3; j++){
            buffer[3*i+j] = l;
        }
    }
}

void MyImage::Mirror(bool horizontally){
    unsigned char* buffer = GetData();
    if (horizontally){
        //on parcours la hauteur
        for(int i=0; i<GetHeight(); i++){
            //on parcours la moitié de la largeur
            for(int j=0; j<GetWidth()/2; j++){
                //on parcours un pixel
                for(int k=0; k<3; k++){
                    int temp = buffer[3*i*GetWidth()+3*j+k];
                    buffer[3*i*GetWidth()+3*j+k] = buffer[3*(i+1)*GetWidth()-(3*j+(3-k))] ;
                    buffer[3*(i+1)*GetWidth()-(3*j+(3-k))] = temp;
                }
            }
        }
    }
    else{
        //on parcours la moitié de la hauteur
        for(int i=0; i<GetHeight()/2; i++){
            //on parcours la largeur
            for(int j=0; j<GetWidth(); j++){
                //on parcours un pixel
                for(int k=0; k<3; k++){
                    int temp = buffer[3*i*GetWidth()+3*j+k];
                    buffer[3*i*GetWidth()+3*j+k] = buffer[(GetHeight()*GetWidth()*3+3) - (3*i*GetWidth()+3*j+(3-k))];
                    buffer[(GetHeight()*GetWidth()*3+3) - (3*i*GetWidth()+3*j+(3-k))] = temp;
                }
            }
        }
    }
}

wxImage MyImage::Rotate90(){
    unsigned char* bufferInImage = GetData();
    MyImage outImage ;
    outImage.Create(GetHeight(), GetWidth() , false);
    unsigned char* bufferOutImage = (unsigned char*) malloc(GetHeight()*GetWidth()*3);

    for(int i=0; i<GetWidth(); i++){
        for(int j=0; j<GetHeight(); j++){
            for (int k=0; k<3; k++){
                bufferOutImage[3*(i*GetHeight())+3*(GetHeight()-j)+k] = bufferInImage[3*j*GetWidth()+3*i+k];
            }
        }
    }
    outImage.SetData(bufferOutImage);
    return outImage;
}

void MyImage::Posterize(){
    unsigned char* buffer = GetData();
    //on parcours la hauteur
    for(int i=0; i<GetHeight(); i++){
        //on parcours la largeur
        for(int j=0; j<GetWidth(); j++){
            //on parcours un pixel
            for(int k=0; k<3; k++){
                if (buffer[3*i*GetWidth()+3*j+k]<128){
                    buffer[3*i*GetWidth()+3*j+k] = 0;
                }
                else buffer[3*i*GetWidth()+3*j+k] = 255;
            }
        }
    }
}

int MyImage::NombreCouleurs(){
    unsigned char* buffer = GetData();
    int n = pow(2,24);
    unsigned char* couleurs = (unsigned char*) malloc(n);
    for(int i=0; i<n; i++){
        couleurs[i] = 0;
    }
    int m = GetHeight()*GetWidth()*3;
    for(int i=0; i<m; i+=3){
        couleurs[(buffer[i] << 16) + (buffer[i+1] << 8) + buffer[i+2]] = 1;
    }
    int cpt = 0;
    for (int j=0; j<n; j++){
        if (couleurs[j]==1){
            cpt++;
        }
    }
    return cpt;
}

void MyImage::EnhenceContrast(int minValue, int maxValue){
    float d = (255 * minValue) / (float)(minValue - maxValue);
    float f = 255 / (float)(maxValue - minValue);
    unsigned char* buffer = GetData();
    int n = GetHeight()*GetWidth()*3;
    for(int i=0; i<n; i++){
        buffer[i] = f*buffer[i]+d;
    }
}
