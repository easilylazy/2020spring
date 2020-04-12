/*
Target Server Type    : SQL SERVER
Filename  :test.sql
Author: Lee Zeeyee
Date: 2020-04-09 
*/

-- ----------------------------
-- test the correctness
-- ----------------------------


USE medicalSystem
GO

/**************医院******************/
PRINT 'TEST  TABLE Hospital'
SELECT * FROM Hospital
WHERE hospitalName='沧州市人民医院'
/**************科室******************/
PRINT 'TEST TABLE Department'
SELECT * FROM Department

/**************存储过程邮编******************/
PRINT 'TEST PROC proc_findZipCode'
update  hospital
set code=null
GO
SELECT top(10)* FROM Hospital
EXECUTE proc_findZipCode;
GO
SELECT top(10)* FROM Hospital


/**************医生******************/
--doctor (ID, name, gender, position, workday, tel, hospitalName, workDeptName
/***********************************/
SELECT * FROM Doctor 

/**************流水******************/
--	医院 cardNumber	amount	时间	柜台（充值处/科室）
/***********************************/
SELECT * FROM Tally



--SELECT idNumber,unitCharacter,hospitalName,number
--FROM Department ,Resident
--WHERE
--hospitalName='河北大学附属医院' and
--convert(int,substring(idNumber,10,3))%11+1=number and
--unitCharacter like '医院%'

--select substring('河北大学附属医院',3,len('河北大学附属医院'))



/*
BEGIN
DECLARE @workday1 nvarchar(20) 
DECLARE @workday2 nvarchar(20) 
DECLARE @workday3 nvarchar(20) 
DECLARE @workday4 nvarchar(20) 

SET @workday1 = '一、三、五'
SET @workday2 = '二、四、六'
SET @workday3=  '三、日'
SET @workday4 = '四、日'
--SET @workday
--SELECT @workday1

DECLARE @sql nvarchar(40) 
SET @sql ='SELECT @workday3'--+'3'
exec sp_executesql @sql
END

convert(nvarchar(29),convert(int,round(rand()*100,0))%4+1))
*/
--select convert(int,round(rand()*100,0))%11+1

--USE medicalSystem
--SELECT * from department






/**************注册******************/
--提供个人name与idNumber号与所在医院即可注册（选取ResidentTABLE中的数据）
--初始amount为100元
/***********************************/
PRINT 'TEST  PROC 注册'
SELECT * FROM Patient
EXECUTE proc_register '郝掂','340321196507203290','河北大学附属医院'
SELECT * FROM Patient
GO
/**************充值******************/
--提供	医院 cardNumber	amount	
--账单中储存充值记录，默认柜台在充值部
/***********************************/
PRINT 'TEST  PROC 充值'
SELECT * FROM TALLY
EXECUTE proc_deposit '河北大学附属医院','5340321196507203290',100
SELECT * FROM TALLY
GO
/**************消费******************/
--提供	医院 cardNumber	amount	柜台（充值处/科室）
--账单中储存消费记录
/***********************************/
PRINT 'TEST  PROC 消费'
SELECT * FROM TALLY
EXECUTE proc_charge '河北大学附属医院','5340321196507203290',-30,'outpatient'
SELECT * FROM TALLY
GO
/**************注销******************/
--提供 name idNumber号 医院  
--删除该身份注册记录
/***********************************/
PRINT 'TEST  PROC 注销'
SELECT * FROM PATIENT
EXECUTE proc_logout'郝掂','340321196507203290','河北大学附属医院'
SELECT * FROM PATIENT
GO