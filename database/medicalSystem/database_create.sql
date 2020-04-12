/*
Target Server Type    : SQL SERVER
Filename  :database_create .sql
Author: Lee Zeeyee
Date: 2020-04-11
*/

-- ----------------------------
-- create database 
-- ----------------------------



--create database 
--select name from sys.databases
--¿ÉÐÞ¸Ä DATABASEÃû³Æ 'medicalSystem'


DECLARE @databaseName varchar(20);

set @databaseName = 'medicalSystem'
PRINT 'START CREATE DATABASE '+@databaseName

if exists (SELECT * FROM sys.databases 
			WHERE name = @databaseName)
BEGIN

	DECLARE @dropSql varchar(40);
	set @dropSql='DROP DATABASE '+@databaseName
	--exec(@dropSql);
	--print @dropSql;
END
--GO
			--print 'database '+@databaseName+' already exists';
else
BEGIN
--DECLARE @databaseName varchar(20);
	DECLARE @createSql varchar(40);
	set @createSql='CREATE DATABASE '+@databaseName
	exec(@createSql);
	print @createSql;
END
GO

USE medicalSystem 
GO

/*
DECLARE @databaseName varchar(20);
DECLARE @createSql varchar(40);
set @databaseName = 'medicalSystem'
PRINT 'START CREATE DATABASE'+@databaseName

if exists (SELECT * FROM sys.databases 
			WHERE name = @databaseName)
BEGIN
	set @createSql='DROP DATABASE '+@databaseName
	exec(@createSql);
	print @createSql;
END
			
			--print 'database '+@databaseName+' already exists';
--else
BEGIN
	set @createSql='CREATE DATABASE '+@databaseName
	exec(@createSql);
	print @createSql;
END




*/