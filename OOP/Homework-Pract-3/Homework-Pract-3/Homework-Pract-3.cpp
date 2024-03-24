#include <iostream>
#include <fstream>
#include <string>

const int MaxPokemonName = 50;
const int MaxPokemonPower = 100;
const int MinPokemonPower = 10;

//Dear programmer 
//When I wrote this code only God 
//and I knew how it worked
//Now, only God knows it!


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
    ifs.setstate(std::ios::binary);

    if (!ifs.is_open())
    {
        return Answer{ Pokemon{},Errors::file_not_open };
    }

    Pokemon result{};

    ifs.read((char*) & result, sizeof(result));

    PokemonVariations vr = CreateVariation(result.type);

    if (ValidatePokemon(result.name, result.power))
    {
        return Answer{ result,Errors::no_error };
    }
    return Answer{ Pokemon{},Errors::wrong_Input };
}

Answer SavePokemonInBin(Pokemon& poke,const char* fileName)
{
    //I am aware that the setting has to be std::ios::trunc instead of app but debugging is easier this way 
    //I will forget to swap it out later (It is what it is)
    std::fstream ofs(fileName,std::ios::binary | std::ios::out | std::ios::app);

    if (!ofs.is_open())
    {
        return Answer{ Pokemon{},Errors::file_not_open };
    }

    ofs.write((char*)&poke, sizeof(poke));
    ofs.close();
    return Answer{ Pokemon{"Success",PokemonVariations::NORMAL,1},Errors::no_error};
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
    if (index < bot||index<=0)
    {
        std::cout << "Too low!";
        return false;
    }
    return true;
}

Pokemon at(const PokemonHandler& ph,const int i) 
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
    return Pokemon{};
}

void swap(const PokemonHandler& ph, const int i,const int j) 
{
    Pokemon pATi = ::at(ph, i);
    Pokemon pATj = ::at(ph, j);
    int size = ::size(ph);

    if (!ValidIndex(i, size, 0))
    {
        return;
    }
    std::ofstream ofs(ph.FileName,std::ios::in|std::ios::ate| std::ios::binary);

    if (!ofs.is_open())
    {
        return;
    }

    Pokemon temp = {" ",pATi.type,pATi.power};
    strcpy_s(temp.name, pATi.name);

    int pos1 = (i - 1) * sizeof(Pokemon);

    ofs.seekp(pos1);
    ofs.write((char*) &pATj,sizeof(Pokemon));

    int pos2 = (j - 1) * sizeof(Pokemon);

    ofs.seekp(pos2);
    ofs.write((char*)&temp, sizeof(Pokemon));

    ofs.close();
}

void insert(const PokemonHandler& ph, const Pokemon& pokemon) 
{
    std::ofstream ofs(ph.FileName,std::ios::app);
    if (!ofs.is_open()||!ValidatePokemon(pokemon.name,pokemon.power))
    {
        return;
    }
    ofs.write((char*)&pokemon, sizeof(pokemon));
}


//should have used fstream
void textify(const PokemonHandler& ph, const char* filename) 
{
    std::ifstream ifs(ph.FileName,std::ios::binary);

    if (!ifs.is_open())
    {
        return;
    }

    int s = size(ph);

    for (size_t i = 0; i < s; i++)
    {
        Answer ans = CreatePokemonFromBin(ifs);
        if (ans.err == Errors::no_error)
        {
            SavePokemonInBin(ans.p,filename);
        }
        else
        {
            std::cout << "Error reading pokemon from file";
        }
    }
    ifs.close();
}

//Yup still no fstream ¯\_(`_`)_/¯ 
void untextify(const PokemonHandler& ph, const char* filename)
{
    std::ifstream ifs(filename, std::ios::binary);

    if (!ifs.is_open())
    {
        return;
    }

    PokemonHandler ph2 = newPokemonHandler(filename);
    int s = size(ph2);

    //Don't hate the player hate the game :)
    std::ofstream ofs(ph.FileName,std::ios::trunc);
    ofs.write((const char*)'\0', 0);
    ofs.close();


    for (size_t i = 0; i < s; i++)
    {
        Answer ans = CreatePokemonFromBin(ifs);
        if (ans.err == Errors::no_error)
        {
            SavePokemonInBin(ans.p, ph.FileName);
        }
        else
        {
            std::cout << "Error reading pokemon from file";
        }
    }
    ifs.close();

}


void print(PokemonHandler &ph)
{
    std::ifstream ifs(ph.FileName,std::ios::in|std::ios::binary);

    if (!ifs.is_open())
    {
        return;
    }
    int s = size(ph);

    for (size_t i = 0; i < s; i++)
    {
        Answer ans = CreatePokemonFromBin(ifs);
        if (ans.err == Errors::no_error)
        {
            std::cout << ans.p.name << " " << ans.p.type << " " << ans.p.power << "\n";
        }
    }
    std::cout << "\n\n\n";
    ifs.close();

}
int main()
{
    const char *fileName= "test.dat";

    /*
    Answer ans = CreatePokemon();
    if (ans.err==Errors::no_error)
    {
        //test purposes 'ans.p' works just as well.
        Pokemon p = {"ManagarmerTheSecondII",PokemonVariations::FLYING,66};
        Answer a = SavePokemonInBin(p, "WriteTest.dat");
        Answer pmc = CreatePokemonFromBin("WriteTest.dat");
    }
    */

    Pokemon p = { "ManagarmerTheSecondII",PokemonVariations::FLYING,66 };
    Answer a = SavePokemonInBin(p, fileName);

    p = { "Gergi",PokemonVariations::WATER,12 };
    a = SavePokemonInBin(p, fileName);

    p = { "Genadii",PokemonVariations::FLYING,44 };
    a = SavePokemonInBin(p, fileName);

    PokemonHandler ph = newPokemonHandler(fileName);
    int s = size(ph);

    Pokemon pokemon = at(ph, 2);

    print(ph);

    std::cout <<"pokemon at position 2 is: " << pokemon.name << " " << pokemon.type << " " << pokemon.power << "\n\n\n";

    swap(ph, 1, 3);

    print(ph);

    insert(ph, p);

    print(ph);

    char fil[] = "textify.dat";

    textify(ph, fil);

    PokemonHandler ph2 = newPokemonHandler(fil);

    print(ph2);

    untextify(ph, fil);

    print(ph);

    std::cout <<"\n" << s;
    std::remove(fileName);
    std::remove(fil);
}