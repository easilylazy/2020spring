/*
Target Server Type    : SQL SERVER
Filename  :proc_findZipCode.sql
Author: Lee Zeeyee
Date: 2020-04-09 
*/

-- ----------------------------
-- procedure to find the corresponding zipcode of a hospital
-- ----------------------------

PRINT 'START CREATE PROC  proc_findZipCode'

USE medicalSystem
GO

if exists (SELECT * FROM sysobjects WHERE name = 'proc_findZipCode')
BEGIN
PRINT 'DROP PROC proc_findZipCode'
DROP PROC proc_findZipCode
END
GO


PRINT 'CREATE PROC proc_findZipCode'
GO

CREATE PROC proc_findZipCode
AS
BEGIN
	UPDATE Hospital
	SET code= zip_code
	FROM Hospital left join hy_area
		on city=name
END
GO
