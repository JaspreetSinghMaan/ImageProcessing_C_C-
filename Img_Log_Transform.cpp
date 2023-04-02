void img_log_transform( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	// Image log transformation
	double temp , min,max;
	unsigned int i , j;
	min = 255;
	max = 0;
	for(i=0; i<ImageLength; i++)
	{
		for(j=0; j<ImageWidthByte; j++)
		{
			temp =	(log(double(1+fxy[i][j])));
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
			temp = (log(double(1+fxy[i][j])));
			fxyout[i][j] =  (unsigned char)0+((double)(255-0)/(double)(max-min))*(double)(temp-min);
		}
   }
}
