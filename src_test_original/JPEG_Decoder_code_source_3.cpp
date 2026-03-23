/*
  JPEGDecoder: Calcul de l'image reconstruite à partir des DCT

  img_dct   : DCT quantifiées <=> données d'entrée
  quality   : Facteur de qualité ( faible = meilleure qaulité )
  cosvalues : Précalcul des valeurs du cosinus pour la DCT
  return    : Image reconstruite
*/
CImg<> JPEGDecoder(CImg<>& img_dct, float quality, CImg<>& cosvalues)
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
    decomp(img_dct.width(),img_dct.height(),1,1,0),
    dct(N,N), blk(N,N);

  for (int k = 0; k<img_dct.width()/N; ++k)
    for (int l = 0; l<img_dct.height()/N; ++l)
    {
      dct = img_dct.get_crop(k*N,l*N,(k + 1)*N - 1,(l + 1)*N - 1);
      dct.mul(Q);
      blk = JPEG_IDCT(dct,cosvalues) + 128;

      cimg_forXY(blk,i,j)
        decomp(k*N + i,l*N + j) = blk(i,j);
    }
  return decomp;
}
