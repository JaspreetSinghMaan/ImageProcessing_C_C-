void ANorderstatistic_filter( unsigned long ImageLength, unsigned long ImageWidthByte, 
				unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )

{
	//3*3 median filter
	long i , j , x , y;
	int d = 0 , sum = 0;
	//double k , k1 , q = -1.5;
	int temp_arr[25] = {0}, f , s , k;
	unsigned char **new_image;
	printf("Enter the size of the filter which should be odd:");
	scanf("%d",&f);
	unsigned long length = (ImageLength + (f - 1));
	unsigned long width = (ImageWidthByte + ( f - 1));
	/*new_image = (unsigned char **)malloc( length * sizeof( unsigned char *));
	for( i = 0 ; i < length ; i++ )
	{
		*(new_image + i) = (unsigned char *)malloc(  width * sizeof(unsigned char ));
	}
	*/
	printf("Enter 1 for median filter\nEnter 2 for max filter\nEnter 3 for min filter\nEnter 4 for alpha-trimmed mean:");
	scanf("%d",&s);
	cout<<endl<<1/9;
	switch( s )
	{
	case 1:
	for ( i = 0 ; i < ImageLength ; i++ )
		{
			for ( j = 0 ; j < ImageWidthByte ; j++ )
			{
				k = 0;
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
						  temp_arr[k++] = fxy[x][y];
					}
				}
				sort( temp_arr , temp_arr+(f*f) );
				fxyout[i][j] = temp_arr[(f*f)/2];
			}
		}
	break;
	case 2:
	for ( i = 0 ; i < ImageLength ; i++ )
		{
			for ( j = 0 ; j < ImageWidthByte ; j++ )
			{
				k = 0;
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
						  temp_arr[k++] = fxy[x][y];
					}
				}
				sort( temp_arr , temp_arr+(f*f) );
				fxyout[i][j] = temp_arr[(f*f)-1];
			}
		}
	break;
	case 3:
	for ( i = 0 ; i < ImageLength ; i++ )
		{
			for ( j = 0 ; j < ImageWidthByte ; j++ )
			{
				k = 0;
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
						  temp_arr[k++] = fxy[x][y];
					}
				}
				sort( temp_arr , temp_arr+(f*f) );
				fxyout[i][j] = temp_arr[0];
			}
		}
	break;
	case 4:
	for ( i = 0 ; i < ImageLength ; i++ )
		{
			for ( j = 0 ; j < ImageWidthByte ; j++ )
			{
				k = 0 , sum = 0;
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
						  temp_arr[k++] = fxy[x][y];
					}
				}
				sort( temp_arr , temp_arr+(f*f) );
				for ( int u = 0+(d/2) ; u < (f*f)-(d/2) ; u++ )
				{
					sum += temp_arr[u];
				}

				fxyout[i][j] = sum / ((f*f)-d);
			}
		}
	break;
	}
}
