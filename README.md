SONiC NAS L2
============

Layer 2 functionality for the SONiC project

Description
-----------

This repo contains the Layer 2 portion of the Network abstraction service. This handles MAC learning, programming STP state, mirroring, sflow and other switch configurations.  

Building
---------
Please see the instructions in the sonic-nas-manifest repo for more details on the common build tools.  [Sonic-nas-manifest](https://stash.force10networks.com/projects/SONIC/repos/sonic-nas-manifest/browse)

Build Requirements:
 - sonic-model-dev
 - sonic-common-dev
 - sonic-nas-common-dev
 - sonic-object-library-dev
 - sonic-logging-dev
 - sonic-nas-ndi-dev
 - sonic-nas-ndi-api-dev
 - sonic-nas-linux-dev

Copy the debian files to the parent folder (default location of debian files) and then run the following command:

BUILD CMD: sonic_build sonic-ndi-api-dev libsonic- -- clean binary

(c) Dell 2016

