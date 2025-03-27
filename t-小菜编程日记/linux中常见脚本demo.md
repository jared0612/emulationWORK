在 Linux/Unix 系统中，Shell 脚本被广泛用于**系统管理、运维自动化、数据处理、定时任务等**。以下是几类常见的 Shell 脚本及示例：  

---

## **1. 文件与目录管理**
### **（1）定期清理日志文件**
**作用**：删除 7 天前的 `.log` 文件，防止日志占满磁盘空间  
```sh
#!/bin/bash
LOG_DIR="/var/log/myapp"
find "$LOG_DIR" -type f -name "*.log" -mtime +7 -exec rm -f {} \;
echo "Old logs deleted."
```

### **（2）自动备份文件**
**作用**：将 `/home/user/data` 目录打包成 `.tar.gz`，并存放到 `/backup` 目录  
```sh
#!/bin/bash
BACKUP_DIR="/backup"
SOURCE_DIR="/home/user/data"
DATE=$(date +%Y%m%d)
tar -czf "$BACKUP_DIR/backup_$DATE.tar.gz" "$SOURCE_DIR"
echo "Backup completed: $BACKUP_DIR/backup_$DATE.tar.gz"
```

---

## **2. 用户管理**
### **（3）批量创建用户**
**作用**：从 `user_list.txt` 文件读取用户名并批量创建 Linux 用户  
```sh
#!/bin/bash
while read user; do
    useradd "$user" -m -s /bin/bash
    echo "User $user created."
done < user_list.txt
```
（假设 `user_list.txt` 的内容是用户名列表，每行一个用户名）

### **（4）检测用户是否在线**
**作用**：检查某个用户是否登录系统  
```sh
#!/bin/bash
USER_TO_CHECK="john"
if who | grep -q "$USER_TO_CHECK"; then
    echo "User $USER_TO_CHECK is online."
else
    echo "User $USER_TO_CHECK is offline."
fi
```

---

## **3. 进程管理**
### **（5）监控指定进程**
**作用**：如果 `nginx` 进程未运行，则自动重启  
```sh
#!/bin/bash
PROCESS="nginx"
if ! pgrep -x "$PROCESS" > /dev/null; then
    echo "$PROCESS is down, restarting..."
    systemctl restart "$PROCESS"
fi
```

### **（6）批量杀死指定进程**
**作用**：终止所有 `java` 相关的进程  
```sh
#!/bin/bash
pkill -f "java"
echo "All Java processes have been terminated."
```

---

## **4. 网络管理**
### **（7）检测服务器是否可达**
**作用**：检查某个 IP 是否可达  
```sh
#!/bin/bash
HOST="192.168.1.1"
if ping -c 3 "$HOST" > /dev/null 2>&1; then
    echo "$HOST is reachable."
else
    echo "$HOST is unreachable."
fi
```

### **（8）自动获取公网 IP**
**作用**：获取当前服务器的公网 IP  
```sh
#!/bin/bash
curl -s https://api64.ipify.org
```

---

## **5. 定时任务（Crontab）**
### **（9）每天凌晨 2 点自动备份**
**设置 Crontab 任务**
```sh
crontab -e
```
**添加以下定时任务**
```
0 2 * * * /home/user/backup.sh
```
（表示每天凌晨 2:00 运行 `/home/user/backup.sh`）

---
## **6. 服务器性能监控**
### **（10）监控 CPU & 内存**
**作用**：输出当前 CPU 和内存使用情况  
```sh
#!/bin/bash
echo "CPU Usage:"
top -b -n 1 | grep "Cpu(s)"
echo "Memory Usage:"
free -m
```

---

## **7. 批量运维**
### **（11）批量 SSH 登录执行命令**
**作用**：在多个远程服务器上执行 `df -h` 命令（查询磁盘使用情况）  
```sh
#!/bin/bash
SERVERS=("192.168.1.10" "192.168.1.11" "192.168.1.12")
for SERVER in "${SERVERS[@]}"; do
    echo "Checking disk usage on $SERVER..."
    ssh user@$SERVER "df -h"
done
```

---

## **8. 其他**
### **（12）生成随机密码**
**作用**：生成一个 12 位随机密码  
```sh
#!/bin/bash
tr -dc A-Za-z0-9 </dev/urandom | head -c 12; echo
```

### **（13）判断一个数是奇数还是偶数**
```sh
#!/bin/bash
read -p "Enter a number: " num
if ((num % 2 == 0)); then
    echo "$num is even."
else
    echo "$num is odd."
fi
```

---
