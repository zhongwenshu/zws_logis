//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)

#include "stdafx.h"
#include "LogisTokenizer.h"
#include <regex>
#include <memory>


using namespace std;
using namespace logis;




bool LogisTokenizer::IsOperator(std::wstring::const_iterator it)
{
   return *it==L'+';
}

bool LogisTokenizer::IsParenthesis(std::wstring::const_iterator it)
{
   return *it==L'(' || *it==L')';
}

bool LogisTokenizer::IsSpace(std::wstring::const_iterator it)
{
   return *it==L' ' || *it==L'\t' || *it==L'\r' || *it==L'\n';
}

bool LogisTokenizer::IsKeywordStart(std::wstring::const_iterator it)
{
   return *it == L'%';
}

bool LogisTokenizer::IsText(std::wstring::const_iterator it)
{
   return *it>=L'0' && *it<='9' || *it>=L'A' && *it<='Z' || *it>=L'a' && *it<='z' || *it==L'-' || *it==L'_';
}

bool LogisTokenizer::IsValid(std::wstring::const_iterator it)
{
   return IsOperator(it) || 
         IsParenthesis(it) || 
         IsSpace(it) || 
         IsText(it) ||
         IsKeywordStart(it);
}



vector<wstring> LogisTokenizer::Run()
{
   vector<wstring> tokens;

   wstring::const_iterator it = _expr.begin();
   while (it != _expr.end())
   {
      if (!IsValid(it))
      {
         throw runtime_error("invalid input");
      }

      if (IsSpace(it))
      {
         while (true)
         {
            if (++it == _expr.end())
               break;

            if (!IsSpace(it))
               break;
         }

         continue;
      }

      if (IsKeywordStart(it))
      {
         _token.assign(1,*it);
         while (true)
         {
            if (++it == _expr.end())
            {
               tokens.push_back(_token);
               break;
            }

            if (IsText(it))
            {
               _token.push_back(*it);
            }
            else
            {
               tokens.push_back(_token);
               break;
            }

         }

         continue;
      }

      if (IsOperator(it))
      {
         _token.assign(1,*it);
         while (true)
         {
            if (++it == _expr.end())
            {
               tokens.push_back(_token);
               break;
            }

            if (IsOperator(it))
            {
               _token.push_back(*it);
            }
            else
            {
               tokens.push_back(_token);
               break;
            }
         }

         continue;
      }

      if (IsParenthesis(it))
      {
         _token.assign(1,*(it++));
         tokens.push_back(_token);

         continue;
      }

      if (IsText(it))
      {
         _token.assign(1,*it);
         while (true)
         {
            if (++it == _expr.end())
            {
               tokens.push_back(_token);
               break;
            }

            if (IsText(it))
            {
               _token.push_back(*it);
            }
            else
            {
               tokens.push_back(_token);
               break;
            }
         }

         continue;
      }
   }

   return tokens;
}


vector<wstring> logis::run_logis_tokenizer(const std::wstring& expr)
{
   std::unique_ptr<LogisTokenizer> tokenizer(new LogisTokenizer(expr));
   return tokenizer->Run();
}