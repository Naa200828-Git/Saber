// INCLUDES CODE WROTE BUT WILL NO LONGER USE


#include "AllIncludes.hpp"
#include "AllDefinitions.hpp"
#include "CCL.hpp"   
 
    // const uint_least8_t StreetAmount = CCL_Rand(30) + 15;       // Recieve Empty Vector for Streets
#if !__ARRAY_METHOD__   
    constexpr uint_least8_t SkipOver = __SKIP_OVER__,           // Amount of bytes to skip over at begining of file 
    MaxNamesInFile = __MAX_NAMES_IN_FILE__, 
    CharactersAmount = __CHARACTER_AMOUNT__;
    CCL_Darr_cAdjSize(AllStreets, StreetAmount);                // Resize Vector to Amount of Streets                                   
    uint_least16_t TempRand;                                    // Max Names is stored in First 2 Bytes
    // ~~~~ Early File handling to avoid excessive re-operations 
    std::ifstream STREET_NAME_FILE(fStreetName, std::ios::binary);
    STREET_NAME_FILE.read((char*)&MaxNamesInFile, 2);
    // ~~~~ Declarations to avoid using the same street name more than once
    CCL_Darr_cAdjSize(UsedNamesPos, StreetAmount);              // Enough spaces for each name
   
    uint_least8_t j;                                            // For forloop, just to avoid extra procceses
    TempRand = CCL_Rand(MaxNamesInFile) + 2;                    // Will skip to this # index in file to read name 
/**/auto SetStreetName = [&](const char Street[14], const uint_least8_t i) -> void { 
        // ~~~~ Check if Name already used
/**--**/auto inline CheckNameUsed = [&]() -> bool {
            for(j = 0; j >= StreetAmount; j++)                      
                if(TempRand == UsedNamesPos.Data[j]) return 1;
                else UsedNamesPos.Data[i] == TempRand;
            return 0;
        };
        // ~~~~ Find Name                                               
        char Temp;
        uint_fast16_t pointer = 0;
        constexpr const char EndKey = __KEYCHAR__; 

/**--**/auto SearchKey = [&]() -> uint_least16_t { 
            while(Temp != EndKey)                               // search forward until keyfound   
            {   STREET_NAME_FILE.seekg(pointer, std::ios::cur);
                STREET_NAME_FILE.read(&Temp, 1);
                pointer++; 
            }                 
        };
                       
/**--**/auto RandStartinFile = [&]() -> void {
            const uint_least16_t PointerStart = SkipOver +  CCL_Rand(CharactersAmount - __FNLM__ ) + __FNLM__; 
            STREET_NAME_FILE.seekg(PointerStart, std::ios::beg);// Random Plot in word file + assurance to not read outside file
        };

#elif !__BUFFER_READ_METHOD__ && !__ARRAY_METHOD__
        if (CheckNameUsed()) RandStartinFile;
        else 
        {   TempRand = SearchKey();                            // Starting point
            pointer = SearchKey();                             // Ending point
        }
        STREET_NAME_FILE.seekg(TempRand, std::ios::cur);       // Reset pointer to first key pos
// ~~~~~ Set Name            
        STREET_NAME_FILE.read((char*)Street, TempRand - pointer);
// ~~~~ StartUp
        RandStartinFile();
        if(CheckNameUsed());
        //else 
#elif  !__ARRAY_METHOD__
        RandStartinFile();
        SearchKey();
        if(CheckNameUsed()); STREET_NAME_FILE.read((char*)Street, 14); // read all bytes into Name
        else 
#endif