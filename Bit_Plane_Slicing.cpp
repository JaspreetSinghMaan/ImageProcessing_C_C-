void bit_pl_slicing( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	// bit plane slicing at reply 3
		int bitpl , val ;
		unsigned int i , j;
		printf("Enter the bitplane u want to see:");
		scanf("%d",&bitpl);
		val = pow(2.0,bitpl-1);
		for(i=0; i<ImageLength; i++)
		{
			for(j=0; j<ImageWidthByte; j++)
			{
			//printf("%d",val);
			if( (val & fxy[i][j]) > 0 )
				fxyout[i][j] = 255;
			else
				fxyout[i][j] = 0;
			}
		}
		//ImageWidthByte = ImageLength = 10;
		/*parallel_for(unsigned long(0), ImageLength ,[&] (unsigned long i)
		{
			for(unsigned long  j = 0 ; j < ImageLength ; j++)
			{
				fxyout[i][j] = 0;
			}
		});*/
}
