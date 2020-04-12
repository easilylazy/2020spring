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

/**************ע��******************/
--�ṩ����name��idNumber��������ҽԺ����ע�ᣨѡȡResidentTABLE�е����ݣ�
--��ʼamountΪ100Ԫ
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
SET nocount ON --�����ؼ���
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
--EXECUTE proc_register '�µ�','340321196507203290','�ӱ���ѧ����ҽԺ'
--SELECT * FROM Patient
PRINT 'CREATE OVER '




/**************��ֵ******************/
PRINT 'START CREATE PROC proc_deposit'

if exists(	SELECT * FROM sysobjects WHERE name ='proc_deposit')
	DROP PROC proc_deposit
GO
CREATE PROC proc_deposit
@hospitalName nvarchar(40),
@cardNumber nvarchar(40),
@money money
AS
SET nocount ON --�����ؼ���
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
--EXECUTE proc_deposit '�ӱ���ѧ����ҽԺ','5340321196507203290',100
--SELECT * FROM TALLY
PRINT 'CREATE OVER '


/**************����******************/
--	ҽԺ cardNumber	amount	ʱ��	��̨����ֵ��/���ң�
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
SET nocount ON --�����ؼ���
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
--EXECUTE proc_charge '�ӱ���ѧ����ҽԺ','5340321196507203290',-30,'���ﲿ'
--SELECT * FROM TALLY
PRINT 'CREATE OVER '








/**************ע��******************/
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
SET nocount ON --�����ؼ���
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
--EXECUTE proc_logout'�µ�','340321196507203290','�ӱ���ѧ����ҽԺ'
--SELECT * FROM PATIENT
PRINT 'CREATE OVER '

