void median_filter(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	//3*3 median filter
	long i , j , x , y;
	int temp_arr[25] = {0}, k = 0 , f , s;
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
	
	printf("Enter 1 for median \nEnter 2 for max \nEnter 3 for min \nEnter 4 for mean:");
	scanf("%d",&s);

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
			k = 0;
			for( int a = (i-f/2) ; a <= (i+f/2) ; a++ )
			{
				for( int b = (j-f/2) ; b <= (j+f/2) ; b++)
				{
					temp_arr[k++] = new_image[a][b];
				}
			}
			sort( temp_arr , temp_arr+(f*f) );
			switch(s)
			{
			case 1:
				fxyout[i-f/2][j-f/2] = (unsigned char)temp_arr[(f * f) / 2];
				break;
			case 2:
				fxyout[i-f/2][j-f/2] = (unsigned char)temp_arr[(f * f) - 1];
				break;
			case 3:
				fxyout[i-f/2][j-f/2] = (unsigned char)temp_arr[0];
				break;
			case 4:
				fxyout[i-f/2][j-f/2] = (temp_arr[(f * f) - 1] + temp_arr[0]) / 2;				
				break;
			default:
				printf("wrong choice");
			}
		}
	}
	/*for ( i = 0 ; i < ImageLength ; i++ )
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
			switch(s)
			{
			case 1:
				fxyout[i][j] = (unsigned char)temp_arr[(f * f) / 2];
				break;
			case 2:
				fxyout[i][j] = (unsigned char)temp_arr[(f * f) - 1];
				break;
			case 3:
				fxyout[i][j] = (unsigned char)temp_arr[0];
				break;
			case 4:
				fxyout[i][j] = (temp_arr[(f * f) - 1] + temp_arr[0]) / 2;				
				break;
			default:
				printf("wrong choice");
			}
		}
	}*/
}
