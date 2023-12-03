#include "../../include/util/gears.hpp"

/**
 * @brief Transforms the input file into a matrix of chars.
 */
std::vector<std::vector<char>> get_matrix(std::string input_file_path)
{
    std::vector<std::vector<char>> matrix;
    std::fstream document_file(input_file_path, std::ios_base::in);
    while (!document_file.eof())
    {
        std::string line;
        std::getline(document_file, line);
        std::vector<char> line_vector;
        for (const auto &c : line)
            line_vector.push_back(c);
        matrix.push_back(line_vector);
    }
    return matrix;
}

/**
 * @brief Returns a vector of pointers to the coordinates of the symbols in the matrix.
 */
std::vector<int *> get_symbol_coordinates(std::vector<std::vector<char>> matrix)
{
    std::vector<int *> coordinates;
    for (int i = 0; i < int(matrix.size()); i++)
    {
        for (int j = 0; j < int(matrix[i].size()); j++)
        {
            if (matrix[i][j] != '.' && !std::isdigit(matrix[i][j]))
            {
                int *index = new int[2];
                index[0] = i;
                index[1] = j;
                coordinates.push_back(index);
                index = nullptr;
                delete[] index;
            }
        }
    }
    return coordinates;
}

/**
 * @brief Returns the numbers near a point coordinate in the matrix.
 */
int *get_nearby_numbers(std::vector<std::vector<char>> matrix, int *coordinate)
{
    // Since the numbers could be longer than what is visible withing the nearby 3x3 matrix,
    // once we find a number, we look left and right to find the whole number (eg, until we find something that is not a digit).
    // We want to void getting the same number multiple times.
    int *numbers = new int[8];
    int numbers_index = 0;

    // Looking around the point coordinate.
    for (int i = coordinate[0] - 1; i <= coordinate[0] + 1; i++)
    {
        for (int j = coordinate[1] - 1; j <= coordinate[1] + 1; j++)
        {
            if (i >= 0 && i < int(matrix.size()) && j >= 0 && j < int(matrix[i].size()))
            {
                if (std::isdigit(matrix[i][j]))
                {
                    // Looking left.
                    int left_index = j - 1;
                    while (std::isdigit(matrix[i][left_index]))
                        left_index--;
                    left_index++;

                    // Looking right.
                    int right_index = j + 1;
                    while (std::isdigit(matrix[i][right_index]))
                        right_index++;
                    right_index--;

                    // Getting the number.
                    std::string number_string = "";
                    for (int k = left_index; k <= right_index; k++)
                        number_string += matrix[i][k];
                    int number = std::stoi(number_string);

                    // Adding the number to the array.
                    bool number_already_added = false;
                    for (int k = 0; k < numbers_index; k++)
                    {
                        if (numbers[k] == number)
                        {
                            number_already_added = true;
                            break;
                        }
                    }
                    if (!number_already_added)
                    {
                        numbers[numbers_index] = number;
                        numbers_index++;
                    }
                }
            }
        }
    }

    return numbers;
}
