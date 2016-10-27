sonic-nas-l2
============

This repo contains the Layer 2 (L2) portion of the network abstraction service (NAS). This handles media access control (MAC) learning, programming spanning-tree protocol (STP) state, mirroring, sflow and other switch configurations.  

Build
---------
See [sonic-nas-manifest](https://github.com/Azure/sonic-nas-manifest) for more information on common build tools.

### Build requirements
* `sonic-model-dev`
* `sonic-common-dev`
* `sonic-nas-common-dev`
* `sonic-object-library-dev`
* `sonic-logging-dev`
* `sonic-nas-ndi-dev`
* `sonic-nas-ndi-api-dev`
* `sonic-nas-linux-dev`

Copy the Debian files to the parent folder (default location of debian files) and run the `sonic_build` command.

### Build command
    sonic_build sonic-ndi-api-dev libsonic- -- clean binary

(c) Dell 2016
