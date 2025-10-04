#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}
// convert image to gray image
unsigned char *convert_to_gray(unsigned char *pic, int w, int h, int c)
{
    unsigned char *grayPic = uc_arrayNew_1d(w * h);
    float red, green, blue;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            red = pic[i * w * c + j * c];
            green = pic[i * w * c + j * c + 1];
            blue = pic[i * w * c + j * c + 2];
            grayPic[i * w + j] = 0.30 * red + 0.59 * green + 0.11 * blue;
        }
    }
    return grayPic;
}
//create gray template
void gray_template()
{
    int wTpl, hTpl, cTpl;

    char path_template[] = "./template/template.jpg";
    unsigned char *template = stbi_load(path_template, &wTpl, &hTpl, &cTpl, 0);

    if (template == NULL)
    {
        printf("\nError in loading the template!");
        exit(1);
    }
    printf("%d %d\n", wTpl, hTpl);

    unsigned char *template1D = convert_to_gray(template, wTpl, hTpl, cTpl);

    char save_template_path[] = "./templates_gray/tpl_gray0.png";
    stbi_write_png(save_template_path, wTpl, hTpl, 1, template1D, wTpl);
}
//create gray image
void gray_images()
{
    int wImg, hImg, cImg;

    char path_img[] = "./images/template.jpg";
    unsigned char *imgTest;

    char file_name[1000];
    char file_nameSave[1000];

    for (int i = 0; i < 63; i++)
    {
        sprintf(file_name, "./images/img%d.jpg", i);
        unsigned char *img = stbi_load(file_name, &wImg, &hImg, &cImg, 0);

        if (img == NULL)
        {
            printf("\nError in loading the image!");
            exit(1);
        }
        unsigned char *imgGray = convert_to_gray(img, wImg, hImg, cImg);

        sprintf(file_nameSave, "./images_gray/img_gray%d.png", i);
        stbi_write_png(file_nameSave, wImg, hImg, 1, imgGray, wImg);
    }
}

int main()
{
    gray_template();
    gray_images();
    return 0;
}