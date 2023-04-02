void rgb_equal( unsigned long ImageLength, unsigned long ImageWidthByte, 
	unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	//histogram equalization at reply 5
	float r[256] = {0.0} , g[256] = { 0.0 } , b[256] = { 0.0 };
	float sum = 0 , temp = 0;
	unsigned int i , j;
	for(i=0; i<ImageLength; i++)
	{
		 //step 1 frequency finding
		for(j=0; j<ImageWidth; j++)
		{
			unsigned int index = fxy[i][3*j];
			r[index] = ++r[index];
			index = fxy[i][3*j+1];
			g[index] = ++g[index];
			index = fxy[i][3*j+2];
			b[index] = ++b[index];
		}

	}
	//step 2 probability
	for( i = 0 ; i < 256 ; i++ )
	{
		r[i] = r[i] / (ImageLength * ImageWidth);
		g[i] = g[i] / (ImageLength * ImageWidth);
		b[i] = b[i] / (ImageLength * ImageWidth);
	}
	//cumulative frequecy
	for( i = 1 ; i < 256 ; i++ )
	{
		r[i] += r[i-1];
		r[i-1] *= 255;
		g[i] += g[i-1];
		g[i-1] *= 255;
		b[i] += b[i-1];
		b[i-1] *= 255;
	}
	r[255] *= 255;
	g[255] *= 255;
	b[255] *= 255;
	for(i=0; i<ImageLength; i++)
	{
		for(j=0; j<ImageWidth; j++)
		{
			fxyout[i][3*j] = (unsigned char)floor(r[fxy[i][3*j]]+0.5);
			fxyout[i][3*j+1] = (unsigned char)floor(g[fxy[i][3*j+1]]+0.5);
			fxyout[i][3*j+2] = (unsigned char)floor(b[fxy[i][3*j+2]]+0.5);
		}
	}
}
