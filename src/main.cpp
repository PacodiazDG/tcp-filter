
#include "nfqueue/nfqueue_manager.h"
#include "toolkit/startup.h"

int main(int argc, char **argv)
{
    startup::iniT();
    nfqueue_control::nfqueue_manager *q = new nfqueue_control::nfqueue_manager(0, true);
    q->run();
    return 0;
}