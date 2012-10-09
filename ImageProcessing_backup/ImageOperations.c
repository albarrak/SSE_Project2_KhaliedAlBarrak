#include <strings.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ImageInterface.h"
#include "ImageOperations.h"
#include "UnionFindInterface.h"

/*-----------------------------------------------------------------------*/

int ImageAvgStdDev(Image *I,float *RedAvg, float *GreenAvg, float *BlueAvg,
		            float *RedStd, float *GreenStd, float *BlueStd)
{
  /* The following routine takes an image as input and returns the 
  red, gree, and blue average and standard deviation. The formulas 
  used here are standard statistics

    avg = sum ( x(i) ) / N
    stdev = sqrt ( ( x(i) - avg )^2 / (n-1) ) */

  int row, col, NRows, NCols, temp ;
  float RedSum, GreenSum, BlueSum, total, tmpcolor;
  Color clr ;

  /* Get sample image size */
  GetSize(I,&NRows,&NCols) ;

  /* Get total number of pxels as a float */
  temp = NRows*NCols ;
  total = (float)temp ;

  /* Here the sum values represent sum ( x(i) ) */
  RedSum = 0.0 ;
  GreenSum = 0.0 ;
  BlueSum = 0.0 ;

  for (row=0; row<NRows; row++)
    {
      for (col=0; col<NCols; col++)
	{
	  clr = GetPixel(I,row,col) ;
	  RedSum += (float)(clr.red) ;
	  GreenSum += (float)(clr.green) ;
	  BlueSum += (float)(clr.blue) ;
	}
    }

  /* Compute Averages */
  *RedAvg = RedSum / total ;
  *GreenAvg = GreenSum / total ;
  *BlueAvg = BlueSum / total ;

  /* Now the sum variables will represent sum ( x(i) - avg )^2 */
  RedSum = 0.0 ;
  GreenSum = 0.0 ;
  BlueSum = 0.0 ;

  for (row=0; row<NRows; row++)
    {
      for (col=0; col<NCols; col++)
	{
	  clr = GetPixel(I,row,col) ;
	  RedSum += sq((float)(clr.red)-*RedAvg) ;
	  GreenSum += sq((float)(clr.green)-*GreenAvg) ;
	  BlueSum += sq((float)(clr.blue)-*BlueAvg) ;
	}
    }

  /* Compute Standard Deviation */
  *RedStd = sqrt(RedSum/(total-1.0)) ;
  *GreenStd = sqrt(GreenSum/(total-1.0)) ;
  *BlueStd = sqrt(BlueSum/(total-1.0)) ;

}

/*-----------------------------------------------------------------------*/

float sq(float x)
{
  /* A simple function that takes a float and returns its square. */
  return(x*x) ;
}

/*-----------------------------------------------------------------------*/

int ThresholdImage(Image *In,float RedAvg,float GreenAvg,float BlueAvg,
                             float RedStd,float GreenStd,float BlueStd,
		             int ThresholdValue,Image *Out)
{
  /* The function takes as input

     1) an input image
     2) average and standard deviation data for red, green, and blue
     3) a threshold value

  and returns a thresholded image. Each pixel is thresholded by the
  formula given in the assignment handout.

  http://figment.csee.usf.edu/~sarkar/DataStructures/Assignment1.pdf */
     
  int row, col, NRows, NCols ;
  Color clr ;
  float red,green,blue,tmpvalue ;

  /* Get size of input Image */
  GetSize(In,&NRows,&NCols) ;

  for (row=0; row<NRows; row++)
    {
      for (col=0; col<NCols; col++)
	{
	  /* for each pixel, get the color */
	  clr=GetPixel(In,row,col) ;

	  /* calculate the value to threshold */
	  red=sq((float)(clr.red)-RedAvg)/sq(RedStd) ;
	  green=sq((float)(clr.green)-GreenAvg)/sq(GreenStd) ;
	  blue=sq((float)(clr.blue)-BlueAvg)/sq(BlueStd) ;
	  tmpvalue = red + green + blue ;

	  /* compare this value versus the threshold */
	  if(tmpvalue < (float)(ThresholdValue))
	    {
	      clr.red = 0 ;
	      clr.green = 0 ;
	      clr.blue = 0 ;
	    }
	  else
	    {
	      clr.red = 255 ;
	      clr.green = 255 ;
	      clr.blue = 255 ;
	    }

	  /* Write the new pixel to the output image */
	  SetPixel(Out,row,col,clr) ;
	}
    }

}

/*-----------------------------------------------------------------------*/

