void contrast_stretch( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	//contrast stretching at reply 4
	int r1 , r2 , s1 , s2;
	unsigned int i , j;
	printf("Enter the value of r1 and r2:");
	scanf("%d %d",&r1,&r2);
	printf("Enter the value of s1 and s2:");
	scanf("%d %d",&s1,&s2);
	printf("the values from %d to %d stretched from %d to %d",r1,r2,s1,s2);
	for(i=0; i<ImageLength; i++)
	{
		for(j=0; j<ImageWidthByte; j++)
		{
			if( r1 <= fxy[i][j] <= r2 )
				fxyout[i][j] = s1 + ((s2 - s1)/(r2 - r1))*(fxy[i][j] - r1);
			else 
				fxyout[i][j] = fxy[i][j];
		}
	}
}
