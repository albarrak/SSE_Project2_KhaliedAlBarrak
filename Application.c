#include <strings.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "UnionFindInterface.h"
#include "ForestInterface.h"
#include "ImageInterface.h"
#include "ImageOperations.h"

int main(int argc, char **argv)
{

  // Check command usage
  if(argc != 5)
    {
      fprintf(stderr,"\nUsage: \n%s SampleImageFile InputImageFile OutputImageFile ThresholdValue\n\n",argv[0]) ;
      return(1) ;
    }


  //Dimension images to be used, test for successful memory allocation
  Image *sample_image, *input_image, *thresholded_image ;

  sample_image = malloc(sizeof(Image)) ;
  input_image = malloc(sizeof(Image)) ;
  thresholded_image = malloc(sizeof(Image)) ;

  if(sample_image == NULL || input_image == NULL || 
     thresholded_image == NULL)
    {
      fprintf(stderr,"Error: Unsuccessful memory allocation\n") ;
      return(1) ;
    }


  // Find Sample Image's Avg, and StDev
  int ThresholdValue ;
  Color clr ;
  float RedAvg,GreenAvg,BlueAvg,RedStd,GreenStd,BlueStd ;

  ReadImage(argv[1],sample_image) ;

  ImageAvgStdDev(sample_image,&RedAvg,&GreenAvg,&BlueAvg,
                             &RedStd,&GreenStd,&BlueStd) ;


  // Read image to Threshold and set Output Image Size
  int row, col ;
  ReadImage(argv[2],input_image) ;
  GetSize(input_image,&row,&col) ;
  SetSize(thresholded_image,row,col) ;


  // Threshold Image and Write to Output image file 
  ThresholdValue = atoi(argv[4]) ;
  ThresholdImage(input_image,RedAvg,GreenAvg,BlueAvg,RedStd,
                 GreenStd,BlueStd,ThresholdValue,thresholded_image) ;

  // Remove backgrounds using UnionFind
  RemoveBackground(thresholded_image) ;

  // Save the image
  SaveImage(argv[3],thresholded_image) ;

return 0;  
}
