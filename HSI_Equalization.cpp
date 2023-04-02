void hsi_equal( unsigned long ImageLength, unsigned long ImageWidthByte, 
	unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	double r , g , b;
	unsigned long i , j;
	double hue[1000][1000] , sat[1000][1000] , in[1000][1000];
    for( i = 0 ; i < ImageLength ; i++ )
	{
		for( j = 0 ; j < ImageWidth ; j++ )
		{
			r = fxy[i][3*j];
			g = fxy[i][3*j+1];
			b = fxy[i][3*j+2];
			float min, max;              /* minimum and maximum RGB values */
			float angle;                 /* temp variable used to compute Hue */
			if((r<=g) && (r<=b))
				min = r;
			else if((g<=r) && (g<=b))
				min = g;
			else
				min = b;

			/* compute intensity */
			in[i][j] = (r + g + b) / 3.0;

			/* compute hue and saturation */
			if((r==g) && (g==b))  /* gray-scale */
			{
				sat[i][j] = 0.0;
				hue[i][j] = 0.0;
				//return;
			}
			else
			{
				sat[i][j] = 1.0 - (3.0 / (float)(r + g + b)) * min;
				angle = (0.5*(2*r - g - b)) / sqrt((r - g) * (r - g)+(r - b) * (g - b));
				hue[i][j] = acos(angle);
				hue[i][j] *= 57.27272727272727;          /* convert to degrees */
			}
			if( b > g )
				hue[i][j] = 360.0 - hue[i][j];
			//cout<<"r-"<<r*255<<"\t g-"<<g*255<<"\t b-"<<b*255<<"\th-"<<*h<<"\ts-"<<*s<<"\tI"<<*i*255<<endl;
//			getch();
		}
	}
	unsigned char inten[1000][1000];
	for(i=0; i<ImageLength; i++)
	{
		 //step 1 frequency finding
		for(j=0; j<ImageWidth; j++)
		{
			inten[i][j] = floor(in[i][j]+0.5);
			//if( inten[i][j] > 255 )
				//count++;
		}
	}
	//cout<<count;
	double arr[256] = {0.0};
	double sum = 0 , temp = 0;
	int count=0;
	//unsigned int i , j;
	for(i = 0; i < ImageLength ; i++)
	{
		 //step 1 frequency finding
		for(j = 0; j < ImageWidth ; j++)
		{
			int index = inten[i][j];
			arr[index] = ++arr[index];
		}
	}
	//step 2 probability
	for( i = 0 ; i < 256 ; i++ )
	{
		arr[i] = arr[i] / (ImageLength * ImageWidth);
	}
	//cout<<"probabilty of arr[255]
	//cumulative frequecy
	for( i = 1 ; i < 256 ; i++ )
	{
		arr[i] += arr[i-1];
		arr[i-1] *= 255;
	}
	arr[255] *= 255;
	cout<<"cumulative frequency:"<<arr[255];
	getch();
	for(i=0; i<ImageLength; i++)
	{
		for(j=0; j<ImageWidth; j++)
		{
			in[i][j] = arr[inten[i][j]];
			/*if( floor(arr[inten[i][j]]+0.5) > 255 )
				count++;
			*/
		}
	}

	// HSI to RGB
	double red[1000][1000] , green[1000][1000] , blue[1000][1000];
	float angle1, angle2, scale, denom;   /* temp variables */
	for( i = 0 ; i < ImageLength ; i++ )
	{
		for( j = 0 ; j < ImageWidth ; j++ )
		{
			if(in[i][j] == 0.0)    /* BLACK */
			{
				red[i][j] = 0.0;
				green[i][j] = 0.0;
				blue[i][j] = 0.0;
				//return;
			}
			else if(sat[i][j]==0.0)     /* gray-scale  H is undefined*/
			{
				red[i][j] = in[i][j];
				green[i][j] = in[i][j];
				blue[i][j] = in[i][j];
				//return;
			}
			if( hue[i][j] < 0.0 )
				hue[i][j] += 360.0;
				scale = 3.0 * in[i][j];
			if( hue[i][j] <= 120.0)
			{
				angle1=hue[i][j] * 0.0174603174603175;    /* convert to radians - mul by pi/180 */
				angle2=(60.0-hue[i][j])*0.0174603174603175;

				blue[i][j] = (1.0-sat[i][j])*in[i][j];
				red[i][j] = (1.0 + (sat[i][j]*cos(angle1)/cos(angle2)))*in[i][j];
				green[i][j] = 3*in[i][j]-red[i][j]-blue[i][j];
			}
			else if((hue[i][j] > 120.0) && (hue[i][j] <= 240.0))
			{
				hue[i][j] -= 120.0;
				angle1=hue[i][j] * 0.0174603174603175;    /* convert to radians - mul by pi/180 */
				angle2=(60.0-hue[i][j])*0.0174603174603175;

				red[i][j] = (1.0-sat[i][j])*in[i][j];
				green[i][j] = (1.0 + (sat[i][j]*cos(angle1)/cos(angle2)))*in[i][j];
				blue[i][j] = 3*in[i][j] - red[i][j] - green[i][j];
			}
			else
			{
				hue[i][j] -= 240.0;
				angle1=hue[i][j]*0.0174603174603175;    /* convert to radians - mul by pi/180 */
				angle2=(60.0-hue[i][j])*0.0174603174603175;

				green[i][j] = (1.0-sat[i][j])*in[i][j];
				blue[i][j] = (1.0 + (sat[i][j]*cos(angle1)/cos(angle2)))*in[i][j];
				red[i][j] = 3*in[i][j] - green[i][j] - blue[i][j];
			}
			red[i][j]=floor(red[i][j]+0.5);
			green[i][j]=floor(green[i][j]+0.5);
			blue[i][j]=floor(blue[i][j]+0.5);
		}
	}
	//cout<<i<<j;
	for( i = 0 ; i < ImageLength ; i++ )
	{
		for( j = 0 ; j < ImageWidth ; j++ )
		{
			 //cout<<endl<<i<<'\t'<<j<<'\t'<<in[i][j];
			if( red[i][j] > 255 )
				fxyout[i][3*j] = 255; 
			else
				fxyout[i][3*j] = red[i][j];
			if( green[i][j] > 255 )
				fxyout[i][3*j+1] = 255;
			else
				fxyout[i][3*j+1] =	green[i][j];
			if( blue[i][j] > 255 )
				fxyout[i][3*j+2] = 255;
			else
				fxyout[i][3*j+2] = blue[i][j];
		}
		//cout<<i;
	}
}
