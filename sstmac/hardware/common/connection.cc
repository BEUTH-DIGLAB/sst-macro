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

#include <sstmac/hardware/common/connection.h>
#include <sprockit/debug.h>

DeclareDebugSlot(timestamp)

namespace sstmac {
namespace hw {

static bool checked_prefix_fxn = false;

class timestamp_prefix_fxn :
  public sprockit::debug_prefix_fxn
{
 public:
  timestamp_prefix_fxn(sstmac::event_scheduler* mgr) : mgr_(mgr){}

  std::string str() {
    double t_ms = mgr_->now().msec();
    return sprockit::printf("T=%12.8e ms:", t_ms);
  }

 private:
  event_scheduler* mgr_;
};

connectable_component::connectable_component(sprockit::sim_parameters* params,
                      uint32_t cid,
                      event_manager* mgr)
  : event_component(params, cid, mgr)
{
  if (!checked_prefix_fxn){
    if (sprockit::debug::slot_active(sprockit::dbg::timestamp)){
      sprockit::debug_prefix_fxn* fxn = new timestamp_prefix_fxn(this);
      sprockit::debug::prefix_fxn = fxn;
    }
    checked_prefix_fxn = true;
  }
}


}
}
