#ifndef H_CSVBUILDER
#define H_CSVBUILDER
//--------------------------------------------------------------------------------------------------
#include <string>
#include <fstream>
//--------------------------------------------------------------------------------------------------
class CCsvBuilder
{
public:
    CCsvBuilder();
    ~CCsvBuilder();

    bool AddDouble(const double numb);
    bool AddInteger(const int numb);

    bool AddText(const std::string str);
    bool AddText(const char* str);

    bool SetOutput(const std::string str);
    bool SetOutput(const char* str);

    void SetAutomaticSep(bool b);
    void SetAutomaticLine(bool b);

    bool AddSep();
    bool AddLine();

    bool SaveAndClose();

private:
    std::ofstream   *m_File;
    bool             m_AutomaticSep;
    bool             m_AutomaticLine;
};
//--------------------------------------------------------------------------------------------------
#endif // H_CSVBUILDER
//--------------------------------------------------------------------------------------------------
