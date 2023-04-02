void robert_opr(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{	
	int gx[2][2] = { -1 , 0 , 0 , 1 };
	int gy[2][2] = { 0 , -1 , 1 , 0 };
	long length , width , i , j , x , y ; 
	int x_grad = 0 , y_grad = 0 , f = 3 , temp = 0;
	//unsigned char **new_image;
	length = (ImageLength + (f - 1));
	width = (ImageWidthByte + ( f - 1));
	// to copy the orignal image to extended image
//	copy_to_new( ImageLength , ImageWidthByte , fxy , length , width  , f );
	for( i = (f/2) ; i <= length - (1 + f / 2) ; i++ )
	{
		for( j = (f/2) ; j <= width - (1 + f / 2) ; j++ )
		{
			x = 0 , x_grad = 0 , y_grad = 0;
			for( int a = (i-f/2) ; a <= i ; a++ , x++ )
			{
				y = 0;
				for( int b = (j-f/2) ; b <= j ; b++ , y++)
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
