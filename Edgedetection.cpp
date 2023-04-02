void edgedetection( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	// image smoothing using unweighted filter at reply 6
	int x , y , masksum = 0;
	unsigned long temp = 0;
	printf("Enter a 3 * 3 filter\n");
	int w1[3][3] = {-1,-1,-1,2,2,2,-1,-1,-1};
	int w2[3][3] = {2,-1,-1,-1,2,-1,-1,-1,2};
	int w3[3][3] = {-1,2,-1,-1,2,-1,-1,2,-1};
	int w4[3][3] = {-1,-1,2,-1,2,-1,2,-1,-1};
	// to calculate the new image g(x,y)
	for ( int i = 0 ; i < ImageLength ; i++ )
	{
		for ( int j = 0 ; j < ImageWidthByte ; j++ )
		{
			temp = 0;
			for ( int a = -1 ; a <= 1; a++ )
			{
				 for ( int b = -1 ; b <= 1 ; b++ )
				 {
					  x = i+a;
					  y = j+b;
					  if( x < 0 )
						x = 0;
					  if( x > ImageLength-1 )
						x = ImageLength-1;
					  if( y < 0 )
						y = 0;
					  if( y > ImageWidthByte-1 )
						y = ImageWidthByte-1;
					  temp += w1[a+1][b+1] * fxy[x][y];
				}
			}
			if( temp > 255 )
				temp = 255;
			else if( temp < 0 )
				temp = 0;
			fxyout[i][j] = temp;
		}
	 }
}
