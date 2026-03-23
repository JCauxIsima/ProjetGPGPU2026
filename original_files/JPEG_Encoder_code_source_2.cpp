/*

  JPEGEncoder: Calcul de l'image transformée par DCT + Quantification

  image     : Image d'entrée
  quality   : Facteur de qualité ( faible = meilleure qualité )
  cosvalues : Précalcul des valeurs du cosinus pour la DCT
  return    : Image des DCT quantifiées

*/
CImg<> JPEGEncoder(CImg<>& image, float quality, CImg<>& cosvalues)
{
  unsigned int N = 8; // Résolution d'un bloc

  // Matrice de quantification JPEG.
  int dataQ[] = { 16,11,10,16,24,40,51,61,
                  12,12,14,19,26,58,60,55,
                  14,13,16,24,40,57,69,56,
                  14,17,22,29,51,87,80,62,
                  18,22,37,56,68,109,103,77,
                  24,35,55,64,81,104,113,92,
                  49,64,78,87,103,121,120,101,
                  72,92,95,98,112,100,103,99 };
  CImg<>
    Q = CImg<>(dataQ,N,N)*quality,
    comp(image.width(),image.height(),1,1,0),
    block(N,N), dct(N,N);

  for (int k = 0; k<image.width()/N; ++k)
    for (int l = 0; l<image.height()/N; ++l)
    {
      block = image.get_crop(k*N,l*N,(k + 1)*N-1,(l + 1)*N - 1);
      block -= 128;

      dct = JPEG_DCT(block,cosvalues);
      cimg_forXY(dct,i,j)
        comp(k*N + i,l*N + j) = cimg::round(dct(i,j)/Q(i,j));
    }

  return comp;
}
