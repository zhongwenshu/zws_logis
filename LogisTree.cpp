//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

//物流表达式
//%铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1)

#include "stdafx.h"
#include <algorithm>
#include "LogisTree.h"
#include "LogisVisitor.h"


using namespace std;
using namespace logis;



void LogisTreeNode::Accept(LogisVisitor* visitor) const
{
   int i = 0;
   for (auto it=GetChildren().begin(); it!=GetChildren().end(); it++,i++)
   {
      GetChild(i).get()->Accept(visitor);
   }

   visitor->VisitNode(this);
}

int LogisTreeNode::height() const
{
   int h = 0;
   
   if (HasChild())
   {
      h = 1;
      auto& it = max_element(GetChildren().begin(),GetChildren().end(),[&](const shared_ptr<LogisTreeNode>& lhs,const auto& rhs)
      {
         return lhs->height() < rhs->height();
      });
      h += (*it)->height();
   }

   return h;
}

int logis::get_tree_height(const std::shared_ptr<LogisTreeNode>& tree)
{
   return tree->height();
}

void LogisTreeNodeExp::Accept(LogisVisitor* visitor) const
{
   visitor->VisitExp(this);
}

void LogisTreeNodePrimeExp::Accept(LogisVisitor* visitor) const
{
   visitor->VisitPrimeExp(this);
}

void LogisTreeNodeKeyExp::Accept(LogisVisitor* visitor) const
{
   visitor->VisitKeyExp(this);
}

void LogisTreeNodeText::Accept(LogisVisitor* visitor) const
{
   visitor->VisitText(this);
}