void AlocalNR_filter( unsigned long ImageLength, unsigned long ImageWidthByte, 
				unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )

{
			long i , j , x , y;
			int g_var = 1000;
			double l_var , l_mean;
			int temp_arr[25] = {0}, f = 7 , s , k;
			unsigned char **new_image;
			unsigned long length = (ImageLength + (f - 1));
			unsigned long width = (ImageWidthByte + ( f - 1));
			for ( i = 0 ; i < ImageLength ; i++ )
			{
			for ( j = 0 ; j < ImageWidthByte ; j++ )
			{
				k = 0 , l_mean = 0;
				//local mean at each pixel
				for ( int a = -(f / 2) ; a <= (f / 2); a++ )
				{
					 for ( int b = -(f /2 ) ; b <= (f / 2) ; b++ )
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
						  k += fxy[x][y];
					}
				}
				l_mean = k / (f*f);
				
				//local variance at each pixel
				l_var = 0;
				for ( int a = -(f / 2) ; a <= (f / 2); a++ )
				{
					 for ( int b = -(f /2 ) ; b <= (f / 2) ; b++ )
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
						  l_var += ( (fxy[x][y] - l_mean) * (fxy[x][y] - l_mean) );
					}
				}
				l_var = l_var / ( f*f );
				if( g_var > l_var )
					fxyout[i][j] = fxy[i][j] - (fxy[i][j] - l_mean);
				else
					fxyout[i][j] = fxy[i][j] - ( g_var / l_var )*(fxy[i][j] - l_mean);
			}
		}
}
