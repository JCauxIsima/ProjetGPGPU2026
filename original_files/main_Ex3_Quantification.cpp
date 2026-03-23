#include "CImg.h"
#include <iostream>
using namespace cimg_library;
using namespace std;
int main(int argc,char **argv)
{
  float empsilon = 0.001;
  CImg<unsigned char> img("butterfly_grey.bmp");
  img.channel(0);

  CImgList<> grad = img.get_gradient("xy",0);
  CImg<> img_norme = grad[0].get_mul(grad[0])+grad[1].get_mul(grad[1]);
  img_norme.sqrt();
  
  CImg<> img_phase = grad[1].atan2(grad[0]);

  CImgDisplay disp(img,"Butterfly");
  CImgDisplay disp_norme(img_norme,"Butterfly - norme du gradient");
  CImgDisplay disp_phase(img_phase,"Butterfly - phase du gradient");

  while(!disp.is_closed()) disp.wait();
  return 0;
}