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

/**************ҽԺ******************/
PRINT 'TEST  TABLE Hospital'
SELECT * FROM Hospital
WHERE hospitalName='����������ҽԺ'
/**************����******************/
PRINT 'TEST TABLE Department'
SELECT * FROM Department

/**************�洢�����ʱ�******************/
PRINT 'TEST PROC proc_findZipCode'
update  hospital
set code=null
GO
SELECT top(10)* FROM Hospital
EXECUTE proc_findZipCode;
GO
SELECT top(10)* FROM Hospital


/**************ҽ��******************/
--doctor (ID, name, gender, position, workday, tel, hospitalName, workDeptName
/***********************************/
SELECT * FROM Doctor 

/**************��ˮ******************/
--	ҽԺ cardNumber	amount	ʱ��	��̨����ֵ��/���ң�
/***********************************/
SELECT * FROM Tally



--SELECT idNumber,unitCharacter,hospitalName,number
--FROM Department ,Resident
--WHERE
--hospitalName='�ӱ���ѧ����ҽԺ' and
--convert(int,substring(idNumber,10,3))%11+1=number and
--unitCharacter like 'ҽԺ%'

--select substring('�ӱ���ѧ����ҽԺ',3,len('�ӱ���ѧ����ҽԺ'))



/*
BEGIN
DECLARE @workday1 nvarchar(20) 
DECLARE @workday2 nvarchar(20) 
DECLARE @workday3 nvarchar(20) 
DECLARE @workday4 nvarchar(20) 

SET @workday1 = 'һ��������'
SET @workday2 = '�����ġ���'
SET @workday3=  '������'
SET @workday4 = '�ġ���'
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






/**************ע��******************/
--�ṩ����name��idNumber��������ҽԺ����ע�ᣨѡȡResidentTABLE�е����ݣ�
--��ʼamountΪ100Ԫ
/***********************************/
PRINT 'TEST  PROC ע��'
SELECT * FROM Patient
EXECUTE proc_register '�µ�','340321196507203290','�ӱ���ѧ����ҽԺ'
SELECT * FROM Patient
GO
/**************��ֵ******************/
--�ṩ	ҽԺ cardNumber	amount	
--�˵��д����ֵ��¼��Ĭ�Ϲ�̨�ڳ�ֵ��
/***********************************/
PRINT 'TEST  PROC ��ֵ'
SELECT * FROM TALLY
EXECUTE proc_deposit '�ӱ���ѧ����ҽԺ','5340321196507203290',100
SELECT * FROM TALLY
GO
/**************����******************/
--�ṩ	ҽԺ cardNumber	amount	��̨����ֵ��/���ң�
--�˵��д������Ѽ�¼
/***********************************/
PRINT 'TEST  PROC ����'
SELECT * FROM TALLY
EXECUTE proc_charge '�ӱ���ѧ����ҽԺ','5340321196507203290',-30,'outpatient'
SELECT * FROM TALLY
GO
/**************ע��******************/
--�ṩ name idNumber�� ҽԺ  
--ɾ�������ע���¼
/***********************************/
PRINT 'TEST  PROC ע��'
SELECT * FROM PATIENT
EXECUTE proc_logout'�µ�','340321196507203290','�ӱ���ѧ����ҽԺ'
SELECT * FROM PATIENT
GO