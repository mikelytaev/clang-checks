#include "NewWithoutDeleteCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void NewWithoutDeleteCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxMethodDecl().bind("method"), this);
}

void NewWithoutDeleteCheck::check(const MatchFinder::MatchResult &Result) {
  const auto newMethod = Result.Nodes.getNodeAs<CXXMethodDecl>("method");
  if (newMethod->getNameAsString() != "new")
    return;
  const auto classDl = newMethod->getParent();
  for (const auto &method : classDl->methods()) {
    if(method->getNameAsString() == "delete")
      return;
  }

  diag(newMethod->getLocStart(), "defenition of custom new operator without delete operator");

}

} // namespace misc
} // namespace tidy
} // namespace clang
