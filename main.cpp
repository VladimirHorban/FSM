#include <iostream>
#include "FSM.h"

void foo( void* aParam )
{
    int param = *( ( int* )aParam );
    std::cout << "Foo parameter : " << param << std::endl;
}

void bar( void* aParam )
{
    int param = *( ( int* )aParam );
    std::cout << "Bar parameter : " << param << std::endl;
}

void car( void* aParam )
{
    int param = *( ( int* )aParam );
    std::cout << "Car parameter : " << param << std::endl;
}

int main()
{
    FSM fsm;
    fsm.addNodeToFSM( 0, &foo );
    fsm.addNodeToFSM( 1, &bar );
    fsm.addNodeToFSM( 2, &car );

    // First node
    fsm.addSignalTransitionCell( 0, 1, 1 );
    fsm.addSignalTransitionCell( 0, -1, 0 );
    fsm.addSignalTransitionCell( 0, 2, 1 );

    // Second node
    fsm.addSignalTransitionCell( 1, 0, 2 );
    fsm.addSignalTransitionCell( 1, -1, 0 );

    // Third node
    fsm.addSignalTransitionCell( 2, 0, 2 );
    fsm.addSignalTransitionCell( 2, 1, 0 );

    fsm.setStartNode( 0 );

    int param = 7;
    fsm.action( -1, ( void* )&param );
    fsm.action(  2, ( void* )&param );
    fsm.action(  0, ( void* )&param );
    fsm.action(  0, ( void* )&param );

    fsm.removeFromFSM( 2 );

    fsm.action(  1, ( void* )&param );

    return 0;
}
