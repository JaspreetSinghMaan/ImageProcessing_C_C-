void lma_threshod( unsigned long ImageLength, unsigned long ImageWidthByte, 
	unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	unsigned long i , j , k = 0;
	int temp[20] = {0};
	unsigned char temp_fxy[1000000];
	for( i = 0 ; i < ImageLength ; i++ )
	{
		if( i % 2 == 0 )
		{
			for( j = 0 ; j < ImageWidth ; j++ )
			{
				temp_fxy[k++] = fxy[i][j];
			}
		}
		else
		{
			for( j = (ImageWidth-1); j >= 0 ; j-- )
			{
				temp_fxy[k++] = fxy[i][j];
			}
		}
	}
	k = 0 ;
	long x , u , sum ;
	double mavg;
	for( i = 0 ; i < ImageLength ; i++ )
	{
		for( j = 0 ; j < ImageWidth ; j++ )
		{
			sum = 0;
			x = k;
			x = x-20;
			if( x < 0 )
				x = 0;
			for( u = x ; u <= k ; u++ )
			{
				sum += temp_fxy[u];
			}
			mavg = sum / 20;
			if( fxy[i][j] > (0.5 * mavg ) )
			{
				fxyout[i][j] = 255 ; 
			}
			else
				fxyout[i][j] = 0;
			k++;
		}
	}
}
