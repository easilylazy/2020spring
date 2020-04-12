/*
Target Server Type    : SQL SERVER
Filename  :proc_patient.sql
Author: Lee Zeeyee
Date: 2020-04-09 
*/

-- ----------------------------
-- procedures for patients to use
-- ----------------------------

PRINT 'START CREATE PROC patient'

USE medicalSystem
GO

/**************注册******************/
--提供个人name与idNumber号与所在医院即可注册（选取ResidentTABLE中的数据）
--初始amount为100元
/***********************************/
PRINT 'START CREATE PROC proc_register'
if exists(	SELECT * FROM sysobjects WHERE name ='proc_register')
BEGIN
	PRINT 'DROP PROC proc_register'
	DROP PROC proc_register 
END
GO

PRINT 'CREATE PROC proc_register '
GO

CREATE PROC proc_register 
@name nvarchar(20),
@ID char(18),
@hospitalName nvarchar(40)
AS
SET nocount ON --不返回计数
BEGIN
	if exists(SELECT * FROM Resident WHERE idNumber=@ID and name=@name)
	BEGIN
		if exists(SELECT * FROM Patient WHERE ID=@ID)
			print @ID+'already registered'
		else		
		BEGIN
			DECLARE @hospitalNumber int
			SELECT @hospitalNumber=ROW_NUMBER() over(order by hospitalName desc)
			FROM Hospital
			INSERT INTO Patient(ID,hospitalName,cardNumber)
			VALUES(@ID,@hospitalName,convert(nvarchar(4),@hospitalNumber)+@ID)
		END
	END
END
GO

--SELECT * FROM Patient
--EXECUTE proc_register '郝掂','340321196507203290','河北大学附属医院'
--SELECT * FROM Patient
PRINT 'CREATE OVER '




/**************充值******************/
PRINT 'START CREATE PROC proc_deposit'

if exists(	SELECT * FROM sysobjects WHERE name ='proc_deposit')
	DROP PROC proc_deposit
GO
CREATE PROC proc_deposit
@hospitalName nvarchar(40),
@cardNumber nvarchar(40),
@money money
AS
SET nocount ON --不返回计数
BEGIN
	if exists (SELECT * FROM Patient 
					WHERE cardNumber=@cardNumber) 
	BEGIN
	DECLARE @departmentNumber int
	SELECT @departmentNumber=number FROM department
		WHERE hospitalName=@hospitalName  and
			name like '%cash%' or name like '%charge%'
	--		SELECT @departmentNumber
	INSERT INTO Tally(hospitalName,cardNumber,amount,departmentNumber) VALUES
		(@hospitalName,@cardNumber,@money,@departmentNumber)
	END
END
GO

--SELECT * FROM TALLY
--EXECUTE proc_deposit '河北大学附属医院','5340321196507203290',100
--SELECT * FROM TALLY
PRINT 'CREATE OVER '


/**************消费******************/
--	医院 cardNumber	amount	时间	柜台（充值处/科室）
/***********************************/
PRINT 'START CREATE PROC proc_charge'

if exists(	SELECT * FROM sysobjects WHERE name ='proc_charge')
	DROP PROC proc_charge
GO
CREATE PROC proc_charge
@hospitalName nvarchar(40),
@cardNumber nvarchar(40),
@money money,
@departmentName nvarchar(20)
AS
SET nocount ON --不返回计数
BEGIN
	if exists (SELECT * FROM Patient 
					WHERE cardNumber=@cardNumber) 
	BEGIN
	DECLARE @departmentNumber int
	SELECT @departmentNumber=number FROM department
		WHERE hospitalName=@hospitalName  and
			name = @departmentName 
	--		SELECT @departmentNumber
	INSERT INTO Tally(hospitalName,cardNumber,amount,departmentNumber) VALUES
		(@hospitalName,@cardNumber,@money,@departmentNumber)
	END
END
GO
--SELECT * FROM TALLY
--EXECUTE proc_charge '河北大学附属医院','5340321196507203290',-30,'门诊部'
--SELECT * FROM TALLY
PRINT 'CREATE OVER '








/**************注销******************/
--JOJ
/***********************************/
PRINT 'START CREATE PROC proc_logout'
if exists(	SELECT * FROM sysobjects WHERE name ='proc_logout')
	DROP PROC proc_logout
GO
CREATE PROC proc_logout
@name nvarchar(20),
@ID char(18),
@hospitalName nvarchar(40)
AS
SET nocount ON --不返回计数
BEGIN
	if exists(SELECT * FROM Resident WHERE idNumber=@ID and name=@name)
	BEGIN
		DELETE FROM Patient
					WHERE ID =@ID and
						hospitalName=@hospitalName
	END				
END
GO

--SELECT * FROM PATIENT
--EXECUTE proc_logout'郝掂','340321196507203290','河北大学附属医院'
--SELECT * FROM PATIENT
PRINT 'CREATE OVER '

