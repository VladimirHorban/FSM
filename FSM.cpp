#include "FSM.h"

FSM::FSM()
{
    mNodesVector       = new std::vector<Node*>;
    mConversationTable = new std::vector<SignalTransitionCell*>;
}

FSM::~FSM()
{
    delete mNodesVector;
    delete mConversationTable;
}

void FSM::addNodeToFSM( int aIndex, Func aFunc )
{
    Node* node = new Node( aIndex, aFunc );
    mNodesVector->push_back( node );
}

void FSM::removeFromFSM( int aIndex )
{
    int offset = 0;
    for( Node* nodeIt : *mNodesVector )
    {
        if( nodeIt->mIndex == aIndex )
        {
            delete nodeIt;
        }
        else
            offset++;
    }
    mNodesVector->erase( mNodesVector->begin() + offset );
}

void FSM::addSignalTransitionCell( int aIndex, int aSignal, int aTransition )
{
    SignalTransitionCell* cell = new SignalTransitionCell( aIndex, aSignal, aTransition );
    mConversationTable->push_back( cell );
}

void FSM::removeSignalTransitionCell( int aIndex, int aSignal, int aTransition )
{
    int offset = 0;
    for( SignalTransitionCell* cellIt : *mConversationTable )
    {
        if( cellIt->mNodeIndex == aIndex && cellIt->mSignal == aSignal && cellIt->mTransition == aTransition )
        {
            delete cellIt;
        }
        else
            offset++;
    }
    mConversationTable->erase( mConversationTable->begin() + offset );
}

void FSM::setStartNode( const int aIndex )
{
    mCurrentNodeIndex = aIndex;
}

void FSM::action( int aSignal , void *aParam )
{
    for( Node* nodeIt : *mNodesVector )
    {
        if( nodeIt->mIndex == mCurrentNodeIndex )
        {
            for( SignalTransitionCell* cellIt : *mConversationTable )
            {
                if( cellIt->mNodeIndex == mCurrentNodeIndex && cellIt->mSignal == aSignal )
                {
                    mPrevNodeIndex    = mCurrentNodeIndex;
                    mCurrentNodeIndex = cellIt->mTransition;
                }
            }

            nodeIt->action( aParam );
            return;
        }
    }
}
