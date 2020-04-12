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
PRINT 'START CREATE TRIGGER trigger_defaultDepartment'

IF EXISTS (SELECT * FROM SYSOBJECTS WHERE name = 'trigger_defaultDepartment')
BEGIN
PRINT 'DROP TRIGGER trigger_defaultDepartment'
DROP TRIGGER trigger_defaultDepartment
END
GO

PRINT 'CREATE TRIGGER  trigger_defaultDepartment ON Hospital'
GO
CREATE TRIGGER  trigger_defaultDepartment ON Hospital
AFTER INSERT 
AS 
BEGIN
	INSERT INTO Department 
	 SELECT D.number,D.name,I.hospitalName FROM defaultDepartment D, inserted I
END
GO
