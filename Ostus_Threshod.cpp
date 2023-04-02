void ostus_threshod( unsigned long ImageLength, unsigned long ImageWidthByte, 
	unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{

  int hist[256];
  double prob[256], omega[256]; /* prob of graylevels */
  double myu[256];   /* mean value for separation */
  double max_sigma, sigma[256]; /* inter-class variance */
  int i, x, y; /* Loop variable */
  int threshold; /* threshold for binarization */
  
  printf("Otsu's binarization process starts now.\n");
  
  /* Histogram generation */
  for (i = 0; i < 256; i++) 
	  hist[i] = 0;
  for (y = 0; y < ImageWidth; y++)
    for (x = 0; x < ImageLength; x++) {
      hist[fxy[y][x]]++;
    }
  /* calculation of probability density */
  for ( i = 0; i < 256; i ++ ) {
    prob[i] = (double)hist[i] / (ImageLength * ImageWidth);
  }
  
  /* omega & myu generation */
  omega[0] = prob[0];
  myu[0] = 0.0;       /* 0.0 times prob[0] equals zero */
  for (i = 1; i < 256; i++) {
    omega[i] = omega[i-1] + prob[i];
    myu[i] = myu[i-1] + i*prob[i];
  }
  
  /* sigma maximization
     sigma stands for inter-class variance 
     and determines optimal threshold value */
  threshold = 0;
  max_sigma = 0.0;
  for (i = 0; i < 256-1; i++) {
    if (omega[i] != 0.0 && omega[i] != 1.0)
      sigma[i] = pow(myu[256-1]*omega[i] - myu[i], 2) / (omega[i]*(1.0 - omega[i]));
    else
      sigma[i] = 0.0;
    if (sigma[i] > max_sigma) {
      max_sigma = sigma[i];
      threshold = i;
    }
  }
  
  printf("\nthreshold value = %d\n", threshold);
  for ( i = 0 ; i < ImageLength ; i++ )
  {
	  for( int j = 0 ; j < ImageWidth ; j++ )
	  {
		  if( fxy[i][j] > threshold )
			  fxyout[i][j] = 255 ;
		  else
			  fxyout[i][j] = 0;
	  }
  }
}
