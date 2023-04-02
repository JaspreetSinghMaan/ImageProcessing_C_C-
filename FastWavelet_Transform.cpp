void fastwavelet( unsigned long ImageLength, unsigned long ImageWidthByte, 
	unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	//ImageLength = ImageWidthByte = 4 ;
	//int im[4][4] = {{2,1,3,4},{2,5,6,1},{3,1,2,0},{1,3,6,4}};
	unsigned int i , j , k , l = 0 , m = 0 ;
	double temp1[2] = {0} , temp2[2] = {0};
	double sai_column[1000][100] = {0.0} , theta_column[1000][1000] = {0} , approx_im[1000][1000],dia_im[1000][1000] , ver_im[1000][1000] , hor_im[1000][1000];
	double sai[2] = { 1/1.4142 , -1/1.4142 };
	double theta[2] = { 1/1.4142 , 1/1.4142 };
	//cout<<"sai"<<sai[0]<<sai[1];
	for ( i = 0  ; i < ImageLength ; i++ , l++ )
	{
		m = 0;
		for ( j = 0 ; j < ImageWidthByte ;  )
		{
			for( k = 0 ; k < 2; k++ )
			{
				temp1[k] = sai[k]*fxy[i][j];
				//temp2 = theta[k]*im[i][j];
				j++;
			}
			sai_column[l][m] = temp1[0]+temp1[1];
			m++;
		}
	}
	l = 0 , m = 0;
	for( i = 0 ; i < ImageWidthByte / 2 ; i++ , l++ )
	{
		m = 0 ;
		for( j = 0 ; j < ImageLength ; )
		{
			for( k = 0 ; k < 2 ; k++ )
			{
				temp1[k] = sai[k]*sai_column[j][i];
				temp2[k] = theta[k]*sai_column[j][i];
				j++;
			}
			dia_im[m][l] = temp1[0]+temp1[1];
			ver_im[m][l] = temp2[0]+temp2[1];
			m++;
		}
	}
	l=0 , m=0;
	for ( i = 0  ; i < ImageLength ; i++ , l++ )
	{
		m = 0;
		for ( j = 0 ; j < ImageWidthByte ;  )
		{
			for( k = 0 ; k < 2; k++ )
			{
				temp1[k] = theta[k]*fxy[i][j];
				//temp2 = theta[k]*im[i][j];
				j++;
			}
			theta_column[l][m] = temp1[0]+temp1[1];
			m++;
		}
	}
		l = 0 , m = 0;
	for( i = 0 ; i < ImageWidthByte / 2 ; i++ , l++ )
	{
		m = 0 ;
		for( j = 0 ; j < ImageLength ; )
		{
			for( k = 0 ; k < 2 ; k++ )
			{
				temp1[k] = sai[k]*theta_column[j][i];
				temp2[k] = theta[k]*theta_column[j][i];
				j++;
			}
			hor_im[m][l] = temp1[0]+temp1[1];
			approx_im[m][l] = temp2[0]+temp2[1];
			m++;
		}
	}
	int count = 0;
	cout<<endl;
	for( i = 0 ; i < ImageLength/2 ; i++ )
	{
		for( j = 0 ; j < ImageWidthByte/2 ; j++ )
		{
			//fxyout[i][j] = approx_im[i][j];
			if ( approx_im[i][j] > 255 )
				fxyout[i][j] = 255;
			else if ( approx_im[i][j] < 0 )
				fxyout[i][j] = 0;
			else 
				fxyout[i][j] = approx_im[i][j];
		}
		//cout<<'\n';
	}
	double min = 255 , max = 0;
	for( i = 0 ; i < ImageLength/2 ; i++ )
	{
		for ( j = 0 ; j < ImageWidth/2 ; j++ )
		{
			if( hor_im[i][j] < min )
				min = hor_im[i][j];
			else if ( hor_im[i][j] > max )
				max = hor_im[i][j];
		}
	}
	for(i=0; i<ImageLength/2; i++)
	{
		for(j=0; j<ImageWidthByte/2; j++)
		{
			//temp = (log(double(1+fxy[i][j])));
			hor_im[i][j] =  ((double)(255-0)/(double)(max-min))*(double)(hor_im[i][j]-min);
		}
   }
	for( i = 0 ; i < ImageLength/2 ; i++ )
	{
		for ( j = ImageWidthByte/2 ; j < ImageWidthByte ; j++ )
		{
			//fxyout[i][j] = hor_im[i][j-ImageWidthByte/2];
		/*	if ( hor_im[i][j-ImageWidthByte/2] > 255 )
				fxyout[i][j] = 255;
			else if ( hor_im[i][j-ImageWidthByte/2] < 0 )
				fxyout[i][j] = 0;
			else 
		*/	fxyout[i][j] = hor_im[i][j-ImageWidthByte/2];
		}
	}
	max = 0 , min = 255;
	for( i = 0 ; i < ImageLength/2 ; i++ )
	{
		for ( j = 0 ; j < ImageWidth/2 ; j++ )
		{
			if( ver_im[i][j] < min )
				min = ver_im[i][j];
			else if ( ver_im[i][j] > max )
				max = ver_im[i][j];
		}
	}
	for(i=0; i<ImageLength/2; i++)
	{
		for(j=0; j<ImageWidthByte/2; j++)
		{
			//temp = (log(double(1+fxy[i][j])));
			ver_im[i][j] =  ((double)(255-0)/(double)(max-min))*(double)(ver_im[i][j]-min);
		}
   }
	for( i = ImageLength/2  ; i < ImageLength ; i++ )
	{
		for ( j = 0 ; j < ImageWidthByte/2 ; j++ )
		{
			//fxyout[i][j] = hor_im[i][j-ImageWidthByte/2];
		/*	if ( ver_im[i-ImageLength/2][j]> 255 )
				fxyout[i][j] = 255;
			else if ( ver_im[i-ImageLength/2][j] < 0 )
				fxyout[i][j] = 0;
			else 
		*/		fxyout[i][j] = ver_im[i-ImageLength/2][j];
		}
	}
	max = 0 , min = 255;
	for( i = 0 ; i < ImageLength/2 ; i++ )
	{
		for ( j = 0 ; j < ImageWidth/2 ; j++ )
		{
			if( dia_im[i][j] < min )
				min = dia_im[i][j];
			else if ( dia_im[i][j] > max )
				max = dia_im[i][j];
		}
	}
	for(i=0; i<ImageLength/2; i++)
	{
		for(j=0; j<ImageWidthByte/2; j++)
		{
			//temp = (log(double(1+fxy[i][j])));
			dia_im[i][j] =  ((double)(255-0)/(double)(max-min))*(double)(dia_im[i][j]-min);
		}
   }
	for( i = ImageLength/2  ; i < ImageLength ; i++ )
	{
		for ( j = ImageWidthByte/2 ; j < ImageWidthByte ; j++ )
		{
			//fxyout[i][j] = hor_im[i][j-ImageWidthByte/2];
		/*	if ( dia_im[i-ImageLength/2][j-ImageWidthByte/2]> 255 )
				fxyout[i][j] = 255;
			else if ( dia_im[i-ImageLength/2][j-ImageWidthByte/2] < 0 )
				fxyout[i][j] = 0;
			else 
		*/		fxyout[i][j] = dia_im[i-ImageLength/2][j-ImageWidthByte/2];
		}
	}
	cout<<count;
/*	cout<<endl;
	for( i = 0 ; i < 2 ; i++ )
	{
		for( j = 0 ; j < 2 ; j++ )
		{
			cout<<approx_im[i][j]<<'\t';
		}
		cout<<'\n';
	}
*/
}
