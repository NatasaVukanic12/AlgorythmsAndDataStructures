/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    float d = atoi(argv[1]);
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy n infile outfile\n");
        return 1;
    }
    if(d>100.0 || d<0.0){
        fprintf(stderr, "n must be between 0-100.\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
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
    
    int staraS = bi.biWidth;
    int staraV = bi.biHeight;
    bi.biWidth *= d; //nova sirina
    bi.biHeight *= d; //nova visina
    int stariP =  (4 - (staraS * sizeof(RGBTRIPLE)) % 4) % 4; //stari padding
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; //novi padding
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof (RGBTRIPLE)) + padding); //podesavanje velicine slike
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);  //apdejt hedera
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    RGBTRIPLE *buf = malloc(sizeof(RGBTRIPLE) * (bi.biWidth));

    // iterate over infile's scanlines
   // if(d >= 1){
        for (int i = 0; i < abs(staraV); i++){
            int pom = 0;
            for (int j = 0; j < staraS ; j++){
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for(int l = 0; l < d; l++) {
                    *(buf+(pom)) = triple;
                    pom++;
                }
            }
            fseek(inptr, stariP, SEEK_CUR);
            for(int m = 0; m < d; m++){
                fwrite((buf), sizeof(RGBTRIPLE), bi.biWidth, outptr);
                for (int k = 0; k < padding; k++)
                    fputc(0x00, outptr);
            }
        }
    /* else {
        d=d*100;
        int inkr =100 / d;
        for(int i=0;i< abs(staraV); i+=inkr){
            for(int j=0; j<staraS;j+=inkr){
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), inkr, inptr);
                 *buf = triple;
            }
            fseek(inptr, stariP, SEEK_CUR);
             fwrite((buf), sizeof(RGBTRIPLE), bi.biWidth, outptr);
            for (int k = 0; k < padding; k++)
                fputc(0x00, outptr);
        }
    }*/
    free(buf);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
