void global_threshod( unsigned long ImageLength, unsigned long ImageWidthByte, 
	unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])			
{
	unsigned int i , j  , g1 = 0 , g2 = 0 , g1sum = 0 , g2sum = 0;
	unsigned char temp_fxy[1000][100];
	double T = 50, t = 0 , m1 , m2;
	for( i = 0 ; i < ImageLength ; i++ )
	{
		for ( j = 0 ; j < ImageWidthByte ; j++ )
		{
			temp_fxy[i][j] = fxy[i][j];
			g1sum += fxy[i][j];
		}
	}
	T = (double)g1sum / (ImageLength * ImageWidthByte);
	cout<<T;
	getch();
	while( T != t )
	{
		t = T;
		g1sum = g2sum = g1 = g2 = 0;
		for( i = 0 ; i < ImageLength ; i++ )
		{
			for ( j = 0 ; j < ImageWidthByte ; j++ )
			{
				if( temp_fxy[i][j] <= T )
				{
					g1sum += temp_fxy[i][j];
					temp_fxy[i][j] = 0;
					g1++;
				}
				else
				{
					g2sum += temp_fxy[i][j];
					temp_fxy[i][j] = 255;
					g2++;
				}
			}
		}
		m1 = (double)g1sum / g1;
		m2 = (double)g2sum / g2;
		T = (m1 + m2 ) / 2;
		cout<<T<<"\t";
	}
	cout<<"Threshold value:"<<T;
	int t_val = T;
	for( i = 0 ; i < ImageLength ; i++ )
	{
		for ( j = 0 ; j < ImageWidthByte ; j++ )
		{
			if( fxy[i][j] <= t_val )
				fxyout[i][j] = 0;
			else 
				fxyout[i][j] = 255;
		}
	}
	getch();
}
