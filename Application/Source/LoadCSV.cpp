#include "LoadCSV.h"

void LoadTextData(int textDataArray[], std::string textDataCSV)
{
	std::ifstream data(textDataCSV);
	std::string line;
	int i = 0;

	if (!data.good())
	{
		std::cout << textDataCSV << " Not Found!";
		return;
	}

	while (std::getline(data, line)) {
		textDataArray[i++] = std::stoi(line);
	}
}
