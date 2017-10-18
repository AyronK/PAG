#include "FileReader.hpp"

std::string FileReader::readFile(std::string fileName)
{
	std::string filetext;
	std::string line;
	std::ifstream file(fileName);

	if (!file)
	{
		file.close();
		std::string errorMessage = "Could not open file";
		errorMessage += fileName.c_str();
		throw std::runtime_error(errorMessage);
	}
	else
	{
		while (file.good())
		{
			getline(file, line);
			filetext.append(line + "\n");
		}

		file.close();

		return filetext;
	}
}