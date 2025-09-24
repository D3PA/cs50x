#include "helpers.h"
#include <math.h> // for round() y sqrt()

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; // temporary array

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumR = 0, sumG = 0, sumB = 0, count = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumR += image[ni][nj].rgbtRed;
                        sumG += image[ni][nj].rgbtGreen;
                        sumB += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            temp[i][j].rgbtRed = round(sumR / (float) count);
            temp[i][j].rgbtGreen = round(sumG / (float) count);
            temp[i][j].rgbtBlue = round(sumB / (float) count);
        }
    }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            image[i][j] = temp[i][j];
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE temp[height][width]; // temporary array

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRx = 0, sumGx = 0, sumBx = 0;
            float sumRy = 0, sumGy = 0, sumBy = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        int factorX = Gx[di + 1][dj + 1];
                        int factorY = Gy[di + 1][dj + 1];

                        sumRx += image[ni][nj].rgbtRed * factorX;
                        sumGx += image[ni][nj].rgbtGreen * factorX;
                        sumBx += image[ni][nj].rgbtBlue * factorX;

                        sumRy += image[ni][nj].rgbtRed * factorY;
                        sumGy += image[ni][nj].rgbtGreen * factorY;
                        sumBy += image[ni][nj].rgbtBlue * factorY;
                    }
                }
            }

            int red = round(sqrt(sumRx * sumRx + sumRy * sumRy));
            int green = round(sqrt(sumGx * sumGx + sumGy * sumGy));
            int blue = round(sqrt(sumBx * sumBx + sumBy * sumBy));

            // clamp 255
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }

    // copy original image
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            image[i][j] = temp[i][j];
}