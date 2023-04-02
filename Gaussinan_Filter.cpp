void gaussinan_filter(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	float filter[15][15] , min = 1.0;
	int filter1[15][15] , sum = 0;
	float temp = 0 ;
	unsigned char **new_image;
	int x , y , f;
	long i , j , length , width;
	printf("Enter the size of the filter which should be odd:");
	scanf("%d",&f);
	length = (ImageLength + (f - 1));
	width = (ImageWidthByte + ( f - 1));
	new_image = (unsigned char **)malloc( length * sizeof( unsigned char *));
	for( i = 0 ; i < length ; i++ )
	{
		*(new_image + i) = (unsigned char *)malloc(  width * sizeof(unsigned char ));
	}
	for( x = -(f / 2) ; x <= (f / 2) ; x++ )
		for( y = -(f /2 ) ; y <= (f / 2) ; y++ )
		{
			double val = -((pow(double(x),2.0)+pow(double(y),2.0))/2);
			filter[(f/2)+x][(f/2)+y] = exp(val);
			//sum += filter[(f/2)+x][(f/2)+y];
			if( min > filter[(f/2)+x][(f/2)+y])
				min = filter[(f/2)+x][(f/2)+y];
		}
	for( x = 0 ; x <= f- 1 ; x++ )
	{
		for( y = 0 ; y <= f - 1 ; y++ )
		{
			printf("%f\t", filter[x][y]);
		}
		printf("\n");
	}
	printf("the min of filter is:%f",min);
	for( x = 0 ; x <= f - 1 ; x++ )
	{
		for( y = 0 ; y <= f - 1 ; y++ )
		{
			filter1[x][y] = floor((filter[x][y] / min) + 0.5);
			sum += filter1[x][y];
			printf("%d\t",filter1[x][y]);
		}
		printf("\n");
	}
	printf("\nsum is :%d",sum);

	getch();
	// to copy orignal image into extended image.
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
			x = 0 , temp = 0;
			for( int a = (i-f/2) ; a <= (i+f/2) ; a++ , x++)
			{
				y = 0;
				for( int b = (j-f/2) ; b <= (j+f/2) ; b++ , y++)
				{
					temp += new_image[a][b] * filter1[x][y];
				}
			}
			fxyout[i-f/2][j-f/2] = (floor( (temp  / sum) + 0.5) );
		}
	}


}
