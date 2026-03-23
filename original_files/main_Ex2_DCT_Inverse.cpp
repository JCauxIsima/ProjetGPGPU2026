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
  JPEG_IDCT: Calcul de la transformée en cosinus discrète inverse (iDCT).

  dct       : DCT <=> données d'entrée
  cosvalues : Précalcul des valeurs du cosinus pour la DCT
  return    : Image de sortie
*/
CImg<> JPEG_IDCT(CImg<>& dct, CImg<>& cosvalues)
{
  unsigned int N = dct.width(); // Taille du bloc

  CImg<> img(N,N,1,1,0);
  cimg_forXY(img,x,y)
  {
    cimg_forXY(dct,i,j)
    {
      float
        ci = (i==0) ? 1/std::sqrt(2) : 1,
        cj = (j==0) ? 1/std::sqrt(2) : 1;
      img(x,y) += ci*cj*dct(i,j)*cosvalues(x,i)*cosvalues(y,j);
    }
    img(x,y) *= 2.0f/N;
  }
  return img;
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
  img -= 128;

  int N = img.width();

  // Précalcul des cosinus
  CImg<> cos_values =  genCosValues(N);

  // Calcul de la DCT sur toute l'image
  CImg<> img_dct = JPEG_DCT(img,cos_values);

  // Calcul de la iDCT sur toute l'image
  CImg<> img_idct = JPEG_IDCT(img_dct,cos_values);
 
  CImgDisplay disp(img,"Image originale");
  CImgDisplay disp_dct(img_dct,"DCT de l'image");
  CImgDisplay disp_idct(img_idct,"IDCT de DCT de l'image");
  while(!disp.is_closed()) disp.wait();
  return 0;
}