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

//  (  表达式的根 %铁路(中通6666 + 圆通YT(8888 + 5641)) + %空运(JD0001-1-1) ) 
//               |                                    |             |
//             %铁路                                  +           %空运       
//      /        |         \                                        |
// 中通6666      +    圆通YT(8888 + 5641)                        JD0001-1-1
//                    /            \
//                 圆通YT        8888 + 5641
//                              /     |     \
//                           8888     +     5641


//语法
//Exp -> Keyexp Exp'
//     | Text Exp'
//Exp' -> + Keyexp Exp'
//      | + Text Exp'
//      | null
//Keyexp -> keyword (Exp)
//Text -> (Exp)
//      | sn

#pragma once

#include <string>
#include <vector>
#include <memory>


namespace logis
{
   class LogisVisitor;

   enum class LogisNodeType
   {
      Undef = -1,
      Root,
      Exp,
      PExp,
      Kexp,
      Text
   };

   class LogisTreeNode
   {
   public:
      LogisTreeNode()
         :_type(LogisNodeType::Undef),
         _children()
      {}

      explicit LogisTreeNode(const LogisNodeType type)
         :_type(type),
         _children()
      {}

      LogisTreeNode(const LogisNodeType type,const std::shared_ptr<LogisTreeNode>& child)
         :_type(type),
         _children(1,child)
      {}

      LogisTreeNode(const LogisNodeType type,const std::vector<std::shared_ptr<LogisTreeNode>>& children)
         :_type(type),
         _children(children)
      {}

      virtual ~LogisTreeNode()
      {}

      const LogisNodeType GetType() const
      {
         return _type;
      }

      void AddChild(const std::shared_ptr<LogisTreeNode>& child)
      {
         _children.push_back(child);
      }

      void PopChild()
      {
         _children.pop_back();
      }

      bool HasChild() const
      {
         return !_children.empty();
      }

      const std::shared_ptr<LogisTreeNode>& GetChild(int idx) const
      {
         return _children[idx];
      }

      const std::vector<std::shared_ptr<LogisTreeNode>>& GetChildren() const
      {
         return _children;
      }

      int height() const;

      virtual void Accept(LogisVisitor* visitor) const;

   private:
      LogisNodeType _type;
      std::vector<std::shared_ptr<LogisTreeNode>> _children;
   };

   int __declspec(dllexport) get_tree_height(const std::shared_ptr<LogisTreeNode>& tree);


   //Exp -> Keyexp Exp'
   //     | Text Exp'
   class LogisTreeNodeExp final : public LogisTreeNode
   {
   public:
      LogisTreeNodeExp()
         :LogisTreeNode(LogisNodeType::Exp)
      {}

      ~LogisTreeNodeExp()
      {}

      void Accept(LogisVisitor* visitor) const;
   };


   //Exp' -> + Keyexp Exp'
   //      | + Text Exp'
   //      | null
   class LogisTreeNodePrimeExp final : public LogisTreeNode
   {
   public:
      LogisTreeNodePrimeExp()
         :LogisTreeNode(LogisNodeType::PExp),
         _op(L"")
      {}

      ~LogisTreeNodePrimeExp()
      {}

      void SetOp(const std::wstring& op)
      {
         _op = op;
      }

      const std::wstring& GetOp() const
      {
         return _op;
      }

      void Accept(LogisVisitor* visitor) const;

   private:
      std::wstring _op;
   };


   //Keyexp -> keyword (Exp)
   class LogisTreeNodeKeyExp final : public LogisTreeNode
   {
   public:
      LogisTreeNodeKeyExp()
         :LogisTreeNode(LogisNodeType::Kexp),
         _keyword(L"")
      {}

      ~LogisTreeNodeKeyExp()
      {}

      void SetKeyword(const std::wstring& keyword)
      {
         _keyword = keyword;
      }

      const std::wstring& GetKeyword() const
      {
         return _keyword;
      }

      void Accept(LogisVisitor* visitor) const;

   private:
      std::wstring _keyword;
   };


   //Text -> (Exp)
   //      | sn
   class LogisTreeNodeText final : public LogisTreeNode
   {
   public:
      LogisTreeNodeText()
         :LogisTreeNode(LogisNodeType::Text),
         _sn(L"")
      {}

      ~LogisTreeNodeText()
      {}

      void SetSn(const std::wstring& sn)
      {
         _sn = sn;
      }

      const std::wstring& GetSn() const
      {
         return _sn;
      }

      void Accept(LogisVisitor* visitor) const;

   private:
      std::wstring _sn;
   };
}