#include <iostream>
#include <cstring>
#include <fstream>

namespace ConstValues
{
	const int BUFFER_MAX_SIZE = 1024;
	const int MAX_ROWS_COUNT_IN_TABLE = 100;
	const int MAX_SYMBOLS_IN_FIELD = 50+1;
	const int MAX_FIELDS_IN_ROW = 15;
}


struct Field
{
	char elements[ConstValues::MAX_SYMBOLS_IN_FIELD];
};

struct Row 
{
	Field fields[ConstValues::MAX_FIELDS_IN_ROW];
};

struct Table
{
	Row rows [ConstValues::MAX_ROWS_COUNT_IN_TABLE];
	Row TitleFields;
	int tilesCount = 0;
	int rowsCount = 0;
	void ReadTableFromFile(const char*);
	void ReadRows(std::ifstream&,int&,bool&);
	void ReadCommand(std::ifstream& ifs, char*& command);
	void ReadField(std::ifstream& ifs, char*& line);
};
Table InitTable()
{
	return Table{};
}
bool ValidateConnection(std::ifstream& ifs)
{
	return !ifs.is_open();
}

void Table::ReadCommand(std::ifstream& ifs, char*& command)
{
	char CMD[8];
	int i = 0;
	for (; i < 8; i++)
	{
		ifs >> CMD[i];
		if (CMD[i]=='>')
		{
			break;
		}
	}
	for (size_t j = i+1; j < 8; j++)
	{
		CMD[j] = '\0';
	}

	if (strcmp(CMD, "<table>") == 0)
	{
		strcpy(command, CMD); 
		return;
	}
	if (strcmp(CMD, "</table>")==0)
	{
		strcpy(command, CMD);
		return;
	}
	if (strcmp(CMD, "<th>") == 0)
	{
		strcpy(command, CMD);
		return;
	}
	else if (strcmp(CMD, "<tr>") == 0)
	{
		strcpy(command, CMD);
		return;
	}
	else if (strcmp(CMD, "<td>") == 0)
	{
		strcpy(command, CMD);
		return;
	}

	if (strcmp(CMD, "</th>") == 0)
	{
		strcpy(command, CMD);
		return;
	}
	else if (strcmp(CMD, "</tr>") == 0)
	{
		strcpy(command, CMD);
		return;
	}
	else if (strcmp(CMD, "</td>") == 0)
	{
		strcpy(command, CMD);
		return;
	}
}
void Table::ReadField(std::ifstream& ifs, char*& line) 
{
	char field[ConstValues::MAX_SYMBOLS_IN_FIELD];
	int i = 0;
	bool hasCERel = false;
	int indexOfCERel = 0;
	for (; i < ConstValues::MAX_SYMBOLS_IN_FIELD; i++)
	{
		ifs >> field[i];
		if (field[i]=='&')
		{
			hasCERel = true;
			indexOfCERel = i;
		}
		if (field[i] == '<')
		{
			break;
		}
	}
	ifs.seekg(-1, std::ios::cur);
	if (hasCERel)
	{
		char tempEl[3];
		if (field[indexOfCERel + 1] == '#')
		{
			field[indexOfCERel + 1] = '\0';
			if (field[indexOfCERel + 2] >= 48 && field[indexOfCERel + 2] <= 57)
			{
				tempEl[0] = field[indexOfCERel + 2];
				field[indexOfCERel + 2] = '\0';
				if (field[indexOfCERel + 3] >= 48 && field[indexOfCERel + 3] <= 57)
				{
					tempEl[1] = field[indexOfCERel + 3];
					field[indexOfCERel + 3] = '\0';
					if (field[indexOfCERel + 4] >= 48 && field[indexOfCERel + 4] <= 57)
					{
						tempEl[2] = field[indexOfCERel + 4];
						field[indexOfCERel + 4] = '\0';
					}
				}
			}
		}
		field[indexOfCERel] = (char)tempEl;
	}
	for (size_t j = i; j < ConstValues::MAX_SYMBOLS_IN_FIELD; j++)
	{
		field[j] = '\0';
	}
	strcpy(line, field);
}
void Table::ReadRows(std::ifstream& ifs,int& counter,bool &isTile)
{
	char* command = new char[ConstValues::BUFFER_MAX_SIZE];
	ReadCommand(ifs, command);
	if (strcmp(command, "<table>") == 0)
	{
		ReadCommand(ifs, command);
	}

	if (strcmp(command,"<tr>")==0)
	{
		while (strcmp(command, "</tr>") != 0)
		{
			ReadCommand(ifs, command);
			if ((strcmp(command, "<th>") == 0))
			{
				char* f = new char[ConstValues::MAX_SYMBOLS_IN_FIELD];
				ReadField(ifs, f);
				Field field{};
				strcpy(field.elements, f);
				TitleFields.fields[tilesCount]=field;
				tilesCount++;
				delete[]f;
				isTile = true;
			}
			if (strcmp(command, "<td>") == 0)
			{
				char* f = new char[ConstValues::MAX_SYMBOLS_IN_FIELD];
				ReadField(ifs, f);
				Field field{};
				strcpy(field.elements, f);
				rows[rowsCount].fields[counter] = field;
				counter++;
				delete[]f;
			}
		}
	}
	delete[] command;
}

void Table::ReadTableFromFile(const char* fileName)
{
	std::ifstream ifs(fileName);

	if (ValidateConnection(ifs))
	{
		std::cout << "Error assert placeholder";
	}
	while (!ifs.eof())
	{
		int fieldsInRow = 0;
		bool isTiles = false;
		ReadRows(ifs,fieldsInRow,isTiles);
		fieldsInRow = 0;
		if (isTiles)
		{
			isTiles = false;
			continue;
		}		
		rowsCount++;
	}
}

int main()
{
	Table t = InitTable();
	const char* filename = "test.txt";
	t.ReadTableFromFile(filename);
	int n = 0;
	int d = 0;
}