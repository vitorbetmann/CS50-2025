#include <cs50.h>
#include <stdio.h>

// Prototypes
int get_height();
void draw_pyramid(int height);

int main(void)
{
    int height = get_height();
    draw_pyramid(height);
}

int get_height()
{
    int height = 0;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;
}

void draw_pyramid(int height)
{
    for (int row = 0; row < height; row++)
    {
        for (int col = height - 1 - row; col > 0; col--)
        {
            printf(" ");
        }
        for (int col = 0; col < row + 1; col++)
        {
            printf("#");
        }
        printf("  ");
        for (int col = 0; col < row + 1; col++)
        {
            printf("#");
        }
        printf("\n");
    }
}