int RemoveBackground(Image *thresholded_image)
{

  // Dimension Space for label image and LabelSets
  Image *label_image = malloc(sizeof(Image)) ;
  UnionFind *LabelSets = malloc(sizeof(UnionFind)) ;

  if(LabelSets == NULL || label_image == NULL)
    {
      return(0) ;
    }

  // Create the Union Find to have 255 distinct sets
  UFCreate(255,LabelSets) ;

  int A[4],i,j,k,row,col ;

  GetSize(thresholded_image,&row,&col) ;
  SetSize(label_image,row,col) ;

  // Initialize the label image to 0
  Color clr,pixel ;
  for(i=0;i<row;i++)
    {
      for(j=0;j<col;j++)
	{
	  clr.red=0 ;
	  clr.blue=0 ;
	  clr.green=0 ;
	  SetPixel(label_image,i,j,clr) ;
	}
    }
  
  // LabelCounter will count how many labels I have set
  int LabelCounter=1 ;

  // Loop over the inner rows and columns
  for(i=1;i<row-1;i++)
    {
      for(j=1;j<col-1;j++)
	{
	  // For each inner pixel, check to see if it is a 
          // background pixel
	  clr = GetPixel(thresholded_image,i,j) ;

	  if(clr.red != 0)
	    {

	      // If it then get the labels of the pixels in the
	      // 1,2,3,4 positions. These get stored in the A array.
	      pixel=GetPixel(label_image,i-1,j-1) ;
	      A[0]=pixel.red ;
	      
	      pixel=GetPixel(label_image,i-1,j) ;
	      A[1]=pixel.red ;

	      pixel=GetPixel(label_image,i-1,j+1) ;
	      A[2]=pixel.red ;

	      pixel=GetPixel(label_image,i,j-1) ;
	      A[3]=pixel.red ;

	      // Now count how many zero labels you have and find the 
	      // minimum non-zero label.
	      int zerocount=0 ;
	      int minval = 255 ;

	      for(k=0;k<4;k++)
		{
		  if(A[k]==0)
		    {
		      zerocount++ ;
		    }
		  else
		    {
		      if(A[k] < minval)
			{
			  minval = A[k] ;
			}
		    }
		}

	      // if all the labels are zero, then the i,jth pixel is 
	      // set to a new label
	      if(zerocount==4)
		{
		  pixel.red = LabelCounter ;
		  SetPixel(label_image,i,j,pixel) ;
		  LabelCounter++ ;
		}
	      else
		{

		  // if there are non-zero labels then set the pixel's
		  // label to the smallest non-zero one. Union the sets
		  // as you go also.
		  pixel.red = minval ;
		  SetPixel(label_image,i,j,pixel) ;
		  for(k=0;k<4;k++)
		    {
		      if(A[k] != 0 && A[k] != minval)
			{
			  UFUnion(A[k],minval,LabelSets) ;
			}
		    }
		}
	      
	    }
	}
    }

  // Find which label each pixel should be. Keep a count of how many of
  // each label are used
  int label[255] ;
  for(i=0;i<255;i++)
    {
      label[i]=0 ;
    }

  for(i=0;i<row;i++)
    {
      for(j=0;j<col;j++)
	{
	  pixel = GetPixel(label_image,i,j) ;
	  if(pixel.red != 0)
	    {

	      label[UFFind(pixel.red, LabelSets)]++ ;
	      pixel.red = (5*(1+UFFind(pixel.red, LabelSets)))%255 ;
	      pixel.green = (5*pixel.red)%255 ;
	      pixel.blue = (10*pixel.red)%255 ;
	      SetPixel(label_image, i, j, pixel) ;
	    }
	}
    }

  // Which label represents the majority of non-background pixels
  int max = 0 ;
  int maxi = -1 ;
  int secondi = -1 ;

  for(i=0;i<255;i++)
    {
      if(label[i] > max)
	{
	  secondi = maxi ;
	  max = label[i] ;
	  maxi = i ;
	}
    }

  // Write out the color if it is not the largest label or if it is a 
  // background pixel.
  secondi = (5*(1+maxi))%255 ;
  for(i=0;i<row;i++)
    {
      for(j=0;j<col;j++)
	{
	  pixel=GetPixel(label_image,i,j) ;
	  if(pixel.red != secondi && pixel.red != 0)
	    {
	      pixel.red=0 ;
	      pixel.blue=0 ;
	      pixel.green=0 ;
	      SetPixel(thresholded_image, i, j, pixel) ;
	    }
	  else
	    {
	      pixel.red=255 ;
	      pixel.blue=255 ;
	      pixel.green=255 ;
	      SetPixel(thresholded_image, i, j, pixel) ;
	    }
	}
    }

  // free up some memory declared here.
  free(label_image) ;
  free(LabelSets) ;

  return(1) ;
}
