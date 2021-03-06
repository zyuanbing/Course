# Linux Instructions
### ls
- 以.开头的文件为隐藏文件，创建的隐藏文件不可见
- .代表当前目录，..代表上级目录
- `-a`可显示隐藏文件
- `-l`以列表形式显示详细信息，开头加d表示为目录
- `-h`配合`-l`使用，更直观显示文件大小；`-l -h`可写为`-lh`，其他同理
- LS通配符
  - `*`   表示任意个字符
  - `?`   表示任意一位字符
  - `[]`  表示可以匹配字符组中的任一个
  - `[abc]` 匹配a, b, c中的任一个。e.g. `ls [123]45.txt`
  - `[a-f]` 匹配从a到f范围的任意一个。 e.g. `ls [1-3]23.txt`

### cd
- `cd / cd ~`  切换到当前用户的主目录
- `cd .`  保持当前目录
- `cd ..`  回到上级目录
- `cd -`   在最近两次工作目录间切换

### touch
- 如果文件不存在，创建文件；如果文件存在，可以修改文件的末次修改日期
- c

### mkdir
- 创建目录 
- `-p`  可递归创建目录。e.g. `mkdir a/b/c/d/e`
- 新建目录**不能**与目录中已有目录或文件**重名**

### rm
- 永久删除文件或目录
- `-f`  强制删除，忽略不存在的文件，无需提示
- `-r`  递归删除目录下的内容，删除文件夹必须加此参数。e.g. `rm -r *`删除全部文件

### tree 
- `tree [目录名]`以树状图列出文件目录结构
- `-d`  只显示目录

### cp
- `cp [目录][源文件] [目录][目标文件]`复制文件或目录
- `-f`  直接覆盖已存在的目标文件，不再提示
- `-i`  覆盖文件前提示
- `-r`  复制目录

### mv
- `mv 原文件 目标文件`  移动文件或目录/重命名
- `-i`  覆盖文件前提示
- 如果源文件/目录和目标文件/目录所在**目录相同**，则达到**重命名**的效果

### cat
- `cat 文件名`  查看文件内容、创建文件、文件合并、追加文件内容，适合查看**内容较少**的文件
- `-b`  对非空行输出行号
- `-n`  对所有行输出行号

### more
- `more 文件名`  用于分屏显示文件内容，每次只显示**一页内容**，适用查看内容较多的文件
- `空格键`  显示下一页
- `Enter`   显示下一行
- `b`   显示上一页一页
- `f`   显示下一页
- `q`   退出
- `/word`   搜索word字符串

### grep
- `grep 搜索文本 文件名`  查找文件中的文本内容，允许**模式查找**；搜索文本中包含空行时加**双引号**
- `-n`  显示匹配行及行号
- `-v`  显示不包含匹配文本的所有行
- `-i`  忽略大小写
- 模式查找
  - `^a`    搜索以`a`开头的行 e.g. `grep ^fe -n 123.txt`
  - `k$`    搜索以`k`结尾的行

### echo
- 再终端中显示指定文字，通常与**重定向**一起使用

### 重定向 >和>>
- 将命令执行结果重定向到一个文件，将本应显示在终端上的内容**输出/追加**到指定文件中
- `>`   表示输出，覆盖原有文件内容  
  e.g. `echo Hello World > a`    `ls -lh > 1.txt`
- `>>`  表示追加，将内容追加到已有文件结尾  
  e.g.`ls >> a`  `tree >> a`

### 管道 |
- 将一个命令的输出作为另一个命令的输入
- 常用管道命令：`more, grep`
- e.g. `ls -lh |more`  `ifconfig | grep inet`

### shutdown
- `shutdown 选项 时间`  关机/重启
- `-r` 重启
- e.g. 
  ```
  # 立即重启
  shutdown -r now

  # 在今天的20:25关机
  shutdown 20:25

  # 再过十分钟自动关机
  shutdown +10

  # 取消关机指令
  shutdown -c
  ```
    > 不指定选项和参数，默认一分钟后关闭电脑

### 网卡和IP地址
- 网卡是一个专门负责网络通讯的的硬件设备
- IP地址是设置在网卡上的地址信息
    > 电脑->电话，网卡->SIM卡，IP地址->电话号码。
- 每台联网的电脑上都有IP地址，保证电脑间的通讯
- 每台电脑的IP地址不能相同 

### ifconfig
- `ifconfig`    查看/配置网卡配置信息
    > 一台计算机可能会有一个**物理网卡**和多个**虚拟网卡**，Linux中物理网卡通常以`ensXX`命名
    > `127.0.0.1`称为**本地环回/环回地址**，以南用来测试本机网卡是否正常

### ping
- `ping IP地址`用于检测当前计算机到目标计算机之间的网络是否畅通；数值越大，速度越慢

### ssh
- `ssh [-p port] user@remote`  关机/重启
    >remote:IP/域名/别名
    port 默认为22
- 只能在Linux或UNIX下使用

### scp
- `scp 用户名@IP:文件名或路径 用户名@IP:文件名或路径` 远程复制文件
- `-P port`端口
- `-r` 复制文件夹
- 配置公钥 `ssh-keygen` 连续三次回车
- 上传公钥到服务器 `ssh-copy-id -p port user@remote` 让远程服务器记住我们的公钥
- 公钥文件:id_rsa.pub 私钥文件:id_rsa。**本地**使用**私钥**对数据加密/解密，**服务器**使用**公钥**对数据进行加密/解密
> 非对称加密算法
> - *使用公钥加密的数据，需要使用私钥解密*
> - *使用私钥加密的数据，需要使用公钥解密*
- 配置别名  
  e.g. 使用`ssh mac`来代替`ssh -p port user@remote`，需要在`~/.ssh/config`中追加以下内容：
  ```
    Host mac
        HostName ip地址
        User XXXX
        Port 22
  ```

## 用户权限相关命令
### read
- 