void pow_law_transform( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	// Image power law transformation
	double temp , min,max , r ; 
	float gama ;
	unsigned int i , j ;
	min = 255;
	max = 0;
	printf("Enter the gama value:");
	scanf("%f",&gama);
	for(i=0; i<ImageLength; i++)
	{
		for(j=0; j<ImageWidthByte; j++)
		{
			r = (double)fxy[i][j];
			temp =	pow( r , (double)gama );
			if(temp<min)
				min = temp;
			if(temp>max)
				max = temp;
		}
	}
	printf("min and max values:%f\t%f",min, max);
	getch();
   for(i=0; i<ImageLength; i++)
   {
     for(j=0; j<ImageWidthByte; j++)
     {
	   temp = (double)fxy[i][j];
	   temp = pow(temp , (double)gama);
	   fxyout[i][j] = (unsigned char)((double)(255-0)/(double)(max-min))*(double)(temp-min);
     }
   }
}