#include <iostream>
int const peakNameMaxChar = 11;

struct Peak
{
    char name[peakNameMaxChar];
};

struct Rib
{
    Peak peakStart;
    Peak peakEnd;
};

struct Graph
{
    int countOfPeaks = 0;
    int countOfRibs = 0;
    Rib* ribs;
};

int GetStrLen(const char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

Peak ValidatePeak(const Peak& p)
{
    Peak res = p;
    while (GetStrLen(res.name) < 0)
    {
        std::cout << "Enter valid data! (lenght has to be more than 1 character)";
        std::cin >> res.name;
    }
    return res;
}

bool VerifyRibExist(const Graph& grp, const Rib& rib)
{
    for (size_t i = 0; i < grp.countOfRibs; i++)
    {
        if (strcmp(grp.ribs[i].peakStart.name, rib.peakStart.name) == 0 && strcmp(grp.ribs[i].peakEnd.name, rib.peakEnd.name) == 0)
        {
            return true;
        }
    }
    return false;
}

bool PeakExist(const Graph& grp, const Peak& peak)
{
    for (size_t i = 0; i < grp.countOfRibs; i++)
    {
        if (strcmp(grp.ribs[i].peakStart.name, peak.name) == 0 || strcmp(grp.ribs[i].peakEnd.name, peak.name) == 0)
        {
            return true;
        }
    }
    return false;
}

void AddRib(Graph& grp, const Peak& p1, const Peak& p2)
{
    Rib rib = { p1,p2 };
    if (VerifyRibExist(grp, rib))
    {
        std::cout << "Such rib exists already!";
        return;
    }
    int peaks = PeakExist(grp, rib.peakStart) + PeakExist(grp, rib.peakEnd);

    grp.ribs[grp.countOfRibs] = rib;
    grp.countOfPeaks += 2 - peaks;
    grp.countOfRibs += 1;
}

int FindDegreeOfPeak(const Graph& gr, const Peak& p)
{
    int countEntering = 0, countLeaving = 0;

    for (size_t i = 0; i < gr.countOfPeaks; i++)
    {
        if (strcmp(gr.ribs[i].peakEnd.name, p.name) == 0)
        {
            countEntering++;
        }
        if (strcmp(gr.ribs[i].peakStart.name, p.name) == 0)
        {
            countLeaving++;
        }
    }
    return countEntering + countLeaving;
}

void FillGraphWithRibs(Graph& gr, const int m)
{
    for (size_t i = 0; i < m; i++)
    {
        Peak peak1, peak2;
        std::cout << "Please enter the name of the first peak (" << i + 1 << ") : ";
        std::cin >> peak1.name;
        peak1 = ValidatePeak(peak1);

        std::cout << "Please enter the name of the secong peak (" << i + 1 << ") : ";
        std::cin >> peak2.name;
        peak2 = ValidatePeak(peak2);

        AddRib(gr, peak1, peak2);
    }
}
Graph CreateGraph(const int m)
{
    if (m <= 0)
    {
        std::cout << "Error throw!";
    }
    Rib* ribs = new Rib[m];
    Graph* result = new Graph{ 0,0,ribs };
    FillGraphWithRibs(*result, m);
    return *result;
}

void DeleteGraph(Graph& gr)
{
    delete[] gr.ribs;
    gr.countOfPeaks = 0;
    gr.countOfRibs = 0;
}

Graph DeleteRib(Graph& gr, const Rib& rib)
{
    if (VerifyRibExist(gr, rib) == 0)
    {
        std::cout << "It's already deleted!";
        return Graph{ 0,0,new Rib{Peak{""},Peak{""}} };
    }
    else
    {
        Rib* ribs = new Rib[gr.countOfRibs - 1];
        Graph* result = new Graph{ gr.countOfPeaks,gr.countOfRibs,ribs };
        for (size_t i = 0; i < gr.countOfRibs; i++)
        {
            if (strcmp(gr.ribs[i].peakEnd.name, rib.peakEnd.name) == 0 && strcmp(gr.ribs[i].peakStart.name, rib.peakStart.name) == 0)
            {
                continue;
            }
            result[0].ribs[i] = gr.ribs[i];
        }
        DeleteGraph(gr);
        return *result;
    }
}

bool IsGraphFull(const Graph& gr)
{
    if (gr.countOfPeaks * (gr.countOfPeaks - 1) / 2 == gr.countOfRibs)
    {
        return true;
    }
    return false;
}

int main()
{
    return 0;
}
