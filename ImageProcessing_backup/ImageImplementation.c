#include <strings.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ImageInterface.h"

/*------------------------------------------------------------------*/

int ReadImage (char *FileName, Image *I)
{
  FILE *fp ;
  int row, col, temp, NRows, NCols ;
  char str[50] ;
  Color clr ;

  // Attempt to open the file containing the image data
  fp = fopen(FileName, "r") ;
  if (fp == NULL )
    {
      fprintf(stderr, "\n Could not open file: %s\n",FileName) ;
      return(0) ;
    }

  // Read Image file data. 
  fscanf(fp,"%s",str) ;
  if(strcmp(str,"P6") == 0)
    {
      // Scan image size and set this information
      fscanf(fp, "%d %d ", &NCols, &NRows) ;
      fscanf(fp, "%d ", &temp) ;

      SetSize(I,NRows,NCols) ;
      
      // Now that I know the image dimensions I can dimension the
      // array of pixels
      I->Pixel = malloc(NCols*NRows*sizeof(Color)) ;
			
      for(row=0; row<NRows; row++)
	{
	  for(col=0; col<NCols; col++)
	    {
	      clr.red = (unsigned char) (getc(fp)) ;
	      clr.green = (unsigned char) (getc(fp)) ;
	      clr.blue = (unsigned char) (getc(fp)) ;
	       
	      SetPixel(I,row,col,clr) ;
	    }
	}
      fclose(fp) ;			
    }
  else
    {
      fprintf(stderr, "\n Image in %s is not in a recognized format: %s\n",FileName) ;
      return(0) ;
    }

  return(1) ;
}

/*------------------------------------------------------------------*/

int SaveImage (char *FileName, Image *I) 
{
  FILE *fp ;
  int row,col,NRows,NCols ;
  Color clr ;

  fp = fopen(FileName,"w") ;
  if(fp==NULL)
    {
      fprintf(stderr, "\n Could not open file for writing: %s\n",FileName) ;
      return(0) ;
    }

  GetSize(I,&NRows,&NCols) ;

  fprintf(fp, "P6\n") ;
  fprintf(fp, "%d %d\n255\n",NCols,NRows) ;
  for(row=0; row<NRows; row++)
    {
      for(col=0; col<NCols; col++)
	{
	  clr=GetPixel(I,row,col) ;
	  putc((unsigned char)(clr.red), fp) ;
	  putc((unsigned char)(clr.green), fp) ;
	  putc((unsigned char)(clr.blue), fp) ;

	}
    }
  fclose(fp) ;


  return(1) ; 
}

/*------------------------------------------------------------------*/

Color GetPixel (Image *I, int Row, int Col) 
{
  Color Value ;

  if(InBounds(I,Row,Col))
    {
      int slot = Row*(I->NCols)+Col ;
      Value.red = (&(I->Pixel)[slot])->red ;
      Value.green =(&(I->Pixel)[slot])->green ;
      Value.blue =(&(I->Pixel)[slot])->blue ;
    }
  else
    {
      Value.red = 0 ;
      Value.green = 0 ;
      Value.blue = 0 ;
    }
  return(Value) ;
}

/*------------------------------------------------------------------*/

int SetPixel (Image *I, int Row, int Col, Color Value) 
{
  
  if(InBounds(I,Row,Col))
    {
      int slot = Row*(I->NCols)+Col ;
      (&(I->Pixel)[slot])->red = Value.red ;
      (&(I->Pixel)[slot])->green = Value.green ;
      (&(I->Pixel)[slot])->blue = Value.blue ;
    }
  else
    {
      return(0) ;
    }
  return(1) ;
}

/*------------------------------------------------------------------*/

int GetSize (Image *I, int *NRow, int *NCol) 
{

  if(I!=NULL)
    {
      *NRow = I->NRows ;
      *NCol = I->NCols ;
    }
  else
    {
      return(0) ;
    }

  return(1) ;
}

/*------------------------------------------------------------------*/

int SetSize (Image *I, int NRow, int NCol) 
{
  if(I != NULL)
    {
      I->NRows = NRow ;
      I->NCols = NCol ;
      I->Pixel = malloc(NRow*NCol*sizeof(Color)) ;
    }
  else
    {
      return(0) ;
    }

  return(1) ;
}

/*------------------------------------------------------------------*/

int InBounds (Image *I, int Row, int Col) 
{
  if(Row < 0 || Row >= I->NRows)
    {
      return(0) ;
    }
  else if(Col < 0 || Col >= I->NCols)
    {

      return(0) ;
    }
  return(1) ;
}
