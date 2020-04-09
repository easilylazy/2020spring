/*
Target Server Type    : SQL SERVER
Filename  :table_create.sql
Author: Lee Zeeyee
Date: 2020-04-09 
*/

-- ----------------------------
-- department

-- ----------------------------


USE medicalSystem
GO

DECLARE @tableName varchar(20)

SET @tableName ='Department'

if exists (SELECT * FROM sysobjects WHERE name = @tableName )
BEGIN
print @tableName+' already exists'
DROP TABLE Department
END
--else
BEGIN
CREATE TABLE Department(
number int NOT NULL,
name nvarchar(20) NOT NULL,
hospitalName  nvarchar(40) NOT NULL

CONSTRAINT pk_department PRIMARY KEY( number,hospitalName),
CONSTRAINT fk_Hospital FOREIGN KEY(hospitalName)
		REFERENCES Hospital(ҽԺ����) ON DELETE CASCADE
)
END

SELECT * FROM Department



DECLARE @tableName varchar(20)
SET @tableName ='defaultDepartment'

if exists (SELECT * FROM sysobjects WHERE name = @tableName )
BEGIN
print @tableName+' already exists'
DROP TABLE defaultDepartment  --TO CHANGE
END
BEGIN
CREATE TABLE defaultDepartment(
number int NOT NULL IDENTITY(001,1),
name nvarchar(20) NOT NULL
CONSTRAINT pk_defaultDepartment PRIMARY KEY( number)
)
END

INSERT INTO defaultDepartment VALUES
	('���ﲿ'),
	('סԺ��'),
	('���ﲿ'),
	('ҩ��'),
	('�շ���'),
	('������'),
	('�����'),
	('������'),
	('B����'),
	('����¥'),
	('���ڿ���')
SELECT * FROM defaultDepartment

