typedef struct color 
{
  int red,green,blue ;
} Color;

typedef struct image
{
  int NRows, NCols ; // Stores the number of rows and cols in an image  
  Color *Pixel ;     // Point to 1D array for pixel color storage
} Image ;
