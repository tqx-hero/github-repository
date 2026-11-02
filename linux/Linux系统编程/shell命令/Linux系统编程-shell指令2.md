### Linux系统编程-shell指令2:

- ##### 程序的安装与卸载：

  ```shell
  #1、安装程序
  #ubuntu:
  sudo apt install pro-name
  #centOS：
  yum install pro-name
  
  #2、卸载
  #ubuntu:
  sudo apt purge pro-name (或者：sudo apt remove --purge pro-name)
  sudo apt autoremove	#自动删除与已删除的程序所依赖的程序
  #3、更新软件库
  #ubuntu
  sudo apt update
  
  #显示已安装的程序：可做grep筛选
  apt list --installed  [| grep name]
  ```

  demo:

  ```shell
  $ sudo apt purge clangd		#删除 clangd
  Reading package lists... Done
  Building dependency tree
  Reading state information... Done
  The following packages were automatically installed and are no longer required:
    clangd-10 libclang-common-10-dev libclang-cpp10 libllvm10
  Use 'sudo apt autoremove' to remove them.
  The following packages will be REMOVED:
    clangd*
  0 upgraded, 0 newly installed, 1 to remove and 86 not upgraded.
  After this operation, 19.5 kB disk space will be freed.
  Do you want to continue? [Y/n] y
  (Reading database ... 176839 files and directories currently installed.)
  Removing clangd (1:10.0-50~exp1) ...
  Processing triggers for man-db (2.9.1-1) ...
  
  $ sudo apt autoremove	#自动删除依赖的程序
  Reading package lists... Done
  Building dependency tree
  Reading state information... Done
  The following packages will be REMOVED:
    clangd-10 libclang-common-10-dev libclang-cpp10 libllvm10
  0 upgraded, 0 newly installed, 4 to remove and 86 not upgraded.
  After this operation, 184 MB disk space will be freed.
  Do you want to continue? [Y/n] y
  (Reading database ... 176833 files and directories currently installed.)
  Removing clangd-10 (1:10.0.0-4ubuntu1) ...
  Removing libclang-common-10-dev (1:10.0.0-4ubuntu1) ...
  Removing libclang-cpp10 (1:10.0.0-4ubuntu1) ...
  Removing libllvm10:amd64 (1:10.0.0-4ubuntu1) ...
  Processing triggers for man-db (2.9.1-1) ...
  Processing triggers for libc-bin (2.31-0ubuntu9.18) ...
  
  $ apt list --installed | grep clang	#筛选查找已安装的程序中是否存在
  
  WARNING: apt does not have a stable CLI interface. Use with caution in scripts.
  ```

  

- ##### 跟踪系统调用与信号相关的工具：

  ```bash
  $ strace ./a.out
  
  execve("./stdout", ["./stdout"], 0x7ffd5a466e50 /* 24 vars */) = 0
  brk(NULL)                               = 0x5611e02aa000
  arch_prctl(0x3001 /* ARCH_??? */, 0x7ffc1ec18070) = -1 EINVAL (Invalid argument)
  access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
  openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
  fstat(3, {st_mode=S_IFREG|0644, st_size=71952, ...}) = 0
  mmap(NULL, 71952, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f95bee47000
  close(3)                                = 0
  openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
  read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\300A\2\0\0\0\0\0"..., 832) = 832
  pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
  pread64(3, "\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32
  pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0W\222s/x1X\306o\264\363udX\312$"..., 68, 880) = 68
  fstat(3, {st_mode=S_IFREG|0755, st_size=2029592, ...}) = 0
  mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f95bee45000
  pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
  pread64(3, "\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32
  pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0W\222s/x1X\306o\264\363udX\312$"..., 68, 880) = 68
  mmap(NULL, 2037344, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f95bec53000
  mmap(0x7f95bec75000, 1540096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0x7f95bec75000
  mmap(0x7f95beded000, 319488, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19a000) = 0x7f95beded000
  mmap(0x7f95bee3b000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7f95bee3b000
  mmap(0x7f95bee41000, 13920, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f95bee41000
  close(3)                                = 0
  arch_prctl(ARCH_SET_FS, 0x7f95bee46540) = 0
  mprotect(0x7f95bee3b000, 16384, PROT_READ) = 0
  mprotect(0x5611d2912000, 4096, PROT_READ) = 0
  mprotect(0x7f95bee86000, 4096, PROT_READ) = 0
  munmap(0x7f95bee47000, 71952)           = 0
  write(1, "a", 1a)                        = 1
  write(1, "b", 1b)                        = 1
  write(1, "a", 1a)                        = 1
  write(1, "b", 1b)                        = 1
  write(1, "a", 1a)                        = 1
  write(1, "b", 1b)                        = 1
  exit_group(0)                           = ?
  +++ exited with 0 +++
  ```

  

- 