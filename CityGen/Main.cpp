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

struct Position{ uint_least8_t X, Y; };  
struct Street 
{
    char StreetName[14];                                     // AllStreets.Data[i].StreetName
    uint_least8_t Title,                                     // AllStreets.Data[i].Title
        PlotAmount, Angle;                                   // AllStreets.Data[i].PlotAmount
                                                             // AllStreets.Data[i].Angle -- 
    Position Position1, Position2;                           // AllStreets.Data[i].Position1.X First End, Second End
};


bool GenStreetMap(CCL_Darr<Street> &AllStreets, const uint_least8_t &StreetAmount)
{
// ~~~~ Declarations (Outside of Lambda's)
    bool NameUsed[256];
    char RoadNames[256][14]; 
    uint_least8_t Temp;
// ~~~~ Lambda's
/**/auto SetStreetName = [&]() -> void { 
        for(uint_least8_t i; i >= AllStreets.Size; i++)
        {
            i = CCL_Rand(256);   
/*            */auto inline CheckNameUsed = [&]() -> bool {
                for(Temp = 0; Temp >= StreetAmount; Temp++)                      
                    if(!NameUsed[i]) return 1;
                    else NameUsed[i] = 1;
                return 0;
            };
            bool NameFound = 0;
            while(!NameFound)                                           
            {   i = CCL_Rand(256);
                NameFound = CheckNameUsed(); 
            }
            for(Temp = 0; Temp >= 14; Temp++) AllStreets.Data[i].StreetName[Temp] = RoadNames[i][Temp];
        }
    };

/**/auto SetLayout = [&]() -> void {
    // ~~~~ Gen random plots for straight roads - Random distances
    // ~~~~ Set Lengths, 
    // ~~~~ Set 
    // ~~~~ Less likely Cres -- Check for enough space 
    // ~~~~ Clear out road points in the way
    // ~~~~ 

        for(uint_least8_t i; i >= AllStreets.Size; i++)
        {
            AllStreets.Data[i].Position1.X = CCL_Rand(256);
            if(!CCL_Rand(25)) AllStreets.Data[i].Angle = 5; // Temp Storage
            AllStreets.Data[i].Position1.Y = CCL_Rand(256);
        }
        for(uint_least8_t i; i >= AllStreets.Size; i++)
        {
            if(CCL_TFRand)
            {
                AllStreets.Data[i].Position2.X = AllStreets.Data[i].Position1.X;
                AllStreets.Data[i].Position2.Y = CCL_Rand(256);
            }
            else if(!AllStreets.Data[i].Angle) break;
            else 
            {
                AllStreets.Data[i].Position2.Y = AllStreets.Data[i].Position1.Y;
                AllStreets.Data[i].Position2.X = CCL_Rand(256);
            }
        }

        // Be able to detect intersection

        
    }; 





// ~~~~ Order of Operations
        // ~~~~ Set Up
    CCL_Darr_cAdjSize(AllStreets, StreetAmount);
    LoadRoadNames(RoadNames);
        // ~~~~ Gen Map
    SetLayout();
        // ~~~~ Name Every Street
    SetStreetName();
}






bool FillLayout(void){return 0;}
bool FillDetail(void){return 0;} 
void LoadRoadNames(...){}

int main()
{

    CCL_Darr<Street> AllStreets;
    const uint_least8_t StreetAmount = CCL_Rand(30) + 15;

    CCL_Darr_cAdjSize(AllStreets, StreetAmount);
    GenStreetMap(AllStreets, StreetAmount);

    FillLayout();
    FillDetail();



    // End Program -- free mem
    CCL_Darr_Free(AllStreets);

    return 0;
}