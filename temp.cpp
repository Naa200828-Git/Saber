
// Game Terminal WackaMole: ** Btw, should run in vsc built in termnial, for auto formatted escape keys

#define __ONLY_SIMPLE__  0  // Works :)
#define __USE_EXPERIMENTAL__ 0 // doesnt work :(
#define __SIMPLE_VERSION__  1 // avoid the bugs as of jan 9 !! RUN THIS STATE
#define __HIGHER_ENTROPY__ 0

// STL
#include <conio.h>
#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <thread>
#include <chrono>
#include <ctime>

// ~~~ Global Mem Space: - Mem declared here gets placed in designated GMS, is faster & saves memory ** small program, use alot

    // ~~~ Hole & Mole Sprites ** If enought Time, potent opti:  One big Arr With indented Acsess
constexpr const char ccEmptyHole[] = { // 8 x 11 
    ' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',
    ' ',' ','#','#','.','.','.','#','#',' ',' ',
    ' ','#','.','.','.','.','.','.','.','#',' ',
    '#','.','.','.','.','.','.','.','.','.','#',
    '#','.','.','.','.','.','.','.','.','.','#',
    ' ','#','.','.','.','.','.','.','.','#',' ',
    ' ',' ','#','#','.','.','.','#','#',' ',' ',
    ' ',' ',' ',' ','#','#','#',' ',' ',' ',' '
},
ccMolePeek1[] = { // 8 x 11
    ' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',
    ' ',' ','#','#','.','.','.','#','#',' ',' ',
    ' ','#','.','.','.','.','.','.','.','#',' ',
    '#','.','.','^','.','.','.','^','.','.','#',
    '#','.','.','*','.','.','.','*','.','.','#',
    ' ','#','.','.','.','.','.','.','.','#',' ',
    ' ',' ','#','#','.','.','.','#','#',' ',' ',
    ' ',' ',' ',' ','#','#','#',' ',' ',' ',' '
},
ccMolePeek2[] = { // 8 x 11
    ' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',
    ' ',' ','#','#','.','.','.','#','#',' ',' ',
    ' ','#','.','.','_','_','_','.','.','#',' ',
    '#','.','.','/',' ',' ',' ','\\','.','.','#',
    '#','.','/',' ','*',' ',' ','*','\\','.','#',
    ' ','#','.','.',' ',' ',' ','.','.','#',' ',
    ' ',' ','#','#','.','.','.','#','#',' ',' ',
    ' ',' ',' ',' ','#','#','#',' ',' ',' ',' '
},
ccMole[] = { // 8 x 11
    ' ',' ',' ',' ','_','_','_',' ',' ',' ',' ',
    ' ',' ','#','/',' ',' ',' ','\\','#',' ',' ',
    ' ','#','/','~',' ',' ',' ','^','\\','#',' ',
    '#','|',' ','*',' ',' ',' ','*',' ','|','#',
    '#','|',' ',' ',' ',' ',' ',' ',' ','|','#',
    ' ','#','.',' ',' ',' ',' ',' ','.','#',' ',
    ' ',' ','#','#','.','.','.','#','#',' ',' ',
    ' ',' ',' ',' ','#','#','#',' ',' ',' ',' '
};

    // ~~~ Custom Vector w/ +2 Adj 
template <typename Type> struct CCL_Darr {            // Using OOP, Heap Allocated, expandble, minimal Arr, w/ <typedef>  
    Type * Data = nullptr;                            // Pointer to dynamically allocated memory
    uint16_t Size = 5;
};
    // ~~~ Base Function: Arr Size += 2:
template <typename Type> void CCL_Darr_cAdjSize(CCL_Darr<Type> & Arr, const uint_least8_t cAdjSize) {
    const uint_least16_t NewSize = Arr.Size + cAdjSize;// Increase size by 2 for default Field Increase
    Type * NewData = new Type[NewSize];                // Allocate new memory
    
    for (int i = Arr.Size; i < NewSize; ++i) 
        NewData[i] = Type();

    Arr.Data = NewData;                                // Point to the new data
    Arr.Size = NewSize;                                // Update the size
}      
    // ~~~ Free CCL_Darr mem
