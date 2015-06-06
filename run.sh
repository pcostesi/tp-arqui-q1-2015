#!/bin/bash
FMT=${1:-qcow2}
qemu-system-x86_64 -soundhw pcspk -snapshot -hda Image/x64BareBonesImage.${FMT} -m 512 
