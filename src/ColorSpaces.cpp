#include "ColorSpaces.h";

/********************************************************************************************************************************/
/* RGB processing */
/********************************************************************************************************************************/
void processing_RGB(const uchar rgbInputImg[], int x, int y, uchar rgbOutputImg[], double R, double G, double B)
{
	for(int i = 0; i< x; i++)
	{
		for(int j=0; j<y; j++)
		{
			rgbOutputImg[j*x*3+i*3] = R*rgbInputImg[j*x*3+i*3];
			rgbOutputImg[j*x*3+i*3+1] = G*rgbInputImg[j*x*3+i*3+1];
			rgbOutputImg[j*x*3+i*3+2] = B*rgbInputImg[j*x*3+i*3+2];
		}
	}
}

/********************************************************************************************************************************/
/* YUV444 processing */
/********************************************************************************************************************************/
void RGBtoYUV444(const uchar rgbImg[], int x, int y, uchar Y_buff[], char U_buff[], char V_buff[]) 
{
	//TO_DO: Implement RGBtoYUV444 conversion
	double R, G, B;
	double Y, U, V;
	
	for (int i = 0; i < x; i++) 
	{
		for (int j = 0; j < y; j++) 
		{	
			R = rgbImg[j * 3 * x + i * 3];
			G = rgbImg[j * 3 * x + i * 3 + 1];
			B = rgbImg[j * 3 * x + i * 3 + 2];

			Y = R*0.299 + G*0.587 + B*0.114;
			U = R*(-0.14713) + G*(-0.28886) + B*(0.436);
			V = R*0.615 + G*(-0.51499) + B*(-0.10001);

			Y_buff[j*x + i] = Y;
			U_buff[j*x + i] = U;
			V_buff[j*x + i] = V;
		}
	}

}

void YUV444toRGB(const uchar Y_buff[], const char U_buff[], const char V_buff[], int x, int y, uchar rgbImg[]) 
{
	double R,G,B;
	double Y, U, V;
	for(int i = 0; i<x; i++)
	{
		for(int j = 0; j<y; j+=1)
		{
			Y = Y_buff[j*x+i];
			U = U_buff[j*x+i];
			V = V_buff[j*x+i];

			R = Y + 1.13983*V;
			G = Y - 0.39465*U - 0.58060*V;
			B = Y + 2.03211*U;
			
			if (R < 0)
				R = 0;
			else if (R > 255)
				R = 255;
			if (G< 0)
				G = 0;
			else if (G> 255)
				G = 255;
			if (B < 0)
				B = 0;
			else if (B > 255)
				B = 255;


			rgbImg[j*3*x+i*3] =  R;
			rgbImg[j*3*x+i*3 + 1] = G;
			rgbImg[j*3*x+i*3 + 2] =  B;
	
		}
	}
}

void procesing_YUV444(uchar Y_buff[], char U_buff[], char V_buff[], int x, int y, double Y, double U, double V)
{

	//TO_DO: Implement YUV444 procesing
	for (int i = 0; i< x; i++)
	{
		for (int j = 0; j<y; j++)
		{
			Y_buff[j*x + i] *= Y;
			U_buff[j*x + i] *= U;
			V_buff[j*x + i] *= V;
		}
	}

}

/*******************************************************************************************************************************/
/* YUV422 processing */
/********************************************************************************************************************************/
void RGBtoYUV422(const uchar rgbImg[], int x, int y, uchar Y_buff[], char U_buff[], char V_buff[]) 
{

	//TO_DO: Implement RGBtoYUV422 conversion
	double R, G, B;
	double Y1, Y2, U1, U2, V1, V2;

	for (int i = 0; i < x; i+=2)
	{
		for (int j = 0; j < y; j++)
		{
			R = rgbImg[j * 3 * x + i * 3];
			G = rgbImg[j * 3 * x + i * 3 + 1];
			B = rgbImg[j * 3 * x + i * 3 + 2];

			Y1 = R*0.299 + G*0.587 + B*0.114;
			U1 = R*(-0.14713) + G*(-0.28886) + B*(0.436);
			V1 = R*0.615 + G*(-0.51499) + B*(-0.10001);

			R = rgbImg[j * 3 * x + (i+1) * 3];
			G = rgbImg[j * 3 * x + (i+1) * 3 + 1];
			B = rgbImg[j * 3 * x + (i+1) * 3 + 2];

			Y2 = R*0.299 + G*0.587 + B*0.114;
			U2 = R*(-0.14713) + G*(-0.28886) + B*(0.436);
			V2 = R*0.615 + G*(-0.51499) + B*(-0.10001);

			Y_buff[j*x + i] = Y1;
			Y_buff[j*x + i+1] = Y2;
			U_buff[j*x/2 + i/2] = (U1+U2)/2;
			V_buff[j*x/2 + i/2] = (V1+V2)/2;
		}
	}
}

