
/*
 * Copyright (c) 2016 Dell Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *  LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 * FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 * See the Apache Version 2.0 License for specific language governing
 * permissions and limitations under the License.
 */


/*
 * filename: nas_switch_mac.cpp
 *
 */

#include "cps_api_object_key.h"
#include "cps_api_operation.h"
#include "cps_api_object_category.h"
#include "dell-base-pas.h"
#include "dell-base-switch-element.h"
#include "nas_ndi_switch.h"
#include "cps_class_map.h"
#include "ds_common_types.h"
#include "event_log.h"

#include <string.h>
#include <unistd.h>

static hal_mac_addr_t sys_mac_base = {0,0,0,0,0,0};

t_std_error nas_switch_mac_get(hal_mac_addr_t *mac_base)
{
    memcpy(*mac_base, sys_mac_base, sizeof(sys_mac_base));
    return(STD_ERR_OK);
}

static t_std_error nas_get_pas_mac_address(void) {

    cps_api_return_code_t ret = cps_api_ret_code_ERR;
    cps_api_get_params_t gp;
    cps_api_get_request_init(&gp);

    cps_api_object_t obj = cps_api_object_list_create_obj_and_append(gp.filters);
    cps_api_key_from_attr_with_qual(cps_api_object_key(obj),
                          BASE_PAS_CHASSIS_OBJ, cps_api_qualifier_OBSERVED);
    if (cps_api_get(&gp) != cps_api_ret_code_OK) {
        EV_LOG_ERR(ev_log_t_SYSTEM, 1, "PLATFORM ",":Error in Getting BASE MAC address from PAS: Error 0x%x ", ret);
        return(STD_ERR(BOARD,FAIL,0));

    }

    cps_api_object_t chassis_obj = cps_api_object_list_get(gp.list,0);
    cps_api_object_attr_t base_mac_attr = cps_api_object_attr_get(chassis_obj,
                               BASE_PAS_CHASSIS_BASE_MAC_ADDRESSES);
    void *_base_mac = cps_api_object_attr_data_bin(base_mac_attr);
    memcpy(sys_mac_base, _base_mac,sizeof(sys_mac_base));
    cps_api_get_request_close(&gp);
    return(STD_ERR_OK);
}

t_std_error nas_switch_mac_init(cps_api_operation_handle_t handle) {
     while(1) {
        if (nas_get_pas_mac_address() == STD_ERR_OK)  {
            break;
        }
        EV_LOG_TRACE(ev_log_t_SYSTEM, 1, "PLATFORM", "waiting for base mac address from PAS");
        sleep(1);
    }

    EV_LOG_TRACE(ev_log_t_SYSTEM, 1, "PLATFORM", "Base MAC address %02x:%02x:%02x:%02x:%02x:%02x",
                           sys_mac_base[0], sys_mac_base[1], sys_mac_base[2], sys_mac_base[3],
                                     sys_mac_base[4], sys_mac_base[5]);
    npu_id_t npu =0; // TODO
    nas_ndi_switch_param_t param;
    (void)nas_switch_mac_get(&param.mac);

    return(ndi_switch_set_attribute(npu, BASE_SWITCH_SWITCHING_ENTITIES_SWITCHING_ENTITY_DEFAULT_MAC_ADDRESS, &param));
}
