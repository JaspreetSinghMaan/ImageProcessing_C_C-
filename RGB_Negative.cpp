void rgb_neg(  unsigned long ImageLength, unsigned long ImageWidthByte, 
	unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	unsigned long i , j ;
	unsigned char r , g , b;
	cout<<"in negative...";
	for( i = 0 ; i < ImageLength ; i++ )
	{
		for( j = 0 ; j < ImageWidth ; j++ )
		{
			r = fxy[i][3*j];
			g = fxy[i][3*j+1];
			b = fxy[i][3*j+2];
			fxyout[i][3*j] = 255 - r;
			fxyout[i][3*j+1] = 255 - g;
			fxyout[i][3*j+2] = 255 - b;
		}
	}
}