void YUV422toRGB(const uchar Y_buff[], const char U_buff[], const char V_buff[], int x, int y, uchar rgbImg[]) 
{
	double R,G,B;
	double Y, U, V;
	for(int i = 0; i<x; i+=2)
	{
		for(int j = 0; j<y; j++)
		{
			U = U_buff[j*x/2+i/2];
			V = V_buff[j*x/2+i/2];

			Y = Y_buff[j*x+i];

			R = Y + 1.13983*V;
			G = Y -0.39465*U - 0.58060*V;
			B = Y + 2.03211*U;

			if (R < 0)
				R = 0;
			else if (R > 255)
				R = 255;
			if (G < 0)
				G = 0;
			else if (G> 255)
				G = 255;
			if (B < 0)
				B = 0;
			else if (B > 255)
				B = 255;

			rgbImg[j*3*x+i*3] =  R;
			rgbImg[j*3*x+i*3 + 1] = G;
			rgbImg[j*3*x+i*3 + 2] = B;

			Y = Y_buff[j*x+(i+1)];

			R = Y + 1.13983*V;
			G = Y -0.39465*U - 0.58060*V;
			B = Y + 2.03211*U;

			if (R < 0)
				R = 0;
			else if (R > 255)
				R = 255;
			if (G< 0)
				G = 0;
			else if (G> 255)
				G = 255;
			if (B < 0)
				B = 0;
			else if (B > 255)
				B = 255;

			rgbImg[j*3*x+(i+1)*3] =  R;
			rgbImg[j*3*x+(i+1)*3 + 1] = G;
			rgbImg[j*3*x+(i+1)*3 + 2] = B;
		}
	}
}

void procesing_YUV422(uchar Y_buff[], char U_buff[], char V_buff[], int x, int y, double Y, double U, double V)
{

	//TO_DO: Implement YUV422 processing
	for (int i = 0; i< x; i+=2)
	{
		for (int j = 0; j<y; j++)
		{
			Y_buff[j*x + i] *= Y;
			Y_buff[j*x + i+1] *= Y;
			U_buff[j*x/2 + i/2] *= U;
			V_buff[j*x/2 + i/2] *= V;
		}
	}
}

/*******************************************************************************************************************************/
/* YUV420 processing */
/*******************************************************************************************************************************/
void RGBtoYUV420(const uchar rgbImg[], int x, int y, uchar Y_buff[], char U_buff[], char V_buff[]) 
{

	//TO_DO: Implement RGBtoYUV420 conversion
	double R, G, B;
	double Y1, Y2, Y3, Y4, U1, U2, U3, U4, V1, V2, V3, V4;

	for (int i = 0; i < x; i += 2)
	{
		for (int j = 0; j < y; j+=2)
		{
			R = rgbImg[j * 3 * x + i * 3];
			G = rgbImg[j * 3 * x + i * 3 + 1];
			B = rgbImg[j * 3 * x + i * 3 + 2];

			Y1 = R*0.299 + G*0.587 + B*0.114;
			U1 = R*(-0.14713) + G*(-0.28886) + B*(0.436);
			V1 = R*0.615 + G*(-0.51499) + B*(-0.10001);

			R = rgbImg[(j + 1) * 3 * x + i * 3];
			G = rgbImg[(j + 1) * 3 * x + i * 3 + 1];
			B = rgbImg[(j + 1) * 3 * x + i * 3 + 2];

			Y2 = R*0.299 + G*0.587 + B*0.114;
			U2 = R*(-0.14713) + G*(-0.28886) + B*(0.436);
			V2 = R*0.615 + G*(-0.51499) + B*(-0.10001);

			R = rgbImg[j * 3 * x + (i + 1) * 3];
			G = rgbImg[j * 3 * x + (i + 1) * 3 + 1];
			B = rgbImg[j * 3 * x + (i + 1) * 3 + 2];

			Y3 = R*0.299 + G*0.587 + B*0.114;
			U3 = R*(-0.14713) + G*(-0.28886) + B*(0.436);
			V3 = R*0.615 + G*(-0.51499) + B*(-0.10001);

			R = rgbImg[(j + 1) * 3 * x + (i + 1) * 3];
			G = rgbImg[(j + 1) * 3 * x + (i + 1) * 3 + 1];
			B = rgbImg[(j + 1) * 3 * x + (i + 1) * 3 + 2];

			Y4 = R*0.299 + G*0.587 + B*0.114;
			U4 = R*(-0.14713) + G*(-0.28886) + B*(0.436);
			V4 = R*0.615 + G*(-0.51499) + B*(-0.10001);

			Y_buff[j*x + i] = Y1;
			Y_buff[(j+1)*x + i] = Y2;
			Y_buff[j*x + i+1] = Y3;
			Y_buff[(j + 1)*x + i+1] = Y4;

			U_buff[j/2*x / 2 + i / 2] = (U1 + U2 + U3 + U4) / 4;
			V_buff[j/2*x / 2 + i / 2] = (V1 + V2 + V3 + V4) / 4;
		}
	}
	
}

