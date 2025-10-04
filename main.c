#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}
// draw bow
void box_creation(double *cosine, double max, int hTpl, int wTpl, int cTpl, int wImg, int hImg, int cImg, int hLen, int wLen, char output_name[1000], char templateName[1000], unsigned char *Image, unsigned char *img)
{
    unsigned char *new_tpl = uc_arrayNew_1d(hTpl * wTpl);
    for (int i = 0; i < hLen; i++)
    {
        for (int j = 0; j < wLen; j++)
        {
            if (cosine[i * wLen + j] == max)
            {
                for (int k = i; k < i + hTpl; k++)
                {
                    for (int m = j; m < j + wTpl; m++)
                    {
                        new_tpl[(k - i) * wTpl + (m - j)] = img[k * wImg + m];
                        if ((k - i == 0) || (m - j == 0) || (k == i + hTpl - 1) || (m == j + wTpl - 1))
                        {
                            for (int c = 0; c < cImg; c++)
                            {
                                Image[k * wImg * cImg + m * cImg + c] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    stbi_write_png(output_name, wImg, hImg, cImg, Image, wImg * cImg);
    stbi_write_png(templateName, wTpl, hTpl, cTpl, new_tpl, wTpl);
    printf("New image saved to %s\n", output_name);
}
//matching 
void detection(unsigned char *template, unsigned char *img, int wTpl, int hTpl, int cTpl, int wImg, int hImg, int cImg, char output_name[1000], char templateName[1000], unsigned char *Image)
{
    int wLen = wImg - wTpl + 1;
    int hLen = hImg - hTpl + 1;
    double cosine[hLen * wLen];
    double n, I, T;
    double max = 0.0;

    for (int i = 0; i < hLen; i += 5)
    {
        for (int j = 0; j < wLen; j += 5)
        {
            n = 0.0;
            I = 0.0;
            T = 0.0;

            for (int k = i; k < i + hTpl; k++)
            {
                for (int l = j; l < j + wTpl; l++)
                {
                    double imgVal = img[k * wImg + l];
                    double tplVal = template[(k - i) * wTpl + (l - j)];
                    n += (double)imgVal * (double)tplVal;

                    I += template[(k - i) * wTpl + (l - j)] * template[(k - i) * wTpl + (l - j)];
                    T += img[k * wImg + l] * img[k * wImg + l];
                }
            }

            cosine[i * wLen + j] = n / (sqrt(I) * sqrt(T));
            if (cosine[i * wLen + j] > max)
            {
                max = cosine[i * wLen + j];
            }
        }
    }
    box_creation(cosine, max, hTpl, wTpl, cTpl, wImg, hImg, cImg, hLen, wLen, output_name, templateName, Image, img);
}

int main()
{
    int wTpl, hTpl, cTpl;
    char path_template[] = "./templates_gray/tpl_gray0.png";
    unsigned char *Tplgray = stbi_load(path_template, &wTpl, &hTpl, &cTpl, 0);

    int wImg, hImg, cImg;
    char fileName[1000];
    char file[1000];
    char outputName[1000];
    char templateName[1000];

    for (int i = 0; i < 63; i++)
    {
        sprintf(fileName, "./images_gray/img_gray%d.png", i);
        sprintf(templateName, "./templates_gray/tpl_gray%d.png", i + 1);
        sprintf(file, "./images/img%d.jpg", i);

        if (Tplgray == NULL)
        {
            printf("Error in loading the template!");
            exit(1);
        }

        unsigned char *Imggray = stbi_load(fileName, &wImg, &hImg, &cImg, 0);
        unsigned char *Image = stbi_load(file, &wImg, &hImg, &cImg, 0);

        if (Imggray == NULL)
        {
            printf("Error in loading the image!");
            exit(1);
        }

        sprintf(outputName, "./images_detected/img_result%d.png", i);
        detection(Tplgray, Imggray, wTpl, hTpl, cTpl, wImg, hImg, cImg, outputName, templateName, Image);
        Tplgray = stbi_load(templateName, &wTpl, &hTpl, &cTpl, 0);
    }
}