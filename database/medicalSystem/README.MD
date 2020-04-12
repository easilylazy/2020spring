##  数据库课设项目    
### 背景
医院与就医    
### 数据库系统
SQL SERVER
### 记录文章：   
1. [数据库课设项目(上) 医院](https://blog.csdn.net/cascara/article/details/105404930)       
2. [数据库课设项目(下)  医护人员与患者](https://blog.csdn.net/cascara/article/details/105418042)
3. [数据库课设项目（续）批处理](https://blog.csdn.net/cascara/article/details/105472431)   
### 使用方式：     
可直接下载打包文件：
[medicalSystem.rar](https://github.com/easilylazy/2020spring/blob/master/database/medicalSystem/medicalSystem.rar)      
另可选择中文版，命名与记录博文中保持一致： 
[中文版medicalSystem.rar](https://github.com/easilylazy/2020spring/blob/master/database/medicalSystem/%E4%B8%AD%E6%96%87%E7%89%88medicalSystem.rar)     
       * 另：中文版由于中文字符问题无法通过SQLCMD进行批量运行，只能逐个文件运行
#### 运行顺序：
- 批处理创建数据库、表等： main.sql
- 分别打开以下文件并执行进行初始数据的导入
1. areaInfo.sql
2. hospitalInfo.sql
3. residentInfo.sql
4. doctorInfo.sql
- 最后可打开以下文件进行测试： test.sql

## 更新
附上修改后的 [RGPerson-master](https://github.com/gh0stkey/RGPerson)
 python代码，可生成随机身份数据的SQL语句。    
[这里是修改后的](https://github.com/easilylazy/2020spring/tree/master/database/medicalSystem/RGPerson-master)


