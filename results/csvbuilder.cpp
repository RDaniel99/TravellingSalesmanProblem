#include "csvbuilder.h"
#include <string>
#include <fstream>
#include <iostream>
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
CCsvBuilder::CCsvBuilder()
{
    m_File          = 0;
    m_AutomaticLine = false;
    m_AutomaticSep  = false;
}
//--------------------------------------------------------------------------------------------------
CCsvBuilder::~CCsvBuilder()
{
    if(m_File)
        delete m_File;
}
//--------------------------------------------------------------------------------------------------
bool CCsvBuilder::AddInteger(const int numb)
{
    string toAdd = std::to_string(numb);

    return AddText(toAdd);
}
//--------------------------------------------------------------------------------------------------
bool CCsvBuilder::AddDouble(const double numb)
{
    string toAdd = std::to_string(numb);

    for(unsigned int i = 0; i < toAdd.size(); i++)
        if(toAdd[i] == '.') toAdd[i] = ',';

    return AddText(toAdd);
}
//--------------------------------------------------------------------------------------------------
bool CCsvBuilder::AddText(const string str)
{
    if(!m_File)
        return false;

    *m_File << str;

    if(m_AutomaticLine)
        return AddLine();

    if(m_AutomaticSep)
        return AddSep();

    return true;
}
//--------------------------------------------------------------------------------------------------
bool CCsvBuilder::AddText(const char* str)
{
    if(!m_File)
        return false;

    for(char* i = const_cast<char*>(str); *i; i++)
        *m_File << *i;

    if(m_AutomaticLine)
        return AddLine();

    if(m_AutomaticSep)
        return AddSep();

    return true;
}
//--------------------------------------------------------------------------------------------------
bool CCsvBuilder::AddSep()
{
    if(!m_File)
        return false;

    *m_File << ';';

    return true;
}
//--------------------------------------------------------------------------------------------------
bool CCsvBuilder::AddLine()
{
    if(!m_File)
        return false;

    *m_File << '\n';

    return true;
}
//--------------------------------------------------------------------------------------------------
bool CCsvBuilder::SetOutput(const char* str)
{
    if(m_File)
        m_File->close();

    m_File = new ofstream(str);

    m_File->flush();

    return true;
}
//--------------------------------------------------------------------------------------------------
bool CCsvBuilder::SetOutput(const string str)
{
    if(m_File)
        m_File->close();

    m_File = new ofstream(str.c_str());

    m_File->flush();

    return true;
}
//--------------------------------------------------------------------------------------------------
void CCsvBuilder::SetAutomaticLine(bool b)
{
    m_AutomaticLine = b;
}
//--------------------------------------------------------------------------------------------------
void CCsvBuilder::SetAutomaticSep(bool b)
{
    m_AutomaticSep = b;
}
//--------------------------------------------------------------------------------------------------
bool CCsvBuilder::SaveAndClose()
{
    if(!m_File)
        return false;

    m_File->close();

    delete m_File;

    return true;
}
//--------------------------------------------------------------------------------------------------
