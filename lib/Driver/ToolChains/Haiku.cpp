//===--- Haiku.cpp - Haiku ToolChain Implementations ------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Haiku.h"
#include "CommonArgs.h"

using namespace clang::driver;
using namespace clang::driver::toolchains;
using namespace clang;
using namespace llvm::opt;

/// Haiku - Haiku tool chain which can call as(1) and ld(1) directly.

Haiku::Haiku(const Driver &D, const llvm::Triple& Triple, const ArgList &Args)
  : Generic_ELF(D, Triple, Args) {
#ifdef HAIKU_HYBRID_SECONDARY
  getProgramPaths().insert(getProgramPaths().begin(), getDriver().SysRoot
                           + "/system/bin/" HAIKU_HYBRID_SECONDARY);
  getFilePaths().clear();
  getFilePaths().push_back(getDriver().SysRoot + "/system/lib/"
                           HAIKU_HYBRID_SECONDARY);
#endif
}

std::string Haiku::findLibCxxIncludePath() const {
  return getDriver().SysRoot + "/system/develop/headers/c++/v1";
}

void Haiku::addLibStdCxxIncludePaths(const llvm::opt::ArgList &DriverArgs,
                                     llvm::opt::ArgStringList &CC1Args) const {
#ifdef HAIKU_HYBRID_SECONDARY
  addLibStdCXXIncludePaths(getDriver().SysRoot, "/system/develop/headers"
                     HAIKU_HYBRID_SECONDARY "/c++", getTriple().str(), "", "", "", 
                     DriverArgs, CC1Args);
#else
  addLibStdCXXIncludePaths(getDriver().SysRoot, "/system/develop/headers/c++",
                           getTriple().str(), "", "", "", DriverArgs, CC1Args);
#endif
}
