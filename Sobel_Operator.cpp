void sobel_opr(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	int gx[3][3] = { -1 , -2 , -1 , 0 , 0 , 0 , 1 , 2 , 1 };
	int gy[3][3] = { -1 , 0 , 1 , -2 , 0 , 2 , -1 , 0 , 1 };
	long length , width , i , j , x , y ; 
	int x_grad = 0 , y_grad = 0 , f = 3 , temp = 0;
	unsigned char **new_image;
	length = (ImageLength + (f - 1));
	width = (ImageWidthByte + ( f - 1));
	new_image = (unsigned char **)malloc( length * sizeof( unsigned char *));
	for( i = 0 ; i < length ; i++ )
	{
		*(new_image + i) = (unsigned char *)malloc(  width * sizeof(unsigned char ));
	}
	for ( i = -( f / 2 ) ; i < (long)ImageLength + f / 2 ; i++ )
	{
		for ( j = -(f / 2) ; j < (long)ImageWidthByte + f / 2 ; j++ )
		{
					  if( i < 0 )
						x = 0;
					  else if( i > ImageLength-1 )
						x = ImageLength-1;
					  else 
						  x = i ;
					  if( j < 0 )
						y = 0;
					  else if ( j > ImageWidthByte-1 )
						y = ImageWidthByte-1;
					  else 
						  y  = j;
					  new_image[i+f/2][j+f/2] = fxy[x][y];
					  //printf("%d",new_image[i+f/2][j+f/2]);
		}
	}
	for( i = (f/2) ; i <= length - (1 + f / 2) ; i++ )
	{
		for( j = (f/2) ; j <= width - (1 + f / 2) ; j++ )
		{
			x = 0 , x_grad = 0 , y_grad = 0;
			for( int a = (i-f/2) ; a <= (i+f/2) ; a++ , x++ )
			{
				y = 0;
				for( int b = (j-f/2) ; b <= (j+f/2) ; b++ , y++)
				{
					x_grad += new_image[a][b] * gx[x][y];
					y_grad += new_image[a][b] * gy[x][y];
				}
			}
			temp  = (abs(x_grad) + abs(y_grad));
			if( temp > 255 )
				fxyout[i-f/2][j-f/2] = 255 ;
			else
				fxyout[i-f/2][j-f/2] = temp;
		}
	}
}
