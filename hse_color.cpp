// This sample code reads in image data from a RAW image file and // writes it into another file// NOTE:	The code assumes that the image is of size 256 x 256 and is in the//			RAW format. You will need to make corresponding changes to//			accommodate images of different sizes and/or types#include <stdio.h>#include <iostream>#include <stdlib.h>#include <math.h>using namespace std;int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size1;	int Size2;	// Check for proper syntax	if (argc < 3) {		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel] [Size1] [Size2] output_final.raw" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4) {		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5) {			Size1 = atoi(argv[4]);			Size2 = atoi(argv[5]);		}	}	// Allocate image data array	unsigned char Imagedata[Size1][Size2][BytesPerPixel];	unsigned char Image[Size1][Size2][BytesPerPixel];	unsigned char Imagell[Size1][Size2][BytesPerPixel];	double nop1[256], nop2[256], nop3[256];	double sum = 0;	double pm1[256], pm2[256], pm3[256];	double cpm1[256], cpm2[256], cpm3[256];	int im1[256], im2[256], im3[256];	double temp1 = 0;	double temp2 = 0;	double temp3 = 0;	int n = 200;	// Read image (filename specified by first argument) into image data matrix	if (!(file = fopen(argv[1], "rb"))) {		cout << "Cannot open file: " << argv[1] << endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////	for (int k = 0; k < 256; k++) {		int count1 = 0;		int count2 = 0;		int count3 = 0;		for (int i = 0; i < Size1; i++) {			for (int j = 0; j < Size2; j++) {				if (Imagedata[i][j][0] == k) {					count1++;				}				if (Imagedata[i][j][1] == k) {					count2++;				}				if (Imagedata[i][j][2] == k) {					count3++;				}			}		}		nop1[k] = count1;		nop2[k] = count2;		nop3[k] = count3;		sum += count1;	}	for (int k = 0; k < 256; k++) {		pm1[k] = nop1[k] / sum;		pm2[k] = nop2[k] / sum;		pm3[k] = nop3[k] / sum;		temp1 += pm1[k];		temp2 += pm2[k];		temp3 += pm3[k];		cpm1[k] = temp1;		cpm1[k] *= n;		cpm2[k] = temp2;		cpm2[k] *= n;		cpm3[k] = temp3;		cpm3[k] *= n;		im1[k] = cpm1[k];		im2[k] = cpm2[k];		im3[k] = cpm3[k];		//cout << cpm[k] <<"   "<< im[k] << endl;	}	for (int k = 0; k < 256; k++) {		for (int i = 0; i < Size1; i++) {			for (int j = 0; j < Size2; j++) {				if (Imagedata[i][j][0] == k) {					Image[i][j][0] = im1[k];				}				if (Imagedata[i][j][1] == k) {					Image[i][j][1] = im2[k];				}				if (Imagedata[i][j][2] == k) {					Image[i][j][2] = im3[k];				}			}		}	}	float Sat;	double Hue;	double b;	double g;	double r;	//unsigned char M_temp;	//unsigned char m_temp;	unsigned char HImage[Size1][Size2];	unsigned char SImage[Size1][Size2];	unsigned char LImage[Size1][Size2];	unsigned char L1Image[Size1][Size2];	double h;	double s;	double l;	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////	for (int i = 0; i < Size1; i++) {		for (int j = 0; j < Size2; j++) {			r = (double)Imagedata[i][j][0] / 255;			g = (double)Imagedata[i][j][1] / 255;			b = (double)Imagedata[i][j][2] / 255;			double M = max(r, max(g, b));			//cout << "M:" << M << endl;			double m = min(r, min(g, b));			//m /= 255;			//cout << "m:" << m << endl;			double C = M - m;			double Lum = (M + m) / 2;			//cout << "Lum:" << Lum << endl;			if (C == 0) {				Hue = 0;				Sat = 0;			}			if (Lum > 0 && Lum < 0.5) {				Sat = C / (2 * Lum);			}			else {				Sat = C / (2 - (2 * Lum));			}			//cout << (double)Imagedata[0][0][2] / 255 << endl;			//cout<< r << endl;			if (M == r) {				Hue = 60 * (fmod(((g - b) / C), 6));			}			else if (M == g) {				Hue = 60 * (((b - r) / C) + 2);			}			else if (M == b) {				Hue = 60 * (((r - g) / C) + 4);			}			//cout << "Hue:" << Hue << endl;			HImage[i][j] = (Hue / 360.0)*255.0;			SImage[i][j] = Sat * 255;			LImage[i][j] = Lum * 255;		}	}	double nop[256];	double sum11 = 0;	double pm[256];	double cpm[256];	int im[256];	double temp = 0;	for (int k = 0; k < 256; k++) {		int count = 0;		for (int i = 0; i < Size1; i++) {			for (int j = 0; j < Size2; j++) {				if (LImage[i][j] == k) {					count++;				}			}		}		nop[k] = count;		sum11 += count;	}	for (int k = 0; k < 256; k++) {		pm[k] = nop[k] / sum11;		temp += pm[k];		cpm[k] = temp;		cpm[k] *= 255;		im[k] = cpm[k];		//cout << cpm[k] <<"   "<< im[k] << endl;	}	for (int k = 0; k < 256; k++) {		for (int i = 0; i < Size1; i++) {			for (int j = 0; j < Size2; j++) {				if (LImage[i][j] == k) {					L1Image[i][j] = im[k];				}			}		}	}	double c;	double x;	double m1;	double rr;	double gg;	double bb;	for (int i = 0; i < Size1; i++) {		for (int j = 0; j < Size2; j++) {			h = (double)HImage[i][j] * (360.0 / 255.0);			s = (double)SImage[i][j] / 255.0;			l = (double)L1Image[i][j] / 255.0;			c = (1 - fabs(2.0*l - 1))*s;			x = c*(1 - fabs(fmod((h / 60), 2) - 1));			m1 = l - c / 2;			if (h >= 0 && h < 60) {				rr = c;				gg = x;				bb = 0;			}			else if (h >= 60 && h < 120) {				rr = x;				gg = c;				bb = 0;			}			else if (h >= 120 && h < 180) {				rr = 0;				gg = c;				bb = x;			}			else if (h >= 180 && h < 240) {				rr = 0;				gg = x;				bb = c;			}			else if (h >= 240 && h < 300) {				rr = x;				gg = 0;				bb = c;			}			else {				rr = c;				gg = 0;				bb = x;			}			Imagell[i][j][0] = (rr + m1) * 255;			Imagell[i][j][1] = (gg + m1) * 255;			Imagell[i][j][2] = (bb + m1) * 255;		}	}	// Write image data (filename specified by second argument) from image data matrix	if (!(file = fopen(argv[2], "wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(Image, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);	if (!(file = fopen(argv[6], "wb"))) {		cout << "Cannot open file: " << argv[6] << endl;		exit(1);	}	fwrite(Imagell, sizeof(unsigned char), Size1*Size2*BytesPerPixel, file);	fclose(file);	return 0;}