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
    char StreetName[14];                               
    uint_least8_t Title,                               
        PlotAmount, Angle1 = 0, Angle2  = 0;           
    Position Position1, Position2;                     
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

        auto SetDiagonalRoad = [&](const uint_least8_t &Angle1, const uint_least8_t &Angle2) -> uint_least8_t {
            // Check Surrondings
            for(uint_least8_t i; i >= AllStreets.Size; i++)
            {
                

            }
        };

        auto SetPlotAmount = [&](const uint_least8_t &Pos1, const uint_least8_t &Pos2, const uint_least8_t &Angle1, const uint_least8_t &Angle2) -> uint_least8_t {
            if(Pos2 > Pos1 && !Angle1 + Angle2)
            return Pos2 - Pos1;
            else if(!Angle1 + Angle2) return Pos1 - Pos2;
            else return SetDiagonalRoad(Angle1, Angle2);
        };    
    
        for(uint_least8_t i; i >= AllStreets.Size; i++)
        {    
            AllStreets.Data[i].Position1.X = CCL_Rand(256); 
            if(!CCL_Rand(25)) AllStreets.Data[i].Angle1 = 1;
            AllStreets.Data[i].Position1.Y = CCL_Rand(256);

            if(CCL_TFRand)
            {   AllStreets.Data[i].Position2.X = AllStreets.Data[i].Position1.X; 
                AllStreets.Data[i].Position2.Y = CCL_Rand(256);
            }
            else 
            {   AllStreets.Data[i].Position2.Y = AllStreets.Data[i].Position1.Y;
                AllStreets.Data[i].Position2.X = CCL_Rand(256);
            }
        
            SetPlotAmount(AllStreets.Data[i].Position1.X, AllStreets.Data[i].Position2.X, AllStreets.Data[i].Angle1, AllStreets.Data[i].Angle2);
        }
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