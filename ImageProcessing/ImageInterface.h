#include "ImageTypes.h"

extern int ReadImage (char *FileName, Image *I) ;
/*    Function: Reads in the image I (greylevel or color) from File
      Preconditions: None 
      Postconditions: All image pixels are read in and the image width
      and height recorded in the appropriate fields. If the image is a
      grey level one, then all the three color values of each pixel is
      set to intensity values of that pixel. It returns 1 for success
      and 0 for failure.
      ----------------------------------------------------------------*/

extern int SaveImage (char *FileName, Image *I) ;
/*    Function: Write out the Image to the File in PPM format
      Preconditions: Image must have size set
      Postconditions: The written image file is in PPM format. Returns 
      1 if successful, 0 if not.
      ----------------------------------------------------------------*/

extern Color GetPixel (Image *I, int Row, int Col) ;
/*    Function: Returns the pixel value at I->Pixels(Row,Col). Returns
      all red, green, and blue as 0 if (Row,Col) is out of bounds.
      Preconditions: Image must have size set
      Postconditions: Image not affected.
      ----------------------------------------------------------------*/

extern int SetPixel (Image *I, int Row, int Col, Color Value) ;
/*    Function: Sets the pixel value at I->Pixels(Row,Col)
      Preconditions: Image must have size set
      Postconditions: Image pixel at (Row,Col) modified to Value. Returns
      0 if the (Row,Col) falls outside the image and 1 otherwise.
      ----------------------------------------------------------------*/

extern int GetSize (Image *I, int *NRow, int *NCol) ;
/*    Function: Returns the total number of Rows and Columns in the Image
      Preconditions: Image must have size set
      Postconditions: The values are returned through the procedure 
      parameters. It returns 1 for success and 0 for failure.
      ----------------------------------------------------------------*/

extern int SetSize (Image *I, int NRow, int NCol) ;
/*    Function: Sets the total number of Rows and Columns in the Image
      Preconditions: None
      Postconditions: The values are return through the Image parameter. 
      It returns 1 for success and 0 for failure.
      ----------------------------------------------------------------*/

extern int InBounds (Image *I, int Row, int Col) ;
/*    Function: Returns 1 if the pixel (Row, Col) is inside the image 
      boundary, return 0, otherwise.
      Preconditions: Image must have size set
      Postconditions: None
      ----------------------------------------------------------------*/
