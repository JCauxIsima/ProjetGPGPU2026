#include "CImg.h"
#include <iostream>
using namespace cimg_library;
using namespace std;

CImg<> genCosValues(int N=8)
{
  CImg<> cosinusvalues(N,N);
  cimg_forXY(cosinusvalues,i,x)
    cosinusvalues(x,i) = std::cos(((2*x+1)*i*cimg::PI)/(2*N));
  return cosinusvalues;
}

/*
  JPEG_DCT: Calcul de la transformée en cosisnus discrète (DCT)

  block     : Image d'entrée
  cosvalues : Précalcul des valeurs du cosinus pour la DCT
  return    : DCT de l'image d'entrée
*/
CImg<> JPEG_DCT(CImg<>& block, CImg<>& cosvalues)
{
  unsigned int N = block.width(); // Taille du bloc

  CImg<> dct(N,N,1,1,0);
  cimg_forXY(dct,i,j)
  {
    float
      ci = i==0 ? 1/sqrt(2.0f) : 1,
      cj = j==0 ? 1/sqrt(2.0f) : 1;

    cimg_forXY(block,x,y)
      dct(i,j) += block(x, y)*cosvalues(x,i)*cosvalues(y,j);

    dct(i,j) *= 2.0f/N*ci*cj;
  }
  return dct;
}

int main(int argc,char **argv)
{
  CImg<> img("kingfischer.bmp");
  img.channel(0);
  img.resize(-25,-25);
  img-=128;

  int N = img.width();

  // Précalcul des cosinus
  CImg<> cos_values =  genCosValues(N);

  // Calcul de la DCT sur toute l'image
  CImg<> img_dct = JPEG_DCT(img,cos_values);

  
  CImgDisplay disp(img,"Image originale");
  CImgDisplay disp_dct(img_dct,"DCT de l'image");
  while(!disp.is_closed()) disp.wait();
  return 0;
}