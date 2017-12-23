#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

#define NUMTHREADS 4

struct threadParams {
    int** image;
    int threadnumber;
    int imageWidth;
    int imageHeight;
};

double scalex(int x, int imageWidth)
{
    double xd = (double)x;
    xd = (xd * 3.5) / imageWidth;
    xd = xd - 2.5;
    return xd;
}

double scaley(int y, int imageHeight)
{
    double yd = (double)y;
    yd = (yd * 2) / imageHeight;
    yd = yd - 1;
    return yd;
}

void* mandelbrot(void *a){

    struct threadParams* args = a;

    if(args->threadnumber == 0){
        for(int i0 = 0; i0 < args->imageHeight; i0 += 4){
            double x0 = 0.0;
            double y0 = 0.0;
            int iter0 = 0;
            double temp0 = 0.0;
            double xNOT0 = 0.0;
            double yNOT0 = 0.0;

            for (int j0 = 0; j0 < args->imageWidth; j0 ++){

                xNOT0 = scalex(j0, args->imageWidth);
                yNOT0 = scaley(i0, args->imageHeight);

                while((x0 * x0 + y0 * y0) < 4 && iter0 < 50){
                    temp0 = x0 * x0 - y0 * y0 + xNOT0;
                    y0 = 2 * x0 * y0 + yNOT0;
                    x0 = temp0;
                    iter0 ++;
                }

                if(iter0 == 50){
                    args->image[i0][j0] = 1;
                }

                x0 = 0.0;
                y0 = 0.0;
                iter0 = 0;
            }
        }
    }
    if(args->threadnumber == 1){
        for(int i1 = 1; i1 < args->imageHeight; i1 += 4){
            double x1 = 0.0;
            double y1 = 0.0;
            int iter1 = 0;
            double temp1 = 0.0;
            double xNOT1 = 0.0;
            double yNOT1 = 0.0;

            for (int j1 = 0; j1 < args->imageWidth; j1 ++){

                xNOT1 = scalex(j1, args->imageWidth);
                yNOT1 = scaley(i1, args->imageHeight);

                while(x1 * x1 + y1 * y1 < 4 && iter1 < 50){
                    temp1 = x1 * x1 - y1 * y1 + xNOT1;
                    y1 = 2 * x1 * y1 + yNOT1;
                    x1 = temp1;
                    iter1 ++;
                }

                x1 = 0.0;
                y1 = 0.0;

                if(iter1 == 50){
                    args->image[i1][j1] = 1;
                }

                iter1 = 0;
            }
        }
    }
    if(args->threadnumber == 2){
        for(int i2 = 2; i2 < args->imageHeight; i2 += 4){
            double x2 = 0.0;
            double y2 = 0.0;
            int iter2 = 0;
            double temp2 = 0.0;
            double xNOT2 = 0.0;
            double yNOT2 = 0.0;

            for (int j2 = 0; j2 < args->imageWidth; j2 ++){

                xNOT2 = scalex(j2, args->imageWidth);
                yNOT2 = scaley(i2, args->imageHeight);

                while(x2 * x2 + y2 * y2 < 4 && iter2 < 50){
                    temp2 = x2 * x2 - y2 * y2 + xNOT2;
                    y2 = 2 * x2 * y2 + yNOT2;
                    x2 = temp2;
                    iter2 ++;
                }

                if(iter2 == 50){
                    args->image[i2][j2] = 1;
                }

                x2 = 0.0;
                y2 = 0.0;
                iter2 = 0;
            }
        }
    }
    if(args->threadnumber == 3){
        for(int i3 = 3; i3 < args->imageHeight; i3 += 4){
            double x3 = 0.0;
            double y3 = 0.0;
            int iter3 = 0;
            double temp3 = 0.0;
            double xNOT3 = 0.0;
            double yNOT3 = 0.0;

            for (int j3 = 0; j3 < args->imageWidth; j3 ++){

                xNOT3 = scalex(j3, args->imageWidth);
                yNOT3 = scaley(i3, args->imageHeight);

                while(x3 * x3 + y3 * y3 < 4 && iter3 < 50){
                    temp3 = x3 * x3 - y3 * y3 + xNOT3;
                    y3 = 2 * x3 * y3 + yNOT3;
                    x3 = temp3;
                    iter3 ++;
                }

                if(iter3 == 50){
                    args->image[i3][j3] = 1;
                }

                x3 = 0.0;
                y3 = 0.0;
                iter3 = 0;
            }
        }
    }
    
    return 0;
        
}

int main(int argc, char *argv[])
{
    int imageWidth = 350;

    if(argc > 2){
        fprintf(stderr, "%s\n", "Invalid argument format.");
        exit(1);
    }
    if(argc == 2){
        if(sscanf(argv[1], "%d", &imageWidth) != 1){
            fprintf(stderr, "%s\n", "Invalid argument format.");
            exit(1);
        }
    }

    int imageHeight = (imageWidth * 4) / 7;

    int **image = malloc(imageHeight*sizeof(int*));

    for(int i = 0; i < imageHeight; i++){
        image[i] = malloc(imageWidth*sizeof(int));
        for (int j = 0; j < imageWidth; j++){
            image[i][j] = 0;
        }
    }

    struct threadParams threadparams[NUMTHREADS];

    pthread_t thread_id[NUMTHREADS];

    for(int i = 0; i < NUMTHREADS; i ++){
        threadparams[i].threadnumber = i;
        threadparams[i].imageWidth = imageWidth;
        threadparams[i].imageHeight = imageHeight;
        threadparams[i].image = image;
        pthread_create(&thread_id[i], NULL, mandelbrot, &threadparams[i]);
    }

    for(int i = 0; i < NUMTHREADS; i ++){
        pthread_join(thread_id[i], NULL);
    }

    FILE *fp;
    fp = fopen("ParallelMandelbrot.pbm", "w");

    fprintf(fp, "%s\n%d %d\n", "P1", imageWidth, imageHeight);
    for(int i = 0; i < imageHeight; i++){
        for (int j = 0; j < imageWidth; j++){
            fprintf(fp, "%d ", image[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return 0;
}