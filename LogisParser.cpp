//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)
//这是免费软件，可以更改源码，但请保留此头部说明，谢谢

//logistics expression
//%railway(zhongtong6666 + yuantong(8888 + 5641)) + %airline(JD0001-1-1)
//it is freeware, you could edit the source code, but please remain this header, thank you

#include "stdafx.h"
#include "LogisParser.h"
#include <regex>
#include <memory>
#include "LogisTree.h"


using namespace std;
using namespace logis;




shared_ptr<LogisTreeNode> LogisParser::Run()
{
   shared_ptr<LogisTreeNode> tree(new LogisTreeNode(LogisNodeType::Root));
   _currentnode = tree.get();

   _tokenit = _tokens.begin();

   if (Exp())
   {
      _success = true;
   }

   return tree;
}

bool LogisParser::NextToken()
{
   if (_state != WrongToken)
   {
      if (_tokenit != _tokens.end()-1)
      {
         _tokenit++;
         return true;
      }
   }
   
   return false;
}

bool LogisParser::Keyword()
{
   wregex pattern(L"^%[a-zA-Z0-9-_\u4e00-\u9fa5]+$"); //以%开头，至少一个数字、字母、减号、下划线、汉字
   return regex_search(*_tokenit,pattern);
}

bool LogisParser::Sn()
{
   wregex pattern(L"^[a-zA-Z0-9-#]+$"); //至少一个数字、字母、减号、井号
   return regex_search(*_tokenit,pattern);
}

//Exp -> Keyexp Exp'
//     | Text Exp'
bool LogisParser::Exp()
{
   shared_ptr<LogisTreeNodeExp> node(new LogisTreeNodeExp);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (KeyExp())
   {
      _currentnode = node.get();
      return PrimeExp();
   }
   else
   {
      _currentnode = node.get();
      _currentnode->PopChild();

      if (Text())
      {
         _currentnode = node.get();
         return PrimeExp();
      }
   }

   return false;
}

//Exp' -> + Keyexp Exp'
//      | + Text Exp'
//      | null
bool LogisParser::PrimeExp()
{
   shared_ptr<LogisTreeNodePrimeExp> node(new LogisTreeNodePrimeExp);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (*_tokenit == L"+")
   {
      node->SetOp(*_tokenit);

      if (NextToken())
      {
         if (KeyExp())
         {
            _currentnode = node.get();
            return PrimeExp();
         }
         else
         {
            _currentnode = node.get();
            _currentnode->PopChild();

            if (Text())
            {
               _currentnode = node.get();
               return PrimeExp();
            }
         }
      }
   }
   else if (*_tokenit==L")" || _tokenit == _tokens.end()-1)
   {
      return true;
   }

   _state = WrongToken;
   return false;
}

//Keyexp -> keyword (Exp)
bool LogisParser::KeyExp()
{
   shared_ptr<LogisTreeNodeKeyExp> node(new LogisTreeNodeKeyExp);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (Keyword())
   {
      node->SetKeyword(*_tokenit);

      if (NextToken())
      {
         if (*_tokenit == L"(")
         {
            if (NextToken())
            {
               if (Exp())
               {
                  if (*_tokenit == L")")
                  {
                     NextToken();
                     return true;
                  }
               }
            }
         }
      }
   }

   return false;
}

//Text -> (Exp)
//      | sn
bool LogisParser::Text()
{
   shared_ptr<LogisTreeNodeText> node(new LogisTreeNodeText);
   _currentnode->AddChild(node);
   _currentnode = node.get();

   if (*_tokenit == L"(")
   {
      if (NextToken())
      {
         if (Exp())
         {
            if (*_tokenit == L")")
            {
               NextToken();
               return true;
            }
         }
      }
   }
   else if (Sn())
   {
      node->SetSn(*_tokenit);

      NextToken();
      return true;
   }

   return false;
}


bool logis::test_logis_parser(const std::vector<std::wstring>& tokens)
{
   std::unique_ptr<LogisParser> parser(new LogisParser(tokens));
   parser->Run();

   return parser->IsSuccess();
}

std::shared_ptr<LogisTreeNode> logis::run_logis_parser(const std::vector<std::wstring>& tokens)
{
   std::unique_ptr<LogisParser> parser(new LogisParser(tokens));
   return parser->Run();
}