template <typename Type> void CCL_Darr_Free(CCL_Darr<Type>& Arr) {
    delete[] Arr.Data;
    Arr.Data = nullptr;
    Arr.Size = 0; // ** 
}
    // ~~~ Field, Amount of Holes      
uint_least16_t FieldSize = 0,                          // Holes that store the stages of present mole, can be more than 255 (uint8) ** doubt will reach
    // ~~~ Chance at Mole Peek     
DiffChance = 1,                                        // for now, possibility of a fake, if 0, non at all, + DEFINE MAX  
    // ~~~ Points
Points = 0;
    // ~~~ Custom Rand: Xorshift seed initialization
#if __USE_EXPERIMENTAL__ && !__HIGHER_ENTROPY__

uint32_t CCL_XOR_13L17R5Lecti_32_t(const uint32_t cMax, ...) {  // Xorshift RNG function
    uint32_t Seed = (uint32_t)(std::time(0));
    Seed ^= Seed << 13;
    Seed ^= Seed >> 17;
    Seed ^= Seed << 5;
    
    Seed = Seed % (cMax + 1);

    if (&cMax + 8) 
        return Seed;
    else CCL_XOR_13L17R5L_32_t(Seed, 0); // ~~~~ Higher Entropy, use goto?
}
#define CCL_XOR_13L17R5Lecti_32_t CCL_XOR_13L17R5L_32_t // legacy
#elif !__HIGHER_ENTROPY__

uint32_t CCL_XOR_13L17R5L_32_t(const uint32_t cMax) {  // Xorshift RNG function
    uint32_t Seed = (uint32_t)(std::time(0));
    Seed ^= Seed << 13;
    Seed ^= Seed >> 17;
    Seed ^= Seed << 5;
    
    return Seed % (cMax + 1);
}

#else

uint32_t CCL_XOR_13L17R5L_32_t(const uint32_t cMax) {  
    // Combine time-based entropy with random device entropy
    uint32_t Seed = (uint32_t)(std::time(0));
    Seed ^= (uint32_t)(std::time(0)) && 0b1111;

    // Xorshift with more entropy mixing
    Seed ^= Seed << 13;
    Seed ^= Seed >> 17;
    Seed ^= Seed << 5;
    
    // More bit manipulation for additional entropy
    Seed ^= Seed >> 3;
    Seed ^= Seed << 21;
    Seed ^= Seed >> 4;
    
    // Return the value in the range [0, cMax]
    return Seed % (cMax + 1);
}

#endif
    // ~~~ T/F Rand
#define CCL_TFRand CCL_XOR_13L17R5L_32_t(1)
#define CCL_Rand(cMax) CCL_XOR_13L17R5L_32_t(cMax)
    // ~~~ Simple Wait Statement
#define CCL_Wait(Seconds) std::this_thread::sleep_for(std::chrono::seconds(CCL_Rand(Seconds) + 1));
    // ~~~ User Input
uint_least16_t Input = 0; // remember to handle as int, random max
    // Logic Slected Hole for State
unsigned int SelectedHole = 0;
// ~~~ End GMS

void SetCursor(const uint32_t cRow, const uint32_t cCol) { //change out of inline if multiple uses in call stack ** LEARN THE CURSOR COMMANDS
    char Command[20]; // Enough to hold the escape sequence
    int Length = sprintf(Command, "\e[%u;%uH", cRow, cCol);
    write(STDOUT_FILENO, Command, Length);
}

void ResizePrintField() 
{           
    write(STDOUT_FILENO, "\n", 1);
    for (uint_least8_t i = 0; i < 8; i++) {                 
        for (uint_least8_t n = 0; n < 5; n++) {      
            write(STDOUT_FILENO, &ccEmptyHole[i * 11], 11);            
            write(STDOUT_FILENO, "     ", 5);  
        }
        write(STDOUT_FILENO, "\n", 1);                           
    }

    FieldSize += 4;
}

