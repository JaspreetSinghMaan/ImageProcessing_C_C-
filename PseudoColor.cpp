void pseudocolor( unsigned long ImageLength, unsigned long ImageWidthByte, 
	unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	double r , g , b;
	unsigned long i , j;
	double hue[1000][1000] , sat[1000][1000] , in[1000][1000];
	//cout<<ImageWidthByte<<endl;
	//cout<<ImageWidth;
	//void rgb2hsi(float r,float g,float b,float *h,float *s,float *i)
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
	//pseudo color processing on intensity component
	for ( i = 0 ; i < ImageLength ; i++ )
	{
		for ( j = 0 ; j < ImageWidth ; j++ )
		{
			if( in[i][j] >= 0 && in[i][j] <= 100 )
			{
				fxyout[i][3*j] = 255;
				fxyout[i][3*j+1] = 0;
				fxyout[i][3*j+2] = 0;
			}
			else if ( in[i][j] >100 && in[i][j] <=200)
			{
				fxyout[i][3*j] = 0;
				fxyout[i][3*j+1] = 255;
				fxyout[i][3*j+2] = 0;
			}
			else
			{
				fxyout[i][3*j] = 0;
				fxyout[i][3*j+1] = 0;
				fxyout[i][3*j+2] = 255;
			}
		}
	}

}
