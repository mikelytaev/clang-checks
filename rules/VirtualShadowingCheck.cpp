//===--- VirtualShadowingCheck.cpp - clang-tidy----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "VirtualShadowingCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void VirtualShadowingCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxMethodDecl(isVirtual()).bind("method"), this);
}

void VirtualShadowingCheck::check(const MatchFinder::MatchResult &Result) {
  const auto method = Result.Nodes.getNodeAs<CXXMethodDecl>("method");
  const auto classDl = method->getParent();
  const auto methodName = method->getName();

  if (classDl->getNumBases() == 0)
    return;

  std::function <bool(const CXXRecordDecl*)> predicate = [&] (const CXXRecordDecl* BaseDefinition) -> bool {
    for (const auto &baseMethod : BaseDefinition->methods())
      if (methodName == baseMethod->getName())
	return not baseMethod->isVirtual();
    return BaseDefinition->forallBases(predicate);
  };
  if (not classDl->forallBases(predicate))
    return;

  diag(method->getLocStart(),
       "method hides non-virtual method from a base class");
}

} // namespace misc
} // namespace tidy
} // namespace clang
