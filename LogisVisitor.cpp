//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#include "stdafx.h"
#include <regex>
#include "LogisTree.h"
#include "LogisVisitor.h"


using namespace std;
using namespace logis;


void LogisTreeToString::VisitNode(const LogisTreeNode* node)
{}

void LogisTreeToString::VisitExp(const LogisTreeNodeExp* exp)
{
   if (exp->GetChild(0)->GetType() == LogisNodeType::Kexp)
   {
      VisitKeyExp(static_cast<LogisTreeNodeKeyExp*>(exp->GetChild(0).get()));
   }
   else
   {
      VisitText(static_cast<LogisTreeNodeText*>(exp->GetChild(0).get()));
   }

   VisitPrimeExp(static_cast<LogisTreeNodePrimeExp*>(exp->GetChild(1).get()));
}

void LogisTreeToString::VisitKeyExp(const LogisTreeNodeKeyExp* kexp)
{
   _str += kexp->GetKeyword() + L"(";
   VisitExp(static_cast<LogisTreeNodeExp*>(kexp->GetChild(0).get()));
   _str += L")";
}

void LogisTreeToString::VisitPrimeExp(const LogisTreeNodePrimeExp* pexp)
{
   if (!pexp->GetOp().empty())
   {
      _str += pexp->GetOp();
      if (pexp->GetChild(0)->GetType() == LogisNodeType::Kexp)
      {
         VisitKeyExp(static_cast<LogisTreeNodeKeyExp*>(pexp->GetChild(0).get()));
      }
      else
      {
         VisitText(static_cast<LogisTreeNodeText*>(pexp->GetChild(0).get()));
      }

      VisitPrimeExp(static_cast<LogisTreeNodePrimeExp*>(pexp->GetChild(1).get()));
   }
}

void LogisTreeToString::VisitText(const LogisTreeNodeText* text)
{
   if (text->HasChild())
   {
      _str += L"(";
      VisitExp(static_cast<LogisTreeNodeExp*>(text->GetChild(0).get()));
      _str += L")";
   }
   else
   {
      _str += text->GetSn();
   }
}




void LogisTreeSearch::VisitNode(const LogisTreeNode* node)
{}

void LogisTreeSearch::VisitExp(const LogisTreeNodeExp* exp)
{
   if (exp->GetChild(0)->GetType() == LogisNodeType::Kexp)
   {
      VisitKeyExp(static_cast<LogisTreeNodeKeyExp*>(exp->GetChild(0).get()));
   }
   else
   {
      VisitText(static_cast<LogisTreeNodeText*>(exp->GetChild(0).get()));
   }

   if (!_found)
   {
      VisitPrimeExp(static_cast<LogisTreeNodePrimeExp*>(exp->GetChild(1).get()));
   }
}

void LogisTreeSearch::VisitKeyExp(const LogisTreeNodeKeyExp* kexp)
{
   VisitExp(static_cast<LogisTreeNodeExp*>(kexp->GetChild(0).get()));
}

void LogisTreeSearch::VisitPrimeExp(const LogisTreeNodePrimeExp* pexp)
{
   if (!pexp->GetOp().empty())
   {
      if (pexp->GetChild(0)->GetType() == LogisNodeType::Kexp)
      {
         VisitKeyExp(static_cast<LogisTreeNodeKeyExp*>(pexp->GetChild(0).get()));
      }
      else
      {
         VisitText(static_cast<LogisTreeNodeText*>(pexp->GetChild(0).get()));
      }

      if (!_found)
      {
         VisitPrimeExp(static_cast<LogisTreeNodePrimeExp*>(pexp->GetChild(1).get()));
      }
   }
}

void LogisTreeSearch::VisitText(const LogisTreeNodeText* text)
{
   if (text->HasChild())
   {
      VisitExp(static_cast<LogisTreeNodeExp*>(text->GetChild(0).get()));
   }
   else
   {
      wstring pattern = wstring(L"^.*") + _sn + L".*$";
      _found = regex_search(text->GetSn(),wregex(pattern));
   }
}


wstring logis::run_logis_visitor(const shared_ptr<LogisTreeNode>& tree)
{
   unique_ptr<LogisTreeToString> builder(new LogisTreeToString);
   tree->Accept(builder.get());

   return builder->GetString();
}


bool logis::search_sn(const shared_ptr<LogisTreeNode>& tree,const std::wstring& sn)
{
   unique_ptr<LogisTreeSearch> searcher(new LogisTreeSearch(sn));
   tree->Accept(searcher.get());

   return searcher->IsFound();
}