void PrintMole(const char* Sprite) // is by copy?
{   // Lots of Numbers for proper indenting, overwriting, spacing and other stuff
    const uint32_t Col = SelectedHole / 5,
        Row = SelectedHole - 5 * Col;

    for (uint_least8_t i = 0; i < 8; i++) { 
        SetCursor((i + (Col * 9) + 2), (Row * 16) + 1);   // ** not working on index 0,(1) so you do need a col + 1, if can fix, minor optimzation
        write(STDOUT_FILENO, &Sprite[i * 11], 11);            
    }

    SetCursor(((FieldSize / 5) * 9) + 9, 1);              // works by finding what index on y, (amount of rows down, * by spacing for each, + indented spacing for new one)
    write(STDOUT_FILENO, "\n", 1);                                    // for correct spacing, fixes bug :)
}

#if !__ONLY_SIMPLE__

void WaitInput(const uint8_t Seconds, const bool MolePresent)
{
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    if (MolePresent)
    {
        while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time).count() < Seconds)
        {
            if (_kbhit()) // Check if a key is pressed
            {
                char16_t Input = static_cast<char16_t>(_getch()); // Read the key without waiting
                char buffer[32];
                int length = snprintf(buffer, sizeof(buffer), "Input received: %lc\n", Input);
                write(1, buffer, length); // Use write() for output
                return; // Exit as soon as input is detected ** WORKS AS A SETTING
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Small delay to avoid busy waiting
        } // WASY TOO FAST ** Can prob remove alot of the excess ** FINALLY WORKS THO ** ADD RESULTS PAGE THING & INSTURCUTIONS AND STARTUPT WaIT TIME
    }
}

#else 

void WaitInput(const uint8_t Seconds)
{
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time).count() < Seconds)
    {
        if (_kbhit()) // Check if a key is pressed
        {
            char16_t Input = static_cast<char16_t>(_getch()); // Read the key without waiting
            char buffer[32];
            int length = snprintf(buffer, sizeof(buffer), "Input received: %lc\n", Input);
            write(1, buffer, length); // Use write() for output
            return; // Exit as soon as input is detected
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Small delay to avoid busy waiting
    } // WASY TOO FAST ** Can prob remove alot of the excess ** FINALLY WORKS THO ** ADD RESULTS PAgE THING & INSTURCUTIONS AND STARTUPT WaIT TIME
}

#endif

