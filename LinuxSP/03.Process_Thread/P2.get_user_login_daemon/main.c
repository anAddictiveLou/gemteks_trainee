#include "user.h"
#include "daemon.h"

int main(int argc, char** argv)
{   
    create_daemon(&daemon_handle, NULL);
}

