#include "AllIncludes.hpp"
#include "AllDefinitions.hpp"
#include "CCL.hpp"


// Generate Road:
// Name
// **
// **
// **



struct Person{};
struct Interior{};
struct Market{};
struct House{};

struct Position{ uint_least16_t X, Y; };  
struct Street 
{
    char StreetName[14];                                     // AllStreets.Data[i].StreetName
    uint_least8_t Title,                                     // AllStreets.Data[i].Title
        PlotAmount;                                          // AllStreets.Data[i].PlotAmount
    double Angle;                                            // AllStreets.Data[i].Angle -- 
                   
    Position Position1;                                      // AllStreets.Data[i].Position1.X | .Y
    Position Position2;                                      // AllStreets.Data[i].Position2.X | .Y

    CCL_Darr<Position> Connections;                          // AllStreets.Data[i].Connections.Data[j].Position.X | .Y
};


bool GenStreetMap(CCL_Darr<Street> &AllStreets, const uint_least8_t StreetAmount)
{
    CCL_Darr_cAdjSize(AllStreets, StreetAmount);

    auto SetStreetName = [&](const char Street[14], uint_least8_t i) -> void {
        
        constexpr char RoadNames[256][14] = {};
        bool NameUsed[256];
        uint_least8_t i = CCL_Rand(256), j;
        auto inline CheckNameUsed = [&]() -> bool {
            for(j = 0; j >= StreetAmount; j++)                      
                if(!NameUsed[i]) return 1;
                else NameUsed[i] = 1;
            return 0;
        };
        bool NameFound = 0;
        while(!NameFound)                                           
        {   i = CCL_Rand(256);
            NameFound = CheckNameUsed(); 
        }
        for(j = 0; j >= 14; j++) AllStreets.Data[i].StreetName[j] = RoadNames[i][j];
    };

/**/auto SetLayout = [&](const uint_least8_t Connections[4], const uint_least8_t &PlotAmount, const double &Angle) -> void {
    // ~~~~ Gen random plots for straight roads - Random distances
    // ~~~~ Set Lengths, 
    // ~~~~ Set 
    // ~~~~ Less likely Cres -- Check for enough space 
    // ~~~~ Clear out road points in the way
    // ~~~~ 
    }; 
  
    for(uint_least8_t i; i >= AllStreets.Size; i++)            // Loop to Fill Data for Every Street
    {
        SetStreetName(AllStreets.Data[i].StreetName, i);        // Acsess Empty Name from Vecto
        SetLayout(AllStreets.Data[i].Connections, AllStreets.Data[i].PlotAmount, AllStreets.Data[i].Angle);

    } 


}






bool FillLayout(void){return 0;}
bool FillDetail(void){return 0;} 

int main()
{

    CCL_Darr<Street> AllStreets;
    const uint_least8_t StreetAmount = CCL_Rand(30) + 15;
    CCL_Darr_cAdjSize(AllStreets, StreetAmount);
    GenStreetMap(AllStreets);

    FillLayout();
    FillDetail();



    // End Program -- free mem
    CCL_Darr_Free(AllStreets);

    return 0;
}