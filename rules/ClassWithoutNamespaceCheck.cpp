//===--- ClassWithoutNamespaceCheck.cpp - clang-tidy-----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ClassWithoutNamespaceCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void ClassWithoutNamespaceCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxRecordDecl().bind("record"), this);
}

void ClassWithoutNamespaceCheck::check(const MatchFinder::MatchResult &Result) {
  const auto classDl = Result.Nodes.getNodeAs<CXXRecordDecl>("record");
  if (not classDl->isInIdentifierNamespace(IdentifierNamespace::IDNS_Namespace))
    diag(classDl->getLocStart(), "class declaration without namespace");
}

} // namespace misc
} // namespace tidy
} // namespace clang
