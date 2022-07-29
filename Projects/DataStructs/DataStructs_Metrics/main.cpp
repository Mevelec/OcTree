#include <Logger.h>
#include <Profiler.h>

int main(int argc, char *argv[])
{
    INIT()
    PROFILER_BEGIN_SESSION("Charge", "Profilling/Profile.json");
    for(int i = 0; i < 1000; ++i){
        PROFILER_SCOPE("name")
    }
    PROFILER_END_SESSION();
    return 0; 
}