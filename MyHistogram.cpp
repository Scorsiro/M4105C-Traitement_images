#include "MyHistogram.hpp"
//#include "MyImage.hpp"

MyHistogram::MyHistogram(MyImage* image){
    this->tableau = (unsigned char*) malloc(256);
    for(int i=0; i<256; i++){
        tableau[i] = 0;
    }
    unsigned char* buffer = image->GetData();
    int n = image->GetHeight()*image->GetWidth()*3;
    for(int i=0; i<n; i+=3){
        if (buffer[i]==buffer[i+1] && buffer[i+1]==buffer[i+2]) {
            tableau[buffer[i]]++;
        }
    }
}

void MyHistogram::GetBorderValues(int *minValue, int *maxValue){
    *minValue = 0;
    *maxValue = 255;
    while (tableau[*minValue]==0 && *minValue<255){
        (*minValue)++;
    }
    while(tableau[*maxValue]==0 && maxValue>0){
        (*maxValue)--;
    }
}
