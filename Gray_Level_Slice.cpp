void gray_level_slice(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	// grey value slicing
	unsigned int lolimit , hilimit , new_val , temp ,  i , j;
	printf("Enter the lower limit , higher limit of interst area and new intensity level: ");
	scanf("%u%u%u",&lolimit,&hilimit,&new_val);
	for(i=0; i<ImageLength; i++)
	{
		for(j=0; j<ImageWidthByte; j++)
		{
		  temp = (unsigned int)fxy[i][j];
		  if( (temp >= lolimit) && (temp<= hilimit) )
			fxyout[i][j] = (unsigned char)new_val;
		  else
			  fxyout[i][j] = fxy[i][j];
		 }
	 }
}
