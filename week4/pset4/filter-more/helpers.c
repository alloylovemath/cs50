#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average_value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average_value;
            image[i][j].rgbtGreen = average_value;
            image[i][j].rgbtRed = average_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Using swap!
    int half_width = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < half_width; j++)
        {
            int reverse = width - 1 -j;
            int tmp_Blue = image[i][j].rgbtBlue;
            int tmp_Green = image[i][j].rgbtGreen;
            int tmp_Red = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][reverse].rgbtBlue;
            image[i][j].rgbtGreen = image[i][reverse].rgbtGreen;
            image[i][j].rgbtRed = image[i][reverse].rgbtRed;
            image[i][reverse].rgbtBlue = tmp_Blue;
            image[i][reverse].rgbtGreen = tmp_Green;
            image[i][reverse].rgbtRed = tmp_Red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //set up a new array of image;
    RGBTRIPLE image_copy[height][width];

    //calculate the new value;

    //corner
    image_copy[0][0].rgbtBlue = round((image[0][0].rgbtBlue + image[0][1].rgbtBlue +
    image[1][0].rgbtBlue + image[1][1].rgbtBlue) / 4.0);
    image_copy[0][0].rgbtGreen = round((image[0][0].rgbtGreen + image[0][1].rgbtGreen +
    image[1][0].rgbtGreen + image[1][1].rgbtGreen) / 4.0);
    image_copy[0][0].rgbtRed = round((image[0][0].rgbtRed + image[0][1].rgbtRed +
    image[1][0].rgbtRed + image[1][1].rgbtRed) / 4.0);

    image_copy[0][width - 1].rgbtBlue = round((image[0][width - 2].rgbtBlue + image[0][width - 1].rgbtBlue +
    image[1][width - 2].rgbtBlue + image[1][width - 1].rgbtBlue) / 4.0);
    image_copy[0][width - 1].rgbtGreen = round((image[0][width - 2].rgbtGreen + image[0][width - 1].rgbtGreen +
    image[1][width - 2].rgbtGreen + image[1][width - 1].rgbtGreen) / 4.0);
    image_copy[0][width - 1].rgbtRed = round((image[0][width - 2].rgbtRed + image[0][width - 1].rgbtRed +
    image[1][width - 2].rgbtRed + image[1][width - 1].rgbtRed) / 4.0);

    image_copy[height - 1][0].rgbtBlue = round((image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue +
    image[height - 1][0].rgbtBlue + image[height - 1][1].rgbtBlue) / 4.0);
    image_copy[height - 1][0].rgbtGreen = round((image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen +
    image[height - 1][0].rgbtGreen + image[height - 1][1].rgbtGreen) / 4.0 );
    image_copy[height - 1][0].rgbtRed = round((image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed +
    image[height - 1][0].rgbtRed + image[height - 1][1].rgbtRed) / 4.0);

    image_copy[height - 1][width - 1].rgbtBlue = round((image[height - 2][width - 2].rgbtBlue + image[height - 2][width - 1].rgbtBlue +
    image[height - 1][width - 2].rgbtBlue + image[height - 1][width - 1].rgbtBlue) / 4.0);
    image_copy[height - 1][width - 1].rgbtGreen = round((image[height - 2][width - 2].rgbtGreen + image[height - 2][width - 1].rgbtGreen +
    image[height - 1][width - 2].rgbtGreen + image[height - 1][width - 1].rgbtGreen) / 4.0);
    image_copy[height - 1][width - 1].rgbtRed = round((image[height - 2][width - 2].rgbtRed + image[height - 2][width - 1].rgbtRed +
    image[height - 1][width - 2].rgbtRed + image[height - 1][width - 1].rgbtRed) / 4.0);

    //edge
    for (int m = 1; m < width - 1; m++)
    {
        image_copy[0][m].rgbtBlue = round((image[0][m - 1].rgbtBlue + image[0][m].rgbtBlue +
        image[0][m + 1].rgbtBlue + image[1][m - 1].rgbtBlue + image[1][m].rgbtBlue +
        image[1][m + 1].rgbtBlue) / 6.0);
        image_copy[0][m].rgbtGreen = round((image[0][m - 1].rgbtGreen + image[0][m].rgbtGreen +
        image[0][m + 1].rgbtGreen + image[1][m - 1].rgbtGreen + image[1][m].rgbtGreen +
        image[1][m + 1].rgbtGreen) / 6.0);
        image_copy[0][m].rgbtRed = round((image[0][m - 1].rgbtRed + image[0][m].rgbtRed +
        image[0][m + 1].rgbtRed + image[1][m - 1].rgbtRed + image[1][m].rgbtRed +
        image[1][m + 1].rgbtRed) / 6.0);

        image_copy[height - 1][m].rgbtBlue = round((image[height - 2][m - 1].rgbtBlue + image[height - 2][m].rgbtBlue +
        image[height - 2][m + 1].rgbtBlue + image[height - 1][m - 1].rgbtBlue + image[height - 1][m].rgbtBlue +
        image[height - 1][m + 1].rgbtBlue) / 6.0);
        image_copy[height - 1][m].rgbtGreen = round((image[height - 2][m - 1].rgbtGreen + image[height - 2][m].rgbtGreen +
        image[height - 2][m + 1].rgbtGreen + image[height - 1][m - 1].rgbtGreen + image[height - 1][m].rgbtGreen +
        image[height - 1][m + 1].rgbtGreen) / 6.0);
        image_copy[height - 1][m].rgbtRed = round((image[height - 2][m - 1].rgbtRed + image[height - 2][m].rgbtRed +
        image[height - 2][m + 1].rgbtRed + image[height - 1][m - 1].rgbtRed + image[height - 1][m].rgbtRed +
        image[height - 1][m + 1].rgbtRed) / 6.0);
    }

    for (int n = 1; n < height - 1; n++)
    {
        image_copy[n][0].rgbtBlue = round((image[n - 1][0].rgbtBlue + image[n - 1][1].rgbtBlue +
        image[n][0].rgbtBlue + image[n][1].rgbtBlue + image[n + 1][0].rgbtBlue +
        image[n + 1][1].rgbtBlue) / 6.0);
        image_copy[n][0].rgbtGreen = round((image[n - 1][0].rgbtGreen + image[n - 1][1].rgbtGreen +
        image[n][0].rgbtGreen + image[n][1].rgbtGreen + image[n + 1][0].rgbtGreen +
        image[n + 1][1].rgbtGreen) / 6.0);
        image_copy[n][0].rgbtRed = round((image[n - 1][0].rgbtRed + image[n - 1][1].rgbtRed +
        image[n][0].rgbtRed + image[n][1].rgbtRed + image[n + 1][0].rgbtRed +
        image[n + 1][1].rgbtRed) / 6.0);

        image_copy[n][width - 1].rgbtBlue = round((image[n - 1][width - 2].rgbtBlue + image[n - 1][width - 1].rgbtBlue +
        image[n][width - 2].rgbtBlue + image[n][width - 1].rgbtBlue + image[n + 1][width - 2].rgbtBlue +
        image[n + 1][width - 1].rgbtBlue) / 6.0);
        image_copy[n][width - 1].rgbtGreen = round((image[n - 1][width - 2].rgbtGreen + image[n - 1][width - 1].rgbtGreen +
        image[n][width - 2].rgbtGreen + image[n][width - 1].rgbtGreen + image[n + 1][width - 2].rgbtGreen +
        image[n + 1][width - 1].rgbtGreen) / 6.0);
        image_copy[n][width - 1].rgbtRed = round((image[n - 1][width - 2].rgbtRed + image[n - 1][width - 1].rgbtRed +
        image[n][width - 2].rgbtRed + image[n][width - 1].rgbtRed + image[n + 1][width - 2].rgbtRed +
        image[n + 1][width - 1].rgbtRed) / 6.0);
    }

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image_copy[i][j].rgbtBlue = round((image[i-1][j-1].rgbtBlue + image[i - 1][j].rgbtBlue +
            image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue +
            image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
            image[i + 1][j + 1].rgbtBlue) / 9.0);
            image_copy[i][j].rgbtGreen = round((image[i-1][j-1].rgbtGreen + image[i - 1][j].rgbtGreen +
            image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen +
            image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
            image[i + 1][j + 1].rgbtGreen) / 9.0);
            image_copy[i][j].rgbtRed = round((image[i-1][j-1].rgbtRed + image[i - 1][j].rgbtRed +
            image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed +
            image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
            image[i + 1][j + 1].rgbtRed) / 9.0);
        }
    }

    for (int L = 0; L < height; L++)
    {
        for (int P = 0; P < width; P++)
        {
            image[L][P].rgbtBlue = image_copy[L][P].rgbtBlue;
            image[L][P].rgbtGreen = image_copy[L][P].rgbtGreen;
            image[L][P].rgbtRed = image_copy[L][P].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height + 2][width + 2];
    //copy the image
    for (int i = 0, b_h = height + 2; i < b_h; i++)
    {
        for (int j = 0, b_w = width + 2; j < b_w; j++)
        {
            image_copy[i][j].rgbtBlue = 0;
            image_copy[i][j].rgbtGreen = 0;
            image_copy[i][j].rgbtRed = 0;
        }
    }
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            image_copy[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
            image_copy[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
            image_copy[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
        }
    }

    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            int Gx_blue = (
                (-1) * image_copy[m][n].rgbtBlue + (1) * image_copy[m][n + 2].rgbtBlue +
                (-2) * image_copy[m + 1][n].rgbtBlue + (2) * image_copy[m + 1][n + 2].rgbtBlue +
                (-1) * image_copy[m + 2][n].rgbtBlue + (1) * image_copy[m + 2][n + 2].rgbtBlue
            );
            int Gy_blue = (
                (-1) * image_copy[m][n].rgbtBlue + (1) * image_copy[m + 2][n].rgbtBlue +
                (-2) * image_copy[m][n + 1].rgbtBlue + (2) * image_copy[m + 2][n + 1].rgbtBlue +
                (-1) * image_copy[m][n + 2].rgbtBlue + (1) * image_copy[m + 2][n + 2].rgbtBlue
            );
            float Edge_blue = sqrt((Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            if (Edge_blue >= 255)
            {
                image[m][n].rgbtBlue = 255;
            }
            else
            {
                image[m][n].rgbtBlue = (int) (Edge_blue + 0.5);
            }

            int Gx_green = (
                (-1) * image_copy[m][n].rgbtGreen + (1) * image_copy[m][n + 2].rgbtGreen +
                (-2) * image_copy[m + 1][n].rgbtGreen + (2) * image_copy[m + 1][n + 2].rgbtGreen +
                (-1) * image_copy[m + 2][n].rgbtGreen + (1) * image_copy[m + 2][n + 2].rgbtGreen
            );
            int Gy_green = (
                (-1) * image_copy[m][n].rgbtGreen + (1) * image_copy[m + 2][n].rgbtGreen +
                (-2) * image_copy[m][n + 1].rgbtGreen + (2) * image_copy[m + 2][n + 1].rgbtGreen +
                (-1) * image_copy[m][n + 2].rgbtGreen + (1) * image_copy[m + 2][n + 2].rgbtGreen
            );
            float Edge_green = sqrt((Gx_green * Gx_green + Gy_green * Gy_green));
            if (Edge_green >= 255)
            {
                image[m][n].rgbtGreen = 255;
            }
            else
            {
                image[m][n].rgbtGreen = (int) (Edge_green + 0.5);
            }

            int Gx_red = (
                (-1) * image_copy[m][n].rgbtRed + (1) * image_copy[m][n + 2].rgbtRed +
                (-2) * image_copy[m + 1][n].rgbtRed + (2) * image_copy[m + 1][n + 2].rgbtRed +
                (-1) * image_copy[m + 2][n].rgbtRed + (1) * image_copy[m + 2][n + 2].rgbtRed
            );
            int Gy_red = (
                (-1) * image_copy[m][n].rgbtRed + (1) * image_copy[m + 2][n].rgbtRed +
                (-2) * image_copy[m][n + 1].rgbtRed + (2) * image_copy[m + 2][n + 1].rgbtRed +
                (-1) * image_copy[m][n + 2].rgbtRed + (1) * image_copy[m + 2][n + 2].rgbtRed
            );
            float Edge_red = sqrt((Gx_red * Gx_red + Gy_red * Gy_red));
            if (Edge_red >= 255)
            {
                image[m][n].rgbtRed = 255;
            }
            else
            {
                image[m][n].rgbtRed = (int) (Edge_red + 0.5);
            }
        }
    }
    return;
}
