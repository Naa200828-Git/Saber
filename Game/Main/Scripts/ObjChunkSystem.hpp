// Define Map Size 
// Chunk Size (Square Size of max Distance of Gun / bullet (Maybe morph to in inventory or screen size))
// Is a chunk from long term memory?? Initializing, chunk instead of saving eveything saves memory?

struct Map_Chunk
{
    Map_Chunk(
        const unsigned char Obj_Positions, 
        const unsigned char Obj_IDs,
        const void* GroundTexture
        ){
        Obj_Data[Obj_Positions][Obj_IDs];
        void* GroundTexture;
    }

    // 
};

// LoadedChunks

// Log Position, Ground Texture in serate load then chunk
// check if moved,
// log distance need t travel awaay for new chunk or to discard chunk to avoid repeate expensive other checking