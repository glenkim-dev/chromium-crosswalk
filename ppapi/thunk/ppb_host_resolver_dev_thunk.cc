// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// From dev/ppb_host_resolver_dev.idl modified Sun Jun 09 11:17:35 2013.

#include "ppapi/c/dev/ppb_host_resolver_dev.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_errors.h"
#include "ppapi/shared_impl/tracked_callback.h"
#include "ppapi/thunk/enter.h"
#include "ppapi/thunk/ppb_host_resolver_api.h"
#include "ppapi/thunk/ppb_instance_api.h"
#include "ppapi/thunk/resource_creation_api.h"
#include "ppapi/thunk/thunk.h"

namespace ppapi {
namespace thunk {

namespace {

PP_Resource Create(PP_Instance instance) {
  VLOG(4) << "PPB_HostResolver_Dev::Create()";
  EnterResourceCreation enter(instance);
  if (enter.failed())
    return 0;
  return enter.functions()->CreateHostResolver(instance);
}

PP_Bool IsHostResolver(PP_Resource resource) {
  VLOG(4) << "PPB_HostResolver_Dev::IsHostResolver()";
  EnterResource<PPB_HostResolver_API> enter(resource, false);
  return PP_FromBool(enter.succeeded());
}

int32_t Resolve(PP_Resource host_resolver,
                const char* host,
                uint16_t port,
                const struct PP_HostResolver_Hint_Dev* hint,
                struct PP_CompletionCallback callback) {
  VLOG(4) << "PPB_HostResolver_Dev::Resolve()";
  EnterResource<PPB_HostResolver_API> enter(host_resolver, callback, true);
  if (enter.failed())
    return enter.retval();
  return enter.SetResult(enter.object()->Resolve(host,
                                                 port,
                                                 hint,
                                                 enter.callback()));
}

struct PP_Var GetCanonicalName(PP_Resource host_resolver) {
  VLOG(4) << "PPB_HostResolver_Dev::GetCanonicalName()";
  EnterResource<PPB_HostResolver_API> enter(host_resolver, true);
  if (enter.failed())
    return PP_MakeUndefined();
  return enter.object()->GetCanonicalName();
}

uint32_t GetNetAddressCount(PP_Resource host_resolver) {
  VLOG(4) << "PPB_HostResolver_Dev::GetNetAddressCount()";
  EnterResource<PPB_HostResolver_API> enter(host_resolver, true);
  if (enter.failed())
    return 0;
  return enter.object()->GetNetAddressCount();
}

PP_Resource GetNetAddress(PP_Resource host_resolver, uint32_t index) {
  VLOG(4) << "PPB_HostResolver_Dev::GetNetAddress()";
  EnterResource<PPB_HostResolver_API> enter(host_resolver, true);
  if (enter.failed())
    return 0;
  return enter.object()->GetNetAddress(index);
}

const PPB_HostResolver_Dev_0_1 g_ppb_hostresolver_dev_thunk_0_1 = {
  &Create,
  &IsHostResolver,
  &Resolve,
  &GetCanonicalName,
  &GetNetAddressCount,
  &GetNetAddress
};

}  // namespace

const PPB_HostResolver_Dev_0_1* GetPPB_HostResolver_Dev_0_1_Thunk() {
  return &g_ppb_hostresolver_dev_thunk_0_1;
}

}  // namespace thunk
}  // namespace ppapi
