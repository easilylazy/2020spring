/*
Target Server Type    : SQL SERVER
Filename  :doctorInfo.sql
Author: Lee Zeeyee
Date: 2020-04-11
*/

-- ----------------------------
-- information of doctors
-- ----------------------------


USE medicalSystem
GO

DELETE FROM Doctor
INSERT INTO Doctor (ID ,position,hospitalName,workDeptNumber)
SELECT idNumber,substring(unitCharacter,4,len(unitCharacter)),hospitalName,number
FROM Department ,Resident
WHERE
hospitalName='河北大学附属医院' and
convert(int,substring(idNumber,10,3))%11+1=number and
unitCharacter like '医院%'


UPDATE Doctor SET directDeptNumber=workDeptNumber
WHERE position='主任医师'

SELECT * FROM Doctor



CREATE TABLE #workday
(
code int IDENTITY PRIMARY KEY,
workday nvarchar(20) 
)
INSERT INTO #workday VALUES
	( '一、三、五'),
	( '二、四、六'),
	('三、日'),
	('四、日')
UPDATE Doctor SET workday=#workday.workday
FROM Doctor,#workday
WHERE
convert(int,substring(ID,10,3))%4+1=CODE
SELECT * FROM #workday
DROP TABLE #workday

SELECT * FROM Doctor