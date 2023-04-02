void histo_specif( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	float arr[256] = {0.0} , arr1[256] = {0.0} ;
	float sum = 0 , temp = 0 , total_spec = 0.0 , min ;
	unsigned int i , j , r1 , r2 , index = 0;
	int final_val[256];
	float s1 , s2;
	for(i=0; i<ImageLength; i++)
	{
		 //step 1 frequency finding of original image
		for(j=0; j<ImageWidth; j++)
		{
			unsigned int index = (unsigned int)fxy[i][j];
			arr[index] = ++arr[index];
		}
	}
	//specified vaules
	arr1[0] = 0.0 ; arr1[15] = 7.00 , arr1[30] = 1.00 , arr1[180] = 0.25 , arr1[220] = 1.00 , arr1[255] = 0.0;
	r2 = 0 , s2 = 0.0;
	while( index != 256 )
	{
		if( arr1[index] > 0 || index == 255 )
		{	
			r1 = r2;
			s1 = s2;
			r2 = index;
			s2 = arr1[index];
			for ( i = r1+1 ; i <= r2 ; i++ )
				arr1[i] = s1 + (( s2 - s1 ) / ( r2 - r1 )) * ( i - r1 );
			index++;
		}
		else
			index++ ;
	}
	for ( i = 0 ; i < 256 ; i++ )
	{
		cout<<"\n"<<arr1[i];
		arr1[i] *= 10000 ;
		total_spec += arr1[i] ;
	}
	getch();
	printf("\n%f",total_spec);
	//step 2 probability
	for( i = 0 ; i < 256 ; i++ )
	{
		arr[i] = arr[i] / (ImageLength * ImageWidthByte);
		arr1[i] = arr1[i] / total_spec;
	}
	//cumulative frequecy
	for( i = 1 ; i < 256 ; i++ )
	{
		arr[i] += arr[i-1];
		arr[i-1] *= 255;
		arr1[i] += arr1[i-1];
		arr1[i-1] *= 255;
	}
	arr[255] *= 255;
	arr1[255] *= 255;
	//end of comulation
	
	
	//convert both to the nearest integer
	/*for( i = 0  ; i < 256 ; i++ )
	{
		arr[i] = floor( arr[i]+0.5);
		arr1[i] = floor( arr1[i]+0.5);
	}*/
	for( i = 0 ; i < 256 ; i++ )
	{
		min = 255;
		for( j = 0 ; j < 256 ; j++ )
		{
			if( abs(arr[i] - arr1[j]) < min )
			{
				index = j ;
				min = abs(arr[i] - arr1[j]);
			}
		}
		final_val[i] = index;
	}
	for( i = 0 ; i < ImageLength ; i++ )
	{
		for( j = 0 ; j < ImageWidthByte ; j++ )
		{
			index = fxy[i][j];
			fxyout[i][j] = final_val[index];
		}
	}
	printf("\n%d %f \t %f ",i , arr[255],arr1[255]);
	for( i = 0 ; i < 256 ; i++)
	{
		printf("\n%d %f \t %f ",i , arr[i],arr1[i]);
	}
	getch();

}
