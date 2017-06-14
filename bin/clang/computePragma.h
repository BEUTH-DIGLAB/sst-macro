/**
Copyright 2009-2017 National Technology and Engineering Solutions of Sandia, 
LLC (NTESS).  Under the terms of Contract DE-NA-0003525, the U.S.  Government 
retains certain rights in this software.

Sandia National Laboratories is a multimission laboratory managed and operated
by National Technology and Engineering Solutions of Sandia, LLC., a wholly 
owned subsidiary of Honeywell International, Inc., for the U.S. Department of 
Energy's National Nuclear Security Administration under contract DE-NA0003525.

Copyright (c) 2009-2017, NTESS

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.

    * Neither the name of Sandia Corporation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Questions? Contact sst-macro-help@sandia.gov
*/
#ifndef bin_clang_computePragma_h
#define bin_clang_computePragma_h

#include "pragmas.h"

class SSTComputePragma : public SSTPragma {
  friend class ComputeVisitor;
 public:
  SSTComputePragma() : SSTPragma(Compute) {}
 private:
  void activate(clang::Stmt *stmt, clang::Rewriter &r, PragmaConfig& cfg) override;
  void activate(clang::Decl* decl, clang::Rewriter& r, PragmaConfig& cfg) override;
  void defaultAct(clang::Stmt* stmt, clang::Rewriter &r);
  void visitForStmt(clang::ForStmt* stmt, clang::Rewriter& r, PragmaConfig& cfg);
  void visitCXXMethodDecl(clang::CXXMethodDecl* decl, clang::Rewriter& r, PragmaConfig& cfg);
  void visitFunctionDecl(clang::FunctionDecl* decl, clang::Rewriter& r, PragmaConfig& cfg);
  void visitIfStmt(clang::IfStmt* stmt, clang::Rewriter& r, PragmaConfig& cfg);
  void visitAndReplaceStmt(clang::Stmt* stmt, clang::Rewriter& r, PragmaConfig& cfg);
};

class SSTOpenMPParallelPragmaHandler : public SSTTokenStreamPragmaHandler
{
 public:
  SSTOpenMPParallelPragmaHandler(SSTPragmaList& plist,
                         clang::CompilerInstance& CI,
                         SkeletonASTVisitor& visitor,
                         std::set<clang::Stmt*>& deld) :
      SSTTokenStreamPragmaHandler("parallel", plist, CI, visitor, deld){}
 private:
  SSTPragma* allocatePragma(clang::SourceLocation loc, const std::list<clang::Token> &tokens) const {
    //this actually just maps cleanly into a compute pragma
    return new SSTComputePragma;
  }
};

class SSTComputePragmaHandler : public SSTSimplePragmaHandler<SSTComputePragma> {
 public:
  SSTComputePragmaHandler(SSTPragmaList& plist, clang::CompilerInstance& CI,
                      SkeletonASTVisitor& visitor, std::set<clang::Stmt*>& deld) :
   SSTSimplePragmaHandler<SSTComputePragma>("compute", plist, CI, visitor, deld)
  {}
};


#endif
