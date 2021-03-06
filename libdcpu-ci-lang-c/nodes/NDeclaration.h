/**

    File:       NDeclaration.h

    Project:    DCPU-16 Tools
    Component:  LibDCPU-ci-lang-c

    Authors:    James Rhodes

    Description:    Declares the NDeclaration AST class.

**/

#ifndef __DCPU_COMP_NODES_DECLARATION_H
#define __DCPU_COMP_NODES_DECLARATION_H

#include "NStatement.h"
#include <nodes/IDeclaration.h>

class NDeclaration : public NStatement, public IDeclaration
{
protected:
    NDeclaration(std::string type) : NStatement("declaration-" + type) { }
};

#endif
