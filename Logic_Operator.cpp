void logic_opr(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	// Logical operators
	unsigned char **new_image;
	unsigned long i  , j;
	int choice;
	int range1 = ( ImageWidthByte / 2 ) - 50 , range2 = ( ImageWidthByte / 2 ) + 50;
	new_image = (unsigned char **)malloc( ImageLength * sizeof( unsigned char *));
	for( i = 0 ; i < ImageLength ; i++ )
	{
		*(new_image + i) = (unsigned char *)malloc( ImageWidthByte * sizeof(unsigned char ));
	}
	printf("1 for AND operator.\n 2 for OR operator \n 3 for XOR operator \n 4 for NOT operator :");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:
		for(i = 0 ; i < ImageLength ; i++ )
			for( j = 0 ; j < ImageWidthByte ; j++ )
				new_image[i][j] = 0;
		for( i = 0 ; i < 200 ; i++ )
			for( j = 0 ; j < ImageWidthByte ; j++ )
			{
				if( j > range1 && j < range2 )
				{
					new_image[i][j] = 255;
				}
			}
		for( i = 0 ; i < ImageLength ; i++ )
			for( j = 0 ; j < ImageWidthByte ; j++ )
			{
				fxyout[i][j] = fxy[i][j] & new_image[i][j];
			}
	break;
	
	case 2:
		for(i = 0 ; i < ImageLength ; i++ )
			for( j = 0 ; j < ImageWidthByte ; j++ )
				new_image[i][j] = 255;
		for( i = 0 ; i < 200 ; i++ )
			for( j = 0 ; j < ImageWidthByte ; j++ )
			{
				if( j > range1 && j < range2 )
				{
					new_image[i][j] = 0;
				}
			}
		for( i = 0 ; i < ImageLength ; i++ )
			for( j = 0 ; j < ImageWidthByte ; j++ )
			{
				fxyout[i][j] = fxy[i][j] | new_image[i][j];
			}
	break;
	
	case 3:
		for(i = 0 ; i < ImageLength ; i++ )
			for( j = 0 ; j < ImageWidthByte ; j++ )
				new_image[i][j] = 255;
		for( i = 0 ; i < ImageLength ; i++ )
			for( j = 0 ; j < ImageWidthByte ; j++ )
			{
				fxyout[i][j] = fxy[i][j] ^ new_image[i][j];
			}
	break;
	
	case 4:
		for( i = 0 ; i < ImageLength ; i++ )
			for( j = 0 ; j < ImageWidthByte ; j++ )
			{
				fxyout[i][j] = ~fxy[i][j] ;
			}
	break;
	
	default:
		printf("Wrong choice.");
	}
}
