#include <iostream>
const int MaxPokemonName = 50;
const int MaxPokemonPower = 100;
const int MinPokemonPower = 10;


//The moment anything is done to this enum the following functions have to be revisited (they will break due to the way they are hard coded):
//ValidatePokemon,ValidatePokemonType,DisplayTypes(does not break when values of constants are changed. Breaks when new are added),CreateVariation,CreatePokemon.
//Got no idea how to do it better.
enum Errors 
{
    no_error,
    wrong_Input
};
struct Answer 
{
    Pokemon p;
    Errors err;
};
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
    char* name;
    PokemonVariations type;
    int power;
};

struct PokemonHandler 
{
    char* FileName;
};

bool ValidatePokemonName(char name[])
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

bool ValidatePokemonPower(int power)
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

bool ValidatePokemon(char name[], int power )
{
    bool ValidName = ValidatePokemonName(name);
    bool ValidPower = ValidatePokemonPower(power);
    return ValidName && ValidPower;
}

PokemonVariations CreateVariation(int type) 
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
        return Answer{ Pokemon{ name,vr,power},Errors::no_error };
    }
    return Answer{ Pokemon{},Errors::wrong_Input };
}

int main()
{
    Answer pmc=CreatePokemon();
    if (pmc.err==Errors::no_error)
    {

    }
}
