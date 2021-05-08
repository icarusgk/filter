#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float result = (float)(image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / (float) 3;

            int new_value = round(result);
            image[i][j].rgbtBlue = new_value;
            image[i][j].rgbtRed = new_value;
            image[i][j].rgbtGreen = new_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a new unmodified image from the original

    // Allocate memory for the new image
    RGBTRIPLE(*original)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Copy the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Pass each pixel to the unmodified image
            original[i][j] = image[i][j];
        }
    }

    int grid_size = 0;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top Left Corner
            if (i == 0 && j == 0)
            {
                float new_red = (float)(original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j].rgbtRed + original[i + 1][j +
                                        1].rgbtRed) / (float) 4;
                float new_green = (float)(original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i + 1][j
                                          + 1].rgbtGreen) / (float) 4;
                float new_blue = (float)(original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i + 1][j +
                                         1].rgbtBlue) / (float) 4;

                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // Top Right Corner
            else if ((i == 0) && (j == width - 1))
            {
                float new_red = (float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j].rgbtRed + original[i + 1][j -
                                        1].rgbtRed) / (float) 4;
                float new_green = (float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i + 1][j
                                          - 1].rgbtGreen) / (float) 4;
                float new_blue = (float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i + 1][j -
                                         1].rgbtBlue) / (float) 4;

                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // Top row
            else if ((i == 0) && (j >= 1 && j < width - 1))
            {
                grid_size = 6;
                float new_red = (float)(original[i][j - 1].rgbtRed + original[i][j].rgbtRed + original[i][j + 1].rgbtRed
                                        + original[i + 1][j - 1].rgbtRed + original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed) / (float) grid_size;

                float new_green = (float)(original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen
                                          + original[i + 1][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / (float) grid_size;

                float new_blue = (float)(original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue
                                         + original[i + 1][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / (float) grid_size;

                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;

            }
            // Remaining rows
            else if ((i >= 1 && i < height - 1) && (j >= 1 && j < width - 1))
            {
                grid_size = 9;
                float new_red = (float)(original[i - 1][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed
                                        + original[i][j - 1].rgbtRed + original[i][j].rgbtRed + original[i][j + 1].rgbtRed
                                        + original[i + 1][j - 1].rgbtRed + original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed) / (float) grid_size;

                float new_green = (float)(original[i - 1][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen
                                          + original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen
                                          + original[i + 1][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / (float) grid_size;

                float new_blue = (float)(original[i - 1][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue
                                         + original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue
                                         + original[i + 1][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / (float) grid_size;

                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;

            }
            // Bottom Left Corner
            else if ((i == height - 1) && (j == 0))
            {
                grid_size = 4;
                float new_red = (float)(original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j +
                                        1].rgbtRed) / (float) 4;
                float new_green = (float)(original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j
                                          + 1].rgbtGreen) / (float) 4;
                float new_blue = (float)(original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j +
                                         1].rgbtBlue) / (float) 4;

                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // Bottom Right Corner
            else if ((i == height - 1) && (j == width - 1))
            {
                grid_size = 4;
                float new_red = (float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j -
                                        1].rgbtRed) / (float) 4;
                float new_green = (float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j
                                          - 1].rgbtGreen) / (float) 4;
                float new_blue = (float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j -
                                         1].rgbtBlue) / (float) 4;

                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // Left Column
            else if ((i >= 1 && i < height - 1) && (j == 0))
            {
                grid_size = 6;
                float new_red = (float)(original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed
                                        + original[i][j].rgbtRed + original[i][j + 1].rgbtRed
                                        + original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed) / (float) grid_size;

                float new_green = (float)(original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen
                                          + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen
                                          + original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / (float) grid_size;

                float new_blue = (float)(original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue
                                         + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue
                                         + original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / (float) grid_size;

                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // // Right Column
            else if ((i >= 1 && height - 1) && (j == width - 1))
            {
                grid_size = 6;
                float new_red = (float)(original[i - 1][j].rgbtRed + original[i - 1][j - 1].rgbtRed
                                        + original[i][j].rgbtRed + original[i][j - 1].rgbtRed
                                        + original[i + 1][j].rgbtRed + original[i + 1][j - 1].rgbtRed) / (float) grid_size;

                float new_green = (float)(original[i - 1][j].rgbtGreen + original[i - 1][j - 1].rgbtGreen
                                          + original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen
                                          + original[i + 1][j].rgbtGreen + original[i + 1][j - 1].rgbtGreen) / (float) grid_size;

                float new_blue = (float)(original[i - 1][j].rgbtBlue + original[i - 1][j - 1].rgbtBlue
                                         + original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue
                                         + original[i + 1][j].rgbtBlue + original[i + 1][j - 1].rgbtBlue) / (float) grid_size;

                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // Bottom row
            else if ((i == height - 1) && (j >= 1 && j < width - 1))
            {
                grid_size = 6;
                float new_red = (float)(original[i][j - 1].rgbtRed + original[i][j].rgbtRed + original[i][j + 1].rgbtRed
                                        + original[i - 1][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed) / (float) grid_size;

                float new_green = (float)(original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen
                                          + original[i - 1][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / (float) grid_size;

                float new_blue = (float)(original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue
                                         + original[i - 1][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / (float) grid_size;

                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a new unmodified image from the original

    // Allocate memory for the new image
    RGBTRIPLE(*original)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Copy the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Pass each pixel to the unmodified image
            original[i][j] = image[i][j];
        }
    }



    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top Left Corner
            if (i == 0 && j == 0)
            {
                int red_channel_x = ((-1 * 0) + (0 * (0)) + (1 * (0))
                                     + (-2 * 0)     + (0 * (original[i][j].rgbtRed)) + (2 * (original[i][j + 1].rgbtRed))
                                     + (-1 * 0) + (0 * (original[i + 1][j].rgbtRed)) + (1 * (original[i + 1][j + 1].rgbtRed)));

                int green_channel_x = ((-1 * 0) + (0 * (0)) + (1 * (0))
                                       + (-2 * 0)     + (0 * (original[i][j].rgbtGreen)) + (2 * (original[i][j + 1].rgbtGreen))
                                       + (-1 * 0) + (0 * (original[i + 1][j].rgbtGreen)) + (1 * (original[i + 1][j + 1].rgbtGreen)));

                int blue_channel_x = ((-1 * 0) + (0 * (0)) + (1 * (0))
                                      + (-2 * 0)     + (0 * (original[i][j].rgbtBlue)) + (2 * (original[i][j + 1].rgbtBlue))
                                      + (-1 * 0) + (0 * (original[i + 1][j].rgbtBlue)) + (1 * (original[i + 1][j + 1].rgbtBlue)));

                // y
                int red_channel_y = ((-1 * 0) + (-2 * (0)) + (-1 * (0))
                                     + (0 * 0)  + (0 * (original[i][j].rgbtRed)) + (0 * (original[i][j + 1].rgbtRed))
                                     + (1 * 0)  + (2 * (original[i + 1][j].rgbtRed))  + (1 * (original[i + 1][j + 1].rgbtRed)));

                int green_channel_y = ((-1 * 0) + (-2 * (0)) + (-1 * (0))
                                       + (0 * 0)  + (0 * (original[i][j].rgbtGreen)) + (0 * (original[i][j + 1].rgbtGreen))
                                       + (1 * 0)  + (2 * (original[i + 1][j].rgbtGreen))  + (1 * (original[i + 1][j + 1].rgbtGreen)));

                int blue_channel_y = ((-1 * 0) + (-2 * (0)) + (-1 * (0))
                                      + (0 * 0)  + (0 * (original[i][j].rgbtBlue)) + (0 * (original[i][j + 1].rgbtBlue))
                                      + (1 * 0)  + (2 * (original[i + 1][j].rgbtBlue)) + (1 * (original[i + 1][j + 1].rgbtBlue)));


                // Compute each channel new value as the square root of gx^2 + gy^2


                // Gx^2
                int red_gx2 = red_channel_x * red_channel_x;
                int green_gx2 = green_channel_x * green_channel_x;
                int blue_gx2 = blue_channel_x * blue_channel_x;

                // Gy^2
                int red_gy2 = red_channel_y * red_channel_y;
                int green_gy2 = green_channel_y * green_channel_y;
                int blue_gy2 = blue_channel_y * blue_channel_y;

                // Gx^2 + Gy^2
                int red_sum = red_gx2 + red_gy2;
                int green_sum = green_gx2 + green_gy2;
                int blue_sum = blue_gx2 + blue_gy2;


                float red_value = (float) sqrt((float) red_sum);
                float green_value = (float) sqrt((float) green_sum);
                float blue_value = (float) sqrt((float) blue_sum);


                if (red_value > 255)
                {
                    red_value = 255;
                }

                if (green_value > 255)
                {
                    green_value = 255;
                }

                if (blue_value > 255)
                {
                    blue_value = 255;
                }

                int final_red = round(red_value);
                int final_green = round(green_value);
                int final_blue = round(blue_value);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // Top Right Corner
            else if ((i == 0) && (j == width - 1))
            {
                // x
                int red_channel_x = ((-1 * 0) + (0 * (0)) + (1 * (0))
                                     + (-2 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (2 * (0))
                                     + (-1 * original[i + 1][j - 1].rgbtRed) + (0 * (original[i + 1][j].rgbtRed)) + (1 * (0)));

                int green_channel_x = ((-1 * 0) + (0 * (0)) + (1 * (0))
                                       + (-2 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (2 * (0))
                                       + (-1 * original[i + 1][j - 1].rgbtGreen) + (0 * (original[i + 1][j].rgbtGreen)) + (1 * (0)));

                int blue_channel_x = ((-1 * 0) + (0 * (0)) + (1 * (0))
                                      + (-2 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue))     + (2 * (0))
                                      + (-1 * original[i + 1][j - 1].rgbtBlue) + (0 * (original[i + 1][j].rgbtBlue)) + (1 * (0)));

                // y
                int red_channel_y = ((-1 * 0) + (-2 * (0)) + (-1 * (0))
                                     + (0 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (0 * (0))
                                     + (1 * original[i + 1][j - 1].rgbtRed)  + (2 * (original[i + 1][j].rgbtRed)) + (1 * (0)));

                int green_channel_y = ((-1 * 0) + (-2 * (0)) + (-1 * (0))
                                       + (0 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (0 * (0))
                                       + (1 * original[i + 1][j - 1].rgbtGreen) + (2 * (original[i + 1][j].rgbtGreen)) + (1 * (0)));

                int blue_channel_y = ((-1 * 0) + (-2 * (0)) + (-1 * (0))
                                      + (0 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue)) + (0 * (0))
                                      + (1 * original[i + 1][j - 1].rgbtBlue) + (2 * (original[i + 1][j].rgbtBlue)) + (1 * (0)));


                // Compute each channel new value as the square root of gx^2 + gy^2

                // Gx^2
                int red_gx2 = red_channel_x * red_channel_x;
                int green_gx2 = green_channel_x * green_channel_x;
                int blue_gx2 = blue_channel_x * blue_channel_x;

                // Gy^2
                int red_gy2 = red_channel_y * red_channel_y;
                int green_gy2 = green_channel_y * green_channel_y;
                int blue_gy2 = blue_channel_y * blue_channel_y;

                // Gx^2 + Gy^2
                int red_sum = red_gx2 + red_gy2;
                int green_sum = green_gx2 + green_gy2;
                int blue_sum = blue_gx2 + blue_gy2;


                float red_value = (float) sqrt((float) red_sum);
                float green_value = (float) sqrt((float) green_sum);
                float blue_value = (float) sqrt((float) blue_sum);


                if (red_value > 255)
                {
                    red_value = 255;
                }

                if (green_value > 255)
                {
                    green_value = 255;
                }

                if (blue_value > 255)
                {
                    blue_value = 255;
                }

                int final_red = round(red_value);
                int final_green = round(green_value);
                int final_blue = round(blue_value);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // Top row
            else if ((i == 0) && (j >= 1 && j < width - 1))
            {
                // x
                int red_channel_x = ((-1 * 0) + (0 * (0)) + (1 * (0))
                                     + (-2 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (2 * (original[i][j + 1].rgbtRed))
                                     + (-1 * original[i + 1][j - 1].rgbtRed) + (0 * (original[i + 1][j].rgbtRed)) + (1 * (original[i + 1][j + 1].rgbtRed)));

                int green_channel_x = ((-1 * 0) + (0 * (0)) + (1 * (0))
                                       + (-2 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (2 * (original[i][j + 1].rgbtGreen))
                                       + (-1 * original[i + 1][j - 1].rgbtGreen) + (0 * (original[i + 1][j].rgbtGreen)) + (1 * (original[i + 1][j + 1].rgbtGreen)));;

                int blue_channel_x = ((-1 * 0) + (0 * (0)) + (1 * (0))
                                      + (-2 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue)) + (2 * (original[i][j + 1].rgbtBlue))
                                      + (-1 * original[i + 1][j - 1].rgbtBlue) + (0 * (original[i + 1][j].rgbtBlue)) + (1 * (original[i + 1][j + 1].rgbtBlue)));;

                // y
                int red_channel_y = ((-1 * 0) + (-2 * (0)) + (-1 * (0))
                                     + (0 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (0 * (original[i][j + 1].rgbtRed))
                                     + (1 * original[i + 1][j - 1].rgbtRed) + (2 * (original[i + 1][j].rgbtRed)) + (1 * (original[i + 1][j + 1].rgbtRed)));

                int green_channel_y = ((-1 * 0) + (-2 * (0)) + (-1 * (0))
                                       + (0 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (0 * (original[i][j + 1].rgbtGreen))
                                       + (1 * original[i + 1][j - 1].rgbtGreen) + (2 * (original[i + 1][j].rgbtGreen)) + (1 * (original[i + 1][j + 1].rgbtGreen)));

                int blue_channel_y = ((-1 * 0) + (-2 * (0)) + (-1 * (0))
                                      + (0 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue)) + (0 * (original[i][j + 1].rgbtBlue))
                                      + (1 * original[i + 1][j - 1].rgbtBlue) + (2 * (original[i + 1][j].rgbtBlue)) + (1 * (original[i + 1][j + 1].rgbtBlue)));


                // Compute each channel new value as the square root of gx^2 + gy^2

                // Gx^2
                int red_gx2 = red_channel_x * red_channel_x;
                int green_gx2 = green_channel_x * green_channel_x;
                int blue_gx2 = blue_channel_x * blue_channel_x;

                // Gy^2
                int red_gy2 = red_channel_y * red_channel_y;
                int green_gy2 = green_channel_y * green_channel_y;
                int blue_gy2 = blue_channel_y * blue_channel_y;

                // Gx^2 + Gy^2
                int red_sum = red_gx2 + red_gy2;
                int green_sum = green_gx2 + green_gy2;
                int blue_sum = blue_gx2 + blue_gy2;


                float red_value = (float) sqrt((float) red_sum);
                float green_value = (float) sqrt((float) green_sum);
                float blue_value = (float) sqrt((float) blue_sum);


                if (red_value > 255)
                {
                    red_value = 255;
                }

                if (green_value > 255)
                {
                    green_value = 255;
                }

                if (blue_value > 255)
                {
                    blue_value = 255;
                }

                int final_red = round(red_value);
                int final_green = round(green_value);
                int final_blue = round(blue_value);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;


            }
            // No borders for the kernel
            if ((i >= 1 && i < height - 1) && (j >= 1 && j < width - 1))
            {
                // x
                int red_channel_x = ((-1 * original[i - 1][j - 1].rgbtRed) + (0 * (original[i - 1][j].rgbtRed)) + (1 *
                                     (original[i - 1][j + 1].rgbtRed))
                                     + (-2 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (2 * (original[i][j + 1].rgbtRed))
                                     + (-1 * original[i + 1][j - 1].rgbtRed) + (0 * (original[i + 1][j].rgbtRed)) + (1 * (original[i + 1][j + 1].rgbtRed)));

                int green_channel_x = ((-1 * original[i - 1][j - 1].rgbtGreen) + (0 * (original[i - 1][j].rgbtGreen)) + (1 *
                                       (original[i - 1][j + 1].rgbtGreen))
                                       + (-2 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (2 * (original[i][j + 1].rgbtGreen))
                                       + (-1 * original[i + 1][j - 1].rgbtGreen) + (0 * (original[i + 1][j].rgbtGreen)) + (1 * (original[i + 1][j + 1].rgbtGreen)));;

                int blue_channel_x = ((-1 * original[i - 1][j - 1].rgbtBlue) + (0 * (original[i - 1][j].rgbtBlue)) + (1 *
                                      (original[i - 1][j + 1].rgbtBlue))
                                      + (-2 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue)) + (2 * (original[i][j + 1].rgbtBlue))
                                      + (-1 * original[i + 1][j - 1].rgbtBlue) + (0 * (original[i + 1][j].rgbtBlue)) + (1 * (original[i + 1][j + 1].rgbtBlue)));;

                // y
                int red_channel_y = ((-1 * original[i - 1][j - 1].rgbtRed) + (-2 * (original[i - 1][j].rgbtRed)) + (-1 *
                                     (original[i - 1][j + 1].rgbtRed))
                                     + (0 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (0 * (original[i][j + 1].rgbtRed))
                                     + (1 * original[i + 1][j - 1].rgbtRed)  + (2 * (original[i + 1][j].rgbtRed))  + (1 * (original[i + 1][j + 1].rgbtRed)));

                int green_channel_y = ((-1 * original[i - 1][j - 1].rgbtGreen) + (-2 * (original[i - 1][j].rgbtGreen)) + (-1 *
                                       (original[i - 1][j + 1].rgbtGreen))
                                       + (0 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (0 * (original[i][j + 1].rgbtGreen))
                                       + (1 * original[i + 1][j - 1].rgbtGreen) + (2 * (original[i + 1][j].rgbtGreen)) + (1 * (original[i + 1][j + 1].rgbtGreen)));

                int blue_channel_y = ((-1 * original[i - 1][j - 1].rgbtBlue) + (-2 * (original[i - 1][j].rgbtBlue)) + (-1 *
                                      (original[i - 1][j + 1].rgbtBlue))
                                      + (0 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue)) + (0 * (original[i][j + 1].rgbtBlue))
                                      + (1 * original[i + 1][j - 1].rgbtBlue) + (2 * (original[i + 1][j].rgbtBlue))  + (1 * (original[i + 1][j + 1].rgbtBlue)));


                // Compute each channel new value as the square root of gx^2 + gy^2

                // Gx^2
                int red_gx2 = red_channel_x * red_channel_x;
                int green_gx2 = green_channel_x * green_channel_x;
                int blue_gx2 = blue_channel_x * blue_channel_x;

                // Gy^2
                int red_gy2 = red_channel_y * red_channel_y;
                int green_gy2 = green_channel_y * green_channel_y;
                int blue_gy2 = blue_channel_y * blue_channel_y;

                // Gx^2 + Gy^2
                int red_sum = red_gx2 + red_gy2;
                int green_sum = green_gx2 + green_gy2;
                int blue_sum = blue_gx2 + blue_gy2;


                float red_value = (float) sqrt((float) red_sum);
                float green_value = (float) sqrt((float) green_sum);
                float blue_value = (float) sqrt((float) blue_sum);


                if (red_value > 255)
                {
                    red_value = 255;
                }

                if (green_value > 255)
                {
                    green_value = 255;
                }

                if (blue_value > 255)
                {
                    blue_value = 255;
                }

                int final_red = round(red_value);
                int final_green = round(green_value);
                int final_blue = round(blue_value);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;

            }

            // Bottom Left Corner
            else if ((i == height - 1) && (j == 0))
            {
                // x
                int red_channel_x = ((-1 * 0) + (0 * (original[i - 1][j].rgbtRed)) + (1 * (original[i - 1][j + 1].rgbtRed))
                                     + (-2 * 0)     + (0 * (original[i][j].rgbtRed)) + (2 * (original[i][j + 1].rgbtRed))
                                     + (-1 * 0) + (0 * (0)) + (1 * (0)));

                int green_channel_x = ((-1 * 0) + (0 * (original[i - 1][j].rgbtGreen)) + (1 * (original[i - 1][j + 1].rgbtGreen))
                                       + (-2 * 0)     + (0 * (original[i][j].rgbtGreen))     + (2 * (original[i][j + 1].rgbtGreen))
                                       + (-1 * 0) + (0 * (0)) + (1 * (0)));;

                int blue_channel_x = ((-1 * 0) + (0 * (original[i - 1][j].rgbtBlue)) + (1 * (original[i - 1][j + 1].rgbtBlue))
                                      + (-2 * 0)     + (0 * (original[i][j].rgbtBlue))     + (2 * (original[i][j + 1].rgbtBlue))
                                      + (-1 * 0) + (0 * (0)) + (1 * (0)));;

                // y
                int red_channel_y = ((-1 * 0) + (-2 * (original[i - 1][j].rgbtRed)) + (-1 * (original[i - 1][j + 1].rgbtRed))
                                     + (0 * 0) + (0 * (original[i][j].rgbtRed)) + (0 * (original[i][j + 1].rgbtRed))
                                     + (1 * 0) + (2 * (0)) + (1 * (0)));

                int green_channel_y = ((-1 * 0) + (-2 * (original[i - 1][j].rgbtGreen)) + (-1 * (original[i - 1][j + 1].rgbtGreen))
                                       + (0 * 0) + (0 * (original[i][j].rgbtGreen)) + (0 * (original[i][j + 1].rgbtGreen))
                                       + (1 * 0)  + (2 * (0))  + (1 * (0)));

                int blue_channel_y = ((-1 * 0) + (-2 * (original[i - 1][j].rgbtBlue)) + (-1 * (original[i - 1][j + 1].rgbtBlue))
                                      + (0 * 0) + (0 * (original[i][j].rgbtBlue)) + (0 * (original[i][j + 1].rgbtBlue))
                                      + (1 * 0) + (2 * (0))  + (1 * (0)));


                // Compute each channel new value as the square root of gx^2 + gy^2

                // Gx^2
                int red_gx2 = red_channel_x * red_channel_x;
                int green_gx2 = green_channel_x * green_channel_x;
                int blue_gx2 = blue_channel_x * blue_channel_x;

                // Gy^2
                int red_gy2 = red_channel_y * red_channel_y;
                int green_gy2 = green_channel_y * green_channel_y;
                int blue_gy2 = blue_channel_y * blue_channel_y;

                // Gx^2 + Gy^2
                int red_sum = red_gx2 + red_gy2;
                int green_sum = green_gx2 + green_gy2;
                int blue_sum = blue_gx2 + blue_gy2;


                float red_value = (float) sqrt((float) red_sum);
                float green_value = (float) sqrt((float) green_sum);
                float blue_value = (float) sqrt((float) blue_sum);


                if (red_value > 255)
                {
                    red_value = 255;
                }

                if (green_value > 255)
                {
                    green_value = 255;
                }

                if (blue_value > 255)
                {
                    blue_value = 255;
                }

                int final_red = round(red_value);
                int final_green = round(green_value);
                int final_blue = round(blue_value);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;

            }
            // Bottom Right Corner
            else if ((i == height - 1) && (j == width - 1))
            {
                // x
                int red_channel_x = ((-1 * original[i - 1][j - 1].rgbtRed) + (0 * (original[i - 1][j].rgbtRed)) + (1 * (0))
                                     + (-2 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (2 * (0))
                                     + (-1 * 0) + (0 * (0)) + (1 * (0)));

                int green_channel_x = ((-1 * original[i - 1][j - 1].rgbtGreen) + (0 * (original[i - 1][j].rgbtGreen)) + (1 * (0))
                                       + (-2 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (2 * (0))
                                       + (-1 * 0) + (0 * (0)) + (1 * (0)));;

                int blue_channel_x = ((-1 * original[i - 1][j - 1].rgbtBlue) + (0 * (original[i - 1][j].rgbtBlue)) + (1 * (0))
                                      + (-2 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue)) + (2 * (0))
                                      + (-1 * 0) + (0 * 0) + (1 * (0)));;

                // y
                int red_channel_y = ((-1 * original[i - 1][j - 1].rgbtRed) + (-2 * (original[i - 1][j].rgbtRed)) + (-1 * (0))
                                     + (0 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (0 * (0))
                                     + (1 * 0)  + (2 * (0))  + (1 * (0)));

                int green_channel_y = ((-1 * original[i - 1][j - 1].rgbtGreen) + (-2 * (original[i - 1][j].rgbtGreen)) + (-1 * (0))
                                       + (0 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (0 * (0))
                                       + (1 * 0)  + (2 * (0))  + (1 * (0)));

                int blue_channel_y = ((-1 * original[i - 1][j - 1].rgbtBlue) + (-2 * (original[i - 1][j].rgbtBlue)) + (-1 * (0))
                                      + (0 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue)) + (0 * (0))
                                      + (1 * 0)  + (2 * (0))  + (1 * (0)));


                // Compute each channel new value as the square root of gx^2 + gy^2

                // Gx^2
                int red_gx2 = red_channel_x * red_channel_x;
                int green_gx2 = green_channel_x * green_channel_x;
                int blue_gx2 = blue_channel_x * blue_channel_x;

                // Gy^2
                int red_gy2 = red_channel_y * red_channel_y;
                int green_gy2 = green_channel_y * green_channel_y;
                int blue_gy2 = blue_channel_y * blue_channel_y;

                // Gx^2 + Gy^2
                int red_sum = red_gx2 + red_gy2;
                int green_sum = green_gx2 + green_gy2;
                int blue_sum = blue_gx2 + blue_gy2;


                float red_value = (float) sqrt((float) red_sum);
                float green_value = (float) sqrt((float) green_sum);
                float blue_value = (float) sqrt((float) blue_sum);


                if (red_value > 255)
                {
                    red_value = 255;
                }

                if (green_value > 255)
                {
                    green_value = 255;
                }

                if (blue_value > 255)
                {
                    blue_value = 255;
                }

                int final_red = round(red_value);
                int final_green = round(green_value);
                int final_blue = round(blue_value);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;


            }
            // Left Column
            else if ((i >= 1 && i < height - 1) && (j == 0))
            {
                // x
                int red_channel_x = ((-1 * 0) + (0 * (original[i - 1][j].rgbtRed)) + (1 * (original[i - 1][j + 1].rgbtRed))
                                     + (-2 * 0) + (0 * (original[i][j].rgbtRed)) + (2 * (original[i][j + 1].rgbtRed))
                                     + (-1 * 0) + (0 * (original[i + 1][j].rgbtRed)) + (1 * (original[i + 1][j + 1].rgbtRed)));

                int green_channel_x = ((-1 * 0) + (0 * (original[i - 1][j].rgbtGreen)) + (1 * (original[i - 1][j + 1].rgbtGreen))
                                       + (-2 * 0) + (0 * (original[i][j].rgbtGreen)) + (2 * (original[i][j + 1].rgbtGreen))
                                       + (-1 * 0) + (0 * (original[i + 1][j].rgbtGreen)) + (1 * (original[i + 1][j + 1].rgbtGreen)));;

                int blue_channel_x = ((-1 * 0) + (0 * (original[i - 1][j].rgbtBlue)) + (1 * (original[i - 1][j + 1].rgbtBlue))
                                      + (-2 * 0) + (0 * (original[i][j].rgbtBlue)) + (2 * (original[i][j + 1].rgbtBlue))
                                      + (-1 * 0) + (0 * (original[i + 1][j].rgbtBlue)) + (1 * (original[i + 1][j + 1].rgbtBlue)));;

                // y
                int red_channel_y = ((-1 * 0) + (-2 * (original[i - 1][j].rgbtRed)) + (-1 * (original[i - 1][j + 1].rgbtRed))
                                     + (0 * 0) + (0 * (original[i][j].rgbtRed)) + (0 * (original[i][j + 1].rgbtRed))
                                     + (1 * 0) + (2 * (original[i + 1][j].rgbtRed)) + (1 * (original[i + 1][j + 1].rgbtRed)));

                int green_channel_y = ((-1 * 0) + (-2 * (original[i - 1][j].rgbtGreen)) + (-1 * (original[i - 1][j + 1].rgbtGreen))
                                       + (0 * 0) + (0 * (original[i][j].rgbtGreen)) + (0 * (original[i][j + 1].rgbtGreen))
                                       + (1 * 0)  + (2 * (original[i + 1][j].rgbtGreen))  + (1 * (original[i + 1][j + 1].rgbtGreen)));

                int blue_channel_y = ((-1 * 0) + (-2 * (original[i - 1][j].rgbtBlue)) + (-1 * (original[i - 1][j + 1].rgbtBlue))
                                      + (0 * 0)      + (0 * (original[i][j].rgbtBlue)) + (0 * (original[i][j + 1].rgbtBlue))
                                      + (1 * 0)  + (2 * (original[i + 1][j].rgbtBlue)) + (1 * (original[i + 1][j + 1].rgbtBlue)));


                // Compute each channel new value as the square root of gx^2 + gy^2

                // Gx^2
                int red_gx2 = red_channel_x * red_channel_x;
                int green_gx2 = green_channel_x * green_channel_x;
                int blue_gx2 = blue_channel_x * blue_channel_x;

                // Gy^2
                int red_gy2 = red_channel_y * red_channel_y;
                int green_gy2 = green_channel_y * green_channel_y;
                int blue_gy2 = blue_channel_y * blue_channel_y;

                // Gx^2 + Gy^2
                int red_sum = red_gx2 + red_gy2;
                int green_sum = green_gx2 + green_gy2;
                int blue_sum = blue_gx2 + blue_gy2;


                float red_value = (float) sqrt((float) red_sum);
                float green_value = (float) sqrt((float) green_sum);
                float blue_value = (float) sqrt((float) blue_sum);


                if (red_value > 255)
                {
                    red_value = 255;
                }

                if (green_value > 255)
                {
                    green_value = 255;
                }

                if (blue_value > 255)
                {
                    blue_value = 255;
                }

                int final_red = round(red_value);
                int final_green = round(green_value);
                int final_blue = round(blue_value);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;


            }
            // // Right Column
            else if ((i >= 1 && height - 1) && (j == width - 1))
            {
                // x
                int red_channel_x = ((-1 * original[i - 1][j - 1].rgbtRed) + (0 * (original[i - 1][j].rgbtRed)) + (1 * (0))
                                     + (-2 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (2 * (0))
                                     + (-1 * original[i + 1][j - 1].rgbtRed) + (0 * (original[i + 1][j].rgbtRed)) + (1 * (0)));

                int green_channel_x = ((-1 * original[i - 1][j - 1].rgbtGreen) + (0 * (original[i - 1][j].rgbtGreen)) + (1 * (0))
                                       + (-2 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (2 * (0))
                                       + (-1 * original[i + 1][j - 1].rgbtGreen) + (0 * (original[i + 1][j].rgbtGreen)) + (1 * (0)));;

                int blue_channel_x = ((-1 * original[i - 1][j - 1].rgbtBlue) + (0 * (original[i - 1][j].rgbtBlue)) + (1 * (0))
                                      + (-2 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue)) + (2 * (0))
                                      + (-1 * original[i + 1][j - 1].rgbtBlue) + (0 * (original[i + 1][j].rgbtBlue)) + (1 * (0)));;

                // y
                int red_channel_y = ((-1 * original[i - 1][j - 1].rgbtRed) + (-2 * (original[i - 1][j].rgbtRed)) + (-1 * (0))
                                     + (0 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (0 * (0))
                                     + (1 * original[i + 1][j - 1].rgbtRed) + (2 * (original[i + 1][j].rgbtRed)) + (1 * (0)));

                int green_channel_y = ((-1 * original[i - 1][j - 1].rgbtGreen) + (-2 * (original[i - 1][j].rgbtGreen)) + (-1 * (0))
                                       + (0 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (0 * (0))
                                       + (1 * original[i + 1][j - 1].rgbtGreen)  + (2 * (original[i + 1][j].rgbtGreen))  + (1 * (0)));

                int blue_channel_y = ((-1 * original[i - 1][j - 1].rgbtBlue) + (-2 * (original[i - 1][j].rgbtBlue)) + (-1 * (0))
                                      + (0 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue)) + (0 * (0))
                                      + (1 * original[i + 1][j - 1].rgbtBlue) + (2 * (original[i + 1][j].rgbtBlue))  + (1 * (0)));


                // Compute each channel new value as the square root of gx^2 + gy^2

                // Gx^2
                int red_gx2 = red_channel_x * red_channel_x;
                int green_gx2 = green_channel_x * green_channel_x;
                int blue_gx2 = blue_channel_x * blue_channel_x;

                // Gy^2
                int red_gy2 = red_channel_y * red_channel_y;
                int green_gy2 = green_channel_y * green_channel_y;
                int blue_gy2 = blue_channel_y * blue_channel_y;

                // Gx^2 + Gy^2
                int red_sum = red_gx2 + red_gy2;
                int green_sum = green_gx2 + green_gy2;
                int blue_sum = blue_gx2 + blue_gy2;


                float red_value = (float) sqrt((float) red_sum);
                float green_value = (float) sqrt((float) green_sum);
                float blue_value = (float) sqrt((float) blue_sum);


                if (red_value > 255)
                {
                    red_value = 255;
                }

                if (green_value > 255)
                {
                    green_value = 255;
                }

                if (blue_value > 255)
                {
                    blue_value = 255;
                }

                int final_red = round(red_value);
                int final_green = round(green_value);
                int final_blue = round(blue_value);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;


            }
            // Bottom row
            else if ((i == height - 1) && (j >= 1 && j < width - 1))
            {
                // x
                int red_channel_x = ((-1 * original[i - 1][j - 1].rgbtRed) + (0 * (original[i - 1][j].rgbtRed)) + (1 *
                                     (original[i - 1][j + 1].rgbtRed))
                                     + (-2 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (2 * (original[i][j + 1].rgbtRed))
                                     + (-1 * 0) + (0 * 0) + (1 * 0));

                int green_channel_x = ((-1 * original[i - 1][j - 1].rgbtGreen) + (0 * (original[i - 1][j].rgbtGreen)) + (1 *
                                       (original[i - 1][j + 1].rgbtGreen))
                                       + (-2 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (2 * (original[i][j + 1].rgbtGreen))
                                       + (-1 * 0) + (0 * 0) + (1 * 0));;

                int blue_channel_x = ((-1 * original[i - 1][j - 1].rgbtBlue) + (0 * (original[i - 1][j].rgbtBlue)) + (1 *
                                      (original[i - 1][j + 1].rgbtBlue))
                                      + (-2 * original[i][j - 1].rgbtBlue)     + (0 * (original[i][j].rgbtBlue))     + (2 * (original[i][j + 1].rgbtBlue))
                                      + (-1 * 0) + (0 * 0) + (1 * (0)));;

                // y
                int red_channel_y = ((-1 * original[i - 1][j - 1].rgbtRed) + (-2 * (original[i - 1][j].rgbtRed)) + (-1 *
                                     (original[i - 1][j + 1].rgbtRed))
                                     + (0 * original[i][j - 1].rgbtRed) + (0 * (original[i][j].rgbtRed)) + (0 * (original[i][j + 1].rgbtRed))
                                     + (1 * 0)  + (2 * (0))  + (1 * (0)));

                int green_channel_y = ((-1 * original[i - 1][j - 1].rgbtGreen) + (-2 * (original[i - 1][j].rgbtGreen)) + (-1 *
                                       (original[i - 1][j + 1].rgbtGreen))
                                       + (0 * original[i][j - 1].rgbtGreen) + (0 * (original[i][j].rgbtGreen)) + (0 * (original[i][j + 1].rgbtGreen))
                                       + (1 * 0)  + (2 * (0))  + (1 * (0)));

                int blue_channel_y = ((-1 * original[i - 1][j - 1].rgbtBlue) + (-2 * (original[i - 1][j].rgbtBlue)) + (-1 *
                                      (original[i - 1][j + 1].rgbtBlue))
                                      + (0 * original[i][j - 1].rgbtBlue) + (0 * (original[i][j].rgbtBlue)) + (0 * (original[i][j + 1].rgbtBlue))
                                      + (1 * 0)  + (2 * (0))  + (1 * (0)));


                // Compute each channel new value as the square root of gx^2 + gy^2

                // Gx^2
                int red_gx2 = red_channel_x * red_channel_x;
                int green_gx2 = green_channel_x * green_channel_x;
                int blue_gx2 = blue_channel_x * blue_channel_x;

                // Gy^2
                int red_gy2 = red_channel_y * red_channel_y;
                int green_gy2 = green_channel_y * green_channel_y;
                int blue_gy2 = blue_channel_y * blue_channel_y;

                // Gx^2 + Gy^2
                int red_sum = red_gx2 + red_gy2;
                int green_sum = green_gx2 + green_gy2;
                int blue_sum = blue_gx2 + blue_gy2;


                float red_value = (float) sqrt((float) red_sum);
                float green_value = (float) sqrt((float) green_sum);
                float blue_value = (float) sqrt((float) blue_sum);


                if (red_value > 255)
                {
                    red_value = 255;
                }

                if (green_value > 255)
                {
                    green_value = 255;
                }

                if (blue_value > 255)
                {
                    blue_value = 255;
                }

                int final_red = round(red_value);
                int final_green = round(green_value);
                int final_blue = round(blue_value);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;


            }
        }
    }


    return;
}
