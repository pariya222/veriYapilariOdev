#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

//Defining pixel and storing its coordinates 
struct Pixel
{
    int row;
    int col;
};

//Using DFS technique to search for blobs
void dfs(char** grid, int rows, int cols, int row, int col, std::vector<Pixel>& blob)
{
    //Base case 
    if (row < 0 || row >= rows ||  col < 0 || col >= cols || grid[row][col] != 'x')
    {
        return;
    }

    //Marking as visited by replacing with space
    grid[row][col] = ' ';

    //Adding coordinates of the current pixel back
    blob.push_back({ row,col });

    //Recursively exploring the pixels
    dfs(grid, rows, cols, row - 1, col, blob);
    dfs(grid, rows, cols, row + 1, col, blob);
    dfs(grid, rows, cols, row, col + 1, blob);
    dfs(grid, rows, cols, row, col - 1, blob);
}

int main()
{

    //Asking for file name
    std::string filename;
    std::cout << "Enter the name of the input file: ";
    std::cin >> filename;

    //Opening file and checking if it's open
    std::ifstream inputFile(filename);
    if (!inputFile)
    {
        std::cout << "Error opening File!" << std::endl;
        return 1;
    }

    int rows, cols;
    //Reading the first two numbers
    inputFile >> rows >> cols;

    //Create a 2D dynamic array
    char** grid = new char* [rows];
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new char[cols];
    }

    //Skipping new line
    inputFile.ignore();

    //Read the data from the file
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = inputFile.get();
        }
        inputFile.ignore();
    }

    inputFile.close();

    //Printing the pixels
    for (int j = 0; j < cols; j++)
    {
        std::cout << std::setw(2) << j;
    }
    std::cout << std::endl;

    std::cout << " +" << std::string(cols * 2, '-') << "+\n";

    for (int i = 0; i < rows; i++)
    {
        std::cout << i << "|";
        for (int j = 0; j < cols; j++)
        {
            std::cout << std::setw(2) << grid[i][j];
        }
        std::cout << " |" << i << std::endl;
    }
    std::cout << " +" << std::string(cols * 2, '-') << "+\n";

    //Calculate blob proporties
    std::vector<std::vector<Pixel>>blobs;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 'x')
            {
                std::vector<Pixel>blob;
                dfs(grid, rows, cols, i, j, blob);
                blobs.push_back(blob);
            }
        }
    }

    std::cout << "Number of blobs found : " << blobs.size() << std::endl;

    //Printing the results in table format
    if (blobs.empty())
    {
        std::cout << "No blobs fouund in the file." << std::endl;
        return 0;
    }


    std::cout << "+------+------------+----------+----------+\n";
    std::cout << "| BLOB | NoOfPixels | CoM Row  | CoM Col  |\n";
    std::cout << "+------+------------+----------+----------+\n";

    for (size_t i = 0; i < blobs.size(); i++)
    {
        int numberOfPixels = blobs[i].size();
        double centerX = 0, centerY = 0;
        for (const Pixel& pixel : blobs[i])
        {
            centerX += pixel.col;
            centerY += pixel.row;
        }

        centerX /= numberOfPixels;
        centerY /= numberOfPixels;
        std::cout << "| " << std::setw(4) << i + 1 << " | " << std::setw(10) << numberOfPixels
            << " | " << std::setw(7) << std::fixed << std::setprecision(2) << centerY
            << " | " << std::setw(8) << std::fixed << std::setprecision(2) << centerX
            << "  |\n";
    }
    std::cout << "+------+------------+----------+----------+\n";

    //Deallocating memory 
    for (int i = 0; i < rows; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}