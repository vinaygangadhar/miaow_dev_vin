#!/bin/bash
swap_file="/scratch/new_swap_file"
dd if=/dev/zero of=$swap_file bs=1M count=32768
# 1024+0 records in
# 1024+0 records out

# Change the permission of the swap file so that only root can access it.
chmod 600 $swap_file

# Make this file as a swap file using mkswap command.
mkswap $swap_file
# Setting up swapspace version 1, size = 1073737 kB


# Enable the newly created swapfile.
swapon $swap_file
# To make this swap file available as a swap area even after the reboot, add the following line to the /etc/fstab file.

# cat /etc/fstab
# /root/myswapfile               swap                    swap    defaults        0 0
# Verify whether the newly created swap area is available for your use.

# swapon -s
# Filename                        Type            Size    Used    Priority
# /dev/sda2                       partition       4192956 0       -1
# /root/myswapfile                file            1048568 0       -2

# free -k
