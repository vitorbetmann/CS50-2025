#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r, g, b;
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;
            int average = round((r + g + b) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgcpy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imgcpy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imgcpy[i][width - 1 - j];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgcpy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumred = 0, sumgreen = 0, sumblue = 0;
            int counter = 0;

            for (int vshift = -1; vshift <= 1; vshift++)
            {
                for (int hshift = -1; hshift <= 1; hshift++)
                {
                    if (i + vshift >= 0 && j + hshift >= 0 && i + vshift < height &&
                        j + hshift < width)
                    {
                        sumred += image[i + vshift][j + hshift].rgbtRed;
                        sumgreen += image[i + vshift][j + hshift].rgbtGreen;
                        sumblue += image[i + vshift][j + hshift].rgbtBlue;
                        counter++;
                    }
                }
            }

            imgcpy[i][j].rgbtRed = round((float) sumred / counter);
            imgcpy[i][j].rgbtGreen = round((float) sumgreen / counter);
            imgcpy[i][j].rgbtBlue = round((float) sumblue / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imgcpy[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgcpy[height][width];

    int gxarr[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gyarr[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumredx = 0, sumgreenx = 0, sumbluex = 0;
            int sumredy = 0, sumgreeny = 0, sumbluey = 0;
            int counter = 0;

            for (int vshift = -1; vshift <= 1; vshift++)
            {
                for (int hshift = -1; hshift <= 1; hshift++)
                {
                    if (i + vshift >= 0 && j + hshift >= 0 && i + vshift < height &&
                        j + hshift < width)
                    {
                        int redamount = image[i + vshift][j + hshift].rgbtRed;
                        int greenamount = image[i + vshift][j + hshift].rgbtGreen;
                        int blueamount = image[i + vshift][j + hshift].rgbtBlue;

                        sumredx += gxarr[counter] * redamount;
                        sumredy += gyarr[counter] * redamount;

                        sumgreenx += gxarr[counter] * greenamount;
                        sumgreeny += gyarr[counter] * greenamount;

                        sumbluex += gxarr[counter] * blueamount;
                        sumbluey += gyarr[counter] * blueamount;
                    }
                    counter++;
                }
            }

            int gradred = round(sqrt(pow(sumredx, 2) + pow(sumredy, 2)));
            int gradgreen = round(sqrt(pow(sumgreenx, 2) + pow(sumgreeny, 2)));
            int gradblue = round(sqrt(pow(sumbluex, 2) + pow(sumbluey, 2)));

            imgcpy[i][j].rgbtRed = gradred < 255 ? gradred : 255;
            imgcpy[i][j].rgbtGreen = gradgreen < 255 ? gradgreen : 255;
            imgcpy[i][j].rgbtBlue = gradblue < 255 ? gradblue : 255;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imgcpy[i][j];
        }
    }
}