void YUV420toRGB(const uchar Y_buff[], const char U_buff[], const char V_buff[], int x, int y, uchar rgbImg[]) 
{
	double R,G,B;
	double Y, U, V;

	for(int j = 0; j<y; j+=2)	
	{
		for(int i = 0; i<x; i+=2)
		{
			U = U_buff[j/2*x/2+i/2];
			V = V_buff[j/2*x/2+i/2];

			Y = Y_buff[j*x+i];

			R = Y + 1.13983*V;
			G = Y -0.39465*U - 0.58060*V;
			B = Y + 2.03211*U;

			if (R < 0)
				R = 0;
			else if (R > 255)
				R = 255;
			if (G< 0)
				G = 0;
			else if (G> 255)
				G = 255;
			if (B < 0)
				B = 0;
			else if (B > 255)
				B = 255;

			rgbImg[j*3*x+i*3] =  R;
			rgbImg[j*3*x+i*3 + 1] = G;
			rgbImg[j*3*x+i*3 + 2] = B;

			Y = Y_buff[j*x+(i+1)];

			R = Y + 1.13983*V;
			G = Y -0.39465*U - 0.58060*V;
			B = Y + 2.03211*U;

			if (R < 0)
				R = 0;
			else if (R > 255)
				R = 255;
			if (G< 0)
				G = 0;
			else if (G> 255)
				G = 255;
			if (B < 0)
				B = 0;
			else if (B > 255)
				B = 255;
		
			rgbImg[j*3*x+(i+1)*3] =  R;
			rgbImg[j*3*x+(i+1)*3 + 1] = G;
			rgbImg[j*3*x+(i+1)*3 + 2] = B;

			Y = Y_buff[(j+1)*x+i];

			R = Y + 1.13983*V;
			G = Y -0.39465*U - 0.58060*V;
			B = Y + 2.03211*U;

			if (R < 0)
				R = 0;
			else if (R > 255)
				R = 255;
			if (G < 0)
				G = 0;
			else if (G> 255)
				G = 255;
			if (B < 0)
				B = 0;
			else if (B > 255)
				B = 255;

			rgbImg[(j+1)*3*x+i*3] =  R;
			rgbImg[(j+1)*3*x+i*3 + 1] = G;
			rgbImg[(j+1)*3*x+i*3 + 2] = B;

			Y = Y_buff[(j+1)*x+(i+1)];

			R = Y + 1.13983*V;
			G = Y -0.39465*U - 0.58060*V;
			B = Y + 2.03211*U;

			if (R < 0)
				R = 0;
			else if (R > 255)
				R = 255;
			if (G< 0)
				G = 0;
			else if (G> 255)
				G = 255;
			if (B < 0)
				B = 0;
			else if (B > 255)
				B = 255;

			rgbImg[(j+1)*3*x+(i+1)*3] =  R;
			rgbImg[(j+1)*3*x+(i+1)*3 + 1] = G;
			rgbImg[(j+1)*3*x+(i+1)*3 + 2] = B;
		}
	}
}

void procesing_YUV420(uchar Y_buff[], char U_buff[], char V_buff[], int x, int y, double Y, double U, double V)
{

	//TO_DO: Implement YUV422 processing
	for (int i = 0; i< x; i += 2)
	{
		for (int j = 0; j<y; j += 2)
		{
			Y_buff[j*x + i] *= Y;
			Y_buff[j*x + i + 1] *= Y;
			Y_buff[(j+1)*x + i] *= Y;
			Y_buff[(j + 1)*x + i + 1] *= Y;

			U_buff[j/2*x / 2 + i / 2] *= U;
			V_buff[j/2*x / 2 + i / 2] *= V;
		}
	}

}

/*******************************************************************************************************************************/
/* Y decimation */
/*******************************************************************************************************************************/
void decimate_Y(uchar Y_buff[], int x, int y)
{
	//Implement Y component decimation
	double Y;
	for (int i = 0; i < x; i += 2)
	{
		for (int j = 0; j < y; j += 2)
		{
			Y = Y_buff[j*x + i];
			Y_buff[j*x + i + 1] = Y;
			Y_buff[(j + 1)*x + i] = Y;
			Y_buff[(j + 1)*x + i + 1] = Y;
		}
	}

}