bool Logic_PopUp()
{   // Runs One State, Asembles State & Executes, Ends.
    // Diff States / Actions ~~~ Ex:
    // Peek, Dip.            ~~~ Short: Peek 2,
    // Peek Heights 1, 2, 3. ~~~ Long:  Dip,
    // Stay, Leave.          ~~~ Short: Peek 1,
    // Short, Long.          ~~~ Long:  Peek 2; Stay.
    
// ~~~~ State Determination
    SelectedHole = CCL_Rand(FieldSize);
#if !__ONLY_SIMPLE__
    if (DiffChance && !CCL_Rand(DiffChance))              // Any Peek Chance, if so; Create States, DiffChance == 0, means no complexity chance, but a HIGH Dif. is a low comlexity chance
    {                                                     //   Else Just Skip to Simple State
        CCL_Darr<uint_least8_t> State;                    // Just a Vector
        CCL_Darr_cAdjSize(State, CCL_Rand(6 /* - x / ratio*/));         // Init All Empty States w/ random amount, 0 - max // THIS IS ALSO A SETTING

        for (uint_least8_t i = 0; i < State.Size; i++)    // Use Diff Chance to Also Determine the difficulty of Peek (/ The amount of Actions in State)
            for (uint_least8_t j = 0; j < 3; j++)         // Instance to Pack each bit needed
                State.Data[i] |= CCL_TFRand << j;         // Packing the bits
                // (1: Peek bit ID || Dip), ~~~ If 0 found at first Peek Bit ID, rest of ID Does Not Matter
                // (2: Peek bit ID),        ~~~ Short Pause Time: _ 
                //                          ~~~ Long Pause Time: _
                // (3: Short || Long)       ~~~ Std Pause Time: _
                // (4: Stay || Leave) (Last State Only) ~~~ Stay Or Leave, 
        State.Data[State.Size] |= CCL_TFRand << 4;        // pack final extra bit in final state

// ~~~~ Run Complex State, ** Ik, real inline saves +100 asm in tricky -- 03 compiler, pmyb tho
        
        for (uint_least8_t i = 0; i < State.Size; i++)                        // Iterate Over Each State
        {   constexpr const char* arr[] = {ccEmptyHole, ccMolePeek1, ccMolePeek2, ccMole};                                              
            PrintMole(arr[(State.Data[i] & 0b11)]);             // print
            if (State.Data[i] & 0b100) { WaitInput(1, State.Data[i] & 0b11); }                       // maybe change to put in print mole, & note what pause for (mole wait)
            else                       { WaitInput(3, State.Data[i] & 0b11); }
        }

        if (State.Data[State.Size] & 0b1000) 
        {
            PrintMole(ccMole); // Last State bit 4 check, stay or leave.
            WaitInput(2, 1);
            PrintMole(ccEmptyHole); // make into function
        }
        else PrintMole(ccEmptyHole); // Print Empty / Rest, NO LOGIC MIGHT BE PROBLEM ** 
    
        CCL_Darr_Free(State);
        return 1;               // Ran complex State
    }

// ~~~~ Run Simple State 

    else
    {
        PrintMole(ccMole);
        WaitInput(2, 1);
        PrintMole(ccEmptyHole);
        return 0;   // ran simple state
    }

#else
    PrintMole(ccMole);
    WaitInput(2, 1);
    PrintMole(ccEmptyHole);
    return 0;   // ran simple state
#endif

}

void ResetScreeen()
{
    write(STDOUT_FILENO, "\e[2J", 4); // For VSC Built In Terminal // ** problem with wirtes commands stuff
    write(STDOUT_FILENO, "\e[0;0H", 6);           // Explicitly set the cursor at the top-left before starting
}

int main() 
{
// ~~~~ Startup

    ResetScreeen(); // *

    write(STDOUT_FILENO, "WackaMole: Press a key when you see the mole pop up!\n", 54);
    write(STDOUT_FILENO, "You have 3 lives. Have Fun!\n", 29);
    write(STDOUT_FILENO, "Press any key to start: ", 23);
    _getch(); 

    ResetScreeen();
    ResizePrintField();                 // Init Print 

// ~~~~ Game Loop

    uint8_t StateType;  // problem might be with return and breaking
    int Lives = 3;

    while (Lives)       // this while loop is ending itself, 
    {   // is redunant with no complext states #if

#if !__ONLY_SIMPLE__
            StateType = Logic_PopUp(); // Runs Logic & accepts Input
#else
            Logic_PopUp();
#endif
#if !__SIMPLE_VERSION__
        if ((Input - '0') == SelectedHole) // Successful input
        {
#  if !__ONLY_SIMPLE__  // this not working
                if (StateType) StateType = 75; // reuse write(STDOUT_FILENO, "TEST1", 5);
                else StateType = 45;    

                if ((Points + StateType) / 200 > Points / 200) ResizePrintField(); // if surpass next benchmark, add a new layer
                Points += StateType;
#  else 
            if ((Points + 45) / 200 > Points / 200) ResizePrintField(); // if surpass next benchmark, add a new layer
                Points += 45;
#  endif
        }        
        else if (!Input) break;
        else Lives--; // Fail  
#endif
    }

// ~~~~ Close

    CCL_Wait(2);
    ResetScreeen();
 
    write(STDOUT_FILENO, &Points, 2);
    write(STDOUT_FILENO, "\nYou Lost!", 10);
}   
