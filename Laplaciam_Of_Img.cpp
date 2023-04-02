void laplaciam_img(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	int w[15][15] , x , y , max =  0 , min = 255 , k = 1 , fil_size = 3 ; 
	int temp_arr[MAXSIZE][3*MAXSIZE] , temp , gxy[MAXSIZE][3*MAXSIZE];
	unsigned long i , j;
	printf("Enter the size of the filter:");
	scanf("%d",&fil_size);
	printf("Enter the Laplacian filter of size 3*3:\n");
	for( i = 0 ; i < fil_size ; i++ )
		for( j = 0 ; j < fil_size ; j++)
			scanf("%d",&w[i][j]);
	if(w[fil_size / 2][fil_size / 2] < 0 )
		k = -1;
	//printf("the value of k :%d",k);
	for ( i = 0 ; i < ImageLength ; i++ )
	{
		for ( j = 0 ; j < ImageWidthByte ; j++ )
		{
			temp = 0;
			for ( int a = -1 ; a <= 1; a++ )
			{
				 for ( int b = -1 ; b <= 1 ; b++ )
				 {
					  x = i+a;
					  y = j+b;
					  if( x < 0 )
						x = 0;
					  if( x > ImageLength-1 )
						x = ImageLength-1;
					  if( y < 0 )
						y = 0;
					  if( y > ImageWidthByte-1 )
						y = ImageWidthByte-1;
					  temp += w[a+1][b+1] * fxy[x][y];
				}
			}
			temp_arr[i][j] = temp;
			gxy[i][j] = fxy[i][j] +(k * temp);
			
		}
	 }
	for ( i = 0 ; i < ImageLength ; i++ )
	{
		for ( j = 0 ; j < ImageWidthByte ; j++ )
		{
			if( gxy[i][j] < 0 )
				fxyout[i][j] = 0;
			else if( gxy[i][j] > 255 )
				fxyout[i][j] = 255;
			else
				fxyout[i][j] = gxy[i][j];
		}
	}
}
