/*
Target Server Type    : SQL SERVER
Filename  :table_create.sql
Author: Lee Zeeyee
Date: 2020-04-09 
*/

-- ----------------------------
--hy_area
--Hospital
-- defaultDepartment
	-- Department
--Resident
	--Doctor
	--Patient
--Tally
-- ----------------------------


USE medicalSystem
GO

DECLARE @tableName varchar(20)
PRINT 'START CREATE TABLE hy_area'
DROP TABLE IF EXISTS "hy_area";
CREATE TABLE "hy_area" (
  "id" int NOT NULL ,-- COMMENT 'ID',--AUTO_INCREMENT
  "pid" int DEFAULT NULL ,--COMMENT '父id',
  "shortname" varchar(100) DEFAULT NULL ,--COMMENT '简称',
  "name" varchar(100) DEFAULT NULL ,--COMMENT '名称',
  "merger_name" varchar(255) DEFAULT NULL ,--COMMENT '全称',
  "level" tinyint DEFAULT NULL ,--COMMENT '层级 0 1 2 省市区县',
  "pinyin" varchar(100) DEFAULT NULL ,--COMMENT '拼音',
  "code" varchar(100) DEFAULT NULL ,--COMMENT '长途区号',
  "zip_code" varchar(100) DEFAULT NULL ,--COMMENT 'code',
  "first" varchar(50) DEFAULT NULL ,--COMMENT '首字母',
  "lng" varchar(100) DEFAULT NULL ,--COMMENT '经度',
  "lat" varchar(100) DEFAULT NULL ,--COMMENT '纬度',
  PRIMARY KEY ("id")
) 
GO

PRINT 'START CREATE TABLE Hospital'
if exists (select * from sysobjects where name = 'Hospital')
BEGIN
	PRINT 'ALREADY EXISTS Hospital'
END
else
BEGIN
CREATE TABLE [dbo].[Hospital](
[hospitalName] nvarchar(40) NOT NULL UNIQUE,
[hospitalRank] nvarchar(4) NULL,
[hospitalType] nvarchar(4) NULL,
[province] nvarchar(10) NULL,
[city] nvarchar(10) NULL,
[county] nvarchar(20) NULL,
[bedNum] int NULL,
[hospitalAddress] nvarchar(60) NULL,
[code] varchar(100) NULL,
constraint pk_Hospital PRIMARY KEY
			NONCLUSTERED([hospitalName]),
--CONSTRAINT fk_Hospital FOREIGN KEY("code")
		--REFERENCES hy_area(zip_code)
)
END
GO

DECLARE @tableName varchar(20)
SET @tableName ='defaultDepartment'
PRINT 'START CREATE TABLE '+@tableName
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
	('outpatient'),
	('inpatient'),
	('emergency'),
	('pharmacy'),
	('cashier'),
	('laboratory'),
	('radiology'),
	('surgery'),
	('B ultrasonic'),
	('administration'),
	('logistic')
--SELECT * FROM defaultDepartment


SET @tableName ='Department'
PRINT 'START CREATE TABLE '+@tableName
if exists (SELECT * FROM sysobjects WHERE name = @tableName )
BEGIN
print @tableName+' already exists'
--DROP TABLE Department
END
else
BEGIN
CREATE TABLE Department(
number int NOT NULL,
name nvarchar(20) NOT NULL,
hospitalName  nvarchar(40) NOT NULL
CONSTRAINT pk_department PRIMARY KEY(number,hospitalName),
CONSTRAINT fk_Hospital FOREIGN KEY(hospitalName)
		REFERENCES Hospital(hospitalName) ON DELETE CASCADE
)
END

--SELECT * FROM Department
--DECLARE @tableName varchar(20)








--USE medicalSystem
--DECLARE @tableName varchar(20)

SET @tableName ='Resident'
PRINT 'START CREATE TABLE '+@tableName
if exists (SELECT * FROM sysobjects WHERE name = @tableName )
BEGIN
print @tableName+' already exists'
--DROP TABLE Resident  --TO CHANGE
END
else
BEGIN
CREATE TABLE Resident(
name nvarchar(20)  NULL,
age tinyint NULL CONSTRAINT cc_age CHECK( age>0 and age<120) ,
sex nvarchar(4)  NULL,
idNumber char(18) NOT NULL,
phoneNumber char(11)  NULL,
operater varchar(20)  NULL,
organizationCode varchar(40)  NULL,
creditCode varchar(20)  NULL,
unitCharacter nvarchar(40)  NULL,
CONSTRAINT pk_resident PRIMARY KEY( idNumber)
)
END



--SELECT * FROM Resident
--SELECT * FROM Resident
--	WHERE unitCharacter like '医院%'





--USE medicalSystem
PRINT 'START CREATE TABLE Doctor'
if exists (SELECT * FROM sysobjects WHERE name= 'Doctor')
	--DROP TABLE Doctor 
	print 'Doctor already exists'
else
CREATE TABLE Doctor 
(
ID char(18) NOT NULL ,
position nvarchar(20) NULL,
workday nvarchar(20) NULL,
hospitalName nvarchar(40) ,
workDeptNumber int,
directDeptNumber int NULL, 
	CONSTRAINT pk_doctor PRIMARY KEY(ID,workDeptNumber,hospitalName),
	CONSTRAINT fk_doctor_ID FOREIGN KEY(ID)
	REFERENCES Resident(idNumber) ON DELETE CASCADE,
	CONSTRAINT fk_doctor_workDept FOREIGN KEY(workDeptNumber,hospitalName)
	REFERENCES Department(number,hospitalName) ON DELETE CASCADE
)
GO

PRINT 'START CREATE TABLE Patient'
if exists (SELECT * FROM sysobjects WHERE name ='Patient')
BEGIN
	PRINT 'DROP TABLE Patient'
	DROP TABLE Patient
END


PRINT 'CREATE TABLE Patient'
CREATE TABLE Patient(
ID char(18) NOT NULL ,
hospitalName nvarchar(40) NOT NULL,
cardNumber nvarchar(40) NULL,
registerTime datetime default getdate(),
CONSTRAINT pk_patient PRIMARY KEY(ID,hospitalName),
CONSTRAINT fk_patient_ID FOREIGN KEY(ID)
	REFERENCES Resident(idNumber) ON DELETE CASCADE,
CONSTRAINT fk_patient_hospital FOREIGN KEY(hospitalName)
	REFERENCES Hospital(hospitalName) ON DELETE CASCADE
)

--SELECT * FROM Patient

PRINT 'START CREATE TABLE Tally'

if exists (SELECT * FROM sysobjects WHERE name ='Tally')
BEGIN
	PRINT 'DROP TABLE Tally'
	DROP TABLE Tally
END

PRINT 'CREATE TABLE Tally'
CREATE TABLE Tally(
hospitalName nvarchar(40) NOT NULL,
cardNumber nvarchar(40) NOT NULL,
amount money NULL,
time datetime default getdate(),
departmentNumber int NOT NULL,
CONSTRAINT pk_tally PRIMARY KEY(departmentNumber,hospitalName,cardNumber,time),
CONSTRAINT fk_tally_department FOREIGN KEY(departmentNumber,hospitalName)
	REFERENCES Department(number,hospitalName) ON DELETE CASCADE,
)

--SELECT * FROM Tally

