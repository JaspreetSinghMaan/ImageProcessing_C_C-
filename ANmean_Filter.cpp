void ANmean_filter( unsigned long ImageLength, unsigned long ImageWidthByte, 
				unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	//3*3 median filter
	long i , j , x , y;
	double k , k1 , q = -1.5;
	int temp_arr[25] = {0}, f , s ;
	unsigned char **new_image;
	printf("Enter the size of the filter which should be odd:");
	scanf("%d",&f);
	unsigned long length = (ImageLength + (f - 1));
	unsigned long width = (ImageWidthByte + ( f - 1));
	new_image = (unsigned char **)malloc( length * sizeof( unsigned char *));
	for( i = 0 ; i < length ; i++ )
	{
		*(new_image + i) = (unsigned char *)malloc(  width * sizeof(unsigned char ));
	}
	
	printf("Enter 1 for mean\nEnter 2 for geometric mean\nEnter 3 for harmonic mean\nEnter 4 for contraharmonic mean:");
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
						  k += fxy[x][y];
					}
				}
				fxyout[i][j] = ( k / ( f * f ) );
			}
		}
		break;
		case 2:
		for ( i = 0 ; i < ImageLength ; i++ )
		{
			for ( j = 0 ; j < ImageWidthByte ; j++ )
			{
				k = 1;
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
						  k = k * fxy[x][y];
					}
				}
				//cout<<k;
				fxyout[i][j] = pow( k , (1.0 / ( f * f )) );
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
						  k += (1.0 / fxy[x][y]);
					}
				}
				//cout<<k;
				fxyout[i][j] = ( f*f )/( k );
			}
		}
		break;
		case 4:
		for ( i = 0 ; i < ImageLength ; i++ )
		{
			for ( j = 0 ; j < ImageWidthByte ; j++ )
			{
				k = 0;
				k1 = 0;
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
						  k += pow( fxy[x][y] , q+1 );
						  k1 += pow( fxy[x][y] , q );
					}
				}
				//cout<<k;
				fxyout[i][j] = k / k1 ;
			}
		}
		break;
	
		default:
			cout<<"Wrong choice.";
	}
}
