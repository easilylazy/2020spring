
/*
Target Server Type    : SQL SERVER
Filename  :trigger_defaultDepartment.sql
Author: Lee Zeeyee
Date: 2020-04-09 
*/

-- ----------------------------
-- Trigger to add default department when insert a new hospital
-- ----------------------------







USE medicalSystem
GO

--SELECT * FROM hy_area
--WHERE shortname like '����%'or name like '����%' or merger_name like '%����%'

drop PROC findZipCode


if exists (SELECT * FROM sysobjects WHERE name = 'findZipCode')
DROP PROC findZipCode
CREATE PROC findZipCode
AS
BEGIN
	UPDATE Hospital
	SET code= zip_code
	FROM Hospital left join hy_area
		on ��=name
END
GO
update  hospital
set code=null
GO
SELECT * FROM Hospital
EXECUTE findZipCode;
GO
SELECT * FROM Hospital



select DISTINCT hospitalName, ʡ, ��, ��, shortname, name, zip_code  
FROM Hospital left join hy_area
on ��=name


select hospitalName, ʡ, ��, ��, shortname, name, zip_code  
FROM Hospital left join hy_area
on ��=name



/*
--ɸѡ��û��ƥ���

(select hospitalName, ʡ, ��, ��, shortname, name, zip_code  into #temp
FROM Hospital left join hy_area
on ��=name)
except
(select hospitalName, ʡ, ��, ��, shortname, name, zip_code
FROM Hospital inner join hy_area
on ��=name)
SELECT * FROM #TEMP
drop table #temp
SELECT * FROM Hospital
--SELECT * FROM #TEMP
--ƥ����һ��
GO

DECLARE cursor_temp scroll CURSOR
FOR
select ʡ ,�� ,�� from #temp
--Declare two variables���� 
DECLARE @mAllFee money	--�ܷ������� 
DECLARE @iFeeID��int		--��������

DECLARE @ʡ nvarchar(10)--ʡ nvarchar(10) NULL,
DECLARE @city nvarchar(10)--�� nvarchar(10) NULL,
DECLARE @county nvarchar(20)--�� nvarchar(20) NULL,
DECLARE @PROCESSCITY nvarchar(10) 
DECLARE @RESULT varchar(100) --code
--initialize the two variables������ 
SET @mAllFee=0���� 
SET @iFeeID=0 
--open the cursor���� 
OPEN cursor_temp��
FETCH FIRST FROM cursor_temp INTO @ʡ,@city,@county
WHILE(@@FETCH_STATUS=0)
BEGIN


SET @PROCESSCITY ='%'+SUBSTRING(@city,0,3)+'%'
print @PROCESSCITY


SELECT @RESULT=zip_code FROM hy_area
--SELECT DISTINCT* INTO #result FROM hy_area
WHERE shortname like @PROCESSCITY-- or name like @PROCESSCITY or merger_name like @PROCESSCITY


UPDATE #temp  SET zip_code =@RESULT

UPDATE Hospital  SET code =@RESULT

FETCH NEXT FROM cursor_temp INTO @ʡ,@city,@county
END

--close the cursor�������� 
CLOSE cursor_temp
--release the cursor���� 
DEALLOCATE cursor_temp 
--SELECT * FROM #TEMP
--ƥ����һ��
GO
drop table #temp


--UPDATE #temp  
--SET #temp.shortname=#result.shortname,name=#result.name,zip_code #result.zip_code

--SELECT SUBSTRING('SFLJGW',0,2)+'WF' 
--IF SUBSTRING('SFLJGW',0,2)+'WF'  LIKE SUBSTRING('SFLJGW',0,2)+'W%'
--PRINT 'YEAH'

SELECT * FROM Hospital

*/