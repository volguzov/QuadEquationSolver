#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "equationClass.h"

coeffStruct initFromFile(std::string fileName)
{
    std::ifstream extractionFile(fileName);
    std::string readLine;
    std::vector<std::string> extractedVec;

    coeffStruct returnedValue;
    if (!extractionFile.is_open())
    {
        std::cout << "Failed to open file " + fileName + "\n";
        returnedValue.failureFlag = 1;
        return returnedValue;
    }

    while (std::getline(extractionFile, readLine, ' '))
        extractedVec.push_back(readLine);

    extractionFile.close();

    auto vecSize = extractedVec.size();
    switch (vecSize)
    {
    case 2:
        try
        {
            returnedValue.constantCoeff = std::stod(extractedVec.at(1));
            returnedValue.regXCoeff = std::stod(extractedVec.at(0));
            returnedValue.squareXCoeff = 0;
            returnedValue.failureFlag = 0;
        }
        catch (std::invalid_argument const& ex)
        {
            returnedValue.constantCoeff = 0;
            returnedValue.regXCoeff = 0;
            returnedValue.squareXCoeff = 0;
            returnedValue.failureFlag = 1;
            return returnedValue;
        }
        return returnedValue;
    case 3:
        try
        {
            returnedValue.constantCoeff = std::stod(extractedVec.at(2));
            returnedValue.regXCoeff = std::stod(extractedVec.at(1));
            returnedValue.squareXCoeff = std::stod(extractedVec.at(0));
            returnedValue.failureFlag = 0;
        }
        catch (std::invalid_argument const& ex)
        {
            returnedValue.constantCoeff = 0;
            returnedValue.regXCoeff = 0;
            returnedValue.squareXCoeff = 0;
            returnedValue.failureFlag = 1;
            return returnedValue;
        }
        return returnedValue;
    default:
        std::cout << "Input parameters inconclusive.\n";

        returnedValue.constantCoeff = 0;
        returnedValue.regXCoeff = 0;
        returnedValue.squareXCoeff = 0;
        returnedValue.failureFlag = 1;
        return returnedValue;
    }
}

double calculateDeterminant(double squareXCoeff, double regXCoeff, double constantCoeff)
{
    if (!squareXCoeff == 0)
    {
        double preSqrt = regXCoeff * regXCoeff - 4 * squareXCoeff * constantCoeff;
        if (preSqrt < 0)
            return -1;

        double det = std::sqrt(preSqrt);
        return det;
    }
    else
        return -1;
}

rootStruct getRoots(double squareXCoeff, double regXCoeff, double constantCoeff)
{
    rootStruct calcedRoots;

    float det = calculateDeterminant(squareXCoeff, regXCoeff, constantCoeff);
    if (det < 0 && squareXCoeff != 0)
    {
        std::cout << "Equation cannot be solved for real roots.\n";
        calcedRoots.rootCount = 0;
        return calcedRoots;
    }

    if (squareXCoeff != 0)
    {
        float det = calculateDeterminant(squareXCoeff, regXCoeff, constantCoeff);
        if (det == 0)
        {
            calcedRoots.rootCount = 1;
            calcedRoots.firstRoot = -1 * regXCoeff * 0.5 / squareXCoeff;
            return calcedRoots;
        }
        else
        {
            calcedRoots.rootCount = 2;
            calcedRoots.firstRoot = (-1 * regXCoeff + det) * 0.5 / squareXCoeff;
            calcedRoots.secondRoot = (-1 * regXCoeff - det) * 0.5 / squareXCoeff;
            return calcedRoots;
        }
    }
    else if (regXCoeff != 0)
    {
        calcedRoots.rootCount = 1;
        calcedRoots.firstRoot = -1 * constantCoeff / regXCoeff;
        return calcedRoots;
    }
    else
    {
        std::cout << "Equation cannot be solved due to lack of coefficients.\n";
        calcedRoots.rootCount = 0;
        return calcedRoots;
    }
}

bool outputRootsToFile(std::string fileName, const rootStruct &calcedRoots)
{
    std::ofstream writeFile(fileName, std::ofstream::trunc);
    if (!writeFile.is_open())
    {
        std::cout << "Failed to open file " + fileName + "\n";
        return false;
    }

    switch (calcedRoots.rootCount)
    {
    case 1:
        writeFile << calcedRoots.firstRoot;
        writeFile.close();
        return true;
    case 2:
        writeFile << std::to_string(calcedRoots.firstRoot);
        writeFile << " ";
        writeFile << std::to_string(calcedRoots.secondRoot);
        writeFile.close();
        return true;
    default:
        writeFile << "No roots.";
        writeFile.close();
        return true;
    }
}

void main(void)
{
    auto extractedCoeffs = initFromFile("input.txt");

    if (extractedCoeffs.failureFlag == 1)
    {
        std::cout << "Equation initialization failure.\n";
        return;
    }

    auto calculatedRoots = getRoots(extractedCoeffs.squareXCoeff, extractedCoeffs.regXCoeff, extractedCoeffs.constantCoeff);
    if (outputRootsToFile("output.txt", calculatedRoots))
    {
        std::cout << "Successfully wrote roots into output file: ";
        std::cout << "output.txt\n";
    }
    else
        std::cout << "Failed to output roots.\n";
}