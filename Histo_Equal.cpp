void histo_equal( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	//histogram equalization at reply 5
	float arr[256] = {0.0};
	float sum = 0 , temp = 0;
	unsigned int i , j;
	for(i=0; i<ImageLength; i++)
	{
		 //step 1 frequency finding
		for(j=0; j<ImageWidth; j++)
		{
			unsigned int index = (unsigned int)fxy[i][j];
			arr[index] = ++arr[index];
		}

	}
	//step 2 probability
	for( i = 0 ; i < 256 ; i++ )
	{
		arr[i] = arr[i] / (ImageLength * ImageWidthByte);
	}
	//cumulative frequecy
	for( i = 1 ; i < 256 ; i++ )
	{
		arr[i] += arr[i-1];
		arr[i-1] *= 255;
	}
	arr[255] *= 255;
	for(i=0; i<ImageLength; i++)
	{
		for(j=0; j<ImageWidthByte; j++)
		{
			fxyout[i][j] = (unsigned char)floor(arr[fxy[i][j]]+0.5);
		}
	}
	//getch();
}