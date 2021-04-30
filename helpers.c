#include "helpers.h"
#include "math.h"
#include <stdlib.h>

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
    for (int i = 0; i < height; i++)
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
                float new_red = (float)(original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed) 
                                            / (float) 4;
                float new_green = (float)(original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen) 
                                            / (float) 4;
                float new_blue = (float)(original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue) 
                                            / (float) 4;
                
                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // Top Rigth Corner
            else if ((i == 0) && (j == width - 1))
            {
                float new_red = (float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j].rgbtRed + original[i + 1][j - 1].rgbtRed) 
                                            / (float) 4;
                float new_green = (float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i + 1][j - 1].rgbtGreen) 
                                            / (float) 4;
                float new_blue = (float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i + 1][j - 1].rgbtBlue) 
                                            / (float) 4;
                
                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // Top row
            else if((i == 0) && (j >= 1 && j < width - 1))
            {
                grid_size = 6;
                float new_red = (float) (original[i][j - 1].rgbtRed + original[i][j].rgbtRed + original[i][j + 1].rgbtRed
                                        +original[i + 1][j - 1].rgbtRed + original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed) / (float) grid_size;

                float new_green = (float) (original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen
                                        +original[i + 1][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / (float) grid_size;

                float new_blue = (float) (original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue
                                        +original[i + 1][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / (float) grid_size;

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
                float new_red = (float) (original[i - 1][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed
                                        +original[i][j - 1].rgbtRed + original[i][j].rgbtRed + original[i][j + 1].rgbtRed
                                        +original[i + 1][j - 1].rgbtRed + original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed) / (float) grid_size;

                float new_green = (float) (original[i - 1][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen
                                        +original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen
                                        +original[i + 1][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / (float) grid_size;

                float new_blue = (float) (original[i - 1][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue
                                        +original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue
                                        +original[i + 1][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / (float) grid_size;

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
                float new_red = (float)(original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed) 
                                            / (float) 4;
                float new_green = (float)(original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen) 
                                            / (float) 4;
                float new_blue = (float)(original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue) 
                                            / (float) 4;
                
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
                float new_red = (float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j - 1].rgbtRed) 
                                            / (float) 4;
                float new_green = (float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j - 1].rgbtGreen) 
                                            / (float) 4;
                float new_blue = (float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j - 1].rgbtBlue) 
                                            / (float) 4;
                
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
                float new_red = (float) (original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed 
                                        + original[i][j].rgbtRed + original[i][j + 1].rgbtRed
                                        + original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed) / (float) grid_size;

                float new_green = (float) (original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen 
                                        + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen
                                        + original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / (float) grid_size;

                float new_blue = (float) (original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue 
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
                float new_red = (float) (original[i - 1][j].rgbtRed + original[i - 1][j - 1].rgbtRed 
                                        + original[i][j].rgbtRed + original[i][j - 1].rgbtRed
                                        + original[i + 1][j].rgbtRed + original[i + 1][j - 1].rgbtRed) / (float) grid_size;

                float new_green = (float) (original[i - 1][j].rgbtGreen + original[i - 1][j - 1].rgbtGreen 
                                        + original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen
                                        + original[i + 1][j].rgbtGreen + original[i + 1][j - 1].rgbtGreen) / (float) grid_size;

                float new_blue = (float) (original[i - 1][j].rgbtBlue + original[i - 1][j - 1].rgbtBlue 
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
                float new_red = (float) (original[i][j - 1].rgbtRed + original[i][j].rgbtRed + original[i][j + 1].rgbtRed
                                        +original[i - 1][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed) / (float) grid_size;

                float new_green = (float) (original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen
                                        +original[i - 1][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / (float) grid_size;

                float new_blue = (float) (original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue
                                        +original[i - 1][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / (float) grid_size;

                int final_red = round(new_red);
                int final_green = round(new_green);
                int final_blue = round(new_blue);

                image[i][j].rgbtRed = final_red;
                image[i][j].rgbtGreen = final_green;
                image[i][j].rgbtBlue = final_blue;
            }
            // // Top Right Corner
            // else if ()

        }
    }

    

    // // Top Left Corner
    // image[0][0].rgbtRed = 255;
    // image[0][0].rgbtGreen = 0;
    // image[0][0].rgbtBlue = 0;

    // // Bottom Left Corner
    // image[height - 1][0].rgbtRed = 0;
    // image[height - 1][0].rgbtGreen = 255;
    // image[height - 1][0].rgbtBlue = 0;

    // // Top Right Corner
    // image[0][width - 1].rgbtRed = 255;
    // image[0][width - 1].rgbtGreen = 0;
    // image[0][width - 1].rgbtBlue = 0;

    // // Bottom Rigth Corner
    // image[height - 1][width - 1].rgbtRed = 0;
    // image[height - 1][width - 1].rgbtGreen = 255;
    // image[height - 1][width - 1].rgbtBlue = 0;
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
