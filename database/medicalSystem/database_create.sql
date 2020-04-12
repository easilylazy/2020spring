--create database 
--select name from sys.databases
--Êý¾Ý¿âÃû³Æ
DECLARE @databaseName varchar(20);
DECLARE @createSql varchar(40);
set @databaseName = 'medicalSystem'
if exists (SELECT * FROM sys.databases 
			WHERE name = @databaseName)
			print 'database '+@databaseName+' already exists';
else
BEGIN
	set @createSql='CREATE DATABASE '+@databaseName
	exec(@createSql);
	print @createSql;
END




