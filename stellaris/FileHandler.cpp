#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class FileHandler
{
    public:
        template<typename T>
        vector<T> ReadInTextFile(string fileName, bool individualElements);
        template<typename T>
        void WriteToTextFile(string fileName, vector<T> elements, string delimeter);

        template<typename T>
        vector<T> ReadInBinaryFile(string fileName);
        template<typename T>
        void WriteToBinaryFile(string fileName, vector<T> structures);
    private:
        template<typename T>
        T ConvertTo(string line);

        void PrintErrorAndExit(string fileName);
};

template<typename T>
vector<T> FileHandler::ReadInTextFile(string fileName, bool individualElements)
{
    string line = "";
    ifstream file(fileName);
    vector<T> linesFromFile;

    if (file)
    {
        if (individualElements == true)
        {
            while (file >> line)
            {
                linesFromFile.push_back(ConvertTo<T>(line));
            }
        }
        else
        {
            while (getline(file, line))
            {
                linesFromFile.push_back(ConvertTo<T>(line));
            }
        }

        file.close();
    }
    else
    {
        PrintErrorAndExit(fileName);
    }

    return linesFromFile;
}

template<>
string FileHandler::ConvertTo<string>(string line)
{
    return line;
}

template<>
int FileHandler::ConvertTo<int>(string line)
{
    return stoi(line);
}

template<>
float FileHandler::ConvertTo<float>(string line)
{
    return stof(line);
}

template<>
double FileHandler::ConvertTo<double>(string line)
{
    return stod(line);
}

template<typename T>
void FileHandler::WriteToTextFile(string fileName, vector<T> elements, string delimeter)
{
    ofstream file(fileName);

    if (file)
    {
        for (T element : elements)
        {
            file << element << delimeter;
        }

        file.close();
    }
    else
    {
        PrintErrorAndExit(fileName);
    }
}

template<typename T>
vector<T> FileHandler::ReadInBinaryFile(string fileName)
{
    vector<T> returnElements;
    ifstream file(fileName, ios::binary);
    T structure;

    if (file)
    {
        while (file.read((char*)&structure, sizeof(T)))
        {
            returnElements.push_back(structure);
        }

        file.close();
    }
    else
    {
        PrintErrorAndExit(fileName);
    }

    return returnElements;
}

template<typename T>
void FileHandler::WriteToBinaryFile(string fileName, vector<T> structures)
{
    ofstream file(fileName, ios::binary);

    if (file)
    {
        for (T structure : structures)
        {
            file.write((char*)&structure, sizeof(T));
        }

        file.close();
    }
    else
    {
        PrintErrorAndExit(fileName);
    }
}

void FileHandler::PrintErrorAndExit(string fileName)
{
    cout << "Unable to open file '" << fileName << "'" << endl;

    exit(1);
}
