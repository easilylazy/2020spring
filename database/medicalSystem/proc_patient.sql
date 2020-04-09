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

/**************ע��******************/
--�ṩ�������������֤��������ҽԺ����ע�ᣨѡȡResident���е����ݣ�
--��ʼ���Ϊ100Ԫ

if exists(	SELECT * FROM sysobjects WHERE name ='proc_register')
	DROP PROC proc_register 
GO
CREATE PROC proc_register 
@name nvarchar(20),
@ID char(18),
@hospitalName nvarchar(40)
AS
SET nocount ON --�����ؼ���
BEGIN
	if exists(SELECT * FROM Resident WHERE ���֤=@ID and ����=@name)
	BEGIN
		if exists(SELECT * FROM Patient WHERE ID=@ID)
			print @ID+'already registered'
		else		
		BEGIN
			DECLARE @hospitalNumber int
			SELECT @hospitalNumber=ROW_NUMBER() over(order by ҽԺ���� desc)
			FROM Hospital
			INSERT INTO Patient(ID,hospitalName,����)
			VALUES(@ID,@hospitalName,convert(nvarchar(4),@hospitalNumber)+@ID)
		END
	END
END
GO

SELECT * FROM Patient
EXECUTE proc_register '�µ�','340321196507203290','�ӱ���ѧ����ҽԺ'
SELECT * FROM Patient




/**************��ֵ******************/

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
					WHERE ����=@cardNumber) 
	BEGIN
	DECLARE @departmentNumber int
	SELECT @departmentNumber=number FROM department
		WHERE hospitalName=@hospitalName  and
			name like '%��%' or name like '%ֵ%'
	--		SELECT @departmentNumber
	INSERT INTO Tally(hospitalName,����,���,departmentNumber) VALUES
		(@hospitalName,@cardNumber,@money,@departmentNumber)
	END
END
GO

SELECT * FROM TALLY
EXECUTE proc_deposit '�ӱ���ѧ����ҽԺ','5340321196507203290',100
SELECT * FROM TALLY

--	ҽԺ ����	���	ʱ��	��̨����ֵ��/���ң�

/**************����******************/
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
					WHERE ����=@cardNumber) 
	BEGIN
	DECLARE @departmentNumber int
	SELECT @departmentNumber=number FROM department
		WHERE hospitalName=@hospitalName  and
			name = @departmentName 
	--		SELECT @departmentNumber
	INSERT INTO Tally(hospitalName,����,���,departmentNumber) VALUES
		(@hospitalName,@cardNumber,@money,@departmentNumber)
	END
END
GO
SELECT * FROM TALLY
EXECUTE proc_charge '�ӱ���ѧ����ҽԺ','5340321196507203290',-30,'���ﲿ'
SELECT * FROM TALLY








/**************ע��******************/
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
	if exists(SELECT * FROM Resident WHERE ���֤=@ID and ����=@name)
	BEGIN
		DELETE FROM Patient
					WHERE ID =@ID and
						hospitalName=@hospitalName
	END				
END
GO

SELECT * FROM PATIENT
EXECUTE proc_logout'�µ�','340321196507203290','�ӱ���ѧ����ҽԺ'
SELECT * FROM PATIENT

