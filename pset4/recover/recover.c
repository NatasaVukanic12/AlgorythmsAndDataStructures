#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    
    if(argc != 2){
        fprintf(stderr, "Usage: ./recover image.\n");
        return 1;
        
    }
    FILE *file = fopen(argv[1], "r");
    char *infile = argv[1];
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    FILE *outptr;
    unsigned char buff[512];
    int foundNumb = 0;
    int foundJPG = 0;
    do {
        if(buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff && (buff[3] == 0xe0 || buff[3] == 0xe1)) {
            foundNumb += 1;
            char str[7];
            sprintf(str, "%.3d.jpg", foundNumb); 
            if(foundJPG != 0) {
                fclose(outptr);
            }
            outptr = fopen(str, "w");
            foundJPG = 1;
        }
        if(foundJPG == 1){
            fwrite(buff, 512, 1, outptr);
        }
    } while(fread(buff, 1, 512, file) == 512);
    return 0;
}