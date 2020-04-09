/*
Target Server Type    : SQL SERVER
Filename  :proc_findZipCode.sql
Author: Lee Zeeyee
Date: 2020-04-09 
*/

-- ----------------------------
-- procedure to find the corresponding zipcode of a hospital
-- ----------------------------
USE medicalSystem
GO

if exists (SELECT * FROM sysobjects WHERE name = 'findZipCode')
BEGIN
DROP PROC findZipCode
END
GO

CREATE PROC findZipCode
AS
BEGIN
	UPDATE Hospital
	SET ” ±‡= zip_code
	FROM Hospital left join hy_area
		on  –=name
END
GO
update  hospital
set ” ±‡=null
GO
SELECT * FROM Hospital
EXECUTE findZipCode;
GO
SELECT * FROM Hospital