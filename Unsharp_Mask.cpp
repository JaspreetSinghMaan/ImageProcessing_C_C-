void unsharp_mask( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{

	// image smoothing using unweighted filter at reply 6
	int x , y , masksum = 0 , i_pixel = 0  ;
	unsigned long temp = 0;
	//unsigned char **new_image;
	int **mask ,f , filter1[5][5] , sum =0;
	float filter[5][5];
	mask = (int **)malloc( ImageLength * sizeof( int *));
	for( int i = 0 ; i < ImageLength ; i++ )
	{
		*(mask + i) = (int *)malloc(  ImageWidthByte * sizeof(int ));
	}
	/*new_image = (unsigned char **)malloc( ImageLength * sizeof( unsigned char *));
	for( int i = 0 ; i < ImageLength ; i++ )
	{
		*(new_image + i) = (unsigned char *)malloc(  ImageWidthByte * sizeof(unsigned char ));
	}*/
	gaussinan_filter(  ImageLength , ImageWidthByte , fxyout , fxy );
	for(int i = 0  ; i < ImageLength ; i++ )
	{
		for(int j = 0 ; j < ImageWidthByte ; j++ )
		{
			mask[i][j] = fxy[i][j] - fxyout[i][j];
		}
	}
	for(int i = 0  ; i < ImageLength ; i++ )
	{
		for(int j = 0 ; j < ImageWidthByte ; j++ )
		{
			i_pixel = fxy[i][j] + mask[i][j];
			if( i_pixel > 255 )
				i_pixel = 255;
			else if ( i_pixel < 0 )
				i_pixel = 0 ;
			fxyout[i][j] = i_pixel;
		}
	}
}
