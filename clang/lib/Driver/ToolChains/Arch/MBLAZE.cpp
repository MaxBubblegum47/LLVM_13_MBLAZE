//===--- MBLAZE.cpp - MBLAZE ToolChain Implementations ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MBLAZE.h"
#include "CommonArgs.h"
#include "clang/Driver/Compilation.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/Options.h"
#include "llvm/Option/ArgList.h"

using namespace clang::driver;
using namespace clang::driver::toolchains;
using namespace clang;
using namespace llvm::opt;

MBLAZEToolChain::MBLAZEToolChain(const Driver &D, const llvm::Triple &Triple,
                               const ArgList &Args)
    : ToolChain(D, Triple, Args) {
  // ProgramPaths are found via 'PATH' environment variable.
}

bool MBLAZEToolChain::isPICDefault() const { return true; }

bool MBLAZEToolChain::isPIEDefault() const { return false; }

bool MBLAZEToolChain::isPICDefaultForced() const { return true; }

bool MBLAZEToolChain::SupportsProfiling() const { return false; }

bool MBLAZEToolChain::hasBlocksRuntime() const { return false; }