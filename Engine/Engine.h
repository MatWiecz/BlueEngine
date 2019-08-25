//
// Created by Mateusz on 2019-08-25.
//

#ifndef BLUEENGINE_ENGINE_H
#define BLUEENGINE_ENGINE_H

typedef enum
{
    EngineCreated = 0x00000001,
    EngineInitiated = 
    
} EngineStatus;

inline EngineStatus operator|(EngineStatus a,
                              EngineStatus b)
{
    return static_cast<EngineStatus> (static_cast<unsigned int>(a) |
                                      static_cast<unsigned int>(b));
}

typedef enum
{
    ENGINE_OK,
    
} EngineRetVal;

typedef enum
{
    UserMode = 0x01,
    DeveloperMode = 0x02,
    DebugMode = 0x04
} EngineOperationMode;

inline EngineOperationMode operator|(EngineOperationMode a,
                                     EngineOperationMode b)
{
    return static_cast<EngineOperationMode> (static_cast<unsigned int>(a) |
                                             static_cast<unsigned int>(b));
}

class Engine
{
    private:
    
    unsigned int status;
    
    
    public:
    Engine();
    
    ~Engine();
    
    EngineRetVal SetOperationMode(EngineOperationMode mode);
    
    EngineRetVal Start();
    
    EngineRetVal Stop();
};

#endif //BLUEENGINE_ENGINE_H
