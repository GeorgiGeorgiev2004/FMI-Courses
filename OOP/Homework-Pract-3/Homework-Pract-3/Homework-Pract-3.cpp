#include <iostream>
#include <fstream>

const int MaxPokemonName = 50;
const int MaxPokemonPower = 100;
const int MinPokemonPower = 10;

//The moment anything is done to this enum the following functions have to be revisited (they will break due to the way they are hard coded):
//DisplayTypes(does not break when values of constants are changed. Breaks when new are added),CreateVariation,CreatePokemon.
//Got no idea how to do it better.
enum PokemonVariations
{
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    GHOST,
    FLYING
};

struct Pokemon 
{
    char name[MaxPokemonName];
    PokemonVariations type;
    int power;
};

struct PokemonHandler 
{
    const char* FileName;
};

enum Errors 
{
    no_error,
    wrong_Input,
    file_not_open
};

struct Answer 
{
    Pokemon p;
    Errors err;
};


bool ValidatePokemonName(const char name[])
{
    int NameSize = strlen(name);
    if (NameSize > MaxPokemonName)
    {
        std::cout << "Name exceeds size of pokemon name!";
        return false;
    }
    else if (NameSize == 0)
    {
        std::cout << "Give your pokemon a name!";
        return false;

    }
    return true;
}

bool ValidatePokemonPower(const int power)
{
    if (power>MaxPokemonPower)
    {
        std::cout << "Lower the supplements (anabolic steroids) and try again some other time!";
        return false;
    }
    else if (power<MinPokemonPower)
    {
        std::cout << "Pokemon is far too weak!";
        return false;
    }
    return true;
}

bool ValidatePokemon(const char name[], const int power )
{
    bool ValidName = ValidatePokemonName(name);
    bool ValidPower = ValidatePokemonPower(power);
    return ValidName && ValidPower;
}

PokemonVariations CreateVariation(const int type) 
{
    PokemonVariations result;
    switch (type)
    {
    case 0:result = PokemonVariations::NORMAL;
        break;
    case 1:result = PokemonVariations::FIRE;
        break;
    case 2:result = PokemonVariations::WATER;
        break;
    case 3:result = PokemonVariations::GRASS;
        break;
    case 4:result = PokemonVariations::ELECTRIC;
        break;
    case 5:result = PokemonVariations::GHOST;
        break;
    case 6:result = PokemonVariations::FLYING;
        break;
    default:
        std::cout << "Unknown pokemon type setting type to Normal";
        return PokemonVariations::NORMAL;
        break;
    }
    return result;
}

void DisplayTypes() 
{
    std::cout <<"Please enter the number of the desired type\n"
        << PokemonVariations::NORMAL << " - NORMAL" << "\n"
        << PokemonVariations::FIRE << " - FIRE" << "\n"
        << PokemonVariations::WATER << " - WATER" << "\n"
        << PokemonVariations::GRASS << " - GRASS" << "\n"
        << PokemonVariations::ELECTRIC << " - ELECTRIC" << "\n"
        << PokemonVariations::GHOST << " - GHOST" << "\n"
        << PokemonVariations::FLYING << " - FLYING" << "\n";
}

Answer CreatePokemon()
{
    char name[MaxPokemonName];
    int type;
    int power;

    DisplayTypes();
    std::cout << "Enter your pokemon specifications --> Pokemon-Name Pokemon-Type Pokemon-Power\n";
    std::cin >> name >> type >> power;

    PokemonVariations vr = CreateVariation(type);

    if (ValidatePokemon(name, power))
    {
        Pokemon res = {"",vr,power};
        strcpy_s(res.name,name);
        return Answer{res,Errors::no_error};
    }
    return Answer{ Pokemon{},Errors::wrong_Input };
}

