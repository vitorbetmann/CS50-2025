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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r, g, b;
            r = image[i][j].rgbtRed;
            g = image[i][j].rgbtGreen;
            b = image[i][j].rgbtBlue;

            int sepiaRed = round(0.393 * r + 0.769 * g + 0.189 * b);
            image[i][j].rgbtRed = sepiaRed < 255 ? sepiaRed : 255;
            int sepiaGreen = round(0.349 * r + 0.686 * g + 0.168 * b);
            image[i][j].rgbtGreen = sepiaGreen < 255 ? sepiaGreen : 255;
            int sepiaBlue = round(0.272 * r + 0.534 * g + 0.131 * b);
            image[i][j].rgbtBlue = sepiaBlue < 255 ? sepiaBlue : 255;
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
            int counter = 0;
            int sumred = 0, sumgreen = 0, sumblue = 0;

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
