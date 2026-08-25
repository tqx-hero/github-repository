1. 远程同步pull：

   ```shell
   git pull --rebase origin [master]
   ```

   

2. 把文件放到暂存区：

   ```shell
   git add .
   ```

   

3. 提交(commit)到本地仓库：

   ```shell
   git commit -m "提交说明"
   ```

   

4. 推送（push）到远程分支:

   ```shell
   git push origin master
   #首次推送建立本地分支与远程分支
   git push -u origin master
    -u: --set-upstream 设置上游分支
   ```

   

5. 关联远程仓库：

   ```bash
   #添加远程仓库 origin
   git remote add origin git@github.com:xxx/xxx.git
   #查看已关联的仓库：
   git remote -v
   #修改远程仓库地址
   git remote set-url origin git@github.com:xxx/new.git
   ```

   

6. 

