#
# Copyright (c) 2015 Dell Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
#
# THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR
# CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
# LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
# FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
#
# See the Apache Version 2.0 License for specific language governing
# permissions and limitations under the License.
#
import sys
import nas_sflow_utils
import cps_object
import nas_ut_framework as nas_ut
import nas_os_utils

dir_map = {
    "ingress": "1",
    "egress": "2",
    "ingress_egress": "3",
}


def nas_sflow_op(op, data_dict):
    obj = cps_object.CPSObject(
        module=nas_sflow_utils.get_sflow_keys()[0],
        data=data_dict)
    print obj.get()
    nas_ut.get_cb_method(op)(obj)


def usage():
    print "\n\nnas_sflow_cli.py enable [iface_name] [direction] [rate] - enables packet sampling on a given \
           \n                                              inreface in given direction and returns a id"
    print "nas_sflow_cli.py disable [id] - disable sampling for a given id"
    print "nas_sflow_cli.py set_rate [id] [rate] - change the packet sampling rate of the given session id"
    print "nas_sflow_cli.py set_direction [id] [direction] - change the packet sampling direction \
          \n                                              of the given session id"
    print "nas_sflow_cli.py show [id] - dump packet sampling information of given session id or all session"
    print "\n[direction] - ingress, egress, ingress_egress\n"
    exit()

if __name__ == '__main__':

    if len(sys.argv) == 1:
        usage()
    elif sys.argv[1] == "enable" and len(sys.argv) == 5:
        nas_sflow_op(
            "create", {"ifindex": nas_os_utils.if_nametoindex(sys.argv[2]), "direction": dir_map[sys.argv[3]],
                       "sampling-rate": sys.argv[4]})
    elif sys.argv[1] == "disable" and len(sys.argv) == 3:
        nas_sflow_op("delete", {"id": sys.argv[2]})
    elif sys.argv[1] == "show" and len(sys.argv) == 3:
        nas_sflow_op("get", {"id": sys.argv[2]})
    elif sys.argv[1] == "set_rate" and len(sys.argv) == 4:
        nas_sflow_op("set", {"id": sys.argv[2], "sampling-rate": sys.argv[3]})
    elif sys.argv[1] == "set_direction" and len(sys.argv) == 4:
        nas_sflow_op(
            "set",
            {"id": sys.argv[2],
             "direction": dir_map[sys.argv[3]]})
    else:
        usage()
