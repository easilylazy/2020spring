/*
Target Server Type    : SQL SERVER
Filename  :proc_patient.sql
Author: Lee Zeeyee
Date: 2020-04-09 
*/

-- ----------------------------
-- procedures for patients to use
-- ----------------------------


USE medicalSystem
GO

/**************注册******************/
--提供个人姓名与身份证号与所在医院即可注册（选取Resident表中的数据）
--初始金额为100元

if exists(	SELECT * FROM sysobjects WHERE name ='proc_register')
	DROP PROC proc_register 
GO
CREATE PROC proc_register 
@name nvarchar(20),
@ID char(18),
@hospitalName nvarchar(40)
AS
SET nocount ON --不返回计数
BEGIN
	if exists(SELECT * FROM Resident WHERE 身份证=@ID and 姓名=@name)
	BEGIN
		if exists(SELECT * FROM Patient WHERE ID=@ID)
			print @ID+'already registered'
		else		
		BEGIN
			DECLARE @hospitalNumber int
			SELECT @hospitalNumber=ROW_NUMBER() over(order by 医院名称 desc)
			FROM Hospital
			INSERT INTO Patient(ID,hospitalName,卡号)
			VALUES(@ID,@hospitalName,convert(nvarchar(4),@hospitalNumber)+@ID)
		END
	END
END
GO

SELECT * FROM Patient
EXECUTE proc_register '郝掂','340321196507203290','河北大学附属医院'
SELECT * FROM Patient




/**************充值******************/

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
					WHERE 卡号=@cardNumber) 
	BEGIN
	DECLARE @departmentNumber int
	SELECT @departmentNumber=number FROM department
		WHERE hospitalName=@hospitalName  and
			name like '%费%' or name like '%值%'
	--		SELECT @departmentNumber
	INSERT INTO Tally(hospitalName,卡号,金额,departmentNumber) VALUES
		(@hospitalName,@cardNumber,@money,@departmentNumber)
	END
END
GO

SELECT * FROM TALLY
EXECUTE proc_deposit '河北大学附属医院','5340321196507203290',100
SELECT * FROM TALLY

--	医院 卡号	金额	时间	柜台（充值处/科室）

/**************消费******************/
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
					WHERE 卡号=@cardNumber) 
	BEGIN
	DECLARE @departmentNumber int
	SELECT @departmentNumber=number FROM department
		WHERE hospitalName=@hospitalName  and
			name = @departmentName 
	--		SELECT @departmentNumber
	INSERT INTO Tally(hospitalName,卡号,金额,departmentNumber) VALUES
		(@hospitalName,@cardNumber,@money,@departmentNumber)
	END
END
GO
SELECT * FROM TALLY
EXECUTE proc_charge '河北大学附属医院','5340321196507203290',-30,'门诊部'
SELECT * FROM TALLY








/**************注销******************/
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
	if exists(SELECT * FROM Resident WHERE 身份证=@ID and 姓名=@name)
	BEGIN
		DELETE FROM Patient
					WHERE ID =@ID and
						hospitalName=@hospitalName
	END				
END
GO

SELECT * FROM PATIENT
EXECUTE proc_logout'郝掂','340321196507203290','河北大学附属医院'
SELECT * FROM PATIENT

