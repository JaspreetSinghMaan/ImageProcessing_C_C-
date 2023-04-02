void img_smoothing( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	// image smoothing using unweighted filter at reply 6
	int x , y , masksum = 0;
	unsigned long temp = 0;
	printf("Enter a 3 * 3 filter\n");
	int w[3][3] = {1,1,1,1,1,1,1,1,1};
	// to find the sum of the mask
	for ( int i = 0 ; i < 3 ; i++ )
	{
		for( int j = 0 ; j < 3 ; j++)
		{
			scanf("%d",&w[i][j]);
			masksum += w[i][j];
		}
	}
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
					  temp += w[a+1][b+1] * fxy[x][y];
				}
			}
			temp /= masksum;
			temp = floor( temp + 0.5 );
			fxyout[i][j] = ( unsigned char )temp;
		}
	 }
}