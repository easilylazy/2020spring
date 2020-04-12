/*
Target Server Type    : SQL SERVER
Filename  :main.sql
Author: Lee Zeeyee
Date: 2020-04-11
*/

-- ----------------------------
-- This is the main caller for each script
-- ----------------------------
SET NOCOUNT ON
GO
:On Error exit
PRINT '/**************CREATE DATABASE****************/'
:r C:\Users\cascara\Desktop\"Learning Materials"\"2020spring"\"2020spring"\database\medicalSystem\database_create.sql
PRINT '/**************CREATE TABLE****************/'
:r C:\Users\cascara\Desktop\"Learning Materials"\"2020spring"\"2020spring"\database\medicalSystem\table_create.sql
PRINT '/**************CREATE TABLE****************/'
:r C:\Users\cascara\Desktop\"Learning Materials"\"2020spring"\"2020spring"\database\medicalSystem\proc_findZipCode.sql
:r C:\Users\cascara\Desktop\"Learning Materials"\"2020spring"\"2020spring"\database\medicalSystem\proc_patient.sql
:r C:\Users\cascara\Desktop\"Learning Materials"\"2020spring"\"2020spring"\database\medicalSystem\trigger_defaultDepartment.sql
PRINT '/**************CREATE OVER****************/'
GO








--分别打开以下文件执行进行初始数据的插入
-- medicalSystem\areaInfo.sql
-- medicalSystem\hospitalInfo.sql
-- medicalSystem\residentInfo.sql
-- medicalSystem\doctorInfo.sql


--打开以下文件进行TEST 
-- medicalSystem\test.sql


/*如果出现无法删除数据库的情况，请取消注释，执行下列语句*/
--EXEC msdb.dbo.sp_delete_database_backuphistory @database_name = N'MEDICALSYSTEM' --填写 DATABASE名称，(msdb.dbo.sp_delete_database_backuphistory删除 DATABASE备份和还原历史记录信息)
--GO
--USE [master]
--GO
--ALTER DATABASE [MEDICALSYSTEM] SET  SINGLE_USER WITH ROLLBACK IMMEDIATE --设置库单用户模式，和设置立即回滚
--GO
--USE [master]
--GO
--DROP DATABASE [MEDICALSYSTEM]
--GO