Answer CreatePokemonFromBin(std::ifstream &ifs)
{
    //std::fstream ifs(fileName,std::ios::binary | std::ios::in);

    if (!ifs.is_open())
    {
        return Answer{ Pokemon{},Errors::file_not_open };
    }

    Pokemon result{};

    ifs.read(reinterpret_cast<char*>( & result), sizeof(result));
    ifs.close();
    PokemonVariations vr = CreateVariation(result.type);

    if (ValidatePokemon(result.name, result.power))
    {
        return Answer{ result,Errors::no_error };
    }
    return Answer{ Pokemon{},Errors::wrong_Input };
}

Answer SavePokemonInBin(Pokemon& poke,const char* fileName)
{
    std::fstream ofs(fileName,std::ios::binary | std::ios::out | std::ios::app);

    if (!ofs.is_open())
    {
        return Answer{ Pokemon{},Errors::file_not_open };
    }

    ofs.write((char*)&poke, sizeof(poke));
    ofs.close();
    return Answer{ Pokemon{},Errors::no_error };
}

PokemonHandler newPokemonHandler(const char* filename)
{
    return PokemonHandler{filename};
}

int size(const PokemonHandler& ph) 
{
    std::ifstream ifs(ph.FileName);
    if (!ifs.is_open())
    {
        return -1;
    }
    int currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    int FileSize = ifs.tellg();
    ifs.seekg(0, currentPos);
    ifs.close();

    return FileSize/sizeof(Pokemon);
}

bool ValidIndex(int index,int top,int bot) 
{
    if (index>top)
    {
        std::cout << "Too high!";
        return false;
    }
    if (index <bot)
    {
        std::cout << "Too low!";
        return false;
    }
    return true;
}

Pokemon at(const PokemonHandler& ph, int i) 
{
    std::ifstream ifs(ph.FileName);

    if (!ifs.is_open())
    {
        return Pokemon{};
    }

    int size = ::size(ph);
    if (ValidIndex(i, size, 0))
    {
        int pos = (i-1) * sizeof(Pokemon);
        ifs.seekg(pos, std::ios::beg);
        Answer ans = CreatePokemonFromBin(ifs);
        if (ans.err==Errors::no_error)
        {
            return ans.p;
        }
    }
    //Another functional solution!!!!
    // 
    //int size = ::size(ph);
    //if (ValidIndex(i,size,0))
    //{
    //    ifs.seekg(0, std::ios::beg);
    //    for (size_t j = 0; j < size; j++)
    //    {
    //        Answer ans = CreatePokemonFromBin(ifs);
    //        if (ans.err == Errors::no_error)
    //        {
    //            if (j == i-1)
    //            {
    //                return ans.p;
    //            }
    //        }
    //    }
    //    ifs.close();
    //}
    ifs.close();

}

void swap(const PokemonHandler& ph, int i, int j) 
{
    Pokemon pATi = ::at(ph, i);
    Pokemon pATj = ::at(ph, j);
    int size = ::size(ph);
    for (size_t k = 0; k < size; k++)
    {

    }
}

int main()
{
    /*
    Answer ans = CreatePokemon();
    if (ans.err==Errors::no_error)
    {
        //test purposes 'ans' works just as well.
        Pokemon p = {"ManagarmerTheSecondII",PokemonVariations::FLYING,66};
        Answer a = SavePokemonInBin(p, "WriteTest.dat");
        Answer pmc = CreatePokemonFromBin("WriteTest.dat");
    }
    */

    Pokemon p = { "ManagarmerTheSecondII",PokemonVariations::FLYING,66 };
    Answer a = SavePokemonInBin(p, "WriteTest.dat");

    p = { "Gergi",PokemonVariations::WATER,12 };
    a = SavePokemonInBin(p, "WriteTest.dat");

    p = { "Genadii",PokemonVariations::FLYING,44 };
    a = SavePokemonInBin(p, "WriteTest.dat");

    PokemonHandler ph = newPokemonHandler("WriteTest.dat");
    int s = size(ph);

    Pokemon pokemon = at(ph, 2);

    std::cout << s;
}
