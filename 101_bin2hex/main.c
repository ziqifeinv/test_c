#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define DATA_NUM_PER_ROW    16

void print_binary(FILE *fp, uint32_t n)
{
    uint8_t arr[32] = {0};
    int len = 0;
    for(len = 0; len < 32; len++){
        arr[len] = (n&1)+'0';
        n = n>>1;

    }

    len--;
    while (len >= 0 ){
        fprintf(fp,"%c", arr[len]);
        len--;
    }
    fprintf(fp,"\n");
}

int main( int argc, char *argv[] )
{
    char buf[128];
    FILE *fin = NULL, *fout = NULL;
    int i = 0;
    uint8_t val;
    off_t filesize, offset;
    uint32_t data_counter = 0;
    uint8_t fill_zero_num = 0;

    printf("argc:%d, ", argc);
    for (uint8_t i = 0; i < argc; i++) {
        printf("argv[%d]:%s, ", i, argv[i]);
    }
    printf("\n");

    if( ( fin = fopen( argv[1], "rb+" ) ) == NULL ){
        printf("fopen(%s,r) failed\n", argv[1] );
        goto exit;
    }

    if( ( fout = fopen( argv[2], "w+" ) ) == NULL ){
        printf("fopen(%s,w+) failed\n", argv[2] );
        goto exit;
    }

    if( argc > 3){
        filesize = atoi(argv[3]);
    } else{
        if( ( filesize = lseek( fileno( fin ), 0, SEEK_END ) ) < 0 ){
            perror( "lseek" );
            goto exit;
        }
    }

    // //4-byte alignment, fill in zeros if not enough
    // fill_zero_num = filesize % 4;
    // if (fill_zero_num != 0) {
    //     if (fseek(fin, 0, SEEK_END) < 0) {
    //         printf( "fseek(0,SEEK_END) failed\n" );
    //         goto exit;
    //     }
    //     char temp = 0;
    //     if (fwrite(&temp, 1, fill_zero_num, fin) != fill_zero_num) {
    //         printf("fwrite(0,%d) failed\n", fill_zero_num);
    //         goto exit;
    //     }
    //     filesize++;
    // }

    if( fseek( fin, 0, SEEK_SET ) < 0 ){
         printf( "fseek(0,SEEK_SET) failed\n" );
         goto exit;
    }
    memset(buf, 0x0,128);
    for( offset = 0; offset < filesize; offset += 1 ){
        if( fread( buf, 1, 4, fin ) != (size_t) 4 ){
            goto exit;
        }
        for(i = 0; i < 4; i++){
            // val = buf[3-i];
            val = buf[i];
            printf("0x%02x", val);
            fprintf(fout, "0x%02x", val);
            data_counter++;
            if (data_counter == filesize) {
                break;
            }
            if (data_counter % DATA_NUM_PER_ROW != 0) {
                printf(", ");
                fprintf(fout, ", ");
            } else {
                printf(",\n");
                fprintf(fout, ",\n");
            }
        }
    }

exit:
    if(fin){
        fclose(fin);
    }

    if(fout){
        fclose(fout);
    }
    return 0;
}
