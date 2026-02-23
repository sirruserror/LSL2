# **LSL2**

## Linux subsystem for Linux version 2 (WIP)

LSL2 is a Linux subsystem for Linux, which allows you to run containerized instances of other Linux distributions (through custom tar containerization and chroot) on top of your existing Linux system. It provides a lightweight and efficient way to run multiple Linux environments simultaneously without the need for full virtualization.

It builds on from the existing LSL1 which relied on Docker and had certain limitations in terms of performance and compatibility. LSL2, on the other hand, uses a more native approach to achieve better performance and compatibility with a wider range of Linux distributions.

## Key Features:
- **Containerization**: LSL2 uses custom tar containerization to create isolated environments for different Linux distributions. This allows you to run multiple distributions simultaneously without conflicts.
- **Chroot-based**: LSL2 utilizes chroot to create a separate filesystem for each Linux distribution, providing a more native experience and better performance compared to traditional virtualization methods.
- **Lightweight**: LSL2 is designed to be lightweight and efficient, allowing you to run multiple Linux environments without consuming excessive system resources.
- **Compatibility**: LSL2 is compatible with a wide range of Linux distributions, allowing you to choose the one that best suits your needs.
- **Accessibility to any rootfs to run**: LSL2 allows you to use any root filesystem (rootfs) to create a new Linux environment, giving you the flexibility to run different distributions or custom setups.

### Interactive Chroot Shell

Run the tool with the path to a prepared rootfs and (when necessary) `sudo` to drop
into an interactive `/bin/sh` inside that root environment:

```sh
sudo ./lsl2 [-d] /path/to/rootfs
```

The `-d`/`--debug` flag will print certification results before entering the chroot.

The binary will perform some basic sanity checks (`cert_rootfs`, `cert_sh`) and
bind-mount `/proc`, `/dev` and `/sys` before invoking `chroot(2)` and executing
`/bin/sh` inside the new root.



## ATTRIBUTION
This project is inspired by the work of Microsoft on WSL2

## LICENSE
LSL2 is licensed under the BSD 3-Clause License, which allows for free use, modification, and distribution of the software. You can find the full text of the license in the LICENSE file included in this repository.