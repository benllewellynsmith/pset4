/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    int choice;
    printf("choice? (clue:its option 9!)");
    choice=get_int();
    printf("\n");
    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // open input file -----------------------------------------------------
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file  -----------------------------------------------------
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //float noof_rs=0;
    // float noof_pixels=0;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

/* trying all 9 combinations
*/

            switch(choice) {

               case 1:
                    /////////////////////////////////////// 1NO RED
                    if (triple.rgbtRed == 0x00){
                     //noof_rs++;
                     //printf("red");
                     triple.rgbtRed = 0xFF;
                     triple.rgbtGreen = 0x00;
                     triple.rgbtBlue = 0x00;
                    }
                  break; /* optional */

               case 2:
            /////////////////////////////////////// 2NO GREEN
            if (triple.rgbtGreen == 0x00){
             //printf("red");
             triple.rgbtRed = 0x00;
             triple.rgbtGreen = 0xFF;
             triple.rgbtBlue = 0x00;
            }
            break; /* optional */

               case 3:
            /////////////////////////////////////// 3NO BLUE
            if (triple.rgbtBlue > 0x00){
             //printf("red");
             triple.rgbtRed = 0x00;
             triple.rgbtGreen = 0x00;
             triple.rgbtBlue = 0xFF;
            }else{
            triple.rgbtRed = 0xFF;
             triple.rgbtGreen = 0xFF;
             triple.rgbtBlue = 0xFF;
            }
            break; /* optional */

               case 4:
            /////////////////////////////////////// 4some RED
            if (triple.rgbtRed > 0x00){
             //noof_rs++;
             //printf("red");
             triple.rgbtRed = 0xFF;
             triple.rgbtGreen = 0x00;
             triple.rgbtBlue = 0x00;
            }
            break; /* optional */

               case 5:
            /////////////////////////////////////// 5some GREEN
            if (triple.rgbtGreen > 0x00){
             //printf("red");
             triple.rgbtRed = 0x00;
             triple.rgbtGreen = 0xFF;
             triple.rgbtBlue = 0x00;
            }
            break; /* optional */

               case 6:
            /////////////////////////////////////// 6some BLUE
            if (triple.rgbtBlue > 0x00){
             //printf("red");
             triple.rgbtRed = 0x00;
             triple.rgbtGreen = 0x00;
             triple.rgbtBlue = 0xFF;
            }
            break; /* optional */

               case 7:
            /////////////////////////////////////// 7 not FULL red xxxxxxxx
            if (triple.rgbtRed < 0xFF){
             //noof_rs++;
             //printf("red");
             triple.rgbtRed = 0xFF;
             triple.rgbtGreen = 0xFF;
             triple.rgbtBlue = 0xFF;
            }
            break; /* optional */

               case 8:
            /////////////////////////////////////// 8 amplify green
            if (triple.rgbtGreen > 0x00){
             //printf("red");
             triple.rgbtRed = 0x00;
             triple.rgbtGreen = 0xFF;
             triple.rgbtBlue = 0x00;
            }else{
            triple.rgbtRed = 0xFF;
             triple.rgbtGreen = 0xFF;
             triple.rgbtBlue = 0xFF;
            }
            break; /* optional */

                case 9:
            // eliminate pure red pixels by whitening them
            if (triple.rgbtRed == 0xFF){

                triple.rgbtRed = 0xFF;
                triple.rgbtGreen = 0xFF;
                triple.rgbtBlue = 0xFF;

            }else{

                triple.rgbtRed = 0x00;
                triple.rgbtGreen = 0x00;
                triple.rgbtBlue = 0xFF;

            }
            break; /* optional */

            default : /* Optional */
            //printf("invalid choice\n");
            break;
            }

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    //printf("%.0f red pixels out of %.0f : %.0f%% red\ns", noof_rs, noof_pixels,noof_rs/noof_pixels*100);


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
