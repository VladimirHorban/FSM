#ifndef FSM_H
#define FSM_H

#include <vector>

class FSM
{
private:
    int mCurrentNodeIndex = 0;
    int mPrevNodeIndex    = 0;
    typedef void( *Func )( void* );

    struct SignalTransitionCell
    {
        int mNodeIndex     = 0;  // Index of node
        int mSignal        = 0;  // Input signal
        int mTransition    = 0;  // Index of node

        SignalTransitionCell(){}
        SignalTransitionCell( int aNodeIndex, int aSignal, int aTransition ) : mNodeIndex( aNodeIndex ), mSignal( aSignal ), mTransition( aTransition )
        {}
    };

    struct Node
    {
        int     mIndex           = 0;
        void ( *mFunc )( void* ) = nullptr;

        Node( int aIndex, Func aFunc ) : mIndex( aIndex ), mFunc( aFunc )
        {}

        void action( void* aParam )
        {
            mFunc( aParam );
        }
    };

    std::vector<SignalTransitionCell*>* mConversationTable = nullptr;
    std::vector<Node*>* mNodesVector                       = nullptr;

public:
    FSM();
    ~FSM();

    void addNodeToFSM( int aIndex, Func aFunc );
    void removeFromFSM( int aIndex );

    void addSignalTransitionCell( int aIndex, int aSignal, int aTransition );
    void removeSignalTransitionCell( int aIndex, int aSignal, int aTransition );
    void setStartNode( const int aIndex );
    void action( int aSignal, void* aParam );
};

#endif // FSM_H
