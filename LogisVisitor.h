//########################################################
//##                                                    ##
//##        Author:    xfu                              ##
//##        E-Mail:    tech@zhongwenshu.de              ##
//##                                                    ##
//########################################################

#pragma once

#include <memory>
#include <string>


namespace logis
{
   class LogisTreeNode;
   class LogisTreeNodeExp;
   class LogisTreeNodeKeyExp;
   class LogisTreeNodePrimeExp;
   class LogisTreeNodeText;

   class LogisVisitor
   {
   protected:
      LogisVisitor()
      {}

   public:
      virtual ~LogisVisitor()
      {}

      virtual void VisitNode(const LogisTreeNode* node) = 0;
      virtual void VisitExp(const LogisTreeNodeExp* exp) = 0;
      virtual void VisitKeyExp(const LogisTreeNodeKeyExp* kexp) = 0;
      virtual void VisitPrimeExp(const LogisTreeNodePrimeExp* pexp) = 0;
      virtual void VisitText(const LogisTreeNodeText* text) = 0;
   };


   class LogisTreeToString : public LogisVisitor
   {
   public:
      LogisTreeToString()
         :LogisVisitor(),
         _str()
      {}

      virtual ~LogisTreeToString()
      {}

      std::wstring GetString() const
      {
         return _str;
      }

      virtual void VisitNode(const LogisTreeNode* node) override;
      virtual void VisitExp(const LogisTreeNodeExp* exp) override;
      virtual void VisitKeyExp(const LogisTreeNodeKeyExp* kexp) override;
      virtual void VisitPrimeExp(const LogisTreeNodePrimeExp* pexp) override;
      virtual void VisitText(const LogisTreeNodeText* text) override;

   private:
      std::wstring _str;
   };


   class LogisTreeSearch : public LogisVisitor
   {
   public:
      LogisTreeSearch(const std::wstring& sn)
         :LogisVisitor(),
         _sn(sn)
      {}

      virtual void VisitNode(const LogisTreeNode* node) override;
      virtual void VisitExp(const LogisTreeNodeExp* exp) override;
      virtual void VisitKeyExp(const LogisTreeNodeKeyExp* kexp) override;
      virtual void VisitPrimeExp(const LogisTreeNodePrimeExp* pexp) override;
      virtual void VisitText(const LogisTreeNodeText* text) override;

      bool IsFound()
      {
         return _found;
      }

   private:
      std::wstring _sn;
      bool _found;
   };

   std::wstring __declspec(dllexport) run_logis_visitor(const std::shared_ptr<LogisTreeNode>& tree);
   bool __declspec(dllexport) search_sn(const std::shared_ptr<LogisTreeNode>& tree,const std::wstring& sn);
}