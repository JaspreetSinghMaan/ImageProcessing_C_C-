void gaussian_specif( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	float arr[256] = {0.0} , arr1[256] = {0.0}  ;
	float p[256] = { 0.0 } , temp = 0 , total_spec = 0.0 , min  , mean = 0  , var = 0 , sum = 0;
	int i , j , r1 , r2 , index = 0;
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
	/*arr1[0] = 0.0 ; arr1[15] = 7.00 , arr1[30] = 1.00 , arr1[180] = 0.25 , arr1[220] = 1.00 , arr1[255] = 0.0;
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
	printf("\n%f",total_spec);*/
	//step 2 probability
	for( i = 0 ; i < 256 ; i++ )
	{
		arr[i] = arr[i] / (ImageLength * ImageWidthByte);
		//arr1[i] = arr1[i] / total_spec;
		mean += i * arr[i];
	}
	printf("\nMean value of image:%f",mean);
	for( i = 0  ; i < 256 ; i++ )
	{
		var += pow((double)( i - mean) , 2.0 ) * arr[i];
	}
	cout<<"\nvarience of image :"<<var;
	var = 2 * var;
	for( i = 0 ; i < 256 ; i++ )
	{
		double val = pow((double)( -i - mean ), 2.0 ) /  var ;
		//cout<<endl<<val;
		//cout<<"\t"<<exp(val);
		p[i] = exp( val );
		sum += p[i];
		//cout<<"\t"<<p[i];
	}
	double sum1 = 0 ;
	cout<<"\n normalized values of p:";
	for( i = 0 ; i < 256 ; i++ )
	{
		p[i] = p[i] / sum;
		sum1 += p[i];
		cout<<p[i]<<endl;
	}
	cout<<"\ntotal sum of probabilites of p:"<<sum1;
	getch();
	//cumulative frequecy
	for( i = 1 ; i < 256 ; i++ )
	{
		arr[i] += arr[i-1];
		arr[i-1] *= 255;
		p[i] += p[i-1];
		p[i-1] *= 255;
	}
	arr[255] *= 255;
	p[255] *= 255;
	for( i = 0 ; i < 256 ; i++ )
	{
		printf("\narr[i]=%f\tp[i]=%f",arr[i],p[i]);
	}
	for( i = 0 ; i < 256 ; i++ )
	{
		min = 255;
		for( j = 0 ; j < 256 ; j++ )
		{
			if( abs(arr[i] - p[j]) < min )
			{
				index = j ;
				min = abs(arr[i] - p[j]);
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
	/*printf("\n%d %f \t %f ",i , arr[255],p[255]);
	for( i = 0 ; i < 256 ; i++)
	{
		printf("\n%d %f \t %f ",i , arr[i],p[i]);
	}*/
	getch();
}
