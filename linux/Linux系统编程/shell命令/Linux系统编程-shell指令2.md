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

  

- 