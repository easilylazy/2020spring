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








--�ֱ�������ļ�ִ�н��г�ʼ���ݵĲ���
-- medicalSystem\areaInfo.sql
-- medicalSystem\hospitalInfo.sql
-- medicalSystem\residentInfo.sql
-- medicalSystem\doctorInfo.sql


--�������ļ�����TEST 
-- medicalSystem\test.sql


/*��������޷�ɾ�����ݿ���������ȡ��ע�ͣ�ִ���������*/
--EXEC msdb.dbo.sp_delete_database_backuphistory @database_name = N'MEDICALSYSTEM' --��д DATABASE���ƣ�(msdb.dbo.sp_delete_database_backuphistoryɾ�� DATABASE���ݺͻ�ԭ��ʷ��¼��Ϣ)
--GO
--USE [master]
--GO
--ALTER DATABASE [MEDICALSYSTEM] SET  SINGLE_USER WITH ROLLBACK IMMEDIATE --���ÿⵥ�û�ģʽ�������������ع�
--GO
--USE [master]
--GO
--DROP DATABASE [MEDICALSYSTEM]
--GO